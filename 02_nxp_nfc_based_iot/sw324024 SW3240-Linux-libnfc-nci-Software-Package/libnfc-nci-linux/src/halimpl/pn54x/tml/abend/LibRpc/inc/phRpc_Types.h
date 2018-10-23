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

// _________________________________________________________________________________________________
//
// Include
// _________________________________________________________________________________________________

#ifndef PH_RPC_SKIP_STDINT
#include <stdint.h>
#endif
#include <wchar.h>

// _________________________________________________________________________________________________
//
// Types, Definitions, Settings
// _________________________________________________________________________________________________

#ifndef PHRPC_TYPES_H
#define PHRPC_TYPES_H

#define PH_RPC_H_DEVNAMELEN         32                              ///< Maximum length of device name
#define PH_RPC_H_DEVBUFLEN          (PH_RPC_CMD_RPCBUFFER_LEN+1u)   ///< Device Buffer Length
#define PH_RPC_2_H_DEVBUFLEN        (PH_RPC_2_CMD_RPCBUFFER_LEN+1u) ///< Device Buffer Length 2
#define PH_RPC_H_USABLE_LEN         (PH_RPC_CMD_USER_DATA_BUFSIZE)  ///< User Data Buffer size
#define PH_RPC_2_H_USABLE_LEN       (PH_RPC_2_CMD_USER_DATA_BUFSIZE)///< User Data Buffer size 2
#define PH_RPC_H_DEFAULT_TO         500u                            ///< Timeout value in ms

/**
 * \name PC library versus LPC software compatibility
 */

#define PH_RPC_H_COMPAT_ERROR       0   ///< Host library is not compatible to LPC software
#define PH_RPC_H_COMPAT_WARNING     1u  ///< Host library is from different delivery, but compatible to LPC software
#define PH_RPC_H_COMPAT_OK          2u  ///< Host library is compatible to LPC software

// _________________________________________________________________________________________________
//
// Hooks
// _________________________________________________________________________________________________

/** \name Hook Call Identification
 *  The definitions identify the point within the library from where the hook function is being called.
 *  The implementation must identify the point and then call the individual event handler, if required.
 */
//@{
// RESERVED Hooks
#define PH_RPC_H_HOOK_RESERVED_0           0u  ///< Reserved, do not use
#define PH_RPC_H_HOOK_RESERVED_1           1u  ///< Reserved, do not use
// Read Hooks
#define PH_RPC_H_HOOK_1ST_READ             2u  ///< The library has read the first part of the response
#define PH_RPC_H_HOOK_READ_TIMEOUT         3u  ///< No response was received within the timeout period
#define PH_RPC_H_HOOK_READ_NOTHING         4u  ///< No data has been received
#define PH_RPC_H_HOOK_READ_OVERFLOW        5u  ///< The library has received too many data: Discarding
#define PH_RPC_H_HOOK_READ_LENERR          6u  ///< Incoming length information error: Too many bytes are going to be received.
#define PH_RPC_H_HOOK_READ_OVERLAPPED_ERR  7u  ///< An overlapped read operation was not successful
#define PH_RPC_H_HOOK_READ_NOTHING_ST_OK   8u  ///< The read operation finished successfully but returned no data
#define PH_RPC_H_HOOK_OVREAD_NOTHING_ST_OK 9u  ///< The overlapped read operation finished successfully but returned no data
#define PH_RPC_H_HOOK_READ_IMM_COMPL       10u ///< The overlapped operation completed immediately and successfully
#define PH_RPC_H_HOOK_READ_RETRY           11u ///< The library has tried to read the data again
#define PH_RPC_H_HOOK_LEGACY_READ          12u ///< The library used the old-style RPC I/O functions
#define PH_RPC_H_HOOK_READ_OK              13u ///< Read OK
// Write Hooks
#define PH_RPC_H_HOOK_PRE_WRITE            20u ///< The calling point is immediately before writing data to the device
#define PH_RPC_H_HOOK_WRITE_ERROR          21u ///< The write function has encountered an error: Nothing written
#define PH_RPC_H_HOOK_WRITE_MISMATCH       22u ///< It was not possible to write all data: Write failed
#define PH_RPC_H_HOOK_WRITE_OVERLAPPED_ERR 23u ///< An overlapped write operation was not successful
#define PH_RPC_H_HOOK_WRITE_TIMEOUT        24u ///< An overlapped write operation timed out
#define PH_RPC_H_HOOK_WRITE_IMM_COMPL      25u ///< The overlapped operation completed immediately and successfully
#define PH_RPC_H_HOOK_POST_WRITE           26u ///< The transfer ended successfully. On error this function is not called
// Waiting Request Hooks
#define  PH_RPC_H_HOOK_RECEIVED_WTX        40u ///< The library has received a device request for more processing time
#define  PH_RPC_H_HOOK_SENT_WTX            41u ///< The library has sent a confirmation to extend the waiting time
//@}

