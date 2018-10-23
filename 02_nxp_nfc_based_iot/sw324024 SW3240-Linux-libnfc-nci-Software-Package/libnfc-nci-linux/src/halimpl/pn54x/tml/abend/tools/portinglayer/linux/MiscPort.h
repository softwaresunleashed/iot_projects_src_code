
#ifndef MISCPORT_H
#define MISCPORT_H

#include "core/Types.h"

void PortingLayer_usleep(uint32_t delay);

uint32_t PortingLayer_getTicks();

void PortingLayer_exit();

int32_t PortingLayer_getIntFromConfig(const char* sectionName,const char* key, int32_t defvalue,const char* filename);

#endif
