
#ifndef LIBINTF_HPP
#define LIBINTF_HPP

#include <sstream>
#include "phRpc_H.h"
#include "phRpc_H_2.h"

//PA
#include <string.h>

//JF 21/10/2012
#ifdef _DEBUG
#define ABEND_TRACE_ENABLED                      1
#define ABEND_TRACE_ENABLED_WITH_TIMESTAMP       1
#define ABEND_TRACE_ENABLED_WITH_GetTickCount    1
#define ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS  0//1
#else
#define ABEND_TRACE_ENABLED                      0
#define ABEND_TRACE_ENABLED_WITH_TIMESTAMP       0
#define ABEND_TRACE_ENABLED_WITH_GetTickCount    0
#define ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS  0
#endif // _DEBUG
//EndJF
#define CSV_SEPARATOR ","

#define PRINT_IN_ONE_LINE                        16

#if ! (ABEND_TRACE_ENABLED)
#   if ABEND_TRACE_ENABLED_WITH_GetTickCount
#       error ABEND_TRACE_ENABLED_WITH_GetTickCount can not be enabled without ABEND_TRACE_ENABLED
#   endif
#   if ABEND_TRACE_ENABLED_WITH_TIMESTAMP
#       error ABEND_TRACE_ENABLED_WITH_TIMESTAMP can not be enabled without ABEND_TRACE_ENABLED
#   endif
#   if ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS
#       error ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS can not be enabled without ABEND_TRACE_ENABLED
#   endif
#endif


#if defined PH_RPC_H_PLAT_WINDOWS
#    include <windows.h>
#elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
#    include <dlfcn.h>
#else
#    error No Platform Definition
#endif


#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
#    include <time.h>
#endif


class LibIntf
{
    public:
	// Getter for the currently set lib nyme and path.
	std::wstring *GetLibName()
	{
	    return &(this->LibName);
	}

	LibIntf() : LibHandle(NULL),
		    AbHandle(NULL),
		    DllOk(false),
		    LibName(L""),
		    ErrMsgS(L"")
	{
	}

	virtual ~LibIntf()
	{
	}

	// When the library is not located in the default/search path, the path can be adjusted with this function.
	void SetLibName(const wchar_t *libName)
	{
	    if (NULL != libName)
	    {
		this->LibName = libName;
	    } else
	    {
		this->LibName = L"";
	    }
	}

	// Get the latest error message once. Once, as the message is deleted by this function.
	std::wstring *GetLastErrMsg()
	{
	    return &(this->ErrMsgS);
	}

	// Load the library
	void DlLoad()
	{
	    const char         *dummy       = "None";       // Debug
	    char               *e           = (char*)dummy; // Debug
	    size_t              len         = this->LibName.length();
	    char               *libname     = new char[len + 1];
	    wchar_t            *wlibname    = (wchar_t*)this->LibName.c_str();

	    wcstombs(libname, wlibname, len);
	    libname[len]    = 0;
	    this->DllOk     = true; // Will be set to false if loading failed

#       if defined PH_RPC_H_PLAT_WINDOWS
	    HMODULE h;
#          ifdef UNICODE
	    h = LoadLibrary(wlibname);
#          else // ANSI
	    h = LoadLibrary(libname);
#          endif // UNICODE
#       elif defined PH_RPC_H_PLAT_IOS
	    void *h = NULL;
	    h = RTLD_DEFAULT;
#       elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
	    void *h = NULL;
	  //  printf("libname = %s\n", libname);
	    h = dlopen(libname, RTLD_NOW);
	    //PA: Warning on cast 
	    //printf("dlopen h = %d\n", (int)h);
	    e = dlerror();
	//    printf("dlerror = %s\n", e);
#       else
#            error No Library to open
#       endif // Platform

	    this->LibHandle = (void*)h;
	    if (NULL == this->LibHandle)
	    {
		// Failed to load DLL
		this->ErrMsgS.clear();
#           if defined PH_RPC_H_PLAT_WINDOWS
		std::wstringstream  wss;
		uint32_t error = GetLastError();
		wss << libname << " status = " << error;
		this->ErrMsgS = wss.str();
		(void)e;
#           else
		for (size_t i = 0; i < strlen((const char*)e); i++)
		{
		    this->ErrMsgS += (wchar_t)(e[i]);
		}
#           endif
	    } else
	    {
		this->LoadAllSymAddresses();
		if (this->DllOk)
		{
		    // Loaded!
		} else
		{
		    // Lib could be loaded, but at least one function failed:
		    this->DlUnload();
		}
	    }
	    #if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
	    {
		time_t rawtime;
		struct tm * timeinfo;
		char buffer [120];
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime (buffer,120,"abend-TxRx-log-%Y%m%d-%H%M%S.txt",timeinfo);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
		this->fpDumpTextLogs = fopen(buffer,"w+");
#endif
		strftime (buffer,120,"abend-TxRx-%Y%m%d-%H%M%S.csv",timeinfo);
		this->fpDumpCSVLogs = fopen(buffer,"a+");

		strftime (buffer,120,"%Y.%m.%d %H:%M:%S",timeinfo);
#if ABEND_TRACE_ENABLED_WITH_TIMESTAMP
		fprintf(this->fpDumpCSVLogs,"TimeStamp,");
#endif
		fprintf(this->fpDumpCSVLogs,"TxRx,Len,Time=%s\n",buffer);
#if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
		fprintf(this->fpDumpTextLogs,"TxRx,Len,Time=%s\n",buffer);
#endif
		}
	    #endif

	    delete(libname);
	}

