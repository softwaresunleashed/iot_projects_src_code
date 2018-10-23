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
* $Author: atp01705 $
* $Revision: 33425 $
* $Date: 2015-01-26 20:01:01 +0100 (lun., 26 janv. 2015) $
*
*/

#ifndef SECFW_DOXY_SKIP // Doxy will skip all but the Secondary Firmware Control API
/**
 * \addtogroup grp_rpc_host
 * \brief RPC Host Functionality
 *
 * @{
 */
 #endif // SECFW_DOXY_SKIP

// _________________________________________________________________________________________________
//
// Platform
// _________________________________________________________________________________________________

#ifndef PHRPC_H_H
#define PHRPC_H_H

#ifndef SECFW_DOXY_SKIP //

#include "phRpc_H_Common.h"

#include <stdlib.h>

#endif // SECFW_DOXY_SKIP

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \defgroup grp_rpc_host_acc_fncall Function Call Requirements
 *
 * Host library functions have some basic requirements. The design of the application which uses the
 * library shall follow these requirements:
 *
 * - Calls are blocking, i.e. a call returns once processing of the request on the device has finished
 *   and the response has been received and processed on the host.
 * - It is not allowed to call a library function while another one is executing. Exception: \ref phRpc_H_CancelIo.
 *   - The software shall wait for all functions to complete. For instance, thread A calls \ref phRpc_H_DutRx
 *     but nothing is received within a certain, application-defined timeout period. The receive call would,
 *     in this example, time out much later. Therefore another thread, say thread B, may call
 *     \ref phRpc_H_CancelIo. The cancel function will return immediately. However, thread A \b must \b wait
 *     for the (canceled) receive function to complete! Once completed, thread A is allowed to continue
 *     using the host library!
 *   .
 * - The library allows for multiple instances within one process. It is possible to run multiple LPC boards
 *   under the control of one process.
 *   - It is allowed for thread A to use instance 1 at the same time as thread B is using instance 2. Instances
 *     are bound to attached hardware and distinguished by the device handle as provided by \ref phRpc_H_Open.
 *   - A board cannot be opened twice.
 *   - For multi-board operation from within one application please see the Q&A section \ref grp_qa_multi.
 *   .
 * - Lock Function: It is possible to register a lock function in order to protect the library against
 *   concurrent API calls. See \ref phRpc_H_SetLockD.
 * .
 *
 */

// ________________________________________________________________________________________________
//
// DEFINITIONS
// ________________________________________________________________________________________________

/**
 * \name PC Library definitions
 *
 * @{
 */

#define PH_RPC_H_OPENPARAM_NOCANCELIO       0x00000001u ///< Suppress the LPC I/O Cancel on call of OPEN
#define PH_RPC_H_OPENPARAM_RAW              0x00000002u ///< Suppress all open-related data exchange

 /** @} */

