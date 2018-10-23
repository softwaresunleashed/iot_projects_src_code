
/*
*                  Copyright (c), NXP Semiconductors
*
*                      (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: RPC Host Library / ARM-Board for PN547 V&V.
* $Author:  $
* $Revision:  $
* $Date:  $
*
*/

/**
 * \addtogroup grp_rpc_host
 * \brief RPC Host Functionality
 *
 * @{
 */

/**
 * \defgroup grp_rpc_host_acc_iofn_buffer I/O Function that Changes Pointers
 *
 * \b Warning! \b Function \b changes \b pointers or \b references \b internal \b storage:
 * Therefore the user needs to \b copy data referenced by the pointer provided/changed.
 * The pointer references a location within the exchange buffer or other internal storage
 * that will be overwritten by the following call that exchanges data with the device.
 * Data must be copied before making any further call which exchanges data.
 * A call to  \ref phRpc_H_GetLastError is safe, however.
 *
 */

/**
 * \defgroup grp_rpc_host_acc_iofn I/O Function Handling
 *
 * This is a guideline for I/O function handling:
 * -# Set the data buffer to the begin of the data to transmit.
 * -# Set the transmit length to the number of bytes to transmit.
 * -# Set the receive length to the maximum number of bytes to receive.
 * -# Call the I/O function.
 * -# Error check (return value, buffer is NULL, \ref phRpc_H_GetLastError, buffer size, ...).
 *    \ref phRpc_H_GetLastError will not change internal buffer so it's safe to call it immediately.
 * -# Copy received data into an own buffer:
 *    The function has set the pointer to the received data to the internal exchange buffer. A subsequent
 *    call to \b any library function will therefore overwrite this buffer. If it is required to keep the
 *    received data for later processing the user must make sure that it is copied into an own buffer before
 *    calling any further library function.
 * -# Next call to a library function is safe now.
 * .
 *
 * The procedure above may deviate under specific circumstances or it may apply only partly for send/receive-only
 * functions.
 *
 * \sa \ref grp_rpc_host_acc_iofn_buffer
 *
 */

#ifndef PHRPC_H_COMMON_H
#define PHRPC_H_COMMON_H

// ________________________________________________________________________________________________
//
// INCLUDE
// ________________________________________________________________________________________________

#include <stdlib.h>

#include "phRpc_Platform.h"
#include "phRpc_Status.h"
#include "phRpc_Cmd_2.h"
#include "phRpc_Types.h"

// ________________________________________________________________________________________________
//
// INTERFACE
// ________________________________________________________________________________________________

