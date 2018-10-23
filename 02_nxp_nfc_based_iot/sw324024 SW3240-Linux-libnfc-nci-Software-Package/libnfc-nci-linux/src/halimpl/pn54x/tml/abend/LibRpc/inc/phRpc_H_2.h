
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
* $Revision: 19533 $
* $Date: 2013-05-22 19:03:21 +0200 (Mi, 22 Mai 2013) $
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

#ifndef PHRPC_H_2_H
#define PHRPC_H_2_H

#ifndef SECFW_DOXY_SKIP //

#include "phRpc_H_Common.h"

#include <stdlib.h>

#endif // SECFW_DOXY_SKIP

#ifdef __cplusplus
extern "C"
{
#endif


// ________________________________________________________________________________________________
//
// DEFINITIONS
// ________________________________________________________________________________________________


// ________________________________________________________________________________________________
//
// Administrative Commands
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_adm_2
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
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DeviceDaq(void *hdl, uint32_t daqAddr, uint16_t daqSetLength, uint16_t daqGetLength, uint8_t **daqData);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DeviceDaq
typedef phRpc_H_Return_t (*pphRpc_2_H_DeviceDaq_t) (void*, uint32_t, uint16_t, uint16_t, uint8_t**);


// ________________________________________________________________________________________________
//
// DUT Operation
// ________________________________________________________________________________________________

/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief Initialise Interface to DUT
 *
 * Initialise the I/O system that services the link between the device and the DUT.
 * Optionally a \ref phRpc_H_DevIoCtl call can be made to tweak selected operating parameters of the
 * host interface.
 *
 * \param [in]      hdl             Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      interfaceSelect Host Interface Function Type. See \ref PH_RPC_2_CMD_DEV_ENABLE_SPI.
 * \param [in]      interfaceAddr   Bus address of the external device under test. For I2C, it may be the
 *                                  selected device address, for SPI or HSU it should be zero. Only 7-bit I2C
 *                                  addresses are supported.
 * \param [in]      interfaceSpeed  Data rate of the host interface.
 * \param [in]      interfaceClkPol SPI Clock Polarity, see \ref PH_RPC_2_CMD_DEV_SPI_CPOL_L
 * \param [in]      interfaceClkPha SPI Clock Phase see \ref PH_RPC_2_CMD_DEV_SPI_CPHA_1ST
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref phRpc_2_H_DevIoCtl for ways to further control the I/O system behaviour.
 * \note It is allowed to call this function more than once in order to re-initialise the interface with
 *       other settings or in another mode.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutInit(void *hdl, uint8_t interfaceSelect , uint8_t interfaceAddr, uint32_t interfaceSpeed, uint8_t interfaceClkPol, uint8_t interfaceClkPha);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DutInit
typedef phRpc_H_Return_t (*pphRpc_2_H_DutInit_t) (void*, uint8_t, uint8_t, uint32_t, uint8_t, uint8_t);

/**
 * \ingroup grp_rpc_host_dut_io2
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
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutGetMode(void *hdl, uint32_t *hiMode);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DutGetMode
typedef phRpc_H_Return_t (*pphRpc_2_H_DutGetMode_t) (void*, uint32_t*);

/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief Receive from the DUT
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      rxFlags     Flags that determine the behaviour of the function. See \ref PH_RPC_2_CMD_TRX_METACHAINING.
 * \param [out]     rxBuf       The function will set the pointer referenced by this parameter to an
 *                              internally allocated buffer that has received the data from the external
 *                              device. In case of a communication error the pointer may become NULL:
 *                              Therefore the caller \b must \b check the pointer for \b NULL.
 * \param [in,out]  rxBufLen    Length of the RX buffer. The caller must specify the pointer to a variable
 *                              that will receive the number of bytes actually read from the DUT. Before calling
 *                              this function the variable must be set to the maximum number of bytes that
 *                              can be read, ranging up to a value of \ref PH_RPC_2_CMD_USER_DATA_BUFSIZE.
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
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutRx(void *hdl, uint32_t *rxFlags, uint8_t **rxBuf, uint16_t *rxBufLen);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DutRx
typedef phRpc_H_Return_t (*pphRpc_2_H_DutRx_t) (void*, uint32_t*, uint8_t**, uint16_t*);


/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief Send to the DUT
 *
 * Send data to the external device and, where possible, return data that have been received in the
 * meantime. The underlying interface must be full-duplex in order to support simultaneous receiving.
 * For instance, a SPI interface is full-duplex while an I2C interface is not.
 *
 * \copydoc grp_rpc_host_acc_iofn_buffer
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      txFlags     Flags that determine the behaviour of the function. See \ref PH_RPC_2_CMD_TRX_METACHAINING.
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
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DutTx(void *hdl, uint32_t txFlags, uint8_t **txBuf, uint16_t *txBufLen);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DutTx
typedef phRpc_H_Return_t (*pphRpc_2_H_DutTx_t) (void*, uint32_t, uint8_t**, uint16_t*);

/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief Device I/O Control
 *
 * Use this I/O Control function to adjust device functionality.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      ctrlMj      Major control code, see e.g. \ref PH_RPC_2_IOCTL_MJ_DEV_LOOPBACK.
 * \param [in]      ctrlMn      Minor control code, see e.g. \ref PH_RPC_2_IOCTL_MN_DISABLE.
 * \param [in,out]  ctrlOpt     Optional control code and/or data. When a control operation requires
 *                              additional data this parameter is used. otherwise, it should be set
 *                              to NULL or to the address of a variable that contains the value
 *                              \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DevIoCtl(void *hdl, uint8_t ctrlMj, uint8_t ctrlMn, uint32_t *ctrlOpt);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DevIoCtl
typedef phRpc_H_Return_t (*pphRpc_2_H_DevIoCtl_t) (void*, uint8_t, uint8_t, uint32_t*);

/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief I/O Line Control
 *
 * Use this I/O Line Control function to control the DUT and peripheral functions.
 *
 * \param [in]      hdl         Device Handle as provided by \ref phRpc_H_Open.
 * \param [in]      ctrlItem    Major control code. See \ref PH_RPC_IO_LINE_CTL_VEN.
 * \param [in]      ctrlAction  Minor control code. See \ref PH_RPC_IO_LINE_CTL_ACT_LOW.
 * \param [in,out]  ctrlOpt     Optional control parameter and/or data. When a control operation requires
 *                              additional data this parameter is used. otherwise, it should be set
 *                              to NULL or to the address of a variable that contains the value
 *                              \ref PH_RPC_2_IO_LINE_CTL_OPT_NOT_APPLICABLE.
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DevIoLineCtl(void *hdl, uint8_t ctrlItem, uint8_t ctrlAction, uint32_t *ctrlOpt);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DevIoLineCtl
typedef phRpc_H_Return_t (*pphRpc_2_H_DevIoLineCtl_t) (void*, uint8_t, uint8_t, uint32_t*);

/**
 * \ingroup grp_rpc_host_dut_io2
 * \brief Get Transfer Log
 *
 * This function provides a log of the most recent transfers.
 *
 * \param[in]   hdl               Device Handle as provided by \ref phRpc_H_Open.
 * \param[in]   rxNotTx           Which log to get.
 * \param[in,out] numTransfers    In: Transfer to select. Out: How many transfers are stored.
 * \param[out]  transferData      First bytes of a transfer
 * \param[out]  transferLen       length of the actual transfer
 *
 * \return Status, see \ref PH_RPC_H_STATUS_OK.
 *
 * \sa \ref grp_rpc_host_acc_fncall
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_GetTransferLog(void *hdl, uint8_t rxNotTx, uint8_t *numTransfers, uint32_t *transferData, uint16_t *transferLen);
/// \brief Function pointer declaration according to \ref phRpc_2_H_GetTransferLog
typedef phRpc_H_Return_t (*pphRpc_2_H_GetTransferLog_t)(void*, uint8_t, uint8_t*, uint32_t*, uint16_t*);

// ________________________________________________________________________________________________
//
// Test Commands
// ________________________________________________________________________________________________


/**
 * \ingroup grp_rpc_host_dut_io2
 * \copydoc phRpc_H_DeviceCommCheck
 *
 * In contrast to the other Comm Check functions like \ref phRpc_H_DeviceCommCheckLong it is possible to
 * extend the waiting time such that the host communication protocol goes into a "waiting Time Extension"
 * mode. This mode is useful to extend I/O operations beyond any host timeout. Use this function to test
 * WTX from point to point.
 *
 */
phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_2_H_DeviceCommCheckWTX(void *hdl, uint8_t *inBuf, uint16_t inBufLen, uint16_t msWait, uint8_t **outBuf, uint16_t *outBufLen);
/// \brief Function pointer declaration according to \ref phRpc_2_H_DeviceCommCheckWTX
typedef phRpc_H_Return_t (*pphRpc_2_H_DeviceCommCheckWtx_t) (void*, uint8_t*, uint16_t, uint16_t, uint8_t**, uint16_t*);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // Guard

