
#include "MiscPort.h"


#include <windows.h>


void PortingLayer_usleep(uint32_t delay)
{
	//FIXME !!!!
	Sleep(delay/1000);
}

uint32_t PortingLayer_getTicks()
{
	return GetTickCount();
}

void PortingLayer_exit()
{
	ExitProcess(0);
}

int32_t PortingLayer_getIntFromConfig(const char * sectionName, const char * key, int32_t defvalue, const char * filename)
{
	return GetPrivateProfileIntA(sectionName, key, defvalue, filename);
}