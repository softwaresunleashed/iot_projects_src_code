
#include "MiscPort.h"

#define VERBOSE_TAG "MiscPort"
#include "core/Verbose.h"

#include <unistd.h>
#include <stdlib.h>


void PortingLayer_usleep(uint32_t delay)
{
	usleep(delay);
}

uint32_t PortingLayer_getTicks()
{
	WARN("%s not implemented\n",__FUNCTION__);
	return 0;
}

void PortingLayer_exit()
{
	exit(0);
}

int32_t PortingLayer_getIntFromConfig(const char * sectionName, const char * key, int32_t defvalue, const char * filename)
{
	WARN("%s not implemented\n",__FUNCTION__);
	return 0;
}