// ________________________________________________________________________________________________
//
// Host Specific
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Error Text
 *
 * Provides a pointer to a text description of the device status code.
 *
 * \param [in] rpcStatus   Pointer to a \ref phRpc_Status_t structure that comprises the status information.
 *
 * \return Error Text
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
uint8_t PH_RPC_H_LIBFUNC *phRpc_H_GetErrorText(phRpc_Status_t *rpcStatus);
/// \brief Function pointer declaration according to \ref phRpc_H_GetErrorText
typedef uint8_t* (*pphRpc_H_GetErrorText_t) (phRpc_Status_t*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Get Host Library Error Text
 *
 * Provides a pointer to a text description of the host status code.
 *
 * \param [in] rpcStatus   Pointer to a \ref phRpc_Status_t structure that comprises the status information.
 *
 * \return Error Text
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
uint8_t PH_RPC_H_LIBFUNC *phRpc_H_GetHostErrorText(phRpc_Status_t *rpcStatus);
/// \brief Function pointer declaration according to \ref phRpc_H_GetHostErrorText
typedef uint8_t* (*pphRpc_H_GetHostErrorText_t) (phRpc_Status_t*);

/**
 * \ingroup grp_rpc_host_acc
 * \brief Host I/O Control
 *
 * Use this I/O Control function to tweak the Host interface to the DUT.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      ctrlMj      Major control code, see \ref PH_RPC_IOCTL_MJ_HOST_SETTRSZMUL.
 * \param [in]      ctrlMn      Minor control code.
 * \param [in,out]  ctrlOpt     Optional control code and/or data. When a control operation requires
 *                              additional data this parameter is used. otherwise, it should be set
 *                              to NULL or to the address of a variable that contains 0.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_HostIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);
/// \brief Function pointer declaration according to \ref phRpc_H_HostIoCtl
typedef phRpc_H_Return_t (*pphRpc_H_HostIoCtl_t) (void*, uint8_t, uint8_t, uint32_t*);

// ________________________________________________________________________________________________
//
// Administrative Commands
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_adm
 * \brief Device DAQ access
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl             Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      daqAddr         Address of the item in the device to acquire or change.
 * \param [in]      daqSetLength    Length of the data to set in the device. If 0, the DAQ is read-only.
 * \param [in]      daqGetLength    Length of the data to get from the device.
 * \param [in,out]  daqData         DAQ data coming from and/or going to the device.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceDaq(void *hdl, uint32_t daqAddr, uint16_t daqSetLength, uint16_t daqGetLength, uint8_t **daqData);
/// \brief Function pointer declaration according to \ref phRpc_H_DeviceDaq
typedef phRpc_H_Return_t (*pphRpc_H_DeviceDaq_t) (void*, uint32_t, uint16_t, uint16_t, uint8_t**);

/**
 * \ingroup grp_rpc_host_adm
 * \brief Control Diagnostics
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in,out]  diagBuffer  Data to be sent to and received from the device. On return, the function sets
 *                              the pointer to the address of the location of the returned data.
 *                              If the pointer itself is NULL no data can be sent or returned. If the pointer
 *                              references NULL no data can be sent but data can be received.
 * \param [in,out]  diagLength  Pointer to a location that contains the number of bytes to be sent to the
 *                              device. On return the function sets the value referenced by the pointer to
 *                              the number of bytes actually received. If 0, nothing is sent to the device.
 * \param [in]      diagJob     Describes the type of diagnostic job, see \ref PH_RPC_CMD_CTRLDIAG_JOB_GET_VBOARD.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_CtrlDeviceDiag(void *hdl, uint8_t **diagBuffer, uint16_t *diagLength, uint8_t diagJob);
/// \brief Function pointer declaration according to \ref phRpc_H_CtrlDeviceDiag
typedef phRpc_H_Return_t (*pphRpc_H_CtrlDeviceDiag_t) (void*, uint8_t**, uint16_t*, uint8_t);

/**
 * \ingroup grp_rpc_host_adm
 * \brief Reboot the device and put it into the specified operating mode
 *
 * This command reboots the device after 1 second. Typically the command is
 * used to activate the Secondary Bootloader for Primary Firmware or Secondary
 * Firmware programming.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      mode        Device operating mode. Please refer to
 *                              \ref PH_RPC_CMD_CTRLDEVMODE_RESETCHECK_REBOOT for
 *                              information about the different modes.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_SetDeviceMode(void *hdl, uint8_t mode);
/// \brief Function pointer declaration according to \ref phRpc_H_SetDeviceMode
typedef phRpc_H_Return_t (*pphRpc_H_SetDeviceMode_t) (void*, uint8_t);

/**
 * \ingroup grp_rpc_host_adm
 * \brief Get Device Secondary Firmware Information
 *
 * Get information from the device. The information that can be queried comprises
 * firmware identification, run time data, operational state, stack watermarks etc.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      infoType    Type of information to be queried as defined, e.g. \ref PH_RPC_CMD_CTINFO_RUNNING .
 * \param [out]     infoNum     Information, represented by a number, returned by the device.
 * \param [out]     infoBuf     Pointer to an internal buffer that has received the information.
 * \param [in,out]  infoLen     Pointer to a variable that will be set to the actual number of bytes received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_GetDeviceCtInfo(void *hdl, uint8_t infoType, uint32_t *infoNum, uint8_t **infoBuf, uint8_t *infoLen);
/// \brief Function pointer declaration according to \ref phRpc_H_GetDeviceCtInfo
typedef phRpc_H_Return_t (*pphRpc_H_GetDeviceCtInfo_t) (void*, uint8_t, uint32_t*, uint8_t**, uint8_t*);

#ifndef SECFW_DOXY_SKIP //

// ________________________________________________________________________________________________
//
// Device Operation
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_adm
 * \brief EEPROM Command
 *
 * The device comprises an EEPROM. It can be accessed via this function.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      eeCmd       EEPROM command such as \ref PH_RPC_CMD_EE_READ_SEQ.
 * \param [in]      eeAddr      Address where to start the EE operation.
 * \param [in,out]  eeBuf       - For write operations, the function takes a pointer to a buffer that contains
 *                                the data to write. The function may change the pointer but the user must
 *                                not access the location the pointer references (usage: development only).
 *                              - For read operations the pointer provided to the function must be initialised
 *                                to the value NULL. On return, the function will set the pointer to the
 *                                address of the internal buffer where the data that has been read is stored.
 *                              .
 * \param [in,out]  eeLen       For read operations the variable that the pointer references must be
 *                              set to the number of bytes to read. The function returns through this
 *                              pointer the number of bytes that have been actually read, or for write
 *                              operations, same applies for the number of bytes written.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note As the function uses the internal buffer the user has to copy the read data to a safe place
 *       where it is not overwritten by the following operations.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_EE(void *hdl, uint8_t eeCmd, uint16_t eeAddr, uint8_t **eeBuf, uint8_t *eeLen);
/// \brief Function pointer declaration according to \ref phRpc_H_EE
typedef phRpc_H_Return_t (*pphRpc_H_EE_t) (void*, uint8_t, uint16_t, uint8_t**, uint8_t*);

/**
 * \ingroup grp_rpc_host_adm
 * \brief EEPROM Configuration Command
 *
 * The device comprises an EEPROM. Storage of configuration settings can be managed via this function.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      eeCmd       EEPROM command such as \ref PH_RPC_CMD_EE_AUTOLOAD_CFG.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_EECfg(void *hdl, uint8_t eeCmd);
/// \brief Function pointer declaration according to \ref phRpc_H_EECfg
typedef phRpc_H_Return_t (*pphRpc_H_EECfg_t) (void*, uint8_t);

#endif // SECFW_DOXY_SKIP

// ________________________________________________________________________________________________
//
// Secondary Firmware
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_ctrltstsw
 * \brief Start the Secondary Firmware
 *
 * If the firmware finds a valid image at the location of the secondary firmware it calls into the primary
 * function, the so-called \c Entry function. \c Entry executes the start code of the image and registers
 * all further entry points. On completion of the secondary firmware start this function returns. The
 * function on the device runs in deferred context via the Async Task.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      startParam  Parameter for the secondary firmware.
 * \param [out]     startStatus Result of the operation. See \ref PH_RPC_CMD_TESTSWCT_STATUS_SUCCESS.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_StartTestSw(void *hdl, uint32_t startParam, uint8_t *startStatus);
/// \brief Function pointer declaration according to \ref phRpc_H_StartTestSw
typedef phRpc_H_Return_t (*pphRpc_H_StartTestSw_t) (void*, uint32_t, uint8_t*);

/**
 * \ingroup grp_rpc_host_ctrltstsw
 * \brief Stop the Secondary Firmware
 *
 * The firmware tries to stop the secondary firmware. The secondary firmware may follow this request
 * or ask for more time to do so (e.g. wait for I/O timeouts to expire) or even deny it. In either case
 * the status is reported by this function. When the function has asked for more time to stop the test
 * software (\ref PH_RPC_CMD_TESTSWCT_STATUS_STOP_PENDING) the host must poll for the completion by
 * calling this function e.g. every 100ms until the secondary firmware.
 * The function on the device runs in deferred context via the Async Task.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      stopStatus  Result of the operation. See \ref PH_RPC_CMD_TESTSWCT_STATUS_SUCCESS.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note It is up to the secondary firmware to stop all threads, deallocate all objects and to restore all
 *       original interrupt handlers. Failing to do so will lead to malfunction. The host application needs
 *       to poll for completion of this function. Failing to stop the secondary firmware and returning a
 *       pending status will cause the host software to go into an endless polling loop.\n
 *       Therefore, if the secondary firmware cannot be stopped, it is recommended to deny the stop request.
 *       In this case the secondary firmware cannot be restarted but the host software will not enter an endless loop.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_StopTestSw(void *hdl, uint8_t *stopStatus);
/// \brief Function pointer declaration according to \ref phRpc_H_StopTestSw
typedef phRpc_H_Return_t (*pphRpc_H_StopTestSw_t) (void*, uint8_t*);

/**
 * \ingroup grp_rpc_host_ctrltstsw
 * \brief Send/Receive to/from the Secondary Firmware
 *
 * This function sends data to the secondary firmware. It waits for the Secondary Firmware to complete its operation. Upon
 * completion the function returns with the data the Secondary Firmware has filled into the specified buffer.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in,out]  xBuf        The caller has to provide a pointer to a valid location with data to send.
 *                              When the function returns, the pointer is set to the internal library
 *                              buffer that contains the received data. \b Caveat: For every call of the
 *                              function the pointer needs to be explicitly set to the location of the data to send.
 *                              Failing to do so before each call leads to malfunction.
 * \param [in,out]  txBufLen    Pointer to a variable that contains the number of bytes to send and that
 *                              receives the number of bytes that have actually been sent.
 * \param [in,out]  rxBufLen    Pointer to a variable that contains the maximum number of bytes to receive.
 *                              On return, it is set to the number of bytes that have actually been received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DataExchangeTestSw(void *hdl, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DataExchangeTestSw
typedef phRpc_H_Return_t (*pphRpc_H_DataExchangeTestSw_t) (void*, uint8_t**, uint16_t*, uint16_t*);

#ifndef SECFW_DOXY_SKIP //

// ________________________________________________________________________________________________
//
// DUT Operation
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Initialise Interface to DUT
 *
 * Initialise the I/O system that services the link between the device and the DUT.
 * Optionally a \ref phRpc_H_DevIoCtl call can be made to tweak selected operating parameters of the
 * host interface.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      hiFn        Host Interface Function Type, see \ref PH_RPC_CMD_DEV_ENABLE_I2C.
 * \param [in]      hiAddr      Bus address of the external device under test. For I2C, it may be the
 *                              selected device address, for SPI or HSU it should be zero. Only 7-bit I2C
 *                              addresses are supported.
 * \param [in]      hiSpeed     Data rate of the host interface.
 * \param [in]      hiClkPol    SPI Clock Polarity, see \ref PH_RPC_CMD_DEV_SPI_CPOL_L. Not applicable
 *                              for I2C, should be set to 0 in that case.
 * \param [in]      hiClkPha    SPI Clock Phase, see \ref PH_RPC_CMD_DEV_SPI_CPHA_1ST. Not applicable
 *                              for I2C, should be set to 0 in that case.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref phRpc_H_DevIoCtl or \ref phRpc_H_DutSetMinIOMode for ways to further control the I/O system behaviour.
 * \note It is allowed to call this function more than once in order to re-initialise the interface with
 *       other settings or in another mode.
 * \note If needed change the I2C address with I/O control code \ref PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS without
 *       re-initialisation.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutInit(void *hdl, uint8_t hiFn , uint8_t hiAddr, uint32_t hiSpeed, uint8_t hiClkPol, uint8_t hiClkPha);
/// \brief Function pointer declaration according to \ref phRpc_H_DutInit
typedef phRpc_H_Return_t (*pphRpc_H_DutInit_t) (void*, uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);

/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Get Interface mode for DUT
 *
 * The function allows to query the host interface mode and parameter setting that is currently in use.
 *
 * \param [in]      hdl    Device Handle as provided by \ref phRpc_H_Open.
 * \param [out]     hiMode Pointer to a variable that receives the interface mode.
 *                         See \ref PH_PN547DL_MODE_MASK or \ref grp_comps_pn547_common for how to
 *                         interpret the individual fields of this parameter. Look at the bit
 *                         \ref PH_PN547DL_EXPG to check whether the function has returned the basic
 *                         or extended mode information. The function alternates with each call between
 *                         the basic and the extended information.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note Call the function twice using a pointer to a temporary variable. Examine the \ref PH_PN547DL_EXPG
 *       bit and copy the value of the temporary variable to other variables, depending on the bit state.
 *       - If the bit is not set the basic mode has been returned
 *       - If the bit is set the extended mode has been returned.
 *       .
 *
 * \sa \ref grp_comps_pn547_common
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutGetMode(void *hdl, uint32_t *hiMode);
/// \brief Function pointer declaration according to \ref phRpc_H_DutGetMode
typedef phRpc_H_Return_t (*pphRpc_H_DutGetMode_t) (void*, uint32_t*);

/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Receive from the DUT
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [out]     rxBuf       The function will set the pointer referenced by this parameter to an
 *                              internally allocated buffer that has received the data from the external
 *                              device. In case of a communication error the pointer may become NULL:
 *                              Therefore the caller \b must \b check the pointer for \b NULL.
 * \param [in,out]  rxBufLen    Length of the RX buffer. The caller must specify the pointer to a variable
 *                              that will receive the number of bytes actually read from the DUT. Before calling
 *                              this function the variable must be set to the maximum number of bytes that
 *                              can be read, ranging up to a value of \ref PH_RPC_CMD_USER_DATA_BUFSIZE.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note The function can be used for event notification. Depending on the \b External \b Interrupt settings
 *       the function returns when there has been an external interrupt event. In order to determine why it has
 *       returned a call to \ref phRpc_H_GetLastError can be made.
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutRx(void *hdl, uint8_t **rxBuf, uint16_t *rxBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DutRx
typedef phRpc_H_Return_t (*pphRpc_H_DutRx_t) (void*, uint8_t**, uint16_t*);


/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Send to the DUT
 *
 * Send data to the external device and, where possible, return data that have been received in the
 * meantime. The underlying interface must be full-duplex in order to support simultaneous receiving.
 * For instance, a SPI interface is full-duplex while an I2C interface is not.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in,out]  txBuf       The caller has to provide a valid pointer to a buffer that contains the data
 *                              that shall be sent to the device. On return, the function will set the
 *                              pointer referenced by this parameter to an internally allocated buffer
 *                              that has received the data from the external device. Thus, for a new call of the
 *                              function the pointer needs to be set to the begin of the send buffer again.
 *                              In case of a communication error the pointer may become NULL:
 *                              Therefore the caller \b must \b check the pointer for \b NULL.
 * \param [in,out]  txBufLen    Length of the TX buffer. The caller must specify the pointer to a variable
 *                              that contains the number of bytes to send and that will receive the
 *                              number of bytes returned by the DUT.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \note Only full-duplex interfaces are able to receive data while sending data.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutTx(void *hdl, uint8_t **txBuf, uint16_t *txBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DutTx
typedef phRpc_H_Return_t (*pphRpc_H_DutTx_t) (void*, uint8_t**, uint16_t*);


/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Half-Duplex Send/Receive to/from the DUT
 *
 * This function is always half-duplex. It waits for the external DUT to complete its operation. Upon
 * external completion the function returns with the data the external DUT has sent in its reply. When
 * in underlying full-duplex mode (e.g. when SPI is active) the data that is simultaneously
 * returned (while sending the request to the external DUT) is discarded. Consequently, the data sent
 * to the external DUT in order to retrieve the response upon completion consists of padding bytes only.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in,out]  xBuf        - Provide a valid buffer with data to send as "Pointer to a buffer".
 *                              - When the function returns, the pointer is set to the internal
 *                                buffer that contains the received data. Thus, for a new call of the
 *                                function the pointer needs to be set to the begin of the send buffer again.
 *                              - In case of a communication error the pointer may become NULL:
 *                                Therefore the caller \b must \b check the pointer for \b NULL.
 *                              .
 * \param [in,out]  txBufLen    Pointer to a variable that contains the number of bytes to send and that
 *                              receives the number of bytes that have actually been sent.
 * \param [in,out]  rxBufLen    Pointer to a variable that contains the maximum number of bytes to receive,
 *                              up to \ref PH_RPC_CMD_USER_DATA_BUFSIZE.
 *                              On return, it is set to the number of bytes that have actually been received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE
 * \sa \ref grp_rpc_host_acc_fncall
 * \sa \ref grp_rpc_host_acc_iofn
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutTRx(void *hdl, uint8_t **xBuf, uint16_t *txBufLen, uint16_t *rxBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DutTRx
typedef phRpc_H_Return_t (*pphRpc_H_DutTRx_t) (void*, uint8_t**, uint16_t*, uint16_t*);

/**
 * \ingroup grp_rpc_host_dut_io
 * \brief Device I/O Control
 *
 * Use this I/O Control function to adjust device functionality.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      ctrlMj      Major control code, see e.g. \ref PH_RPC_IOCTL_MJ_DEV_LOOPBACK.
 * \param [in]      ctrlMn      Minor control code, see e.g. \ref PH_RPC_IOCTL_MN_DISABLE.
 * \param [in,out]  ctrlOpt     Optional control code and/or data. When a control operation requires
 *                              additional data this parameter is used. otherwise, it should be set
 *                              to NULL or to the address of a variable that contains the value
 *                              \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);
/// \brief Function pointer declaration according to \ref phRpc_H_DevIoCtl
typedef phRpc_H_Return_t (*pphRpc_H_DevIoCtl_t) (void*, uint8_t, uint8_t, uint32_t*);

/**
 * \ingroup grp_rpc_host_dut_io
 * \brief I/O Line Control
 *
 * Use this I/O Line Control function to control the DUT and peripheral functions.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      ctrlItem    Major control code, see e.g. \ref PH_RPC_IO_LINE_CTL_VEN.
 * \param [in]      ctrlAction  Minor control code, see e.g. \ref PH_RPC_IO_LINE_CTL_ACT_LOW.
 * \param [in,out]  ctrlOpt     Optional control parameter and/or data. When a control operation requires
 *                              additional data this parameter is used. otherwise, it should be set
 *                              to NULL or to the address of a variable that contains the value
 *                              \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DevIoLineCtl(void *hdl, uint8_t ctrlItem, uint8_t ctrlAction, uint32_t *ctrlOpt);
/// \brief Function pointer declaration according to \ref phRpc_H_DevIoLineCtl
typedef phRpc_H_Return_t (*pphRpc_H_DevIoLineCtl_t) (void*, uint8_t, uint8_t, uint32_t*);

// ________________________________________________________________________________________________
//
// Composite Commands
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_dut_composite
 * \brief Minimum I/O mode with alternate address (I2C only) and without interrupt handling
 *
 * This composite command comprises a set of calls to \ref phRpc_H_DevIoCtl.
 * The purpose of this function is to conveniently switch between an I2C node with full data link layer
 * support and another one that supports raw communication only. \n
 * On activation it will:
 * - Set an alternate address (I2C only)
 * - Deactivate external interrupt sensing
 * - Activate raw communication mode
 * - Deactivate all Data Link Layer features
 * .
 * Deactivation restores the settings that had been applied previous to activation.
 *
 * \note As it is possible to change individual settings again through \ref phRpc_H_DevIoCtl while in
 * this mode the user should be aware that the individually overwritten settings will be changed again
 * by this function on deactivation of this mode (restore previous, original settings).
 *
 * \param [in]      hdl             Device Handle as provided by \ref phRpc_H_Open.
 * \param [in,out]  altAddr         Pointer to a variable that stores the new I/O address (I2C). The
 *                                  new I/O address is applied while the address so far is returned
 *                                  via this parameter. The new content of the variable is therefore
 *                                  the old I/O address. This allows simple I/O address swap.
 * \param [in]      activationState Set to \c 1 for activation and \c 0 for deactivation.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DutSetMinIOMode(void *hdl, uint8_t *altAddr, uint8_t activationState);
/// \brief Function pointer declaration according to \ref phRpc_H_DutSetMinIOMode
typedef phRpc_H_Return_t (*pphRpc_H_DutSetMinIOMode_t) (void*, uint8_t*, uint8_t);

// ________________________________________________________________________________________________
//
// Test Commands
// ________________________________________________________________________________________________


/**
 * \ingroup grp_rpc_host_adm
 * \brief Communication Check
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      inBuf       Pointer to input buffer.
 * \param [in]      inBufLen    Length of input buffer.
 * \param [in]      msWait      How many ms the device shall wait to send back the response.
 * \param [out]     outBuf      Pointer that is set by the function and references the output buffer.
 * \param [out]     outBufLen   Pointer to a variable that receives the number of bytes received.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheck(void *hdl, uint8_t *inBuf, uint8_t inBufLen, uint8_t msWait, uint8_t **outBuf, uint8_t *outBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DeviceCommCheck
typedef phRpc_H_Return_t (*pphRpc_H_DeviceCommCheck_t) (void*, uint8_t*, uint8_t, uint8_t, uint8_t**, uint8_t*);

/**
 * \ingroup grp_rpc_host_adm
 * \copydoc phRpc_H_DeviceCommCheck
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheckLong(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint8_t msWait, uint8_t **outBuf, uint16_t *outBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DeviceCommCheckLong
typedef phRpc_H_Return_t (*pphRpc_H_DeviceCommCheckLong_t) (void*, uint8_t*, uint16_t, uint8_t, uint8_t**, uint16_t*);

/**
 * \ingroup grp_rpc_host_adm
 * \copydoc phRpc_H_DeviceCommCheck
 *
 * In contrast to the other Comm Check functions like \ref phRpc_H_DeviceCommCheckLong it is possible to
 * extend the waiting time such that the host communication protocol goes into a "waiting Time Extension"
 * mode. This mode is useful to extend I/O operations beyond any host timeout. Use this function to test
 * WTX from point to point.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_DeviceCommCheckWTX(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint16_t msWait, uint8_t **outBuf, uint16_t *outBufLen);
/// \brief Function pointer declaration according to \ref phRpc_H_DeviceCommCheckWTX
typedef phRpc_H_Return_t (*pphRpc_H_DeviceCommCheckWtx_t) (void*, uint8_t*, uint16_t, uint16_t, uint8_t**, uint16_t*);

#ifndef SECFW_DOXY_SKIP //
/** @} */
#endif // SECFW_DOXY_SKIP

#endif // SECFW_DOXY_SKIP

#ifdef __cplusplus
}
#endif

#endif // Guard