/** \name Engineering data location information
 *  The definitions identify the point within the library from where the most recent update of the engineering data
 *  has been done.
 */
//@{
#define PH_RPC_H_ENGDATAPOINT_WRITE        0x00u ///< I/O write function
#define PH_RPC_H_ENGDATAPOINT_READ         0x10u ///< I/O read function
//@}

#ifndef SECFW_DOXY_SKIP //
#ifdef __cplusplus
extern "C"
{
#endif

/** \name Lock-Control Definition
 *  When the host library uses the Lock Delegate these values are valid for the delegate control parameter.
 */
//@{
#define PH_RPC_H_LOCK_ACQUIRE              1u   ///< Acquire lock
#define PH_RPC_H_LOCK_RELEASE              0    ///< Release lock
//@}

/**
 * \ingroup grp_rpc_host_acc
 * \brief Function Pointer to a Mutex Wrapper
 *
 * Defines the function pointer to an optional function that wraps a Mutex in order to simplify
 * multi-thread PC library access.
 *
 * \par Parameters
 * - Argument 1: Pointer to arbitrary \b User \b Data or the underlying synchronisation object.
 * - Argument 2: Whether to \b acquire (\ref PH_RPC_H_LOCK_ACQUIRE)
 *               or to \b release (\ref PH_RPC_H_LOCK_RELEASE) the lock.
 * .
 * \note Use the underlying synchronisation object only for the single purpose of protection against
 *       concurrent API function execution. Do not wait on that synchronisation object in other functions,
 *       in particular not in those located within the API function's call tree: This is particularly
 *       valid for the hook and log delegates \ref pphRpc_H_EventHook_t and \ref pphRpc_H_LogF_t.
 *
 */
typedef void (*pphRpc_H_LockD_t) (void*, uint8_t);


/**
 * \ingroup grp_rpc_host_acc
 * \brief Hook Function Pointer definition
 *
 * Defines the function pointer to an optional hook function that can be applied by a call to
 * \ref phRpc_H_SetHookF.
 *
 * \par Parameters
 * - Argument 1: Pointer to arbitrary \b User \b Data that the hook function may access.
 * - Argument 2: \b Reason for the call: It identifies the point from where the function is called.
 * .
 *
 */
typedef void (*pphRpc_H_EventHook_t) (void*, uint8_t);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Log Function Pointer definition
 *
 * Defines the function pointer to an optional log function that can be applied by a call to
 * \ref phRpc_H_SetLogF.
 *
 * \par Parameters
 * - Argument 1: Pointer to arbitrary \b User \b Data that the log function may access.
 * - Argument 2: \b Log String: Unicode representation of the logged data.
 * .
 *
 */
typedef void (*pphRpc_H_LogF_t) (void*, wchar_t*);

#ifdef __cplusplus
}
#endif
#endif // SECFW_DOXY_SKIP

#endif // Guard

