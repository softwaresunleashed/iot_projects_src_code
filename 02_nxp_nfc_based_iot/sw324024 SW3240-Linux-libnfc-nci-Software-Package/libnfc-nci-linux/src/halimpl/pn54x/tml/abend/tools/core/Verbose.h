

#ifndef VERBOSE_H
#define VERBOSE_H

#ifndef VERBOSE_TAG
#define VERBOSE_TAG "UNDEFINED VERBOSE_TAG"
#endif // ndef VERBOSE_TAG

#include "Types.h"

struct sToolsInstrument
{
	uint32_t begin;
	uint32_t end;
};

#define INIT_INSTRUMENT(x) sToolsInstrument x = {0,0}
#define INSTRUMENT_START(x) x.begin = Tools_GETTICKS()

#define INSTRUMENT_RESULT(x) \
do \
{ \
	x.end = Tools_GETTICKS(); \
	PERFS("%i ms or %f fps \n",x.end-x.begin,1.0f/(((float)(x.end-x.begin))/1000.0f)); \
}while(0)

#define VERBOSE_VAR_INT(logMode,x) logMode("%s %i\n",#x,x);
#define VERBOSE_VAR_HEX(logMode,x) logMode("%s 0x%X\n",#x,x);
#define VERBOSE_VAR_STR(logMode,x) logMode("%s %s\n",#x,x);

#define LOG(FMT,...) Tools_LOG(VERBOSE_TAG,FMT, ##__VA_ARGS__)
#define WARN(FMT,...) Tools_WARN(VERBOSE_TAG,FMT, ##__VA_ARGS__)
#define ERROR(FMT,...) Tools_ERROR(VERBOSE_TAG,__FILE__,__LINE__,FMT, ##__VA_ARGS__)
#define FATAL(FMT,...) Tools_FATAL(VERBOSE_TAG,__FILE__,__LINE__,FMT, ##__VA_ARGS__)
#define PERFS(FMT,...) Tools_PERFS(VERBOSE_TAG,__FILE__,__LINE__,FMT, ##__VA_ARGS__)
#define HEXDUMP(buf,size) Tools_HEXDUMP(VERBOSE_TAG,buf,size);

void Tools_LOG(const char* tag,const char* str,...);
void Tools_WARN(const char* tag,const char* str,...);
void Tools_ERROR(const char* tag,const char* file,const int line,const char* str,...);
void Tools_FATAL(const char* tag,const char* file,const int line,const char* str,...);

uint32_t Tools_GETTICKS();
void Tools_PERFS(const char* tag,const char* file,const int line,const char* str,...);


void Tools_HEXDUMP(const char* tag,const void* buffer,uint32_t size);

#endif // ndef VERBOSE_H
