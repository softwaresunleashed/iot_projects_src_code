

#include "Verbose.h"

#include "OSVerbose.h"



#include <stdarg.h>
#include <stdio.h>

void Tools_LOG(const char * tag, const char * str,...)
{
	va_list varg;
	va_start(varg, str);
	OSVerbose_LOG(tag,str, varg);
	va_end(varg);
}

void Tools_WARN(const char * tag, const char * str,...)
{
	va_list varg;
	va_start(varg, str);
	OSVerbose_WARN(tag,str, varg);
	va_end(varg);
}

void Tools_ERROR(const char * tag,const char* file,int line, const char * str,...)
{
	va_list varg;
	va_start(varg, str);
	OSVerbose_ERROR(tag,file,line,str, varg);
	va_end(varg);
}

void Tools_FATAL(const char * tag,const char* file,int line, const char * str,...)
{
	va_list varg;
	va_start(varg, str);
	OSVerbose_FATAL(tag,file,line,str, varg);
	va_end(varg);
}

uint32_t Tools_GETTICKS()
{
	return OSVerbose_GETTICKS();
}

void Tools_PERFS(const char* tag,const char* file,const int line,const char* str,...)
{
	va_list varg;
	va_start(varg, str);
	OSVerbose_PERFS(tag,file,line,str, varg);
	va_end(varg);
}

void Tools_HEXDUMP(const char * tag,const void * buffer,uint32_t size)
{
	char      tmpBuff[128];
	uint8_t  *dataBuffer=(uint8_t*)buffer;
	uint32_t  i         = 0;
	uint32_t  buffIter  = 0;
	uint32_t  tmpI      = 0;
	while (i < size)
	{
		buffIter = 0;
		tmpI     = i;
		while ((tmpI<size)&& (buffIter<24))
		{
			sprintf(tmpBuff+buffIter,"%.2X ",dataBuffer[tmpI]);
			buffIter+=3;
			tmpI++;
		}

		tmpI = i;
		while ((tmpI<size)&& (buffIter<32))
		{
			if (dataBuffer[tmpI] == '%')
			{
				tmpBuff[buffIter++] = '%';
				tmpBuff[buffIter++] = '%';
			}else if (dataBuffer[tmpI]>=32)
			{
				tmpBuff[buffIter++]=dataBuffer[tmpI];
			}else
			{
				tmpBuff[buffIter++] = '.';
			}
			tmpI++;
		}
		i = tmpI;
		tmpBuff[buffIter++] = '\n';
		tmpBuff[buffIter++] = 0;

		Tools_LOG(tag,tmpBuff);
	}
}
