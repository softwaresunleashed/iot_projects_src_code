#include "OSVerbose.h"

#include <stdio.h>
#include <time.h>
#include <string.h>

#include <windows.h>

#define WHITE  FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
#define GRAY   FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define CYAN   FOREGROUND_GREEN | FOREGROUND_INTENSITY | FOREGROUND_BLUE
#define GREEN  FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define YELLOW FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
#define RED    FOREGROUND_RED | FOREGROUND_INTENSITY

#include "core/Locker.h"

static Locker m_outLock;

void SetColor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon,color);
}

void OSVerbose_getDate(char *buff)
{
	char* timeStr = buff;
	struct tm *ptr;
	time_t tm;
	tm = time(NULL);
	ptr = localtime(&tm);
	sprintf(timeStr, "%.2i:%.2i:%.2i",ptr->tm_hour,ptr->tm_min,ptr->tm_sec);
}

void OSVerbose_LOG(const char * tag, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);

	m_outLock.lock();
	
	SetColor(GRAY);
	printf("[");
	SetColor(CYAN);
	printf("%s",timeStr);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(">");
	SetColor(GRAY);
	printf("[");
	SetColor(GREEN);
	printf("%s",tag);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(" : ");
	vprintf(str, ap);
	SetColor(GRAY);
	
	if (!strstr(str,"\n"))
	{
		printf("\n");
	}
	
	m_outLock.unlock();

}

void OSVerbose_WARN(const char * tag, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	
	m_outLock.lock();
	
	SetColor(GRAY);
	printf("[");
	SetColor(CYAN);
	printf("%s",timeStr);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(">");
	SetColor(GRAY);
	printf("[");
	SetColor(YELLOW);
	printf("%s",tag);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(" : ");
	vprintf(str, ap);
	SetColor(GRAY);
	
	if (!strstr(str,"\n"))
	{
		printf("\n");
	}
	
	m_outLock.unlock();

}

void OSVerbose_ERROR(const char * tag,const char* file,int line, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	
	m_outLock.lock();
	
	SetColor(GRAY);
	printf("[");
	SetColor(CYAN);
	printf("%s",timeStr);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(">");
	SetColor(GRAY);
	printf("[");
	SetColor(RED);
	printf("%s",tag);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(" : ");
	SetColor(RED);
	printf("ERROR");
	SetColor(WHITE);
	printf(" : ");
	SetColor(YELLOW);
	printf("%s",file);
	SetColor(WHITE);
	printf(" line ");
	SetColor(YELLOW);
	printf("%i",line);
	SetColor(WHITE);
	printf(" : ");
	vprintf(str, ap);
	SetColor(GRAY);
	
	if (!strstr(str,"\n"))
	{
		printf("\n");
	}
	
	m_outLock.unlock();

}

void OSVerbose_FATAL(const char * tag,const char* file,int line, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	
	m_outLock.lock();
	
	SetColor(GRAY);
	printf("[");
	SetColor(CYAN);
	printf("%s",timeStr);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(">");
	SetColor(GRAY);
	printf("[");
	SetColor(RED);
	printf("%s",tag);
	SetColor(GRAY);
	printf("]");
	SetColor(WHITE);
	printf(" : ");
	SetColor(RED);
	printf("FATAL");
	SetColor(WHITE);
	printf(" : ");
	SetColor(YELLOW);
	printf("%s",file);
	SetColor(WHITE);
	printf(" line ");
	SetColor(YELLOW);
	printf("%i",line);
	SetColor(WHITE);
	printf(" : ");
	vprintf(str, ap);
	SetColor(GRAY);
	
	if (!strstr(str,"\n"))
	{
		printf("\n");
	}
	
	m_outLock.unlock();

}

uint32_t OSVerbose_GETTICKS()
{
	return GetTickCount();
}

void OSVerbose_PERFS(const char * tag,const char* file,int line, const char * str,va_list ap)
{
	char timeStr[100];
	OSVerbose_getDate(timeStr);
	printf("[%s]>[%s] : PERFS : %s line %i : ",timeStr,tag,file,line);
	vprintf(str, ap);

}

