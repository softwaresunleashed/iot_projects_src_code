

#ifndef AllocatorsPF_H
#define AllocatorsPF_H

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

void* tools_malloc(uint32_t size);
void *tools_realloc(void *ptr,uint32_t size);
void tools_free(void *ptr);
char* tools_strdup(const char* str);

#endif // ndef AllocatorsPF_H


