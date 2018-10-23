/*
*                   Copyright (c), NXP Semiconductors
*
*                      (C)NXP Semiconductors
*        All rights are reserved. Reproduction in whole or in part is
*       prohibited without the written consent of the copyright owner.
*   NXP reserves the right to make changes without notice at any time.
*  NXP makes no warranty, expressed, implied or statutory, including but
*  not limited to any implied warranty of merchantability or fitness for any
* particular purpose, or that the use will not infringe any third party patent,
*  copyright or trademark. NXP must not be liable for any loss or damage
*                           arising from its use.
*/

/** \file
* Project: RPC Host Library Status Definitions / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 33279 $
* $Date: 2015-01-22 08:09:03 +0100 (jeu., 22 janv. 2015) $
*
* Created: Gerald Kersch-Koncar, March 2011
*
*/

#ifndef PHRPC_STATUS_H //
#define PHRPC_STATUS_H ///< \internal Guard

#ifndef PH_RPC_SKIP_STDINT
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // CPP

/**
 * \addtogroup grp_rpc_common
 * @{
 */

/**
 * \defgroup grp_rpc_common_pclib_status PC Library Status Codes
 *
 * PC library status codes are about host to device communication status (USB). No I/O status
 * (device to DUT) is indicated by these status values.
 *
 * @{
 */

/**
 * \brief PC library function return status
 * For documentation of the return status values see \ref PH_RPC_H_STATUS_OK.
 */
typedef uint8_t phRpc_H_Return_t;

/** \name Library Function Return values
 *
 * The library functions return status values are defined in this section.
 * \sa Return status type \ref phRpc_H_Return_t.
 *
 * @{
 */

#define PH_RPC_H_STATUS_OK                      0   ///< The operation was successful
#define PH_RPC_H_STATUS_INVALID_PARAMETER       1u  ///< One or more parameters are invalid
#define PH_RPC_H_STATUS_NOT_IMPLEMENTED         2u  ///< The function is not implemented
#define PH_RPC_H_STATUS_INVALID_HANDLE          3u  ///< The handle is invalid
#define PH_RPC_H_STATUS_DEVICE_IO               4u  ///< An I/O error or warning on the device has occurred.
#define PH_RPC_H_STATUS_FRAMING_ERROR           5u  ///< A communication framing error has occurred.
#define PH_RPC_H_STATUS_IO_TIMEOUT              6u  ///< A communication timeout error has occurred.
#define PH_RPC_H_STATUS_IO_LIBERROR             7u  ///< The I/O library or driver has malfunctioned.
#define PH_RPC_H_STATUS_OPEN_ERROR              8u  ///< The I/O library or driver could not be opened.
#define PH_RPC_H_STATUS_DATA_ERROR              9u  ///< The I/O library received invalid data.

/** @} */ // Name

/** \name Cancel Result
 * The function \ref phRpc_H_CancelIo indicates whether the I/O operation could be cancelled. It could
 * also mean that no operation at all was ongoing, because the cancel request was not submitted in time
 * and the I/O operation was able to complete normally.
 *
 * \note Always get the result of the I/O operation by calling the \b GetLastError function in order to
 *       determine whether the operation was actually cancelled in the device. In case that the I/O status
 *       being other than \ref PH_RPC_STATUS_W_CANCELED the data may be valid, depending on the status.
 * @{
 */

#define PH_RPC_CANCELRESULT_OK              0  ///< The I/O operation was cancelled or finished itself in time.
#define PH_RPC_CANCELRESULT_ERROR           1u ///< Error, no operation could be cancelled.

/** @} */ // Name

/** @} */ // PC Library Status Codes

/**
 * \defgroup grp_rpc_common_device_status Device I/O Status Codes
 *
 * Device I/O status codes are about device to external device-under-test communication.
 *
 * @{
 */

/**
 * \brief Device function status
 * For documentation of the return status values see \ref PH_RPC_STATUS_OK, \ref PH_RPC_STATUS_COMP_IO, and \ref PH_RPC_STATUS.
 */
typedef uint16_t phRpc_CommStatus_t;

/**
 * \brief Status definition for RPC Device commands.
 */
typedef struct phRpc_Status_s
{
    phRpc_CommStatus_t  CommStatusM;    ///< Status of the RPC function being called on the device.
    uint16_t            CommIncidents;  ///< Count of RPC communication incidents. This should normally remain zero.
    uint16_t            LastTx;         ///< Last number of bytes sent.
    uint16_t            LastRx;         ///< Last number of bytes received.
    phRpc_H_Return_t    PcLibStatus;    ///< Status of the RPC function being called on the host.
} phRpc_Status_t;

/**
 * \brief I/O System Data.
 *
 * Then using hook functions (\ref phRpc_H_SetHookF) the hook implementation can call \ref phRpc_H_GetHostInfo
 * in order to determine the underlying reason for the handler invocation. Care has to be taken to spend as
 * little as possible time and resources within the handler is order not to distort the timing behaviour of
 * the I/O system during such debug operations.
 *
 */
typedef struct phRpc_IoSystemData_s
{
    uint16_t    NumTx;  // Most recent number of bytes sent
    uint16_t    NumRx;  // Most recent number of bytes received
    uint8_t    *TxBuf;  // Points to the location used for the most recent transmission
    uint8_t    *RxBuf;  // Points to the location used for the most recent receive operation
    uint8_t     LocId;  // Where in the file the structure was last updated
} phRpc_IoSystemData_t;