	// Check whether all functions could be loaded and the library is ready for usage
	bool IsValid()
	{
	    return (NULL == this->LibHandle) ? false : true;
	}

	void RememberAbHandle(void *abHandle)
	{
	    this->AbHandle = abHandle;
	}

	void *RecallAbHandle()
	{
	    return this->AbHandle;
	}

	void *GetLibHandle()
	{
	    return this->LibHandle;
	}

    void DlUnload()
    {
	if (this->IsValid())
	{
#          if defined PH_RPC_H_PLAT_WINDOWS
	    (void)FreeLibrary((HMODULE)(this->LibHandle));
#          elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
	    dlclose(this->LibHandle);
#          endif
	} else { }
	// Anyway:
	this->LibHandle = NULL;
    }

    protected:
	void                       *LibHandle;
	void                       *AbHandle;
	bool                        DllOk;
	std::wstring                LibName;
	std::wstring                ErrMsgS;

    virtual void LoadAllSymAddresses() = 0;

#if defined(ABEND_TRACE_ENABLED) && ABEND_TRACE_ENABLED == 1
#   if defined(ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS) && ABEND_TRACE_ENABLED_WITH_DUT_IOCTL_LOGS == 1
	FILE                        *fpDumpTextLogs;
#   endif
    FILE                        *fpDumpCSVLogs;

#endif

    void *GetSymAddress(wchar_t *symName)
    {
	return this->GetSymAddress(symName, NULL);
    }

    void *GetSymAddress(wchar_t *symName, void *substituteFunction)
    {
	void            *fn_addr     = NULL;
	std::wstring     sym_name    = symName;
	size_t           len         = sym_name.length();
	char            *symbol_str  = new char[len + 1];
	wcstombs(symbol_str, sym_name.c_str(), len);
	symbol_str[len] = 0;

#        if defined PH_RPC_H_PLAT_WINDOWS
	    FARPROC proc;
	    proc = GetProcAddress((HMODULE)this->LibHandle, symbol_str);
	    if (NULL != proc)
	    {
		fn_addr = (void*)proc;
	    } else
	    {
		fn_addr = NULL;
		std::wstringstream wss;
		wss << (wchar_t*)L"Error loading: " << sym_name << (wchar_t*)L" Error = " << (uint32_t)GetLastError();
		this->ErrMsgS = wss.str().c_str();
	    }
#        elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
	    char *err_str;
	    (void)dlerror(); // Clear any existing error
	    fn_addr = dlsym(this->LibHandle, symbol_str);
	    err_str = dlerror();
	    if (NULL != err_str)
	    {
		// Error:
		fn_addr = NULL;
		this->ErrMsgS = L"Error loading: " + sym_name;
		this->ErrMsgS += L": ";
		for (size_t i = 0; i < strlen(err_str); i++)
		{
		    this->ErrMsgS += (wchar_t)(err_str[i]);
		}
	    } else { }
#endif

	if (NULL != fn_addr)
	{
	    // OK
	} else
	{
	    // Symbol not found
	    if (NULL != substituteFunction)
	    {
		this->ErrMsgS = L"Loaded substitute for: " + sym_name;
		fn_addr = substituteFunction;
	    } else
	    {
		this->ErrMsgS = L"Loaded: " + sym_name;
		this->DllOk = false;
	    }
	}

	delete symbol_str;
	return fn_addr;
    }
};

#endif // Guard
