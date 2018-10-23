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
* Project: RPC Host Library Command and Data Field Definitions / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 33802 $
* $Date: 2015-02-11 09:01:32 +0100 (mer., 11 févr. 2015) $
*
* Created: Gerald Kersch-Koncar, March 2011
*
*/

#ifndef PHRPC_CMD_H //
#define PHRPC_CMD_H //

#ifdef __cplusplus
extern "C" {
#endif // CPP

/**
 * \defgroup grp_rpc_common_buffer_sizes  System Buffer Sizes and Definitions
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_DutRx
 * \copydoc phRpc_H_DutRx
 * \n \b Function: \ref phRpc_H_DutTx
 * \copydoc phRpc_H_DutTx
 * \n \b Function: \ref phRpc_H_DutTRx
 * \copydoc phRpc_H_DutTRx
 * \n \b Function: \ref phRpc_H_DataExchangeTestSw
 * \copydoc phRpc_H_DataExchangeTestSw
 *
 * @{
 */

// ________________________________________________________________________________________________
//
// Buffer Definitions
// ________________________________________________________________________________________________

/** \name User Buffer Definition
 *
 * The user buffer is internally allocated by the PC library and of a fixed size. Allocation is done
 * by \ref phRpc_H_Open.
 *
 * @{
 */

#define PH_RPC_H_MINDEVBUFLEN                           64u     ///< Minimum number of bytes to transfer
#define PH_RPC_CMD_PREPEND_LEN                          16u     ///< Reserved for further data encapsulation at endpoint

/** \brief Maximum Data size without prepended header for communication between device and DUT
 *
 * The maximum size of user data without any protocol header for the DUT. As a protocol for communication
 * between the device and the DUT is used data must be prepended. This length definition does not comprise the
 * length of prepended data.
 *
 * Functions: \ref phRpc_H_DutRx, \ref phRpc_H_DutTx, \ref phRpc_H_DutTRx, \ref phRpc_H_DataExchangeTestSw
 *
 */
 #define PH_RPC_CMD_USER_DATA_BUFSIZE                   1200u   //

/** \brief Maximum number of bytes available for the transfer (see \ref PH_RPC_CMD_RPCBUFFER_LEN)
 *
 *   Maximum number of bytes that the RPC functions can fill with user data.
 *   The user must be aware that this is the total number of bytes
 *   that may be transferred comprising all serialised data. The sum of the individual
 *   data field sizes to serialise must not become larger than this number.
 */
#define PH_RPC_CMD_USER_BUFSIZE                         (PH_RPC_CMD_USER_DATA_BUFSIZE+PH_RPC_CMD_PREPEND_LEN) //

/// \brief Maximum number of bytes that can be transferred (buffer size)
#define PH_RPC_CMD_RPCBUFFER_LEN                        (PH_RPC_CMD_USER_BUFSIZE+PH_RPC_H_MINDEVBUFLEN)


// TODO: [phESe related] These are ALSO used by secondary interface functions! Search for occurrences.
//                       Check if this is correct because it can easily introduce bugs!
#define PH_RPC_CMD_PAD_PLUS_1                               1u  ///< Add one extra byte for Linux
#define PH_RPC_CMD_VARIABLE_LEN_RPCBUF                      2u  ///< RPC serialisation shall use variable-length buffers
#define PH_RPC_CMD_PAD_MUL_MASK                    0x0000FF00u  ///< adding multiplier for Linux: size = N * \ref PH_RPC_H_MINDEVBUFLEN
#define PH_RPC_CMD_PAD_MUL_SHIFT                             8  ///< Position of the padding multiplier
#define PH_RPC_CMD_PAD_MUL_MAX                              10  ///< Minimum data size in multiples of a bulk size (maximum value allowed for the minimum size of the frame)
#define PH_RPC_CMD_RESET_FRAME_LEN                           6  ///< \internal Length of the Reset Frame
#define PH_RPC_CMD_RESET_FRAME                   {0,0,0,0,0,0}  ///< \internal RC Reset Frame

/** @} */

/** @} */ // Group

// ________________________________________________________________________________________________
//
// Timing
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_timing  Host I/O Timing
 * \ingroup grp_rpc_common
 *
 * @{
 */

#define PH_RPC_CMD_MIN_HOST_TIMEOUT_MILLISECONDS           40u  ///< Minimum USB timeout in ms.

/** @} */ // Timing


// ________________________________________________________________________________________________
//
// I/O Control
// ________________________________________________________________________________________________


/**
 * \defgroup grp_rpc_common_ioctl  I/O Control Codes
 * \ingroup grp_rpc_common
 * \n \b Function: \ref phRpc_H_HostIoCtl
 * \copydoc phRpc_H_HostIoCtl
 * \n \b Function: \ref phRpc_H_DevIoCtl
 * \copydoc phRpc_H_DevIoCtl
 *
 * @{
 */

/** \name Common I/O Control Definitions for Minor I/O Control Codes
 * Functions: \ref phRpc_H_DevIoCtl, \ref phRpc_H_HostIoCtl
 * @{
 */
#define PH_RPC_IOCTL_MN_DISABLE                ((uint8_t)0x00)  ///< Deactivate Feature
#define PH_RPC_IOCTL_MN_ENABLE                 ((uint8_t)0x01)  ///< Activate Feature
#define PH_RPC_IOCTL_MN_VOID                   ((uint8_t)0xFF)  ///< No minor code applicable
/** @} */

/** \name Common I/O Control Definitions Optional Parameter
 * Functions: \ref phRpc_H_DevIoCtl, \ref phRpc_H_HostIoCtl
 * @{
 */

#define PH_RPC_IOCTL_OPT_RESERVED_1               0x00000000u   ///< IOCTL Reserved value 1

/**
 * \brief I/O Control Not Available Value
 *
 * Within the host software, the value NULL is also allowed. The secondary firmware requires a valid address
 * of a variable containing the "not applicable" value, however.
 *
 */
#define PH_RPC_IOCTL_OPT_NOT_APPLICABLE           0xFFFFFFFFu   //

/** @} */

/** \name Host-Only I/O Control
 * \n \b Function: \ref phRpc_H_HostIoCtl
 * @{
 */
#define PH_RPC_IOCTL_MJ_HOST_SETTRSZMUL                 ((uint8_t)0x00)   ///< Transfer Size Multiplier: Limit the transfer size of the host library to \ref PH_RPC_H_MINDEVBUFLEN * opt bytes
#define PH_RPC_IOCTL_MJ_HOST_PROPAGATE_DEV_ERR_RETVAL   ((uint8_t)0x01)   ///< If set the return value of the PC library depends on the device status
#define PH_RPC_IOCTL_OPT_HOST_SETTRSZMUL_DEFAULT        0x0000000Fu       ///< Transfer Size Multiplier default value

/**
 * \brief Enable Fast Cancel (defunct)
 *
 * Performance of Cancel I/O has been increased. Fast Cancel is therefore obsolete.
 *
 */
#define PH_RPC_IOCTL_MJ_HOST_FAST_CANCEL                ((uint8_t)0x02) //

/** @} */

/** \name Device I/O Control
 *
 * Major Device I/O Control Codes.
 *
 * \note Some control codes have a \b NV attribute: This means that the setting can be stored in the
 * EEPROM of the board.
 *
 * \par Code Spaces
 * - 00..0F: USB Communication, RPC
 * - 10..3F: System, OS, Tasks
 * - 40..7F: I/O, Communication Mode, Parameters
 * - 80..FF: Reserved
 * .
 *
 * \n \b Function: \ref phRpc_H_DevIoCtl
 *
 * @{
 */

// ________________________________________________________________________________________________
// USB Communication, RPC

/**
 * \brief Set Transfer Size Multiplier
 *
 * Limit the transfer size of the device library. The lower the number the
 * more individual transfers have to be done. The default setting is optimised for almost all cases.
 * Use for debug or performance tweaking.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Transfer size in bytes = \ref PH_RPC_H_MINDEVBUFLEN * opt
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_SETTRSZMUL                  ((uint8_t)0x00) //

/**
 * \brief Reserved 01 (defunct PH_RPC_IOCTL_MJ_DEV_SET_SERIAL_HOST_MODE)
 * (The serial host interface can directly transmit to or receive data from the DUT.)
 * Functionality has been removed.
 */
#define PH_RPC_IOCTL_MJ_DEV_RESERVED_01                 ((uint8_t)0x01) //

// ________________________________________________________________________________________________
// System, OS, Tasks

/**
 * \brief System Supervisor default status indicator mode
 *
 * The System supervisor controls a status indicator LED for quick visual diagnosis.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: See \ref PH_RPC_IOCTL_OPT_DEV_SET_SSUPER_STI_NORMAL
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_SSUPER_STATUS_MODE      ((uint8_t)0x10) //

// ________________________________________________________________________________________________
// I/O, Communication Mode, Parameters

/**
 * \brief SPI/HSU Loop Back Control
 *
 * The SPI Loop Back Control enables the built-in diagnostic feature that echoes data sent via SPI and HSU.
 * Use this for diagnosis only, as the terminal to the external device is deactivated.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_LOOPBACK                    ((uint8_t)0x40) //


/**
 * \brief [NV] Auto-NSS
 *
 * SPI HW handles the SPI \c NSS line automatically. Switch to Software NSS by disabling this feature.
 * SW NSS keeps NSS low during the entire transfer regardless of CPHA and CPOL.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note When a DLL mode (\ref PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE) is active and the \c Raw \c Mode is
 * OFF (\ref PH_RPC_IOCTL_MJ_DEV_RAWMODE), the software also controls \c NSS regardless of
 * this setting.
 */
#define PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS                 ((uint8_t)0x41) //

/**
 * \brief [NV] Raw Mode Control
 *
 * In Raw Mode, no device specific data encapsulation is done. Data is sent as provided by the host.
 * The device does not prepend \c SOF bytes. This setting overrides \ref PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_RAWMODE                     ((uint8_t)0x42) //

/**
 * \brief [NV] Raw Mode Control - Deprecated: Use \ref PH_RPC_IOCTL_MJ_DEV_RAWMODE
 */
#define PH_RPC_IOCTL_MJ_DEV_I2C_SPI_RAWMODE             PH_RPC_IOCTL_MJ_DEV_RAWMODE //

/**
 * \brief Pad Write Buffer for SPI Read operations
 *
 * For SPI Read, an underlying full duplex communication takes place.
 * This option allows to pad the unused Write buffer.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: Low byte specifies the pad data
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_SPI_FILL_WRBUF_ON_RD        ((uint8_t)0x43) //

/**
 * \brief [NV] External Interrupt Sensing Mode/Type
 *
 * Set the sensing mode and type {Level H/L, Edge R/F} for External Interrupt
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Sense settings see \ref PH_RPC_IOCTL_OPT_EINT_SENSE_LEVEL_L and others
 * .
 * \note    This command changes interrupt sensing mode only. In order to activate or deactivate
 *          interrupt sensing please use \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE.
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE              ((uint8_t)0x44) //

/**
 * \brief [NV] External Interrupt Timeout
 *
 * Set the timeout period of the external interrupt, in ms.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Timeout, in ms. The value range is 16 bit (64K). The value
 *        \ref PH_RPC_IOCTL_OPT_EINT_TIMEOUT_INFINITE means infinite waiting time. Use this for
 *        DUT debug sessions only in order to halt the DUT for arbitrary time.
 *        It is not recommended to use infinite waiting time in an automatic test setup.
 * .
 *
 * \note There is no lower limit of the timeout value. Even a value of 0 is accepted. If the timeout value
 *       is too low the system may experience false timeout conditions. Care must be taken to select proper values.
 *       The value 0 has no specific meaning.
 *
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT            ((uint8_t)0x45) //

/**
 * \brief External Interrupt Test Mode Control
 *
 * External interrupt test mode is useful to debug hardware. It is not intended to be used for any other
 * purpose. The System Supervisor LED flashes on each interrupt. The interrupt sense settings are used
 * as previously applied by \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE. The interface to the DUT is
 * deactivated.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_EINT_TESTMODE           ((uint8_t)0x46) //

/**
 * \brief [NV] Control the Data Link Layer Mode
 *
 * The Data Link Layer mode to set with this code determines how the behaviour I/O system. This setting
 * is overridden by \ref PH_RPC_IOCTL_MJ_DEV_RAWMODE but overrides \ref PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS.
 * Please see those codes for further information.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NONE and others
 * .
 * \note \ref PH_RPC_IOCTL_MJ_DEV_RAWMODE must be deactivated, furthermore it is recommended
 *       to disable \ref PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS in SPI mode as well.
 * \note Moreover an activation of PH_RPC_IOCTL_MJ_DEV_RAWMODE while in DLL mode will cause the
 *       device to temporarily leave DLL mode. On deactivation of the raw mode, DLL mode is entered again.
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE                 ((uint8_t)0x47) //

/**
 * \brief Convert the current I2C address to PN547 format
 *
 * An arbitrary 7 bit I2C address can be set via the I/O control code \ref PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS.
 * This code converts the I2C address into a valid PN547 address.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_MASK_I2C_ADDRESS_PN547      ((uint8_t)0x48) //

/**
 * \brief [NV] Set the I2C Address
 *
 * Sets the I2C address only and leaves all other settings as they are. Moreover the address set to far
 * is returned.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: In: New address. Out: Address that had been set so far.
 * .
 * \note The function can be used to conveniently switch between two I2C addresses. The I/O lines for
 *       address selection are not changed (use \ref PH_RPC_IOCTL_MJ_DEV_I2C_SET_ADDRSEL for address select
 *       line control).
 */
#define PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS             ((uint8_t)0x49) //

/**
 * \brief [NV] Force Read Despite Timeout
 *
 * Forces the I/O layer to continue the operation even after an external interrupt timeout.
 * The default behaviour is to cancel the I/O operation when an error has occurred. This code allows,
 * mainly for debug purpose, to ignore I/O timeout conditions.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note It is not recommended to use this in an automatic setup. When the external interrupt is not
 *       triggered in time the operation should rather be cancelled than continued.
 */
#define PH_RPC_IOCTL_MJ_DEV_FORCE_READ_ON_EXT_TIMEOUT   ((uint8_t)0x4A) //

/**
 * \brief [NV] Enables/disables Deadline Monitoring on the Asynchronous Worker Task
 *
 * The I/O system operates within a worker task. This task allows for long I/O operations. The default
 * setting deactivates the deadline monitoring on the worker task. This code allows to enable it.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note Deadline monitoring on the asynchronous task means that a non-responding software or external
 *       device may cause a watchdog reset.
 * \note The external interrupt timeout (code \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT) should be less
 *       than the task deadline (code \ref PH_RPC_IOCTL_MJ_DEV_ASYN_TASK_MONITOR_TIMEOUT) in order to
 *       avoid watchdog resets when an I/O operation times out.
 */
#define PH_RPC_IOCTL_MJ_DEV_ENABLE_ASYN_TASK_MONITOR    ((uint8_t)0x4B) //

/**
 * \brief [NV] Set the Completion Deadline for the Asynchronous Worker Task
 *
 * I/O operations take place in the context of the worker task. As I/O operations can take from very
 * short to very long time it is possible to use this function to twaek the deadline.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Timeout value, in ms, for the asynchronous task. The value must not be less than 1000.
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_ASYN_TASK_MONITOR_TIMEOUT   ((uint8_t)0x4C) //

/**
 * \brief [NV] Activate or Deactivate External Interrupt Sensing
 *
 * Controls the automatic external interrupt sensing. For special I/O operations the external Interrupt line
 * may not be needed. In order to avoid an interrupt timeout on every I/O use this code. The default setting
 * is ON.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note The following applies for external interrupt sensing:
 *       -  \b Avoid \b Race \b Conditions: For normal I/O operations where an external device indicates
 *          data to be present by applying a certain level to the IRQ line it is not recommended to deactivate
 *          interrupt sensing. A race condition that may disrupt the external device could be the consequence.
 *          However, when an external device must be polled for data presence it is preferable to deactivate
 *          external interrupt sensing.
 *       -  \b Sense \b Settings: The interrupt sense settings are used as previously applied by
 *          \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE.
 *       -  \b Host \b Based \b Operation: When the host decides to sense external interrupt events
 *          (using \ref PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ) automatic sensing has to be switched OFF.
 *       -  Secondary Firmware Notification Callback (\ref phCtApi_RegisterNotificationCallback and related):
 *          For usage of the external Interrupt directly in the Secondary Firmware the interrupt sensing
 *          in the I/O system has to be disabled (\ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE / \ref PH_RPC_IOCTL_MN_DISABLE).
 *       .
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE, \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT,
 *      \ref PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ, \ref PH_RPC_IOCTL_MJ_DEV_IRQ_FILTER
 */
#define PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE           ((uint8_t)0x4D) //

/**
 * \brief [NV] Activate or Deactivate CRC Calculation
 *
 * Controls the CRC calculation. The default setting is OFF. A CRC16 is calculated with the PN547
 * default values. \b Caution: The CRC is not calculated over the entire data. In DLL mode, the length
 * field is excluded and so are prepended (SOF) bytes.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE                  ((uint8_t)0x4E) //

/**
 * \brief [NV] Activate or Deactivate Immediate I2C Transfer
 *
 * Controls the I2C behaviour. The default setting is OFF. When active, the I2C TRx command is not a
 * composite of Tx, Wait for Interrupt, and RX; Instead a full/atomic I2C transfer without intermediate
 * Stop/Start condition is done.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note Use for debug or special I/O only. Not to be used for Data link layer I/O (DLL mode).
 */
#define PH_RPC_IOCTL_MJ_DEV_I2C_ATOMIC_TRX_ENABLE       ((uint8_t)0x4F) //

/**
 * \brief Set I2C Address Select Lines
 *
 * Controls the I2C address behaviour. The default setting is 0. Moreover the address set to far
 * is returned.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_00 and others
 * .
 * \note The function allows to conveniently swap address line settings. The I2C address in the control
 *       byte is not changed (use \ref PH_RPC_IOCTL_MJ_DEV_SET_I2C_ADDRESS to change the control byte content).
 */
#define PH_RPC_IOCTL_MJ_DEV_I2C_SET_ADDRSEL             ((uint8_t)0x50) //

/**
 * \brief [NV] Control Adding/Discarding the RX SOF Byte for SPI/HSU when not in RAW Mode
 *
 * This code configures the LPC firmware to en-/disable discarding of the SOF byte of a received package.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note By default, the board handles SOF
 */
 #define PH_RPC_IOCTL_MJ_DEV_RX_SOF_ENABLE              ((uint8_t)0x51) //

/**
 * \brief [NV] Enable/Disable the TX SOF Byte for SPI/HSU when not in RAW Mode
 *
 * The firmware can automatically add a byte to the beginning of the data to be sent.
 * When the firmware (and not the host) calculates the CRC the prepended bytes is not included in the calculation.
 * For entirely host-provided data (including prepended TX bytes) the CRC calculation in the firmware must be
 * switched off.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_CRC_ENABLE, \ref PH_RPC_IOCTL_MJ_DEV_TX_SOF_MODE
 * \note By default, the board handles SOF
 */
 #define PH_RPC_IOCTL_MJ_DEV_TX_SOF_ENABLE              ((uint8_t)0x52) //

/**
 * \brief [NV] Set the Logical ID of the LPC Board for Multi-Device Operation
 *
 * Sets the logical ID of the board for multi-device operation. The Logical ID is an alternative
 * to \ref PH_RPC_CMD_DEVINFO_CPUSNR. The assigned device ID can be retrieved with the command
 * \b GetDeviceInfo using \ref PH_RPC_CMD_DEVINFO_LOGICAL_ID.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: The new 8-bit ID in the LSB is provided via this parameter. Upon completion, the function
 *        returns the previous ID. A value of \b 0xFF should \b not be used as it is the default value
 *        that is applied by the LPC firmware when no data set could be loaded from the EEPROM.
 * .
 *
 * \note The device will persist its logical ID together with the EEPROM data. Storage of EEPROM data
 *       is no automatic process, it requires the command \b EECfg. The ID is however loaded
 *       automatically regardless of the load settings of the LPC board firmware, i.e. even if the
 *       auto-load action is disabled.
 */
 #define PH_RPC_IOCTL_MJ_DEV_SET_LOGICAL_ID             ((uint8_t)0x53) //

 /**
 * \brief [NV] Set HSU Hardware Control Flow Enable State
 *
 * This code configures the LPC firmware to en-/disable HSU Hardware Control Flow.
 * \b Both RTS and CTS are enabled for automatic action. In order to enable CTS
 * automatic action only (and RTS being static and asserted during receive) use
 * the code \ref PH_RPC_IOCTL_MJ_DEV_HW_CTL_FLOW_CTS.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note By default, Hardware Control Flow is switched OFF
 */
 #define PH_RPC_IOCTL_MJ_DEV_HW_CTL_FLOW                ((uint8_t)0x54) //

/**
 * \brief [NV] Set Full Duplex Enable State
 *
 * This code configures the LPC firmware to en-/disable SPI/HSU Full Duplex mode.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note By default, Full Duplex mode is switched ON for HSU and for SPI.
 */
 #define PH_RPC_IOCTL_MJ_DEV_FULL_DUPLEX_ENABLE         ((uint8_t)0x55) //

/**
 * \brief [NV] Set Device Speed
 *
 * This code configures the device speed any time after device interface initialisation.
 * Use \ref PH_RPC_IOCTL_MJ_DEV_GET_SPEED to read back the speed setting.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Communication speed [baud]
 * .
 *
 * \note The setting can only be applied if one of the interfaces has been initialised.
 */
 #define PH_RPC_IOCTL_MJ_DEV_SET_SPEED                  ((uint8_t)0x56) //

/**
 * \brief Wait Function
 *
 * Waits at least for the number of ms specified by the Opt parameter, ranging from 1 to 1000.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Time to wait [ms]
 * .
 *
 * \note Due to host communication the actual time will be typically 2..3 ms longer. The function
 *       can not be used to generate accurate host timings, but it works where minimum timings are
 *       required.
 */
 #define PH_RPC_IOCTL_MJ_DEV_WAIT                       ((uint8_t)0x57) //

/**
 * \brief Get IRQ Input Level
 *
 * Reads the logical level at the IRQ input.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Output only: IRQ Level
 * .
 * \note The Function does not block until an interrupt occurs.
 *
 */
 #define PH_RPC_IOCTL_MJ_DEV_GET_IRQLVL                 ((uint8_t)0x58) //

/**
 * \brief Wait for External Interrupt Event
 *
 * Waits for external interrupt event to occur. This requires the I/O system to be initialised. See the function
 * \ref phRpc_H_DutInit.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note The function blocks until an interrupt occurs, the device times out or the I/O operation is cancelled.
 *       Automatic external interrupt sensing for I/O \b must be switched OFF to be able to use this function:
 *       See \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE.
 */
 #define PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ                   ((uint8_t)0x59) //

/**
 * \brief Suspend Read at Number Of Bytes Transferred
 *
 * Suspend the I/O Read operation at the specified number of bytes transferred. Suspending is effective only when the
 * I/O system is in DLL mode, and RAW communication is turned OFF (\ref PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE).
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Byte number to pause at
 * .
 *
 * \note The interruption of the transfer works at a byte number greater than the protocol header
 *       length, i.e. when NCI is selected the minimum value is 4.
 */
 #define PH_RPC_IOCTL_MJ_DEV_SUSPEND_R_AT_BYTE          ((uint8_t)0x5A) //

/**
 * \brief Suspend Read Waiting Time
 *
 * Suspend the I/O Read operation at the specified number of bytes transferred for the specified time.
 * See \ref PH_RPC_IOCTL_MJ_DEV_SUSPEND_R_AT_BYTE.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Waiting time in µs
 * .
 */
 #define PH_RPC_IOCTL_MJ_DEV_SUSPEND_R_TIME             ((uint8_t)0x5B) //

/**
 * \brief Get Device Speed
 *
 * This code returns the device interface speed. Please note that the returned speed may
 * considerably deviate from the speed set during initialisation or via the code
 * \ref PH_RPC_IOCTL_MJ_DEV_SET_SPEED. This is because the interface hardware with
 * its peripheral clock frequency and prescalers, divide and multiply registers
 * does not support every speed setting.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[out]: Communication speed [baud]
 * .
 *
 * \note The returned value is only valid if the interfaces has been initialised.
 */
 #define PH_RPC_IOCTL_MJ_DEV_GET_SPEED                  ((uint8_t)0x5C) //

/**
 * \brief [NV] Set HSU Hardware Control Flow CTS-Only State
 *
 * This code configures the LPC firmware to en-/disable CTS-Only HSU Hardware Control Flow.
 * \b Only CTS is enabled for automatic action. In order to enable CTS and RTS
 * automatic action use the code \ref PH_RPC_IOCTL_MJ_DEV_HW_CTL_FLOW.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note By default, Hardware Control Flow is switched OFF
 * \note On disable this command switches OFF control flow completely (RTS and CTS).
 */
 #define PH_RPC_IOCTL_MJ_DEV_HW_CTL_FLOW_CTS            ((uint8_t)0x5D) //

/**
 * \brief [NV] Set HSU EOF Character Count
 *
 * Configures the HSU EOF \b character count. A frame ends when the line is idle for a cerain time, i.e. number of
 * characters at a given speed. The number of characters is set by this IOCTL.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Number of bytes that the line must be idle to create an EOF condition
 * - Opt[out]: Previous value
 * .
 */
 #define PH_RPC_IOCTL_MJ_DEV_HSU_EOF_N_BYTES            ((uint8_t)0x5E) //

/**
 * \brief [NV] Set HSU Format
 *
 * Configures the HSU data format. The default setting is 8 data bits, no parity, 1 stop bit.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Format code, see \ref PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_5.
 * - Opt[out]: Previous value
 * .
 *
 */
 #define PH_RPC_IOCTL_MJ_DEV_HSU_FORMAT                 ((uint8_t)0x5F) //

/**
 * \brief Get last CRC
 *
 * Get the most recent CRC that has been calculated and received. The TX and RX CRC is packed into the opt parameter.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Format code, see \ref PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_5.
 * - Opt[out]: The last CRC pair. The lower two bytes contain the generated CRC for TX, the upper two
 *             bytes are filled with the received CRC.
 * .
 */
 #define PH_RPC_IOCTL_MJ_DEV_GET_LAST_CRC               ((uint8_t)0x60) //

/**
 * \brief Set the number of TX prepend bytes and the prepend behaviour
 *
 * For some configurations, the number of TX prepend bytes shall be configurable.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: Number of bytes to prepend, see \ref PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_1_STEP_1.
 * .
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_TX_SOF_ENABLE.
 *
 * \note Please see the individual version's release notes for availability of the feature.
 *       Check last error returned (through \ref phRpc_H_GetLastError) to see whether the command
 *       has been accepted.
 *
 */
 #define PH_RPC_IOCTL_MJ_DEV_TX_SOF_MODE                ((uint8_t)0x61) //

/**
 * \brief Set IRQ Filter
 *
 * Allows the IRQ input signal to be filtered. Short glitches of a duration less than a microsecond are suppressed.
 * This function only works if the IRQ sense mode is set to LEVEL (\ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE).
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE, \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE,
 * \note This function is enabled by default.
 */
 #define PH_RPC_IOCTL_MJ_DEV_IRQ_FILTER                 ((uint8_t)0x62) //

/**
 * \brief Get Pseudo Random Value
 *
 * Provide a pseudo random value. The seed comprises input from various internal computation processes and is
 * updated frequently.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Not used
 * - Opt[out]: Pseudo random value
 * .
 */
 #define PH_RPC_IOCTL_MJ_DEV_RND                        ((uint8_t)0x63) //

/**
 * \brief SOF Check for TX command
 *
 * Set whether the I/O system shall check SOF byte content returned via a SPI I/O operation.
 * This works only in data link layer mode (\ref PH_RPC_IOCTL_MJ_DEV_SET_DLLMODE) and not
 * in raw mode. The default setting is ON.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: The low byte contains the new SOF value.
 * .
 */
 #define PH_RPC_IOCTL_MJ_DEV_SOFCHECK_TX                ((uint8_t)0x64) //

/**
 * \brief Get IRQ filter count
 *
 * Gets the value of a counter that increments on ignored IRQ events (glitches). Some boards exhibit
 * a high level of noise on the control lines under specific conditions (e.g. test rig, long cables, ground loops
 * due to attached oscilloscope, etc.).
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt[in]: Not used
 * - Opt[out]: Counter Value
 * .
 *
 * \note The LPC resets the counter on I/O system initialisation, i.e. when the interface mode is set.
 *
 */
 #define PH_RPC_IOCTL_MJ_DEV_GET_IRQ_FLT_COUNT          ((uint8_t)0x65) //


/** @} */ // Dev IOCTL

/** \name Device I/O Control Opt: DLL Mode
 *
 * Optional parameter settings for Data Link Layer mode.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NONE           0x00000000u     ///< No Data Link Layer Mode support, but SOF padding still available
#define PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_DNLD           0x00000001u     ///< Download Mode support
#define PH_RPC_IOCTL_OPT_DEV_SET_DLLMODE_NCI            0x00000002u     ///< NCI Mode support
/** @} */

/** \name Device I/O Control Opt: DLL Mode
 *
 * Optional parameter settings for serial host interface.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_DEV_SERIAL_HOST_MODE_RPC       0x00000000u     ///< Serial host interface supports the RPC protocol
#define PH_RPC_IOCTL_OPT_DEV_SERIAL_HOST_MODE_DNLD      0x00000001u     ///< Serial host interface supports Download Mode
#define PH_RPC_IOCTL_OPT_DEV_SERIAL_HOST_MODE_NCI       0x00000002u     ///< Serial host interface supports NCI
/** @} */

/** \name Device I/O Control Opt: External Interrupt Sense Mode
 *
 * Sense mode and type of the external interrupt input.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_EINT_SENSE_LEVEL_L             0x00000001u     ///< External Interrupt sense Type: Low Level
#define PH_RPC_IOCTL_OPT_EINT_SENSE_LEVEL_H             0x00000002u     ///< External Interrupt sense Type: High Level
#define PH_RPC_IOCTL_OPT_EINT_SENSE_EDGE_F              0x00000003u     ///< External Interrupt sense Type: Falling Edge
#define PH_RPC_IOCTL_OPT_EINT_SENSE_EDGE_R              0x00000004u     ///< External Interrupt sense Type: Rising Edge
/** @} */

/** \name Device I/O Control Opt: External Interrupt Timeout
 *
 * Timeout Setting for the external interrupt input.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_EINT_TIMEOUT_INFINITE          0x0000FFFFu     ///< External Interrupt Timeout set to INFINITE
/** @} */

/** \name Device I/O Control Opt: Transfer Size Multiplier
 *
 * The USB transfer size multiplier default setting is as shown within this section. It is possible to change
 * it for debug- or performance tweaking purpose. However it is recommended not to change it as it is
 * optimised for fast I/O and low latency.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_DEV_SETTRSZMUL_DEFAULT         0x0000000Cu     ///< Transfer Size Multiplier default value

/** @} */

/** \name Device I/O Control Opt: System Supervisor Status Indicator Setting
 *
 * The System Supervisor switches a LED to to allow quick diagnosis. For debug purpose it may be useful
 * to change the setting.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_DEV_SET_SSUPER_STI_NORMAL      0x00000001u     ///< System Supervisor default status indicator mode
#define PH_RPC_IOCTL_OPT_DEV_SET_SSUPER_STI_WDFEED      0x00000002u     ///< System Supervisor watchdog feed indicator mode
#define PH_RPC_IOCTL_OPT_DEV_SET_SSUPER_STI_MAIN        0x00000003u     ///< System Supervisor main task indicator mode
/** @} */

/** \name Device I/O Control Opt: I2C Address Select Setting
 *
 * Set the I2C address selection line state.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_00         0x00000000u     ///< I2C address 00
#define PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_01         0x00000001u     ///< I2C address 01
#define PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_10         0x00000002u     ///< I2C address 10
#define PH_RPC_IOCTL_OPT_DEV_I2C_SET_ADDRSEL_11         0x00000003u     ///< I2C address 11
/** @} */

/** \name Device I/O Control Opt: UART data format
 *
 * Defines the UART data format. The format must be a logical OR combination of the fields for
 * data bits, stop bit, parity enable, and parity select. See IOCTL code \ref PH_RPC_IOCTL_MJ_DEV_HSU_FORMAT.
 *
 * @{
 */
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_5          0x00u           ///< 5 data bits
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_6          0x01u           ///< 6 data bits
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_7          0x02u           ///< 7 data bits
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_8          0x03u           ///< 8 data bits
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_MASK       0x03u           ///< \internal Masks data bit field
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_DATABITS_SHIFT          0           ///< \internal Offset of the data bits field

#define PH_RPC_IOCTL_OPT_HSU_FORMAT_STOPBIT_1           0x00u           ///< 1 stop bit
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_STOPBIT_2           0x04u           ///< 2 stop bits
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_STOPBIT_MASK        0x04u           ///< \internal Masks stop bit field
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_STOPBIT_SHIFT           1           ///< \internal Offset of stop bit field

#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_DISABLE      0x00u           ///< Disable parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_ODD          0x08u           ///< Select odd parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_EVEN         0x18u           ///< Select even parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_STICK_1      0x28u           ///< Select forced 1 parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_STICK_0      0x38u           ///< Select forced 0 parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_MASK         0x38u           ///< \internal Masks field for enable parity
#define PH_RPC_IOCTL_OPT_HSU_FORMAT_PARITY_SHIFT            3           ///< \internal Enable parity field offset

/** @} */

/** \name Device I/O Control Opt: SOF Bytes
 *
 * SOF settings: If more than one byte needs to be prepended automatically, these definitions shall be
 * used to put together the content of the optional parameter. See \ref PH_RPC_IOCTL_MJ_DEV_TX_SOF_MODE.
 * Stepping means in this context: Send first step data anyway, only in second step activate the LPC CTS flow.
 *
 * @{
 */

#define PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_1              0x01u           ///< Prepend 1 byte more
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_MASK           0x0Fu           ///< \internal Mask value for the number
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_SHIFT              0           ///< \internal Shift value for the number

#define PH_RPC_IOCTL_OPT_HSU_PREPEND_STEP_1             0x10u           ///< Step after 1 byte
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_STEP_MASK          0xF0u           ///< \internal Mask value for the number
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_STEP_SHIFT             4           ///< \internal Field offset for the number

/// Add one extra byte that is sent anyway
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_1_STEP_1       (PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_1 | PH_RPC_IOCTL_OPT_HSU_PREPEND_STEP_1) //

/// Add no extra byte, switch feature off
#define PH_RPC_IOCTL_OPT_HSU_PREPEND_ADD_0                  0           //

 /** @} */

/** @} */ // IOCTL Group


// ________________________________________________________________________________________________
//
// I/O Line Control
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_iolnctl  I/O Line Control Codes
 * \ingroup grp_rpc_common
 * \n \b Function: \ref phRpc_H_DevIoLineCtl
 * \copydoc phRpc_H_DevIoLineCtl
 *
 * @{
 */

/** \name Common I/O Line Control Definitions for Action Control Codes
 * \n \b Function: \ref phRpc_H_DevIoLineCtl
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_ACT_OFF              ((uint8_t)0x00)             ///< Deprecated: Switch OFF (logical LOW)
#define PH_RPC_IO_LINE_CTL_ACT_ON               ((uint8_t)0x01)             ///< Deprecated: Switch ON (logical HIGH)
#define PH_RPC_IO_LINE_CTL_ACT_LOW              PH_RPC_IO_LINE_CTL_ACT_OFF  ///< Switch to logical LOW ("OFF")
#define PH_RPC_IO_LINE_CTL_ACT_HIGH             PH_RPC_IO_LINE_CTL_ACT_ON   ///< Switch to logical HIGH ("ON")
#define PH_RPC_IO_LINE_CTL_ACT_PULSE            ((uint8_t)0x02)             ///< Create a Pulse of a specific duration
#define PH_RPC_IO_LINE_CTL_ACT_SET              ((uint8_t)0x03)             ///< Apply new setting (via the opt parameter)
#define PH_RPC_IO_LINE_CTL_ACT_GET              ((uint8_t)0x04)             ///< Get the current state / setting (via the opt parameter)
#define PH_RPC_IO_LINE_CTL_ACT_AUTO             ((uint8_t)0x05)             ///< Automatic action
#define PH_RPC_IO_LINE_CTL_ACT_ENABLE_F         ((uint8_t)0x06)             ///< Alternate function only: Enable.
#define PH_RPC_IO_LINE_CTL_ACT_DISABLE_F        ((uint8_t)0x07)             ///< Alternate function only: Switch back to primary function.
#define PH_RPC_IO_LINE_CTL_ACT_CHDIR            ((uint8_t)0x08)             ///< Change I/O terminal direction
#define PH_RPC_IO_LINE_CTL_ACT_VOID             ((uint8_t)0xFF)             ///< Not applicable
/** @} */

/** \name Common I/O LineControl Definitions for Optional Parameter
 * \n \b Function: \ref phRpc_H_DevIoLineCtl
 * @{
 *
 */

/**
 * \brief I/O Line Control Not Available Value
 *
 * Within the host software, the value NULL is also allowed. The secondary firmware requires a valid address
 * of a variable containing the "not applicable" value, however.
 *
 */
#define PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE       0xFFFFFFFFu   //

/**
 * \brief Trigger / BL2 button logical state
 *
 * Mask for the bit position to get the current logical state of the line.
 * \see \ref PH_RPC_IO_LINE_CTL_TRIGGER.
 *
 */
#define PH_RPC_IO_LINE_CTL_OPT_TRIGGER_LINE_STATE   0x80000000u   //

/** @} */

/**
 * \defgroup grp_rpc_common_iolnctl_pe Port Expanders
 *
 * Port Expanders are I2C peripherals with 8 bit open-drain I/O ports. Extending the number of I/O lines, this feature
 * however introduces delay or performance penalty as access to I/O lines is serial via the I2C bus.
 *
 * \par Control the port expander
 * - \b Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_SET,
 *              \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - \b Opt for \ref PH_RPC_IO_LINE_CTL_ACT_LOW:    Pattern of '1' Bits that shall be cleared.
 * - \b Opt for \ref PH_RPC_IO_LINE_CTL_ACT_HIGH:   Pattern of '1' Bits that shall be set.
 * - \b Opt for \ref PH_RPC_IO_LINE_CTL_ACT_SET:    Value that shall be set.
 * - \b Opt for \ref PH_RPC_IO_LINE_CTL_ACT_GET:    Pattern to use as AND mask. In order to get the complete port state,
 *                                                  use \ref PH_RPC_IO_LINE_CTL_OPT_EXP_1_ALL.
 *                                                  Do not use \ref PH_RPC_IO_LINE_CTL_OPT_EXP_1_NONE.
 * \par Output Level
 * The port expander can sink considerable but source only little current (open-drain with current-source pull-up action).
 * The level set via the command and control codes described above is the configuration of the output register only. It
 * is not necessarily the level that an attached device sees:
 * - The level of a pin, configured to be logical High, can be pulled Low because of the weak pull-up action. In this case
 *   a read operation will also yield a zero for that pin.
 * - Pins configured to High level can serve as input pins.
 * - Pins configured to Low level can not serve as input pins, however.
 * - Peripheral devices may see different levels due to attached transistors, drivers and level-shifters.
 * - LEDs as indicators directly connected to the expander terminals are ON if the output level is LOW.
 *   This is because the LEDs connect to VCC as the expander can only sink (but not source) sufficient current.
 * .
 *
 */

/**
 * \defgroup grp_rpc_common_iolnctl_auto_act_notes Notes on Automatic I/O Actions (.._REQ lines)
 *
 * Some lines can perform automatic actions. These actions go beyond the standard actions
 * get/set level.
 *
 * The special lines are
 * - Power Request (PWR_REQ, \ref PH_RPC_IO_LINE_CTL_PWR_REQ)
 * - Clock Request (CLK_REQ, \ref PH_RPC_IO_LINE_CTL_CLK_REQ)
 * - Tx Power Request (TX_PWR_REQ_LPC, \ref PH_RPC_IO_LINE_CTL_TX_PWR_REQ)
 * .
 *
 * These lines can propagate its value to output lines:
 * - Power Control (Some boards: PMUVCC_EN, \ref PH_RPC_IO_LINE_CTL_PWR_CTL, \ref PH_RPC_IO_LINE_CTL_ESE_RESET)
 * - Clock Control (LPC24, \ref PH_RPC_IO_LINE_CTL_CLK_CTL)
 * - TX Power Control (TX_PWR_REQ_LPC_OUT, \ref PH_RPC_IO_LINE_CTL_TX_PWR_CTL)
 * .
 *
 * When automatic propagation of the line state is required, the dedicated interrupt
 * \ref PH_RPC_IO_LINE_CTL_PWR_CLK_CTL_ENABLESTATE needs to be activated. Only then
 * the line state will be propagated.
 * - Power Request (\ref PH_RPC_IO_LINE_CTL_PWR_REQ)
 * - Clock Request (\ref PH_RPC_IO_LINE_CTL_CLK_REQ)
 * - Tx Power Request will work without this setting, however.
 * .
 *
 * \note On boards with a T=1 / SPI ESE the \b Power \b Request line \ref PH_RPC_IO_LINE_CTL_PWR_REQ
 *       is used as ESE IRQ line when the ESE interrupt is enabled (no busy-polling).
 *
 */

/** \name Device I/O Line Control
 *
 * Device I/O Line Control Codes.
 * \n \b Function: \ref phRpc_H_DevIoLineCtl
 *
 * @{
 */

/**
 * \brief Control MUX Line Status
 *
 * Control the MUX for the analog test bus.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: Channel number, see \ref PH_RPC_IO_LINE_CTL_OPT_MUX0; out: Logical level
 * .
 */
#define PH_RPC_IO_LINE_CTL_MUX                      ((uint8_t)0x00) //

/**
 * \brief Control VEN Line Status
 *
 * Control the VEN line level or behaviour.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_PULSE,
 *           \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \note The level set during a pulse is the opposite of the static level so far. The pulse duration is set
 *       with the code \ref PH_RPC_IO_LINE_CTL_VEN_PULSE_WIDTH.
 *
 * \note The default state is ON
 */
#define PH_RPC_IO_LINE_CTL_VEN                      ((uint8_t)0x04) //

/**
 * \brief Control VEN Line Pulse Width
 *
 * Control the VEN line Pulse with for the \ref PH_RPC_IO_LINE_CTL_VEN code with action \ref PH_RPC_IO_LINE_CTL_ACT_PULSE.
 * The range is 1 microsecond up to 1 second with a resolution of 1 microsecond. The duration is generated by the PWM
 * peripheral of the LPC microcontroller therefore it can be considered accurate.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_SET, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: Pulse width in steps of µs, see also \ref PH_RPC_IO_LINE_CTL_OPT_VEN_1_US.
 * .
 */
#define PH_RPC_IO_LINE_CTL_VEN_PULSE_WIDTH          ((uint8_t)0x05) //

/**
 * \brief Control DWL_REQ Line Status
 *
 * Control the Download line level.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 */
#define PH_RPC_IO_LINE_CTL_DWL_REQ                  ((uint8_t)0x08) //

/**
 * \brief Get CLK_REQ Line Status
 *
 * Get the CLK-Request line level.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Level of the line
 * .
 * \note In order to control the way CLK_REQ is propagated please use \ref PH_RPC_IO_LINE_CTL_CLK_CTL.
 */
#define PH_RPC_IO_LINE_CTL_CLK_REQ                  ((uint8_t)0x0C) //

/**
 * \brief Control CLK_REQ Line Propagation Delay
 *
 * Control the \ref PH_RPC_IO_LINE_CTL_CLK_REQ line propagation delay to the CLK_CTL output.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_SET, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: Delay in microseconds, see \ref PH_RPC_IO_LINE_CTL_OPT_CLK_REQ_MAX.
 * .
 * \note A value of \ref PH_RPC_IO_LINE_CTL_OPT_CLK_REQ_INFINITE disables this function.
 */
#define PH_RPC_IO_LINE_CTL_CLK_REQ_DELAY            ((uint8_t)0x0D) //

/**
 * \brief Get PWR_REQ Line Status
 *
 * Get the PWR-Request line level.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Level of the line
 * .
 * \note In order to control the way PWR_REQ is propagated please use \ref PH_RPC_IO_LINE_CTL_PWR_CTL.
 */
#define PH_RPC_IO_LINE_CTL_PWR_REQ                  ((uint8_t)0x10) //

/**
 * \brief Control PWR_REQ Line Propagation Delay
 *
 * Control the \ref PH_RPC_IO_LINE_CTL_PWR_REQ line propagation delay to the control output.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_SET, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: Delay in microseconds, see also \ref PH_RPC_IO_LINE_CTL_OPT_PWR_REQ_MAX.
 * .
 * \note A value of \ref PH_RPC_IO_LINE_CTL_OPT_PWR_REQ_INFINITE disables this function.
 */
#define PH_RPC_IO_LINE_CTL_PWR_REQ_DELAY            ((uint8_t)0x14) //

/**
 * \brief Control PMUVCC Line Level
 *
 * Control the PMUVCC line level.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \sa \ref PH_RPC_IO_LINE_CTL_PWR_CTL.
 */
#define PH_RPC_IO_LINE_CTL_PMUVCC                   ((uint8_t)0x18) //

/**
 * \brief Control Host Interface Select 7
 *
 * Control the Host Interface Select 7 line that is present on some boards instead of PMUVCC_VAL.
 * Otherwise the same as for \ref PH_RPC_IO_LINE_CTL_PMUVCC applies regarding control parameters.
 *
 */
#define PH_RPC_IO_LINE_CTL_HOST_IF_SEL_7            PH_RPC_IO_LINE_CTL_PMUVCC //

/**
 * \brief Control CLK_CTL Behaviour
 *
 * Control the CLK_CTL line behaviour.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_AUTO,
 *           \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \note When set to \ref PH_RPC_IO_LINE_CTL_ACT_AUTO the device propagates the level sensed at the CLK_REQ input
 *       directly to the CLK_CTL output. Code \ref PH_RPC_IO_LINE_CTL_CLK_REQ_DELAY controls the propagation delay.
 *       Moreover, \ref PH_RPC_IO_LINE_CTL_ACT_AUTO requires PH_RPC_IO_LINE_CTL_PWR_CLK_CTL_ENABLESTATE to be ON.
 */
#define PH_RPC_IO_LINE_CTL_CLK_CTL                  ((uint8_t)0x19) //

/**
 * \brief Control PWR_CTL Behaviour. Alternate Function: ESE Reset
 *
 * Control the PWR_CTL line behaviour or, if the secondary channel is enabled, control the state of the ESE Reset line.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_AUTO,
 *           \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical Level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \note When set to \ref PH_RPC_IO_LINE_CTL_ACT_AUTO the device propagates the level sensed at the PWR_REQ input
 *       directly to the PWR_CTL output. Code \ref PH_RPC_IO_LINE_CTL_PWR_REQ_DELAY controls the propagation delay.
 *       Moreover, \ref PH_RPC_IO_LINE_CTL_ACT_AUTO requires PH_RPC_IO_LINE_CTL_PWR_CLK_CTL_ENABLESTATE to be ON.
 * \par Operation with Secondary RPC Channel Enabled
 * With the secondary RPC channel active the code supports only \ref PH_RPC_IO_LINE_CTL_ACT_LOW and
 * \ref PH_RPC_IO_LINE_CTL_ACT_HIGH. Moreover, a direct control of the interface is not recommended. In alternate function
 * mode control of this signal is performed from within the ESE component which is part of the secondary RPC channel.
 * \sa \ref PH_RPC_IO_LINE_CTL_ESE_RESET
 */
#define PH_RPC_IO_LINE_CTL_PWR_CTL                  ((uint8_t)0x1A) //

/** \brief ESE Reset. Internal use by ESE /  Secondary RPC only. Function: See \ref PH_RPC_IO_LINE_CTL_PWR_CTL. */
#define PH_RPC_IO_LINE_CTL_ESE_RESET                PH_RPC_IO_LINE_CTL_PWR_CTL

/**
 * \brief Control Host Interface Select 6
 *
 * Control the Host Interface Select 6 line that is present on some boards instead of PMUVCC_VAL.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE, out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \b Caution: Code \ref PH_RPC_IO_LINE_CTL_ACT_AUTO shall not be used.
 *
 */
#define PH_RPC_IO_LINE_CTL_HOST_IF_SEL_6            PH_RPC_IO_LINE_CTL_PWR_CTL //

/**
 * \brief Set PWR_REQ/CTL and CLK_REQ/CTRL Enable State
 *
 * Enable or disable the PWR_REQ and CLK_REQ interrupt sensing. This IOCTL disables both functionality as
 * they share the same interrupt.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH
 * - Opt: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note Enable this together with \ref PH_RPC_IO_LINE_CTL_ACT_AUTO for \ref PH_RPC_IO_LINE_CTL_CLK_CTL or
 *       \ref PH_RPC_IO_LINE_CTL_PWR_CTL.
 *
 */
#define PH_RPC_IO_LINE_CTL_PWR_CLK_CTL_ENABLESTATE  ((uint8_t)0x1B) //

/**
 * \brief Get Frequency on the Testbus Line that Connects CLK_REQ
 *
 * When not in automatic mode for CLK_REQ the LPC can measure the frequency of a square wave on the
 * CLK_REQ input.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Level of the line
 * .
 *
 * \note The frequency is only measured if CLK_REQ/CTL handling is not set to automatic. Please see the
 *       request code \ref PH_RPC_IO_LINE_CTL_CLK_CTL.
 */
#define PH_RPC_IO_LINE_CTL_TB_CLK_REQ_FREQUENCY     ((uint8_t)0x1C) //

/**
 * \brief Reserved 1D (defunct PH_RPC_IO_LINE_CTL_VBAT_SEL)
 * This control signal has been removed.
 */
#define PH_RPC_IO_LINE_CTL_RESERVED_1D              ((uint8_t)0x1D) //

/**
 * \brief Port Expander 1 Control
 *
 * \copydoc grp_rpc_common_iolnctl_pe
 *
 * \sa \ref PH_RPC_IO_LINE_CTL_OPT_EXP_1_NONE and the other definitions of this section.
 *
 */
#define PH_RPC_IO_LINE_CTL_EXP_1                    ((uint8_t)0x1E) //

/**
 * \brief Port Expander 2 Control
 *
 * \copydoc grp_rpc_common_iolnctl_pe
 *
 * \sa \ref PH_RPC_IO_LINE_CTL_OPT_EXP_2_NONE and the other definitions of this section.
 *
 */
#define PH_RPC_IO_LINE_CTL_EXP_2                    ((uint8_t)0x1F) //

/**
 * \brief Control Host Interface Select 8
 *
 * Control the Host Interface Select 8 line that is present on some boards instead of TXD3.
 * - Action:  \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 */
#define PH_RPC_IO_LINE_CTL_HOST_IF_SEL_8            ((uint8_t)0x20) //

/**
 * \brief Control TX_PWR_CTL Behaviour
 *
 * Control the TX_PWR_CTL line behavior.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_LOW, \ref PH_RPC_IO_LINE_CTL_ACT_HIGH, \ref PH_RPC_IO_LINE_CTL_ACT_AUTO
 *           \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Logical level when \ref PH_RPC_IO_LINE_CTL_ACT_GET is used.
 * .
 * \note When set to \ref PH_RPC_IO_LINE_CTL_ACT_AUTO the device propagates the level sensed at the \ref PH_RPC_IO_LINE_CTL_TX_PWR_REQ
 *       input directly to the TX_PWR_CTL output. Code \ref PH_RPC_IO_LINE_CTL_TX_PWR_REQ_DELAY controls the propagation delay.
 */
#define PH_RPC_IO_LINE_CTL_TX_PWR_CTL               ((uint8_t)0x21) //

/**
 * \brief Control TX_PWR_REQ Line Propagation Delay
 *
 * Control the TX_PWR_REQ line propagation delay to the TX_PWR_CTL output.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_SET, \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: Delay in microseconds, see also \ref PH_RPC_IO_LINE_CTL_OPT_TX_PWR_REQ_MAX.
 * .
 * \note A value of \ref PH_RPC_IO_LINE_CTL_OPT_TX_PWR_REQ_INFINITE disables this function.
 */
#define PH_RPC_IO_LINE_CTL_TX_PWR_REQ_DELAY         ((uint8_t)0x22) //

/**
 * \brief Get TX_PWR_REQ Line Status
 *
 * Get the TX PWR-Request line level.
 * - Action: \ref PH_RPC_IO_LINE_CTL_ACT_GET
 * - Opt: in: PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE; out: Level of the line
 * .
 * \note In order to control the way TX_PWR_REQ is propagated and to control the output itself
 *       please use \ref PH_RPC_IO_LINE_CTL_TX_PWR_CTL.
 */
#define PH_RPC_IO_LINE_CTL_TX_PWR_REQ               ((uint8_t)0x23) //

/**
 * \brief Set External Trigger
 *
 * Pulse the trigger line. The trigger can be used to control external test equipment to capture a specific event:
 * - The trigger output is the same pin as used for Bootloader 2 activation.
 * - The external trigger input of an oscilloscope can be connected to the switch SW2 or its pull-up resistor.
 * - The idle level of the line is HIGH.
 * - In case of an event the line is pulled low for 100..200 microseconds.
 * - Trigger recommendation:
 *   - Trigger on the falling edge.
 *   - if possible, filter for pulses larger than 50 microseconds (advanced oscilloscope setting). This may help to
 *     reduce the likelihood of false trigger due to interference, in particular when long cables are used.
 *   .
 * .
 *
 * Controlling the pin:
 * - Action:
 *   - Arm the trigger: \ref PH_RPC_IO_LINE_CTL_ACT_SET
 *   - Get the current trigger setting: \ref PH_RPC_IO_LINE_CTL_ACT_GET, except the bit defined by
 *     mask \ref PH_RPC_IO_LINE_CTL_OPT_TRIGGER_LINE_STATE.
 *   - Pulse the trigger: \ref PH_RPC_IO_LINE_CTL_ACT_PULSE
 *   - Get the current logical state of the line: \ref PH_RPC_IO_LINE_CTL_ACT_GET: Use the mask
 *     \ref PH_RPC_IO_LINE_CTL_OPT_TRIGGER_LINE_STATE to get the bit that holds the logical state.
 *   .
 * - Opt:
 *   - Arm the trigger by setting an error code:
 *     - Trigger on all errors (but never on status OK (\ref PH_RPC_STATUS_OK) itself): Set \ref PH_RPC_STATUS_OK.
 *     - Disable trigger (host triggered action using \ref PH_RPC_IO_LINE_CTL_ACT_PULSE still works): \ref PH_RPC_STATUS_NONE.
 *     - Select specific trigger error code: \ref PH_RPC_STATUS_E_TIMEOUT, \ref PH_RPC_STATUS_W_LESS_DATA and others.
 *     - \b Note The function returns the previous settings through the opt parameter.
 *   - Pulse the trigger: \ref PH_RPC_IO_LINE_CTL_OPT_NOT_APPLICABLE. Pulsing the trigger is useful if the
 *     host application has detected a complex scenario that needs to be recorded.
 *   - Get the current setting via the opt parameter with PH_RPC_IO_LINE_CTL_ACT_GET.
 *   .
 * .
 */
#define PH_RPC_IO_LINE_CTL_TRIGGER                  ((uint8_t)0x24) //

/**
 * \brief Port Expander 3 Control
 *
 * \copydoc grp_rpc_common_iolnctl_pe
 *
 * \sa \ref PH_RPC_IO_LINE_CTL_OPT_EXP_3_NONE and the other definitions of this section.
 *
 */
#define PH_RPC_IO_LINE_CTL_EXP_3                    ((uint8_t)0x25) //

/**
 * \brief Port Expander 4 Control
 *
 * \copydoc grp_rpc_common_iolnctl_pe
 *
 * \sa \ref PH_RPC_IO_LINE_CTL_OPT_EXP_4_NONE and the other definitions of this section.
 *
 */
#define PH_RPC_IO_LINE_CTL_EXP_4                    ((uint8_t)0x26) //


/** @} */ // Name

/** \name VEN Control
 *
 * Optional parameter settings for VEN control code \ref PH_RPC_IO_LINE_CTL_VEN.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_VEN_1_US             1u          ///< VEN Pulse duration is 1 µs
#define PH_RPC_IO_LINE_CTL_OPT_VEN_50_US            50u         ///< VEN Pulse duration is 50 µs
#define PH_RPC_IO_LINE_CTL_OPT_VEN_500_US           500u        ///< VEN Pulse duration is 500 µs
#define PH_RPC_IO_LINE_CTL_OPT_VEN_1_MS             1000u       ///< VEN Pulse duration is 1ms
#define PH_RPC_IO_LINE_CTL_OPT_VEN_50_MS            50000u      ///< VEN Pulse duration is 50 ms
#define PH_RPC_IO_LINE_CTL_OPT_VEN_500_MS           500000u     ///< VEN Pulse duration is 500 ms
#define PH_RPC_IO_LINE_CTL_OPT_VEN_1_S              1000000u    ///< VEN Pulse duration is 1 s
#define PH_RPC_IO_LINE_CTL_OPT_VEN_MIN              PH_RPC_IO_LINE_CTL_OPT_VEN_1_US ///< Minimum VEN time
#define PH_RPC_IO_LINE_CTL_OPT_VEN_MAX              PH_RPC_IO_LINE_CTL_OPT_VEN_1_S ///< Maximum VEN time
#define PH_RPC_IO_LINE_CTL_OPT_VEN_DEFAULT          PH_RPC_IO_LINE_CTL_OPT_VEN_50_MS ///< Default VEN time
/** @} */

/** \name Delay Control
 *
 * Optional parameter setting for propagation delay control.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_INFINITE_DELAY       0xFFFFFFFFu ///< Infinite delay, no propagation is done.
/** @} */

/** \name PWR_REQ Delay Control
 *
 * Optional parameter settings for PWR_REQ control code \ref PH_RPC_IO_LINE_CTL_PWR_REQ_DELAY.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_PWR_REQ_MAX          1000000u    ///< Maximum delay for PWR_REQ in steps of 1µs
#define PH_RPC_IO_LINE_CTL_OPT_PWR_REQ_INFINITE     PH_RPC_IO_LINE_CTL_OPT_INFINITE_DELAY ///< Infinite delay; Function disabled
/** @} */

/** \name TX_PWR_REQ Delay Control
 *
 * Optional parameter settings for TX_PWR_REQ control code \ref PH_RPC_IO_LINE_CTL_TX_PWR_REQ_DELAY.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_TX_PWR_REQ_MAX       1000000u    ///< Maximum delay for TX_PWR_REQ in steps of 1µs
#define PH_RPC_IO_LINE_CTL_OPT_TX_PWR_REQ_INFINITE  PH_RPC_IO_LINE_CTL_OPT_INFINITE_DELAY ///< Infinite delay; Function disabled
/** @} */

/** \name CLK_REQ Delay Control
 *
 * Optional parameter settings for CLK_REQ control code \ref PH_RPC_IO_LINE_CTL_CLK_REQ_DELAY.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_CLK_REQ_MAX          1000000u    ///< Maximum delay for CLK_REQ in steps of 1µs
#define PH_RPC_IO_LINE_CTL_OPT_CLK_REQ_INFINITE     PH_RPC_IO_LINE_CTL_OPT_INFINITE_DELAY ///< Infinite delay; Function disabled
/** @} */

/** \name MUX Control
 *
 * Optional parameter settings for MUX control code \ref PH_RPC_IO_LINE_CTL_MUX.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_MUX0                 0           ///< MUX 0
#define PH_RPC_IO_LINE_CTL_OPT_MUX1                 1u          ///< MUX 1
#define PH_RPC_IO_LINE_CTL_OPT_MUX2                 2u          ///< MUX 2
#define PH_RPC_IO_LINE_CTL_OPT_MUX3                 3u          ///< MUX 3
#define PH_RPC_IO_LINE_CTL_OPT_MUX_NUM_CH           4u          ///< Number of MUX channels
/** @} */

/** \name Port Expander 1 Control
 *
 * Optional parameter settings for Port Expander 1 Control code \ref PH_RPC_IO_LINE_CTL_EXP_1.
 *
 * \note The level \c HIGH (\ref PH_RPC_IO_LINE_CTL_ACT_HIGH) or \c LOW (\ref PH_RPC_IO_LINE_CTL_ACT_LOW)
 *       are the logical levels at the terminals of the port expanders. On some boards the signals may
 *       be inverted because of attached buffers, transistors and high-side switches.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_NONE               0x00u   ///< None
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_ALL                0xFFu   ///< All
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_VBAT            0x01u   ///< EN_VBAT
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_PVDD            0x02u   ///< EN_PVDD
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_SIM_PMUVCC      0x04u   ///< EN_SIM_PMUVCC
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_2V5           0x08u   ///< VBAT_2V5
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_PVDD_3V0           0x10u   ///< PVDD_3V0: May be inverted on some boards.
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_PMUVCC_3V0         0x20u   ///< PMUVCC_3V0
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_2V2           0x40u   ///< VBAT_2V2
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_SVDD_PWR_REQ_LPC   0x80u   ///< SVDD_PWR_REQ_LPC
/** @} */

/** \name Port Expander 1 Control Legacy Names
 *
 * Legacy names for optional parameter settings of Port Expander 1 Control. The definitions are deprecated. It is not
 * recommended to use them any more. They are retained for compatibility.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN197_1            PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_VBAT            ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN199_1            PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_PVDD            ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN199_2            PH_RPC_IO_LINE_CTL_OPT_EXP_1_EN_SIM_PMUVCC      ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_VBAT2_MFET    PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_2V5           ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_PVDD_MFET          PH_RPC_IO_LINE_CTL_OPT_EXP_1_PVDD_3V0           ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_PMUVCC_MFET        PH_RPC_IO_LINE_CTL_OPT_EXP_1_PMUVCC_3V0         ///< Retained for compatibility
#define PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_VBAT2_MFET2   PH_RPC_IO_LINE_CTL_OPT_EXP_1_VBAT_2V2           ///< Retained for compatibility
/** @} */

/** \name Port Expander 2 Control
 *
 * Optional parameter settings for Port Expander 2 Control code \ref PH_RPC_IO_LINE_CTL_EXP_2.
 *
 * \note The level \c HIGH (\ref PH_RPC_IO_LINE_CTL_ACT_HIGH) or \c LOW (\ref PH_RPC_IO_LINE_CTL_ACT_LOW)
 *       are the logical levels at the terminals of the port expanders. On some boards the signals may
 *       be inverted because of attached buffers, transistors and high-side switches.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_NONE               0x00u   ///< None
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_ALL                0xFFu   ///< All
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_AVDD_TO_VDD        0x01u   ///< AVDD_TO_VDD
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_DVDD_TO_VDD        0x02u   ///< DVDD_TO_VDD
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_INPUT_CLK_CTRL     0x04u   ///< INPUT_CLK_CTRL
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_HOST_IF_SEL1       0x08u   ///< HOST_IF_SEL1
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_HOST_IF_SEL2       0x10u   ///< HOST_IF_SEL2
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_HOST_IF_SEL3       0x20u   ///< HOST_IF_SEL3
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_HOST_IF_SEL4       0x40u   ///< HOST_IF_SEL4
#define PH_RPC_IO_LINE_CTL_OPT_EXP_2_HOST_IF_SEL5       0x80u   ///< HOST_IF_SEL5
/** @} */

/** \name Port Expander 3 Control
 *
 * Optional parameter settings for Port Expander 3 Control code \ref PH_RPC_IO_LINE_CTL_EXP_3.
 *
 * \note The level \c HIGH (\ref PH_RPC_IO_LINE_CTL_ACT_HIGH) or \c LOW (\ref PH_RPC_IO_LINE_CTL_ACT_LOW)
 *       are the logical levels at the terminals of the port expanders. On some boards the signals may
 *       be inverted by buffers, transistors and high-side switches.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_NONE               0x00u   ///< None
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_ALL                0xFFu   ///< All
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_SIM_PRESENT        0x01u   ///< SIM Present signal
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_WKUP_REQUEST       0x02u   ///< Wakeup Request (FIXED assignment for all boards)
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_RELAY_TVDD_EXT     0x04u   ///< Relay TVDD Control
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_TX_ADR1_MOSI_RELAY 0x08u   ///< Control TX/ADR1/MOSI/RELAY
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_RTS_ADR0_NSS_RELAY 0x10u   ///< Control RTS/ADR0/NSS/RELAY
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_B5                 0x20u   ///< Bit 5
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_B6                 0x40u   ///< Bit 6
#define PH_RPC_IO_LINE_CTL_OPT_EXP_3_B7                 0x80u   ///< Bit 7
/** @} */

/** \name Port Expander 4 Control
 *
 * Optional parameter settings for Port Expander 4 Control code \ref PH_RPC_IO_LINE_CTL_EXP_4.
 *
 * \note The level \c HIGH (\ref PH_RPC_IO_LINE_CTL_ACT_HIGH) or \c LOW (\ref PH_RPC_IO_LINE_CTL_ACT_LOW)
 *       are the logical levels at the terminals of the port expanders. On some boards the signals may
 *       be inverted by buffers, transistors and high-side switches.
 *
 * @{
 */
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_NONE               0x00u   ///< None
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_ALL                0xFFu   ///< All
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B0                 0x01u   ///< Bit 0
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B1                 0x02u   ///< Bit 1
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B2                 0x04u   ///< Bit 2
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B3                 0x08u   ///< Bit 3
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B4                 0x10u   ///< Bit 4
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B5                 0x20u   ///< Bit 5
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B6                 0x40u   ///< Bit 6
#define PH_RPC_IO_LINE_CTL_OPT_EXP_4_B7                 0x80u   ///< Bit 7
/** @} */

/** @} */ // I/O Line Control

// ________________________________________________________________________________________________
//
// Device and Host Information
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_devinf  Device Information
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_GetDeviceInfo
 * \copydoc phRpc_H_GetDeviceInfo
 * \n \b Function: \ref phRpc_H_GetHostInfo
 * \copydoc phRpc_H_GetHostInfo
 *
 * @{
 */

/** \name Get Host Information
 *
 * The device provides detailed host-specific information.
 *
 * \n \b Function: \ref phRpc_H_GetHostInfo
 *
 * @{
 */
#define PH_RPC_CMD_HOSTINFO_BUFLEN              ((uint8_t)48)   ///< Maximum length of the Host Information
// Commands
#define PH_RPC_CMD_HOSTINFO_PCLIB_SWID          ((uint8_t)0x00) ///< PC library SW ID
#define PH_RPC_CMD_HOSTINFO_PCLIB_ENGDATA       ((uint8_t)0x01) ///< PC library Engineering data, see \ref phRpc_IoSystemData_t
/** @} */
// ________________________________________________________________________________________________
//
// Device Information
// ________________________________________________________________________________________________

/** \name Get Device Information
 *
 * The device provides detailed device-specific information.
 * The function may return a number or an array or both:
 * - [N]: A number is returned via the \b infoNum parameter of \ref phRpc_H_GetDeviceInfo
 * - [A]: An array is returned via the \b infoBuf parameter of \ref phRpc_H_GetDeviceInfo
 * .
 *
 * \n \b Function: \ref phRpc_H_GetDeviceInfo
 *
 * @{
 */
#define PH_RPC_CMD_DEVINFO_BUFLEN                   ((uint8_t)48)   ///< Maximum length of the Device Information
// Commands
#define PH_RPC_CMD_DEVINFO_CPUSNR                   ((uint8_t)0x00) ///< [A] CPU serial number
#define PH_RPC_CMD_DEVINFO_CPUID                    ((uint8_t)0x01) ///< [A] CPU ID
#define PH_RPC_CMD_DEVINFO_CORESPEED                ((uint8_t)0x02) ///< [N] CPU core speed in Hz
#define PH_RPC_CMD_DEVINFO_SERIAL_HOST_MODE         ((uint8_t)0x03) ///< [N] Serial host communication mode
#define PH_RPC_CMD_DEVINFO_BLID                     ((uint8_t)0x04) ///< [A] Bootloader identification string
#define PH_RPC_CMD_DEVINFO_SWID                     ((uint8_t)0x05) ///< [A] Primary Firmware SW identification string
#define PH_RPC_CMD_DEVINFO_LOGICAL_ID               ((uint8_t)0x06) ///< [N] Logical device ID, see \ref PH_RPC_IOCTL_MJ_DEV_SET_LOGICAL_ID

#define PH_RPC_CMD_DEVINFO_RESETINFO                ((uint8_t)0x10) ///< [N] Reason of device reset. The major code is in the upper, the minor code is in the lower byte.
#define PH_RPC_CMD_DEVINFO_WDENABLESTATE            ((uint8_t)0x11) ///< [N] CPU Watchdog timer activation state
#define PH_RPC_CMD_DEVINFO_SWITCHSTATE              ((uint8_t)0x12) ///< [N] GP Switch state
#define PH_RPC_CMD_DEVINFO_ASYN_MONITOR_ENABLED     ((uint8_t)0x13) ///< [N] Asynchronous task deadline monitoring enable state
#define PH_RPC_CMD_DEVINFO_ASYN_MONITOR_TIMEOUT     ((uint8_t)0x14) ///< [N] Asynchronous task deadline monitoring timeout value in ms
#define PH_RPC_CMD_DEVINFO_EXT_INT_TIMEOUT          ((uint8_t)0x15) ///< [N] External Interrupt Timeout value in ms

#define PH_RPC_CMD_DEVINFO_MICROSECFAST             ((uint8_t)0x20) ///< [N] Most recent run time in µs of fast task
#define PH_RPC_CMD_DEVINFO_MICROSECCOMM             ((uint8_t)0x21) ///< [N] Most recent run time in µs of DAQ/communication task
#define PH_RPC_CMD_DEVINFO_MICROSECMAIN             ((uint8_t)0x22) ///< [N] Most recent run time in µs of main task
#define PH_RPC_CMD_DEVINFO_MICROSECASYN             ((uint8_t)0x23) ///< [N] Most recent run time in µs of asynchronous task
#define PH_RPC_CMD_DEVINFO_MICROSECUSB              ((uint8_t)0x24) ///< [N] Most recent run time in µs of USB task
#define PH_RPC_CMD_DEVINFO_MICROSECFAST_MAX         ((uint8_t)0x25) ///< [N] Maximum run time in µs of fast task
#define PH_RPC_CMD_DEVINFO_MICROSECCOMM_MAX         ((uint8_t)0x26) ///< [N] Maximum run time in µs of DAQ/communication task
#define PH_RPC_CMD_DEVINFO_MICROSECMAIN_MAX         ((uint8_t)0x27) ///< [N] Maximum run time in µs of main task
#define PH_RPC_CMD_DEVINFO_MICROSECASYN_MAX         ((uint8_t)0x28) ///< [N] Maximum run time in µs of asynchronous task
#define PH_RPC_CMD_DEVINFO_MICROSECUSB_MAX          ((uint8_t)0x29) ///< [N] Maximum run time in µs of USB task
#define PH_RPC_CMD_DEVINFO_MICROSECCTFAST           ((uint8_t)0x2A) ///< [N] Most recent run time in µs of fast task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTCOMM           ((uint8_t)0x2B) ///< [N] Most recent run time in µs of DAQ/communication task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTMAIN           ((uint8_t)0x2C) ///< [N] Most recent run time in µs of main task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTASYN           ((uint8_t)0x2D) ///< [N] Most recent run time in µs of asynchronous task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTFAST_MAX       ((uint8_t)0x2E) ///< [N] Maximum run time in µs of fast task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTCOMM_MAX       ((uint8_t)0x2F) ///< [N] Maximum run time in µs of DAQ/communication task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTMAIN_MAX       ((uint8_t)0x30) ///< [N] Maximum run time in µs of main task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTASYN_MAX       ((uint8_t)0x31) ///< [N] Maximum run time in µs of asynchronous task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_FAST      ((uint8_t)0x32) ///< [N] Stack watermark of fast task
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_COMM      ((uint8_t)0x33) ///< [N] Stack watermark of DAQ/communication task
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_MAIN      ((uint8_t)0x34) ///< [N] Stack watermark of main task
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_ASYN      ((uint8_t)0x35) ///< [N] Stack watermark of asynchronous task
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_USB       ((uint8_t)0x36) ///< [N] Stack watermark of USB task
#define PH_RPC_CMD_DEVINFO_FTIME_DIRECT_MAX         ((uint8_t)0x37) ///< [N] Maximum time in µs of direct endpoint call
#define PH_RPC_CMD_DEVINFO_FTIME_DEFERRED_MAX       ((uint8_t)0x38) ///< [N] Maximum time in µs of direct endpoint call
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_INT       ((uint8_t)0x39) ///< [N] Stack watermark for Interrupts
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_BGND      ((uint8_t)0x3A) ///< [N] Stack watermark of the background thread
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_HSU       ((uint8_t)0x3B) ///< [N] Stack watermark of the HSU thread
#define PH_RPC_CMD_DEVINFO_MICROSECASYN_2           ((uint8_t)0x3C) ///< [N] Most recent run time in µs of secondary asynchronous task
#define PH_RPC_CMD_DEVINFO_MICROSECASYN_2_MAX       ((uint8_t)0x3D) ///< [N] Maximum run time in µs of secondary asynchronous task
#define PH_RPC_CMD_DEVINFO_MICROSECCTASYN_2         ((uint8_t)0x3E) ///< [N] Most recent run time in µs of secondary asynchronous task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_MICROSECCTASYN_2_MAX     ((uint8_t)0x3F) ///< [N] Maximum run time in µs of secondary asynchronous task in Secondary Firmware
#define PH_RPC_CMD_DEVINFO_STACKWATERMARK_ASYN_2    ((uint8_t)0x40) ///< [N] Stack watermark of secondary asynchronous task
#define PH_RPC_CMD_DEVINFO_IOTIME                   ((uint8_t)0x41) ///< [A] I/O time measurement result, serialised as {Status|ID|V0V1V2V3}; {Start|Checkpoint1|..}

/** @} */

/** @} */ // Device and Host Information

// ________________________________________________________________________________________________
//
// Secondary Firmware Image Information
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_ctinf  Secondary Firmware Query Codes
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_GetDeviceCtInfo
 * \copydoc phRpc_H_GetDeviceCtInfo
 *
 * @{
 */

/** \name Get Secondary Firmware Information
 *
 * The device provides detailed information about operational data via \ref phRpc_H_GetDeviceCtInfo.
 *
 * @{
 */
#define PH_RPC_CMD_CTINFO_BUFLEN                 ((uint8_t)48)     ///< Maximum length of the Secondary Firmware Information
// Commands
#define PH_RPC_CMD_CTINFO_RUNNING                ((uint8_t)0x00)   ///< Secondary Firmware is running
#define PH_RPC_CMD_CTINFO_IMGPRESENT             ((uint8_t)0x01)   ///< Secondary Firmware Image is present
#define PH_RPC_CMD_CTINFO_IMGVALID               ((uint8_t)0x02)   ///< Secondary Firmware Image is valid
#define PH_RPC_CMD_CTINFO_IMGCHECKSUM            ((uint8_t)0x03)   ///< Secondary Firmware Image stored checksum
#define PH_RPC_CMD_CTINFO_CALCCHECKSUM           ((uint8_t)0x04)   ///< Secondary Firmware Image calculated checksum
#define PH_RPC_CMD_CTINFO_MAJOR_VERSION          ((uint8_t)0x05)   ///< Secondary Firmware Image major version
#define PH_RPC_CMD_CTINFO_MINOR_VERSION          ((uint8_t)0x06)   ///< Secondary Firmware Image minor version

/** @} */

/** @} */ // 2FW Query

// ________________________________________________________________________________________________
//
// Diagnostics
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_diag  Diagnostics
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_CtrlDeviceDiag
 * \copydoc phRpc_H_CtrlDeviceDiag
 *
 * @{
 */

/** \name Diagnostics
 *
 * Basic diagnostic information may be queried via \ref phRpc_H_CtrlDeviceDiag.
 *
 * @{
 */
#define PH_RPC_CMD_CTRLDIAG_BUFLEN              256u   ///< Diagnostics exchange buffer length

/** @} */

/** \name Diagnostic Job ID
 *
 * Diagnostic information is available through various diagnostic jobs.
 *
 * @{
 */

 /**
 * \brief Diagnostic Responsiveness
 *
 * Receive, change and send back data.
 *
 * \par Parameters
 * - Buffer: References a pointer that will receive the address of the returned data. The referenced pointer
 *           may be NULL, but not the pointer itself.
 * - Length: Pointer to a variable that will receive the number of bytes returned (string length).
 *           May not be NULL.
 * .
 */
#define PH_RPC_CMD_CTRLDIAG_JOB_DIAGNOSTIC_RESPONSIVENESS   0x00u   //

 /**
 * \brief Get board supply voltage in [mV]
 *
 * Get the supply voltage of the board in [mV] as a non zero-terminated(!) string.
 *
 * \par Parameters
 * - Buffer: References a pointer that will receive the address of the returned data. The referenced pointer
 *           may be NULL, but not the pointer itself.
 * - Length: Pointer to a variable that will receive the number of bytes returned (string length).
 *           May not be NULL.
 * .
 */
#define PH_RPC_CMD_CTRLDIAG_JOB_GET_VBOARD                  0x01u   //

 /**
 * \brief Get Device Under Test supply voltage in [mV]
 *
 * Get the supply voltage of the DUT as a non zero-terminated(!) string.
 * For restrictions on parameters please see \ref PH_RPC_CMD_CTRLDIAG_JOB_GET_VBOARD
 *
 */
#define PH_RPC_CMD_CTRLDIAG_JOB_GET_VDUT                    0x02u   //

 /**
 * \brief Get Stacked Registers
 *
 * Get the stacked CPU registers. The software stores, upon a fatal error, the content
 * of the last stack frame in a structure. On restart, the content can be queried with
 * this code as the space of the structure is preserved during reset.
 * The registers can be found at defined locations in the buffer, in little endian format. This is useful
 * to find errors in the Secondary Firmware (user defined software) or to report a bug in the primary firmware or both.
 * Check \ref grp_diag_stackedregs for more details.
 * \sa Definitions starting with \ref PH_RPC_CMD_CTRLDIAG_STACKED_POS_SP.
 */
#define PH_RPC_CMD_CTRLDIAG_JOB_GET_STACKED_REG             0x03u   //
#define PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE                0x04u   ///< Size of a register in bytes
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_SP                  (0x00u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< Stack Pointer
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_R0                  (0x01u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< R0
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_R1                  (0x02u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< R1
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_R2                  (0x03u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< R2
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_R3                  (0x04u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< R3
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_R12                 (0x05u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< R12
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_LR                  (0x06u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< Link Register
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_PC                  (0x07u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< Program Counter
#define PH_RPC_CMD_CTRLDIAG_STACKED_POS_PSR                 (0x08u * PH_RPC_CMD_CTRLDIAG_STACKED_REG_SIZE)  ///< Program Status Register

 /**
 * \brief Get diagnostic events
 *
 * Get the array of diagnostic data stored in the device. The byte array can be decoded according to the
 * event number defined in \ref phDiagEH_Events, such as \ref PH_DIAG_EH_EXT_RTERR, and the definition of
 * bit fields within an array element. See \ref PH_DIAG_EH_COUNTMASK, \ref PH_DIAG_EH_STATUSMASK and
 * \ref PH_DIAG_EH_STATUS_PASSED.
 *
 */
#define PH_RPC_CMD_CTRLDIAG_JOB_GET_EVENTS                  0x04u   //

/** @} */

/** @} */ // Diag

// ________________________________________________________________________________________________
//
// Data Acquisition and Waveform Generator
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_addaq  Analog I/O Subsystem
 * \ingroup grp_rpc_common
 *
 * The ADC subsystem is able to perform high-accuracy measurements of on-board voltages or currents.
 * The control system also has a built-in DAC that can operate independently from other functions.
 * DMA action supplies, on DAC request, samples from within a circular buffer in order
 * to generate periodic waveforms.
 *
 * \see grp_rpc_host_ad_io
 *
 * @{
 */

/** \name Logical ADC channels
 * @{
 */
#define PH_RPC_CMD_ADC_CH_VREF          0u      ///< V REF
#define PH_RPC_CMD_ADC_CH_V_I_TST       1u      ///< V/I TEST
#define PH_RPC_CMD_ADC_CH_VBOARD        2u      ///< V BOARD
#define PH_RPC_CMD_ADC_CH_DAC_CAL       3u      ///< DAC Cal.
#define PH_RPC_CMD_ADC_CH_COUNT         4       ///< ADC Channel Count
/** @} */ // Name

/** \name Logical DAC channels
 * @{
 */
#define PH_RPC_CMD_DAC_CH_VVAR          0u      ///< V Var
#define PH_RPC_CMD_DAC_CH_COUNT         1       ///< DAC Channel Count
/** @} */ // Name

/** \name HW Type
 * @{
 */
#define PH_RPC_CMD_ADC_HWTYPE           0       ///< Hardware type is ADC
#define PH_RPC_CMD_DAC_HWTYPE           1u      ///< Hardware type is DAC
/** @} */ // Name

/** \name Wave Type
 * @{
 */
#define PH_RPC_CMD_DAC_WAVETYPE_TST     0x00u   ///< Test output wave
#define PH_RPC_CMD_DAC_WAVETYPE_RND     0x01u   ///< Random output wave
#define PH_RPC_CMD_DAC_WAVETYPE_SINE    0x10u   ///< Sine wave
#define PH_RPC_CMD_DAC_WAVETYPE_ST_AS   0x20u   ///< Sawtooth wave, ascending
#define PH_RPC_CMD_DAC_WAVETYPE_ST_DS   0x21u   ///< Sawtooth wave, descending
#define PH_RPC_CMD_DAC_WAVETYPE_TRI     0x30u   ///< Triangle wave
#define PH_RPC_CMD_DAC_WAVETYPE_RECT    0x90u   ///< Square wave, base
#define PH_RPC_CMD_DAC_WAVETYPE_RECT_50 PH_RPC_CMD_DAC_WAVETYPE_RECT + 50u    ///< Square wave, 50%
/** @} */ // Name

/** @} */ // ADDAQ

// ________________________________________________________________________________________________
//
// Device Mode
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_devmode  Device Mode
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_SetDeviceMode
 * \copydoc phRpc_H_SetDeviceMode
 *
 * @{
 */

/** \name Device Mode
 *
 * Via \ref phRpc_H_SetDeviceMode the board can be restarted and set to another operating mode.
 * Use this command for system supervisor check or reprogramming.
 *
 * \note The system waits at least for 1 second until it restarts. This allows the controlling
 *       application to close the communication library handle before the underlying driver unloads.
 * \note The host library does not automatically close the connection after sending this command.
 *       Doing so by calling \ref phRpc_H_Close is within the host application's responsibility.
 *
 * @{
 */
#define PH_RPC_CMD_CTRLDEVMODE_VOID                 ((uint8_t)0x00)   ///< Must not be used
#define PH_RPC_CMD_CTRLDEVMODE_RESETCHECK_REBOOT    ((uint8_t)0x01)   ///< Reboot the board
#define PH_RPC_CMD_CTRLDEVMODE_FLASHREQUEST_APP     ((uint8_t)0x02)   ///< Request Reprogramming of Primary Firmware
#define PH_RPC_CMD_CTRLDEVMODE_FLASHREQUEST_CT      ((uint8_t)0x03)   ///< Request Reprogramming of Secondary Firmware
#define PH_RPC_CMD_CTRLDEVMODE_RESETCHECK           ((uint8_t)0x04)   ///< Check System Supervisor
#define PH_RPC_CMD_CTRLDEVMODE_CHECK_ERRORHANDLER   ((uint8_t)0x05)   ///< Crash the system in order to test fault handler
/** @} */

/** @} */ // Device Mode

// ________________________________________________________________________________________________
//
// EEPROM Access
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_ee  EEPROM Access
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_EE
 * \copydoc phRpc_H_EE
 * \n \b Function: \ref phRpc_H_EECfg
 * \copydoc phRpc_H_EECfg
 *
 * @{
 */

/** \name EEPROM Raw Access
 *
 * The device's own EEPROM can be accessed using \ref phRpc_H_EE. The function is a raw EEPROM I/O function.
 * \n \b Function: \ref phRpc_H_EE
 *
 * @{
 */
#define PH_RPC_CMD_EE_BUFLEN                      ((uint8_t)255)   ///< EEPROM access exchange buffer size
#define PH_RPC_CMD_EE_PREPEND             PH_RPC_CMD_PREPEND_LEN   ///< Reserved for EEPROM data encapsulation at endpoint
// Commands
#define PH_RPC_CMD_EE_READ_SEQ                   ((uint8_t)0x00)   ///< EEPROM Sequential Read command
#define PH_RPC_CMD_EE_WRITE_PAGE                 ((uint8_t)0x01)   /**< \brief EEPROM Page Write command
                                                                    *
                                                                    *   When the address of the EE operation is not
                                                                    *   aligned to a page begin, only the
                                                                    *   section starting at the address and
                                                                    *   ending at the upper page limit is written */
/** @} */

/** \name EEPROM Configuration Access
 *
 * The device's EEPROM is used for configuration storage by \ref phRpc_H_EECfg.
 * \n \b Function: \ref phRpc_H_EECfg
 *
 * @{
 */
#define PH_RPC_CMD_EE_AUTOLOAD_CFG               ((uint8_t)0x02)   ///< Make the configuration auto-load at start. Do not load it now, however
#define PH_RPC_CMD_EE_AUTOLOAD_CFG_SWITCH        ((uint8_t)0x03)   ///< Make the configuration auto-load at start-up with current switch settings only
#define PH_RPC_CMD_EE_NO_AUTOLOAD_CFG            ((uint8_t)0x04)   ///< Do not automatically load the configuration at start-up. Forget about switch settings
#define PH_RPC_CMD_EE_LOAD_CFG                   ((uint8_t)0x05)   ///< Load the configuration now
#define PH_RPC_CMD_EE_STORE_CFG                  ((uint8_t)0x06)   ///< Store the I/O configuration and load parameters in the EEPROM now
/** @} */

/** @} */ // EE

// ________________________________________________________________________________________________
//
// Secondary Firmware Control
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_ct_control  Secondary Firmware Control
 * \ingroup grp_rpc_common
 * \n \b Function: \ref phRpc_H_StartTestSw
 * \copydoc phRpc_H_StartTestSw
 * \n \b Function: \ref phRpc_H_StopTestSw
 * \copydoc phRpc_H_StopTestSw
 * \n \b Function: \ref phRpc_H_DataExchangeTestSw
 * \copydoc phRpc_H_DataExchangeTestSw
 *
 * @{
 */

/** \name Test Software Control
 *
 * The test software (or user software) that runs in parallel returns stati as shown here:
 *
 * @{
 */
#define PH_RPC_CMD_TESTSWCT_STATUS_SUCCESS       ((uint8_t)0x00) ///< Operation was successful
#define PH_RPC_CMD_TESTSWCT_STATUS_INIT_ERROR    ((uint8_t)0x01) ///< Initialisation failed
#define PH_RPC_CMD_TESTSWCT_STATUS_STOP_OK       ((uint8_t)0x02) ///< The test SW could be stopped
#define PH_RPC_CMD_TESTSWCT_STATUS_STOP_PENDING  ((uint8_t)0x03) ///< The test SW is stopping on request
#define PH_RPC_CMD_TESTSWCT_STATUS_STOP_ERROR    ((uint8_t)0x04) ///< The test SW could not be stopped
 /** @} */

 /** @} */ // 2FW Control

// ________________________________________________________________________________________________
//
// I2C and SPI Converter
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_intf_conv  Interface Converter
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_DutInit
 * \copydoc phRpc_H_DutInit
 *
 * @{
 */

/** \name USB to I2C and SPI Conversion Buffer Sizes
 *
 * \par Buffer Sizes
 * There is a maximum number of bytes allowed to be transferred to and from the device. Mainly
 * this is a limitation imposed by the size of the allocated RAM both on PC and microcontroller side.
 * The amount of RAM allocated is determined by the DUT memory size where any valus in excess to this would
 * be of limited use.
 *
 * \par Auto Selection of Buffer Size Usage
 * The underlying library uses Bulk transfer on the USB. Before any call to the USB, the RPC library
 * serialises discrete data into a buffer that is handed over to the USB library. Serialisation can,
 * depending on the data and buffer sizes to marshal, consume more or less bytes. The PC library decides
 * whether to use the short or long serialisation. By dynamically selecting one of the options the
 * communication speed can be considerably increased with randomly varying data sizes during a host
 * to device communication.
 *
 * \par Data Encapsulation
 * For the basic protocol from the device to the external DUT further encapsulation is needed. This is
 * done automatically by the device therefore the caller on the PC side does not need to reserve a small
 * fraction at the start of the transfer buffer for that purpose on each call.
 * for details.
 *
 * @{
 */
#define PH_RPC_CMD_EXT_DEV_BUFSIZE          PH_RPC_CMD_USER_BUFSIZE  ///< Maximum Host Interface user buffer size
#define PH_RPC_CMD_EXT_DEV_SHORT_EXCHANGE_LIMIT     ((uint16_t)200)  ///< \internal From there onwards the large buffer will be (de-)serialised
#define PH_RPC_CMD_EXT_DEV_PREPEND          PH_RPC_CMD_PREPEND_LEN   ///< Reserved for further data encapsulation at endpoint
/** @} */

/** \name USB to I2C and SPI Conversion, INIT
 * @{
 */
#define PH_RPC_CMD_DEV_DISABLE_EXT_INTF           ((uint8_t)0x00)  ///< Switch off the Host Interface
#define PH_RPC_CMD_DEV_ENABLE_I2C                 ((uint8_t)0x01)  ///< Enable the I2C Host Interface
#define PH_RPC_CMD_DEV_ENABLE_SPI                 ((uint8_t)0x02)  ///< Enable the SPI Host Interface
#define PH_RPC_CMD_DEV_ENABLE_HSU                 ((uint8_t)0x03)  ///< Enable the HSU Host Interface
/** @} */

/** \name USB to I2C and SPI Conversion, I/O
 * @{
 * \par I2C
 * Use \ref phRpc_H_DutInit to activate the periperal. Initialisation determines device address and speed.
 * Please see \ref PH_RPC_CMD_DEV_ENABLE_I2C, ignore SPI specific parameters.
\code
// Activating I2C with speed = 400kHz, ignoring return values.
// Assuming that the device is opened and dev_handle is valid.
(void)phRpc_H_DutInit(dev_handle, PH_RPC_CMD_DEV_ENABLE_SPI,
                      0,                                        // External device address
                      400000,                                   // Speed
                      0, 0);                                    // Ignore these, set to 0
\endcode
 * \b Example Device Interface Activation
 * \n\n
 * \par SPI
 * The software uses the processor's SSP0 periperal in SPI mode. A set of different operating modes
 * is available. The user must ensure that the selected mode is compatible to what the external device
 * supports.
 *
\verbatim
    ____________________________________________

    CPOL    CPHA    AUTO    SW      IDLE    DATA
                    NSS     NSS     SCK     CAPT
    ____________________________________________

    0       0       T       L       L       1st
    0       1       L       L       L       2nd
    1       0       T       L       H       1st
    1       1       L       L       H       2nd

\endverbatim
 * \b Table Overview of SPI Signal behaviour
 * \n\n
 * When the interface is idle, NSS is forced HIGH.
 * - CPOL controls the SCK idle level:
 *      - With CPOL being 0, SCK is forced LOW in idle state.
 *      - Else it is idle HIGH.
 *      .
 * - CPHA determines at which edge the data shall be sampled:
 *      - With CPHA being 0, \b T in the table above means that NSS goes HIGH between words transmitted.
 *        CPHA being 0 means also that sampling of the serial data takes place on the first edge.
 *      - Else, data is captured on the second clock edge.
 *      .
 * - NSS Auto mode and Software Override:
 *      - With this mode set to 0, the periperal automatically applies NSS according to what is written above.
 *      - When the mode is active, NSS is held LOW all the time while data is being transferred, regardless
 *        of the clock phase setting.
 *      .
 * .
 *
 * Use \ref phRpc_H_DutInit to activate the periperal. Initialisation determines CPOL and CPHA and
 * activates AUTO NSS. Please see \ref PH_RPC_CMD_DEV_ENABLE_SPI, \ref PH_RPC_CMD_DEV_SPI_CPOL_L,
 * \ref PH_RPC_CMD_DEV_SPI_CPOL_H, \ref PH_RPC_CMD_DEV_SPI_CPHA_1ST, \ref PH_RPC_CMD_DEV_SPI_CPHA_2ND.
 * \n\n
 * When it is desired to have a stable LOW NSS regardless of the CPOL and CPHA settings call
 * \ref phRpc_H_DevIoCtl immediately after initialisation. Deactivate AUTO mode with \ref PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS
 * as major code and use as minor code the value \ref PH_RPC_IOCTL_MN_DISABLE.
 *
\code
// Activating SPI with AUTO NSS = OFF, speed = 1MHz, ignoring return values.
// Assuming that the device is opened and dev_handle is valid.
uint32_t opt = 0; // No optional parameter needed, set to 0 therefore.

(void)phRpc_H_DutInit(dev_handle, PH_RPC_CMD_DEV_ENABLE_I2C,
                      0,                                        // External device address
                      1000000,                                  // Speed
                      PH_RPC_CMD_DEV_SPI_CPOL_H,                // Clock Polarity
                      PH_RPC_CMD_DEV_SPI_CPHA_1ST);             // Clock Phase
(void)phRpc_H_DevIoCtl(dev_handle,
                       PH_RPC_IOCTL_MJ_DEV_SPI_AUTONSS,         // Control AUTO NSS behaviour
                       PH_RPC_IOCTL_MN_DISABLE, &opt);          // Disable feature
\endcode
 * \b Example Device SPI Interface Activation
 * \n\n
 * SPI uses DMA. The SPI transfer is done while the CPU performs other activities. The external device
 * therefore sees a contiguous stream of data even at high rates.
 *
 */

// Attributes
#define PH_RPC_CMD_DEV_SPI_CPOL_L                 ((uint8_t)0x00)  ///< Clock Polarity idle Low
#define PH_RPC_CMD_DEV_SPI_CPOL_H                 ((uint8_t)0x01)  ///< Clock Polarity idle High
#define PH_RPC_CMD_DEV_SPI_CPHA_1ST               ((uint8_t)0x00)  ///< Clock Phase L, capture data on first clock edge
#define PH_RPC_CMD_DEV_SPI_CPHA_2ND               ((uint8_t)0x01)  ///< Clock Phase H, capture data on second clock edge

// Commands (RPC Ordinals!)
#define PH_RPC_CMD_DEV_RW_SHORT                   ((uint8_t)0x42)  ///< \internal Short exchange
#define PH_RPC_CMD_DEV_RW_LONG                    ((uint8_t)0x43)  ///< \internal Long exchange

#define PH_RPC_CMD_DEV_R                          ((uint8_t)0x00)  ///< \internal Read command for DUT
#define PH_RPC_CMD_DEV_W                          ((uint8_t)0x01)  ///< \internal Write command for DUT
#define PH_RPC_CMD_DEV_RW                         ((uint8_t)0x02)  ///< \internal Write + [interrupt + ] Read commands for DUT

/** @} */

/** @} */ // Intf Conv


// ________________________________________________________________________________________________
//
// Check Functions
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_chkfn  Check Functions
 * \ingroup grp_rpc_common
 *
 * \n \b Function: \ref phRpc_H_DeviceCommCheck
 * \copydoc phRpc_H_DeviceCommCheck
 * \n \b Function: \ref phRpc_H_DeviceCommCheckLong
 * \copydoc phRpc_H_DeviceCommCheckLong
 * \n \b Function: \ref phRpc_H_DeviceCommCheckWTX
 * \copydoc phRpc_H_DeviceCommCheckWTX
 *
 * @{
 */

/** \name Communication Check
 * @{
 */
#define PH_RPC_CMD_COMMCHECK_BUFLEN            ((uint8_t)240)   ///< Device Communication check buffer length
#define PH_RPC_CMD_COMMCHECK_L_BUFLEN        ((uint16_t)1200)   ///< Device Communication check buffer length, long buffer
/** @} */

/** \name Microcontroller Log
 * @{
 */
#define PH_RPC_CMD_WTXLOG_BUFLEN                ((uint8_t)8)   ///< Device Communication check buffer length
/** @} */

/** @} */ // Check

#ifdef __cplusplus
}
#endif // CPP

#endif // Guard