/**
 * \name Device component and device error codes
 * See the function \ref phRpc_H_GetErrorText. It contains a LUT that transforms the code into text.
 *
 * @{
 */

/// The status composition macro encodes component ID and status value into a value of type uint16_t.
#define PH_RPC_STATUS(_comp, _st)    ((uint16_t)(((uint8_t)(_st)) | (((uint16_t)(_comp)) << 8))) //
/// Get the status value without component ID from a pointer to the \ref phRpc_Status_t structure.
#define PH_RPC_GET_STATUS(p_commStatus_) ((uint8_t)(p_commStatus_->CommStatusM))

#define PH_RPC_STATUS_COMP_VOID             0x00u   ///< No component specified
#define PH_RPC_STATUS_COMP_IO               0x01u   ///< The DUT I/O Component
#define PH_RPC_STATUS_COMP_TASKSYS          0x02u   ///< Multitasking System
#define PH_RPC_STATUS_COMP_IO_LINES         0x03u   ///< The DUT I/O Line Control Component
#define PH_RPC_STATUS_COMP_EE               0x04u   ///< EEPROM subsystem
#define PH_RPC_STATUS_COMP_INFO             0x05u   ///< Device Information
#define PH_RPC_STATUS_COMP_DIAG             0x06u   ///< Diagnostics
#define PH_RPC_STATUS_COMP_AD               0x07u   ///< Analogue/Digital I/O
#define PH_RPC_STATUS_COMP_2CH_ESE          0x20u   ///< Secondary Channel; ESE

#define PH_RPC_STATUS_OK                    0x00u   ///< Operation finished normally
#define PH_RPC_STATUS_E_INIT                0x01u   ///< An initialisation failed
#define PH_RPC_STATUS_E_TIMEOUT             0x02u   ///< An I/O operation timed out
#define PH_RPC_STATUS_W_LESS_DATA           0x03u   ///< The device sent/received less data than requested (e.g. due to a missing I2C ACK)
#define PH_RPC_STATUS_E_INVALID_PARAMETER   0x04u   ///< A parameter is not valid (e.g. out of range)
#define PH_RPC_STATUS_E_CRC                 0x05u   ///< CRC Error
#define PH_RPC_STATUS_E_INVALID_STATE       0x06u   ///< Invalid device state
#define PH_RPC_STATUS_E_HW_FAILURE          0x07u   ///< Hardware failure detected
#define PH_RPC_STATUS_E_OVERRUN             0x08u   ///< FIFO Overrun
#define PH_RPC_STATUS_E_FRAMING             0x09u   ///< Framing error
#define PH_RPC_STATUS_RESERVED_A            0x0Au   ///< Reserved
#define PH_RPC_STATUS_RESERVED_B            0x0Bu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_C            0x0Cu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_D            0x0Du   ///< Reserved
#define PH_RPC_STATUS_RESERVED_E            0x0Eu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_F            0x0Fu   ///< Reserved
#define PH_RPC_STATUS_E_BREAK               0x10u   ///< Break Condition
#define PH_RPC_STATUS_E_FIFOERR             0x11u   ///< FIFO Error
#define PH_RPC_STATUS_E_DMA                 0x12u   ///< DMA Error
#define PH_RPC_STATUS_E_TX_TIMEOUT          0x13u   ///< TX Timeout Error
#define PH_RPC_STATUS_E_BUFFER_TOO_SMALL    0x14u   ///< The provided buffer is too small to hold the response
#define PH_RPC_STATUS_E_DATA_LENGTH         0x15u   ///< Length error or mismatch in the received data
#define PH_RPC_STATUS_E_TX_ERROR            0x16u   ///< Error occurred during transmission
#define PH_RPC_STATUS_E_RX_ERROR            0x17u   ///< Error occurred during reception
#define PH_RPC_STATUS_E_DUT_ABORTED         0x18u   ///< The transfer has been aborted by the DUT, i.e. it was unable to complete the transfer
#define PH_RPC_STATUS_E_INVALID_HEADER      0x19u   ///< Invalid header or protocol control byte
#define PH_RPC_STATUS_RESERVED_1A           0x1Au   ///< Reserved
#define PH_RPC_STATUS_RESERVED_1B           0x1Bu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_1C           0x1Cu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_1D           0x1Du   ///< Reserved
#define PH_RPC_STATUS_RESERVED_1E           0x1Eu   ///< Reserved
#define PH_RPC_STATUS_RESERVED_1F           0x1Fu   ///< Reserved
#define PH_RPC_STATUS_E_INVALID_DESCRIPTOR  0x20u   ///< The descriptor is wrong, applicable for T=1 ATR or any other capability descriptor
#define PH_RPC_STATUS_W_RESYNC              0x21u   ///< An internal re-synchronization was done

#define PH_RPC_STATUS_E_INTERNAL            0xF8u   ///< An internal error has occurred
#define PH_RPC_STATUS_E_INVALID_REQ         0xF9u   ///< An invalid request has been issued
#define PH_RPC_STATUS_E_OTHER               0xFAu   ///< An other, unspecified error has occurred
#define PH_RPC_STATUS_W_CANCELED            0xFBu   ///< The I/O operation was cancelled

#define PH_RPC_STATUS_NONE                  0xFFu   ///< Not to be used as error code

/** @} */ // Name

/** @} */ // Group Device Status Codes

/**
 * @}
 */ // Group

#ifdef __cplusplus
}
#endif // CPP

#endif // Guard
