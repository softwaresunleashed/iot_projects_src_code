#ifndef ALLOCATORS_H
#define ALLOCATORS_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>


extern void* tools_malloc(uint32_t size);
extern void* tools_realloc(void *ptr,uint32_t size);
extern void tools_free(void *ptr);
extern char* tools_strdup(const char* str);

#define _malloc(x)	tools_malloc(x)
#define _realloc(x,y)   tools_realloc(x,y);
#define _free(x)	\
do \
{ \
	if (x) \
	{ \
		tools_free(x); \
		x = 0; \
	} \
}while(0)
#define _strdup(x)      tools_strdup(x)

#define NEW(x)	new x;
#define DELETE(x)	\
do \
{ \
	if (x) \
	{ \
		delete x; \
		x = 0; \
	} \
}while(0)


//#define malloc(x) DONT_USE_MALLOC
//#define free(x)   DONT_USE_FREE
//#define strdup(x) DONT_USE_STRDUP

#endif // ndef ALLOCATORS_H
