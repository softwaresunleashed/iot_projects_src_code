/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Host Library Low Level / ARM-Board for PN547 V&V.
* $Author: nxp72238 $
* $Revision: 31965 $
* $Date: 2014-11-25 15:34:21 +0100 (mar., 25 nov. 2014) $
*
*/


#ifndef PHRPC_HOSTIO_H
#define PHRPC_HOSTIO_H

#include    "phRpc_Platform.h"
#include    "phRpc_Cmd.h"
#include    "phRpc_Status.h"
#include    "phRpc_Types.h"

// _________________________________________________________________________________________________
//
// Platform Diversity Include
// _________________________________________________________________________________________________

#if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
#   include <termios.h>
#   include <fcntl.h>
#   include <sys/select.h>
#   include <errno.h>
#   include <pthread.h>
    // Definitions
    typedef pthread_mutex_t phRpc_Mutex_t; //
#elif defined PH_RPC_H_PLAT_WINDOWS
#   include <windows.h>
#   include <process.h>
#    include <usb.h>    // LibUSB Header. Also needs libusb.a
    // Definitions
    typedef HANDLE phRpc_Mutex_t; //
#else
#    error "No platform specified"
#endif

// _________________________________________________________________________________________________
//
// Platform Diversity Definition
// _________________________________________________________________________________________________

#if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
#   define PH_RPC_H_SWPRINTF swprintf
#elif defined PH_RPC_H_PLAT_WINDOWS
#   define PH_RPC_H_SWPRINTF _snwprintf
#endif

// _________________________________________________________________________________________________
//
// Internal definitions and prototype
// _________________________________________________________________________________________________

#define PH_RPC_H_IOCTLFNSELECT_DEVIOCTL     0u              //
#define PH_RPC_H_IOCTLFNSELECT_DEVIOLINECTL 1u              //
#define PH_RPC_H_MAGIC_ID                   0x07091972      // Handle valid check
#define PH_RPC_H_HDL_OK(rpc__handle)        ((uint32_t)PH_RPC_H_MAGIC_ID == rpc__handle->MagicID) //

#define PH_RPC_H_LIN_BD_RATE    B57600                      // Baudrate definition on serial ports under Linux (and MAC)
#define PH_RPC_H_WIN_SER_FMT    L"57600,n,8,1"              // Serial definition on serial ports under Windows
#define PH_RPC_H_IOS_BD_RATE    TBD                         // Baudrate definition on serial ports under IOS

#define PH_RPC_HOSTIO_RCRESET               0u              //

// IO Pending
uint8_t phRpc_AuxIsIoPending(void *hdl);
void    phRpc_AuxSetPendingFlag(void *hdl);
void    phRpc_AuxClearPendingFlag(void *hdl);
// IO Cancel
void    phRpc_AuxSetCancelFlag(void *hdl);
void    phRpc_AuxClearCancelFlag(void *hdl);
uint8_t phRpc_AuxIoCancelCb(void *hdl);
void    phRpc_H_SendCancelFrame(void *hdl, uint8_t type);
// Log
void phRpc_H_LogPtr(void *hdl, void *ptr);
void phRpc_H_LogInt(void *hdl, int val, int base);
void phRpc_H_LogWStr(void *hdl, wchar_t *logStr);
// Engineering
phRpc_IoSystemData_t *phRpc_H_GetEngData(void *hdl);
// Init
phRpc_H_Return_t phRpc_H_BoardInit(void *hdl);


// _________________________________________________________________________________________________
//
// Handle Struct and Auxiliary Definitions
// _________________________________________________________________________________________________

/**
 * \internal
 * \brief RPC Host Structure
 *
 */
typedef struct phRpc_H_MinIO
{
    uint8_t Active;
    uint8_t HandleIntr;
    uint8_t CalcCrc;
    uint8_t RawMode;
} phRpc_H_MinIO_t;

// ________________________________________________________________________________________________
//
// AUX, INTERNAL
// ________________________________________________________________________________________________

void    phRpc_H_Lock(void *hdl, uint8_t lockAction);

void    phRpc_H_LimitLength(uint16_t *txBufLen, uint16_t *rxBufLen);

uint8_t phRpc_H_WriteData(void *hdl, uint8_t *buffer, uint16_t length);
uint8_t phRpc_H_ReadData(void *hdl, uint8_t *buffer, uint16_t *length);
uint8_t phRpc_H_RWData(void *hdl, uint16_t *length);
uint8_t phRpc_H_ReadErrorRecovery(void *hdl, uint16_t *length);
uint8_t phRpc_H_ReadErrorRecoveryAux(void *hdl, uint8_t ret);

#endif // Guard