#ifdef __cplusplus
extern "C"
{
#endif

// ________________________________________________________________________________________________
//
// Raw Communication
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_adm
 * \brief Raw data exchange
 *
 * The Raw Data Exchange function can be used for device debug or library cascading. The function is provided
 * by the Primary Channel's library and can be used by the Secondary Channel's library to tunnel commands.
 * This is useful when using a single channel firmware or a host where just the primary channel is available.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      txBuf       Pointer to a buffer that contains the raw data to be sent to the device.
 * \param [in]      txBufLen    Number of raw bytes to be sent to the device. With invalid parameters
 *                              (pointer parameters set to NULL) and this item set to maximum value possible
 *                              ((uint16_t)-1) the library cancels the current I/O operation.
 *                              See \ref phRpc_H_CancelIo for more information.
 * \param [in,out]  rxBuf       Pointer to a buffer that will receive the raw data coming from the device.
 * \param [in,out]  rxBufLen    Pointer to a variable that specifies the size in bytes of the receive buffer.
 *                              The function then fills in the actual number of bytes received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref phRpc_H_OpenC
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Raw(void *hdl, uint8_t *txBuf, uint16_t txBufLen, uint8_t *rxBuf, uint16_t *rxBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_Raw
typedef phRpc_H_Return_t (*pphRpc_H_Raw_t) (void*, uint8_t*, uint16_t, uint8_t*, uint16_t*);


// ________________________________________________________________________________________________
//
// HOST
// ________________________________________________________________________________________________


/**
 * \ingroup grp_rpc_host_acc
 * \brief Open the device
 *
 * Opens the device specified by the \b Device \b Name. Sucessfully opened, the device will be
 * represented by the \b Device \b Handle. An underlying object is allocated by the function
 * in order to manage storage needed to operate the device. In order to avoid memory leaks a call to
 * \ref phRpc_H_Close is required at the end unless the handle set by the function is NULL.
 * When a handle that represents an already open device is recycled to open another device the
 * reference to the previously opened device is lost, resulting in its unavailability and a memory leak.
 *
 * \param [out] hdl         The device is represented by the underlying object. The handle is
 *                          anonymous as there is no need to access its elements. Set the pointer to NULL
 *                          before calling the function. The function will, through the address of the pointer,
 *                          set its value to the internal object that it allocates.
 * \param [in]  devName     Name of the device. This must be the symbolic name of the communication
 *                          interface:\n
 *                          - On Windows, \c NULL needs to be provided to select \b LibUSB. When a
 *                            valid device name such as <tt>\"\\\\\\\\.\\\\COM3\"</tt> is specified
 *                            a communication device (CDC driver) is opened.
 *                          - On Linux the function accepts something like <tt>\"/dev/ttyACM0\"</tt>.
 *                          .
 * \param [in]  devNameLen  Length of the device name or \c 0 if no device name is specified. The
 *                          length needs to be provided as number of characters and not as number of bytes,
 *                          e.g.: len = sizeof(dev_name) / sizeof(wchar_t)
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \par Windows
 * The library requires \b libusb to be installed on the system. This important library provided generic
 * USB services. Alternatively a CDC driver may be used. In this case a device name has to be specified,
 * as can be seen in the parameter description.
 * \par Linux
 * Under Linux, as said already, the device appears as a communication device. No extra driver is needed.
 * However, by default Linux is very restrictive with standard user privileges. Consequently it will likely
 * not allow a user to access the device as not being member of the required group:
\verbatim
x@y:~> ll /dev/ttyA*
crw-rw---- 1 root dialout 166, 0 /dev/ttyACM0
\endverbatim
 * So obviously no standard user access is granted, unless the user is added to the \b dialout group. Please refer
 * to the corresponding HowTo documents and/or to the distribution-specific user management utility. A log off/on or reboot
 * may be required afterwards.\n
 * It is also possible to \c chmod the device (in our example /dev/ttyACM0). While perfectly fine for testing, the change is temporary
 * and the rights will be reset with the next reset/unplug of the external device or reboot of the PC.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Open(void **hdl, wchar_t *devName, uint8_t devNameLen);
/// \brief Function pointer declaration according to \ref phRpc_H_Open
typedef phRpc_H_Return_t (*pphRpc_H_Open_t) (void**, wchar_t*, uint8_t);

/**
 * \ingroup grp_rpc_host_acc
 * \copydoc phRpc_H_Open
 * \param [in]  logF        Pointer to the Log Function. If NULL, the log is not installed.
 * \param [in]  userLData   Pointer that will be passed to the log function.
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenL(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                pphRpc_H_LogF_t logF, void *userLData);
/// \brief Function pointer declaration according to \ref phRpc_H_OpenL
typedef phRpc_H_Return_t (*pphRpc_H_OpenL_t) (void**, wchar_t*, uint8_t, pphRpc_H_LogF_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \copydoc phRpc_H_OpenL
 * \param [in]  hookF       Pointer to the Hook Function. If NULL, the hook is not installed.
 * \param [in]  userHData   Pointer that will be passed to the hook function.
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenLH(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                 pphRpc_H_LogF_t logF, void *userLData,
                                                 pphRpc_H_EventHook_t hookF, void *userHData);
/// \brief Function pointer declaration according to \ref phRpc_H_OpenLH
typedef phRpc_H_Return_t (*pphRpc_H_OpenLH_t) (void**, wchar_t*, uint8_t, pphRpc_H_LogF_t, void*, pphRpc_H_EventHook_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \copydoc phRpc_H_OpenLH
 * \param [in]  optFlags                Flags that control the behaviour of the function. See \ref PH_RPC_H_OPENPARAM_NOCANCELIO.
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenLHF(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                  pphRpc_H_LogF_t logF, void *userLData,
                                                  pphRpc_H_EventHook_t hookF, void *userHData,
                                                  uint32_t optFlags);
/// \brief Function pointer declaration according to \ref phRpc_H_OpenLHF
typedef phRpc_H_Return_t (*pphRpc_H_OpenLHF_t) (void**, wchar_t*, uint8_t, pphRpc_H_LogF_t, void*, pphRpc_H_EventHook_t, void*, uint32_t);

/**
 * \brief Attach to a device object in cascaded mode, using the underlying raw communication function.
 *
 * A device object is represented by the handle provided by one of the \c Open functions. This function
 * allows to attach to such a device and to use its raw communication functionality. A typical application
 * is the usage of a single communication channel (single-channel firmware) to tunnel commands for the
 * Secondary I/O system.
 *
 * \param [out] hdl                 The device is represented by the underlying object. The handle is
 *                                  anonymous as there is no need to access its elements. Set the pointer to NULL
 *                                  before calling the function. The function will, through the address of the pointer,
 *                                  set its value to the internal object that it allocates.
 * \param [in]  primaryLibRawCmd    Pointer to the \c RAW communication function of the Primary Channel.
 * \param [in]  primaryLibH         Handle of the Primary Channel, i.e. pointer that has been provided by
 *                                  the \c Open functions of the Primary Channel.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref phRpc_H_Open
 * \sa \ref phRpc_H_OpenL
 * \sa \ref phRpc_H_OpenLHF
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenC(void **hdl, pphRpc_H_Raw_t primaryLibRawCmd, void *primaryLibH);
/// \brief Function pointer declaration according to \ref phRpc_H_OpenC
typedef phRpc_H_Return_t (*pphRpc_H_OpenC_t) (void**, pphRpc_H_Raw_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Close the device
 *
 * Closes the device. The underlying object is de-allocated.
 *
 * \param [in,out] hdl     Handle to the device. The pointer behind this anonymous object is set to NULL.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Close(void **hdl);
/// \brief Function pointer declaration according to \ref phRpc_H_Close
typedef phRpc_H_Return_t (*pphRpc_H_Close_t) (void**);

#ifndef SECFW_DOXY_SKIP //

/**
 * \ingroup grp_rpc_host_acc
 * \brief Set Timeout in ms
 *
 * Set the maximum time the host shall wait for a response from the device. As the USB driver uses
 * Bulk I/O it is possible that the transfer is delayed. Please note that the library will apply
 * the timeout value to a pair of transfers (OUT and IN). The timeout value is not applied to the
 * device with this command.
 *
 * \param [in]  hdl     Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  msTo    Host timeout value in ms. The host should not specify less than \b 50. It is
 *                      recommended to leave the value at the default of \ref PH_RPC_H_DEFAULT_TO.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref phRpc_H_SetCommParam to apply the new settings also on the device.
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetTimeout(void *hdl, uint16_t msTo);
/// \brief Function pointer declaration according to \ref phRpc_H_SetTimeout
typedef phRpc_H_Return_t (*pphRpc_H_SetTimeout_t) (void*, uint16_t);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Provide information about PC library versus LPC software compatibility
 *
 * When \ref phRpc_H_Open has provided a valid handle the function should be used to check
 * whether the currently used PC library is compatible to the LPC software.
 *
 * \param [in]  hdl     Device Handle as provided by \ref phRpc_H_Open.
 * \param [out] cptLvl  Pointer to a location that will receive the Compatibility level information.
 *                      See \ref PH_RPC_H_COMPAT_OK, \ref PH_RPC_H_COMPAT_WARNING, \ref PH_RPC_H_COMPAT_ERROR.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetCompatibilityInfo(void *hdl, uint8_t *cptLvl);
/// \brief Function pointer declaration according to \ref phRpc_H_SetTimeout
typedef phRpc_H_Return_t (*pphRpc_H_GetCompatibilityInfo_t) (void*, uint8_t*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Last Error
 *
 * Provides a pointer to an already allocated structure that comprises library and device status codes.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [out] lastError   Address of a pointer of type \ref phRpc_Status_t that will receive the location
 *                          of the internally stored status information.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetLastError(void *hdl, phRpc_Status_t **lastError);
/// \brief Function pointer declaration according to \ref phRpc_H_GetLastError
typedef phRpc_H_Return_t (*pphRpc_H_GetLastError_t) (void*, phRpc_Status_t**);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Host Library Context Member Information Text
 *
 * Provides textual information about the values of the individual members of the component instance.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  itemNum     Number of the item to query. As the purpose is to query the entire content, the user
 *                          shall start with 0 and loop until (txtBufLen) becomes zero which means that the entire
 *                          structure has been queried.
 * \param[out]  txtBuf      Buffer provided by the caller into which the function copies the text.
 * \param[out]  txtBufLen   The caller provides the total size of the buffer as the number of characters (not bytes)
 *                          and will receive the number of unicode characters actually written to the buffer.
 *
 * \return Component instance member text
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
uint8_t PH_RPC_H_LIBFUNC phRpc_H_GetHostCtxText(void *hdl, int itemNum, wchar_t *txtBuf, size_t *txtBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_GetHostCtxText
typedef uint8_t (*pphRpc_H_GetHostCtxText_t) (void*, int, wchar_t*, size_t*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Transfer Buffers and Sent/Received Length
 *
 * Provides information about what has been sent or received during the most recent transfer. This function
 * is useful for debug purpose.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [out] outBuf      Pointer to a pointer that will receive the address of the internal OUT buffer.
 * \param [out] numSent     Pointer to a variable that will receive the number of bytes that have been sent.
 * \param [out] inBuf       Pointer to a pointer that will receive the address of the internal IN buffer.
 * \param [out] numReceived Pointer to a variable that will receive the number of bytes that have been received.
 *
 * \note It is possibe to set \b out parameters to NULL when not all data is required.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetBuffers(void *hdl, uint8_t **outBuf, uint16_t *numSent, uint8_t **inBuf, uint16_t *numReceived);
/// \brief Function pointer declaration according to \ref phRpc_H_GetBuffers
typedef phRpc_H_Return_t (*pphRpc_H_GetBuffers_t) (void*, uint8_t**, uint16_t*, uint8_t**, uint16_t*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Set Lock Delegate
 *
 * The library can call a lock function to simplify the library usage in multi-threading environments.
 * It can be set, changed or removed any time provided that the device handle is valid and no operation is
 * pending. The lock function implementation affects performance thus it should be kept without
 * calls that consume too much time.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  lockD       Pointer to a Lock Function (delegate). If NULL, the lock is uninstalled.
 * \param [in]  userData    Pointer to data that the lock function will be called with.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note When using the lock functionality the user must make sure that this does not cause deadlocks:
 *       -  The lock zone encloses the entire function, including the log acquisition and the event hook callback.
 *       -  In particular, functionality wrapped by the callback functions registered by
 *          \ref phRpc_H_SetLogF and \ref phRpc_H_SetHookF must not comprise code that waits on the same
 *          synchronisation object as used by the lock delegate \ref pphRpc_H_LockD_t.
 *       -  All functions of this library are guarded except for those with a specific remark. See the individual
 *          functions for more details and whether they allow to be called from within a hook function.
 *       -  Under Windows the implementation of the delegate should \b not use a \b mutex object. It is strongly
 *          recommended to use a semaphore instead. The reason is that mutex objects under Windows are context
 *          sensitive, i.e. the associated wait function will not wait if called twice or more times from within
 *          the same context. This behaviour should not cause problems in a proper implementation, though. In
 *          a wrong implementation however usage or call nesting errors will likely go unnoticed.
 *       .
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetLockD(void *hdl, pphRpc_H_LockD_t lockD, void *userData);
/// \brief Function pointer declaration according to \ref phRpc_H_SetLockD
typedef phRpc_H_Return_t (*pphRpc_H_SetLockD_t) (void*, pphRpc_H_LockD_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Set Log Function
 *
 * The library can call a log function, which is useful for debugging or tracing.
 * It can be set, changed or removed any time provided that the device handle is valid and no
 * call into a library function is in progress.
 * The log implementation directly influences performance thus it should be kept without calls that
 * consume too much time.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  logF        Pointer to a Log Function. If NULL, the log is uninstalled.
 * \param [in]  userData    Pointer to data that the log function will be called with.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetLogF(void *hdl, pphRpc_H_LogF_t logF, void *userData);
/// \brief Function pointer declaration according to \ref phRpc_H_SetLogF
typedef phRpc_H_Return_t (*pphRpc_H_SetLogF_t) (void*, pphRpc_H_LogF_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Set Hook Function
 *
 * The library can call a hook function on special events such as transfer begin, end or error.
 * This is useful for debugging, tracing or adding a custom pre/post event handler. The hook can
 * be set, changed or removed any time provided that the device handle is valid and no
 * call into a library function is in progress.
 * The hook implementation directly influences performance thus its code should be kept without calls that
 * consume too much time.
 *
 * \note    As only one hook function exists it is necessary to determine the reason for the call by
 *          evaluating its second parameter. See \ref pphRpc_H_EventHook_t.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  hookF       Pointer to a Hook Function. If NULL, the hook will be uninstalled.
 * \param [in]  userData    Pointer to data that the hook function will be called with. Typically
 *                          this is a pointer to a "context" structure of the hook implementation.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetHookF(void *hdl, pphRpc_H_EventHook_t hookF, void *userData);
/// \brief Function pointer declaration according to \ref phRpc_H_SetHookF
typedef phRpc_H_Return_t (*pphRpc_H_SetHookF_t) (void*, pphRpc_H_EventHook_t, void*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Cancel the ongoing I/O Operation
 *
 * The current I/O operation will be cancelled. As the I/O functions are synchronous this function must
 * be called from within another thread in order to allow the I/O operation to be cancelled.
 *
 * \param [in]      hdl             Device Handle as provided by \ref phRpc_H_Open.
 *
 * \return \ref PH_RPC_CANCELRESULT_OK and related.
 *
 * \note The function does \b not wait until the I/O operation completes. The calling thread however
 *       \b must wait for the cancelled function to return in order to be allowed to issue the next
 *       call. For systems that require a fast reaction enable \ref PH_RPC_IOCTL_MJ_HOST_FAST_CANCEL.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_CancelIo(void *hdl);
/// \brief Function pointer declaration according to \ref phRpc_H_CancelIo
typedef phRpc_H_Return_t (*pphRpc_H_CancelIo_t) (void*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Host Information
 *
 * Get operational information from the PC library. The information that can be queried comprises
 * SW identification, engineering data and other fields.
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      infoType    Type of information to be queried as defined, e.g. \ref PH_RPC_CMD_HOSTINFO_PCLIB_SWID.
 * \param [out]     infoNum     Information, represented by a number, returned by the library.
 * \param [out]     infoBuf     Pointer to an internal buffer that has received the information.
 * \param [in,out]  infoLen     Pointer to a variable that will be set to the actual number of bytes received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 * \note This function is not guarded by a lock function registered with \ref phRpc_H_SetLockD. It can be called from within
 *       the implementation of the \b Event \b Hook (\ref phRpc_H_SetHookF) therefore.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetHostInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen);
/// \brief Function pointer declaration according to \ref phRpc_H_GetHostInfo
typedef phRpc_H_Return_t (*pphRpc_H_GetHostInfo_t) (void*, uint8_t, uint32_t*, uint8_t**, uint8_t*);

// ________________________________________________________________________________________________
//
// Administrative Commands
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_adm
 * \brief Get Device Information
 *
 * Get static and dynamic information from the device. The information that can be queried comprises
 * CPU or SW identification, run time data, operational state etc.
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      infoType    Type of information to be queried as defined, e.g. \ref PH_RPC_CMD_DEVINFO_CPUSNR
 *                              or \ref PH_RPC_2_CMD_DEVINFO_CPUSNR respectively.
 * \param [out]     infoNum     Information, represented by a number, returned by the device.
 * \param [out]     infoBuf     Pointer to a location that will receive the pointer to an internal buffer
 *                              that has received the information.
 * \param [out]     infoLen     Pointer to a variable that will be set to the actual number of bytes received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetDeviceInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen);
/// \brief Function pointer declaration according to \ref phRpc_H_GetDeviceInfo
typedef phRpc_H_Return_t (*pphRpc_H_GetDeviceInfo_t) (void*, uint8_t, uint32_t*, uint8_t**, uint8_t*);


/**
 * \ingroup grp_rpc_host_adm
 * \brief Synchronise host and device communication settings
 *
 * The host may apply specific communication settings. Most important, the timeout value
 * set in the host instance must be known by the device in order to let it request more
 * processing time.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetCommParam(void *hdl);
/// \brief Function pointer declaration according to \ref phRpc_H_SetCommParam
typedef phRpc_H_Return_t (*pphRpc_H_SetCommParam_t) (void*);

// ________________________________________________________________________________________________
//
// Analogue/Digital I/O System
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Get measured value.
 *
 * Gets the measured and converted value. The function takes into account the board hardware, i.e.
 * voltage dividers of amplifiers. If different factors or calibration are required the gain can
 * be adjusted using \ref phRpc_H_DaqSetGain.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  channelID   ID of the channel to query. See \ref PH_RPC_CMD_ADC_CH_V_I_TST.
 * \param [out] daqVal      Pointer to a variable that will receive the value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The default unit is microvolt [µV] unless otherwise specified.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_AdcGetValue(void *hdl, uint8_t channelID, int32_t *daqVal);
/// \brief Function pointer declaration according to \ref phRpc_H_AdcGetValue
typedef phRpc_H_Return_t (*pphRpc_H_AdcGetValue_t) (void*, uint8_t, int32_t*);


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Set constant output voltage.
 *
 * For boards that connect the DAC output a constant output voltage can be set. The gain of the channel
 * can be calibrated or adjusted to the actual gain of the board's power amplifier/driver. See the function
 * \ref phRpc_H_DaqSetGain. The command terminates any previously set output action, i.e. a previously set
 * waveform (\ref phRpc_H_DacSetWave) will be stopped and the output becomes constant again.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  channelID   ID of the channel to control. See \ref PH_RPC_CMD_DAC_CH_VVAR.
 * \param [in]  newValue    New constant output value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The default unit is microvolt [µV] unless otherwise specified.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacSetValue(void *hdl, uint8_t channelID, int32_t newValue);
/// \brief Function pointer declaration according to \ref phRpc_H_DacSetValue
typedef phRpc_H_Return_t (*pphRpc_H_DacSetValue_t) (void*, uint8_t, int32_t);


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Set output waveform.
 *
 * Configures the output waveform. A range of different waveforms with amplitude, frequency and DC offset can be configured.
 * The command will overwrite previous settings, i.e. previously set voltages (\ref phRpc_H_DacSetValue) will
 * not be superimposed.
 *
 * \param [in]  hdl             Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  channelID       ID of the channel to control. See \ref PH_RPC_CMD_DAC_CH_VVAR.
 * \param [in]  waveType        Type of the AC-component of the waveform. See \ref PH_RPC_CMD_DAC_WAVETYPE_SINE.
 * \param [in]  waveFrequency   Waveform output frequency (not the update rate of the DAC output register).
 * \param [in]  waveAmplitude   Amplitude, i.e. peak-to-peak voltage of the AC-component.
 * \param [in]  waveOffset      DC-component of the waveform.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note Unless otherwise specified, the default units are as follows:
 *       - Voltages: microvolt [µV].
 *       - Frequency: milli-hertz [mHz]: The range is 1 mHz to 10 KHz.
 *       .
 *       The waveform can be output within a certain range only. The I/O system will clip all parts of the waveform
 *       that would otherwise lie outside the voltage range. The range depends on the board hardware.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacSetWave(void *hdl, uint8_t channelID, uint8_t waveType, uint32_t waveFrequency,
                                                     int32_t waveAmplitude, int32_t waveOffset);
/// \brief Function pointer declaration according to \ref phRpc_H_DacSetWave
typedef phRpc_H_Return_t (*pphRpc_H_DacSetWave_t) (void*, uint8_t , uint8_t ,
                                                   uint32_t , int32_t , int32_t );


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Get the configured reference voltage.
 *
 * Get the reference voltage value currently configured. The value can be set using \ref phRpc_H_DaqSetVRef.
 *
 * \param [in]  hdl     Device Handle as provided by \ref phRpc_H_Open.
 * \param [out] vrefVal Pointer to a variable that will receive the value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The unit is microvolt [µV].
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqGetVRef(void *hdl, uint32_t *vrefVal);
/// \brief Function pointer declaration according to \ref phRpc_H_DaqGetVRef
typedef phRpc_H_Return_t (*pphRpc_H_DaqGetVRef_t) (void*, uint32_t*);


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Set the reference voltage value.
 *
 * Set the reference voltage to a user-defined value. This function can be used to calibrate the reference voltage
 * for precision measurement. If the actual voltage provided by the on-board reference is known this parameter can be
 * set to exactly this voltage. This way it is possible to eliminate even small reference and thus measurement errors.
 * See also \ref phRpc_H_DaqSetGain.
 *
 * \param [in]  hdl     Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  vrefVal New reference voltage value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The unit is microvolt [µV].
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqSetVRef(void *hdl, uint32_t vrefVal);
/// \brief Function pointer declaration according to \ref phRpc_H_DaqSetVRef
typedef phRpc_H_Return_t (*pphRpc_H_DaqSetVRef_t) (void*, uint32_t );


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Set the gain of an analogue I/O channel.
 *
 * Change the gain of a specific analogue I/O channel. This function allows to adapt do different boards using
 * different voltage divider ratio configuration. Use this function also for precision-measurement fine-tuning if the
 * exact divider ratio is known. See also \ref phRpc_H_DaqSetVRef.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  hwType      Type of the hardware to control: See \ref PH_RPC_CMD_ADC_HWTYPE or \ref PH_RPC_CMD_DAC_HWTYPE.
 * \param [in]  channelID   ID of the channel to control. See \ref PH_RPC_CMD_DAC_CH_VVAR or \ref PH_RPC_CMD_ADC_CH_V_I_TST.
 * \param [in]  gainVal     New gain value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The gain unit is ppm, i.e. a gain of 1.5 will have to be given as 1500000.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqSetGain(void *hdl, uint8_t hwType, uint8_t channelID, int32_t gainVal);
/// \brief Function pointer declaration according to \ref phRpc_H_DaqSetGain
typedef phRpc_H_Return_t (*pphRpc_H_DaqSetGain_t) (void*, uint8_t, uint8_t, int32_t);


/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Get the gain of an analogue I/O channel.
 *
 * Get the currently configured gain of an analogue I/O channel.
 *
 * \param [in]  hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  hwType      Type of the hardware to query: See \ref PH_RPC_CMD_ADC_HWTYPE or \ref PH_RPC_CMD_DAC_HWTYPE.
 * \param [in]  channelID   ID of the channel to query. See \ref PH_RPC_CMD_DAC_CH_VVAR or \ref PH_RPC_CMD_ADC_CH_V_I_TST.
 * \param [out] gainVal     Pointer to a variable that will receive the value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 * \note The gain unit is ppm, i.e. a received value of 1500000 is an actual value of 1.5.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DaqGetGain(void *hdl, uint8_t hwType, uint8_t channelID, int32_t *gainVal);
/// \brief Function pointer declaration according to \ref phRpc_H_DaqGetGain
typedef phRpc_H_Return_t (*pphRpc_H_DaqGetGain_t) (void *, uint8_t, uint8_t, int32_t*);

/**
 * \ingroup grp_rpc_host_ad_io
 * \brief Get the frequency of an analogue I/O channel.
 *
 * Get the currently configured frequency of an analogue I/O channel.
 *
 * \param [in]  hdl             Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]  channelID       ID of the channel to query. See \ref PH_RPC_CMD_DAC_CH_VVAR or \ref PH_RPC_CMD_ADC_CH_V_I_TST.
 * \param [out] frequencyVal    Pointer to a variable that will receive the value.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DacGetFrequency(void *hdl, uint8_t channelID, uint32_t *frequencyVal);
/// \brief Function pointer declaration according to \ref phRpc_H_DacGetFrequency
typedef phRpc_H_Return_t (*pphRpc_H_DacGetFrequency_t) (void *, uint8_t, uint32_t*);


/** @} */

#endif // Doxy

#ifdef __cplusplus
}
#endif

#endif // Guard
