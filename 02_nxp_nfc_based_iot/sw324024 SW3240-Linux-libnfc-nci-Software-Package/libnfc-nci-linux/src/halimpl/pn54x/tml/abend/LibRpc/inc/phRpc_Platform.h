/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
*  copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Host Library Platform Definitions / ARM-Board for PN547 V&V.
* $Author:  $
* $Revision:  $
* $Date: $
*
* Created: Marc Stibane, July 2012
*
*/

#ifndef PHRPC_PLATFORM_H
#define PHRPC_PLATFORM_H

#if defined (_WIN32) || defined (_WIN64) || defined (ming) || defined (__MINGW32__) || defined (__GNUWIN32__)
#    define PH_RPC_H_PLAT_WINDOWS
// #   warning PH_RPC_H_PLAT_WINDOWS // Debug
#   if defined (_WIN64)                        // Windows (64-bit)
#        warning Experimental Platform (Win64)
#       define PH_RPC_H_PLAT_WINDOWS_64
#   endif
#elif  defined(__GNUC__)                                // GCC
#    define PH_RPC_H_PLAT_GNUC
#    if defined (__APPLE__)                             // Apple could be
#        include "TargetConditionals.h"
#        if TARGET_OS_IPHONE                            // iOS
//#        if __arm__                                   // iOS (uses an ARM processor)
#            define PH_RPC_H_PLAT_IOS
#        elif TARGET_IPHONE_SIMULATOR                   // iOS Simulator
#            error Unsupported Platform (iOS Simulator)
#        elif TARGET_OS_MAC                             // MacOS
#            define PH_RPC_H_PLAT_MACOS
#        endif
#    else                                               // Linux with gcc
#        define PH_RPC_H_PLAT_LINUX
#    endif
#elif defined(_linux) || defined(__linux)               // Linux with some other compiler
#    define PH_RPC_H_PLAT_LINUX
#else
#    error Missing Platform Specification
#endif


#if defined PH_RPC_H_PLAT_WINDOWS
#    define PH_RPC_H_LIBFUNC __declspec(dllexport) //
#elif defined PH_RPC_H_PLAT_GNUC
#    define PH_RPC_H_LIBFUNC __attribute__ ((visibility("default"))) // requires  -fvisibility=hidden  as compiler option
#else
#    error Missing PH_RPC_H_LIBFUNC Specification
#endif

#endif // Guard
