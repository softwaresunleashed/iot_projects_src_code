

#ifndef OSVerbose_H
#define OSVerbose_H

#include <stdarg.h>

#include "core/Types.h"

void OSVerbose_LOG(const char* tag,const char* str,va_list ap);
void OSVerbose_WARN(const char* tag,const char* str,va_list ap);
void OSVerbose_ERROR(const char* tag,const char* file,int line,const char* str,va_list ap);
void OSVerbose_FATAL(const char* tag,const char* file,int line,const char* str,va_list ap);

uint32_t OSVerbose_GETTICKS();
void OSVerbose_PERFS(const char* tag,const char* file,int line,const char* str,va_list ap);

#endif // ndef OSVerbose_H


