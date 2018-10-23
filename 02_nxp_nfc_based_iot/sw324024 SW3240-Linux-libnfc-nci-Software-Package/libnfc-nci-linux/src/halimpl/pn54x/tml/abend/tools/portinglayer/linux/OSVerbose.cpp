


#include "OSVerbose.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>
#include <execinfo.h>

#define LOGENABLED

void demangleStack(char** symbollist,int addrlen);
void dumpCallStack();

void OSVerbose_getDate(char *buff)
{
	char* timeStr = buff;
	struct tm *ptr;
	time_t tm;
	struct timeval t;

	gettimeofday(&t, NULL);
	tm = time(NULL);
	ptr = localtime(&tm);
	sprintf(timeStr, "%.2i:%.2i:%.2i:%.3i",ptr->tm_hour,ptr->tm_min,ptr->tm_sec,((t.tv_usec) * 1000));
}


static struct sigaction old_sa[NSIG];

void linux_sigaction(int signal, siginfo_t */*info*/, void */*reserved*/)
{
	printf("ErrorCatcher : Signal caugth : %i (%s)\n",signal,strsignal(signal));
	dumpCallStack();
	old_sa[signal].sa_handler(signal);
}

static void internalRegisterSigHandler()
{
	struct sigaction handler;
	memset(&handler, 0, sizeof(struct sigaction));
	handler.sa_sigaction = linux_sigaction;
	handler.sa_flags = SA_RESETHAND;
#define CATCHSIG(X) sigaction(X, &handler, &old_sa[X])
	CATCHSIG(SIGILL);
	CATCHSIG(SIGABRT);
	CATCHSIG(SIGBUS);
	CATCHSIG(SIGFPE);
	CATCHSIG(SIGSEGV);
	CATCHSIG(SIGPIPE);
// 	printf("ErrorCatcher : Signal catcher registered\n");
}

class Registrator
{
	public:
		Registrator(){internalRegisterSigHandler();}
};

#define TOOLS_TAG "Native"

Registrator singletonRegister;

void OSVerbose_LOG(const char * tag, const char * str,va_list ap)
{
#ifdef LOGENABLED
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	char tmp[512];
	sprintf(tmp,"[%s]>[%s] : %s",timeStr,tag,str);

	vprintf(tmp,ap);
#endif // def LOGENABLED
}

void OSVerbose_WARN(const char * tag, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	char tmp[512];
	sprintf(tmp,"[%s]>[%s] : %s",timeStr,tag,str);
	vprintf(tmp,ap);
}

void OSVerbose_ERROR(const char * tag,const char* file,int line, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	char tmp[512];
	sprintf(tmp,"[%s]>[%s] : ERROR : %s line %i :  %s",timeStr,tag,file,line,str);

	vprintf(tmp,ap);
}

void OSVerbose_FATAL(const char * tag,const char* file,int line, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	char tmp[512];
	sprintf(tmp,"[%s]>[%s] : FATAL : %s line %i :  %s",timeStr,tag,file,line,str);

	vprintf(tmp,ap);
}

uint32_t OSVerbose_GETTICKS()
{
	struct timeval sNow;
	gettimeofday(&sNow, 0);
	return sNow.tv_sec*1000 + sNow.tv_usec/1000;
}

void OSVerbose_PERFS(const char * tag,const char* /*file*/,int /*line*/, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	char tmp[512];
	sprintf(tmp,"[%s]>[%s] : %s",timeStr,tag,str);

	vprintf(tmp,ap);
}

void dumpCallStack()
{
	void *array[10];
	size_t size;
	char **strings;

	size = backtrace (array, 10);
	strings = backtrace_symbols (array, size);
	demangleStack(strings,size);
}

// *****************************************************
#include <cxxabi.h>
void demangleStack(char** symbollist,int addrlen)
{
	uint32_t level = 0;
	// allocate string which will be filled with the demangled function name
	size_t funcnamesize = 256;
	char* funcname = (char*)malloc(funcnamesize);

	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (int i = 1; i < addrlen; i++)
	{
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		
		for (char *p = symbollist[i]; *p; ++p)
		{
			if (*p == '(')
				begin_name = p;
			else if (*p == '+')
				begin_offset = p;
			else if (*p == ')' && begin_offset)
			{
				end_offset = p;
				break;
			}
		}

		if (begin_name && begin_offset && end_offset
				  && begin_name < begin_offset)
		{
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';

			// mangled name is now in [begin_name, begin_offset) and caller
			// offset in [begin_offset, end_offset). now apply
			// __cxa_demangle():

			int status;
			char* ret = abi::__cxa_demangle(begin_name,
					funcname, &funcnamesize, &status);
			if (status == 0)
			{
				funcname = ret; // use possibly realloc()-ed string
				printf("[%i] %s : %s+%s\n", level,symbollist[i], funcname, begin_offset);
			}
			else
			{
				// demangling failed. Output function name as a C function with
				// no arguments.
				printf("[%i] %s : %s()+%s\n", level, symbollist[i], begin_name, begin_offset);
			}
		}
		else
		{
			// couldn't parse the line? print the whole line.
			printf("[%i] %s\n", level,symbollist[i]);
		}
		level++;
	}

	free(funcname);
}


