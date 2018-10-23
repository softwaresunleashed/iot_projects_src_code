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
* Project: Secondary RPC Host Library Command and Data Field Definitions / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 19198 $
* $Date: 2013-05-13 09:40:09 +0200 (Mo, 13 Mai 2013) $
*
* Created: Gerald Kersch-Koncar, May 2013
*
*/

#ifndef PHRPC_CMD_2_H //
#define PHRPC_CMD_2_H //

// ________________________________________________________________________________________________
//
// INCLUDE
// ________________________________________________________________________________________________

#include "phRpc_Cmd.h"  // Common definitions taken from there

// ________________________________________________________________________________________________
//
// DEFINE
// ________________________________________________________________________________________________

#ifdef __cplusplus
extern "C" {
#endif // CPP


/**
 * \addtogroup grp_rpc_common2
 *
 * @{
 */

// ________________________________________________________________________________________________
//
// Buffer Definitions
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_secondary_buffer Secondary Channel Buffer Definitions
 * \ingroup grp_rpc_common2
 *
 * @{
 */

/** \name User Buffer Definition
 *
 * The user buffer is internally allocated by the PC library and of a fixed size. Allocation is done
 * by \ref phRpc_H_Open.
 *
 * @{
 */

#define PH_RPC_2_CMD_H_MINDEVBUFLEN                           64u     ///< Minimum number of bytes to transfer
#define PH_RPC_2_CMD_PREPEND_LEN                               4u     ///< Reserved for further data encapsulation at endpoint

/** \brief Maximum Data size without prepended header for communication between device and secondary channel
 *
 * The maximum size of user data without any protocol header for the secondary channel. As a protocol for communication
 * between the device and the DUT can be used data must be prepended. This length definition does not comprise the
 * length of prepended data.
 *
 */
 #define PH_RPC_2_CMD_USER_DATA_BUFSIZE                 320u //

/** \brief Maximum number of bytes available for the transfer (see \ref PH_RPC_2_CMD_RPCBUFFER_LEN)
 *
 *   Maximum number of bytes that the RPC functions can fill with user data.
 *   The user must be aware that this is the total number of bytes
 *   that may be transferred comprising all serialised data. The sum of the individual
 *   data field sizes to serialise must not become larger than this number.
 */
#define PH_RPC_2_CMD_USER_BUFSIZE                       (PH_RPC_2_CMD_USER_DATA_BUFSIZE+PH_RPC_2_CMD_PREPEND_LEN) //

/// \brief Maximum number of bytes that can be transferred via the secondary channel
#define PH_RPC_2_CMD_RPCBUFFER_LEN                      (PH_RPC_2_CMD_USER_BUFSIZE+PH_RPC_2_CMD_H_MINDEVBUFLEN) //

/** @} */ // name

/** @} */ // group.

/**
 * \defgroup grp_rpc_common_secondary_ioctl Secondary Channel I/O Control
 * \ingroup grp_rpc_common2
 *
 * @{
 */

 /** \name Common I/O Control Definitions for Minor I/O Control Codes
 * Functions: \ref phRpc_H_DevIoCtl, \ref phRpc_H_HostIoCtl
 * @{
 */
#define PH_RPC_2_IOCTL_MN_DISABLE                ((uint8_t)0x00)  ///< Deactivate Feature
#define PH_RPC_2_IOCTL_MN_ENABLE                 ((uint8_t)0x01)  ///< Activate Feature
#define PH_RPC_2_IOCTL_MN_VOID                   ((uint8_t)0xFF)  ///< No minor code applicable
/** @} */

/** \name Device I/O Control Opt: Not Applicable
 * @{
 */
#define PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE       0xFFFFFFFFu     ///< Value is not used.
/** @} */

/** \name Device I/O Control Opt: Post-Reset Waiting Time
 * @{
 */
#define PH_RPC_2_IOCTL_OPT_PRWT_MAX             2000u           ///< Maximum waiting time after ESE reset.
#define PH_RPC_2_IOCTL_OPT_PRWT_DEFAULT         10u             ///< Default waiting time after ESE reset.
/** @} */

/** \name Device I/O Control Opt: Protocol Type
 *
 * Optional parameter settings for configuration of protocol type to be used.
 *
 * @{
 */
#define PH_RPC_2_IOCTL_OPT_DEV_SET_PROTOCOL_RAW           0x00000000u     ///< No protocol: raw mode will be used.
#define PH_RPC_2_IOCTL_OPT_DEV_SET_PROTOCOL_T_EQ_1        0x00000001u     ///< T=1 protocol will be used.
/** @} */

// ________________________________________________________________________________________________
// USB Communication, RPC (0..)

// ________________________________________________________________________________________________
// System, OS, Tasks (0x10..)

// ________________________________________________________________________________________________
// I/O, Communication Mode, Parameters (0x40..)

/**
 * \brief [NV] Auto-NSS
 *
 * SPI HW handles the SPI \c NSS line automatically. Switch to Software NSS by disabling this feature.
 * SW NSS keeps NSS low during the entire transfer regardless of CPHA and CPOL.
 * - Minor: \ref PH_RPC_2_IOCTL_MN_DISABLE, \ref PH_RPC_2_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_2_IOCTL_MJ_DEV_SPI_AUTONSS                 ((uint8_t)0x40) //

/**
 * \brief Control the Protocol Type Mode
 *
 * This code configures the communication protocol to be used by the ESE.
 * - Minor: \ref PH_RPC_2_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_DEV_SET_PROTOCOL_T_EQ_1
 */
#define PH_RPC_2_IOCTL_MJ_DEV_SET_PROTOCOL_TYPE          ((uint8_t)0x41) //

/**
 * \brief SPI Loop Back Control
 *
 * The SPI Loop Back Control enables the built-in diagnostic feature that echoes data sent.
 * Use this for diagnosis only, as the terminal to the external device is deactivated.
 * - Minor: \ref PH_RPC_2_IOCTL_MN_DISABLE, \ref PH_RPC_2_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 */
#define PH_RPC_2_IOCTL_MJ_DEV_LOOPBACK                    ((uint8_t)0x42) //

/**
 * \brief Set Device Speed
 *
 * This code configures the device speed any time after device interface initialisation.
 * Use \ref PH_RPC_2_IOCTL_MJ_DEV_GET_SPEED to read back the speed setting.
 *
 * - Minor: \ref PH_RPC_2_IOCTL_MN_VOID
 * - Opt[in]: Communication speed [baud]
 * .
 *
 * \note The setting can only be applied if the interface has been initialised.
 */
 #define PH_RPC_2_IOCTL_MJ_DEV_SET_SPEED                ((uint8_t)0x43) //

/**
 * \brief Get Device Speed
 *
 * This code returns the device interface speed. Please note that the returned speed may
 * considerably deviate from the speed set during initialisation or via the code
 * \ref PH_RPC_2_IOCTL_MJ_DEV_SET_SPEED. This is because the interface hardware with
 * its peripheral clock frequency and prescalers, divide and multiply registers
 * does not support every speed setting.
 *
 * - Minor: \ref PH_RPC_2_IOCTL_MN_VOID
 * - Opt[out]: Communication speed [baud]
 * .
 *
 * \note The returned value is only valid if the interfaces has been initialised.
 *
 */
 #define PH_RPC_2_IOCTL_MJ_DEV_GET_SPEED                ((uint8_t)0x44) //

/**
 * \brief Wait for external interrupt or interrupt timeout.
 *
 * This code causes ESE to wait for an external interrupt event or timeout condition.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 *
 */
 #define PH_RPC_2_IOCTL_MJ_DEV_WAIT_EXT_INT             ((uint8_t)0x45) //

/**
 * \brief Get the ESE communication status.
 *
 * This code fetches the current communication status.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 *
 */
 #define PH_RPC_2_IOCTL_MJ_DEV_GET_COMM_STATUS          ((uint8_t)0x46) //

/**
 * \brief Activate or Deactivate External Interrupt Sensing
 *
 * Controls the automatic external interrupt sensing. For special I/O operations the external Interrupt line
 * may not be needed. The default setting is OFF.
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 * \note The following applies for external interrupt sensing:
 *       -  \b Avoid \b Race \b Conditions: For normal I/O operations where an external device indicates
 *          data to be present by applying a certain level to the IRQ line it is not recommended to deactivate
 *          interrupt sensing. A race condition that may disrupt the external device could be the consequence.
 *          However, when an external device must be polled for data presence it is preferable to deactivate
 *          external interrupt sensing.
 *       - \b Sense \b Settings: The interrupt sense settings are used as previously applied by
 *          \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE.
 *       - \b Host \b Based \b Operation: When the host decides to sense external interrupt events
 *          (using \ref PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ) automatic sensing has to be switched OFF.
 *       .
 *
 * \sa \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_SENSE, \ref PH_RPC_IOCTL_MJ_DEV_SET_EINT_TIMEOUT,
 *      \ref PH_RPC_IOCTL_MJ_DEV_WAIT_IRQ
 */
#define PH_RPC_2_IOCTL_MJ_DEV_EINT_SENSE_ENABLE        ((uint8_t)0x47) //

 /**
 * \brief External Interrupt Sensing Mode/Type
 *
 * Set the sensing mode and type {Level H/L, Edge R/F} for External Interrupt
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Sense settings see \ref PH_RPC_IOCTL_OPT_EINT_SENSE_LEVEL_L and others
 * .
 * \note    This command changes interrupt sensing mode only. In order to activate or deactivate
 *          interrupt sensing please use \ref PH_RPC_IOCTL_MJ_DEV_EINT_SENSE_ENABLE.
 * \sa \ref PH_RPC_2_IOCTL_MJ_DEV_EINT_SENSE_ENABLE
 */
#define PH_RPC_2_IOCTL_MJ_DEV_SET_EINT_SENSE            ((uint8_t)0x48) //

/**
 * \brief Reset ESE
 *
 * Resets the ESE and the protocol.
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 * \note The reset command performs the following steps:
 *          -# Check for the current baud rate: If lower than 500kbd it is set to 1Mbd.
 *          -# Set the reset line to active level.
 *          -# Wait for 1 ms.
 *          -# Send one byte (0xFF) causing SCK to toggle.
 *          -# Wait for 1 ms.
 *          -# Set the reset line to non-active level.
 *          -# If required, restore the previous baud rate.
 *          -# Reset the protocol state machine.
 *          -# Wait for a predefined time
 *          .
 */
#define PH_RPC_2_IOCTL_MJ_DEV_RESET_ESE                 ((uint8_t)0x49) //

/**
 * \brief Determine whether the secondary interface I/O system will use DMA.
 *
 * Switch DMA action on or off. The default setting is ON.
 * - Minor: \ref PH_RPC_2_IOCTL_MN_DISABLE, \ref PH_RPC_2_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 */
#define PH_RPC_2_IOCTL_MJ_DEV_SET_USE_DMA               ((uint8_t)0x4A) //

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
 #define PH_RPC_2_IOCTL_MJ_DEV_WAIT                      ((uint8_t)0x4B) //

/**
 * \brief Set External Interrupt Timeout
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
#define PH_RPC_2_IOCTL_MJ_DEV_SET_EINT_TIMEOUT          ((uint8_t)0x4C) //

/**
 * \brief Get IRQ Input Level
 *
 * Reads the logical level at the IRQ input on the secondary channel.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Output only: IRQ Level
 * .
 * \note The Function does not block until an interrupt occurs.
 *
 */
#define PH_RPC_2_IOCTL_MJ_DEV_GET_IRQLVL                ((uint8_t)0x4D) //

/**
 * \copydoc PH_RPC_IOCTL_MJ_DEV_RND
 */
 #define PH_RPC_2_IOCTL_MJ_DEV_RND                      ((uint8_t)0x4E) //

 /**
 * \brief Set Post-Reset waiting time
 *
 * Sets the time the LPC waits after a reset of the ESE
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_VOID
 * - Opt: Waiting time in ms. Maximum time is \ref PH_RPC_2_IOCTL_OPT_PRWT_MAX.
 * .
 *
 */
#define PH_RPC_2_IOCTL_MJ_DEV_SET_PRWT                  ((uint8_t)0x4F) //

 /**
 * \brief Control virtual card for communications self-test.
 *
 * A built-in virtual card is used for communications self-test: Enable or
 * disable the card. Not for production. The default setting is OFF.
 *
 * - Minor: \ref PH_RPC_IOCTL_MN_DISABLE, \ref PH_RPC_IOCTL_MN_ENABLE
 * - Opt: \ref PH_RPC_2_IOCTL_OPT_NOT_APPLICABLE
 * .
 *
 */
#define PH_RPC_2_IOCTL_MJ_DEV_VCARD_TEST                ((uint8_t)0x50) //

/** @} */ // CH2 IOCTL

/**
 * \defgroup grp_rpc_common_secondary_test Secondary Channel Test Functions
 * \ingroup grp_rpc_common2
 *
 * @{
 */

/** \name Communication Check
 * @{
 */

#define PH_RPC_2_CMD_COMMCHECK_WTX_BUFLEN               PH_RPC_2_CMD_USER_DATA_BUFSIZE   ///< Device Communication check buffer length, long buffer

/** @} */ // name

/** @} */ // grp Test


// ________________________________________________________________________________________________
//
// SPI Converter
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_secondary_intf_conv  Interface Converter
 * \ingroup grp_rpc_common_2
 *
 * \n \b Function: \ref phRpc_2_H_DutInit
 * \copydoc phRpc_2_H_DutInit
 *
 * @{
 */

/** \name USB to SPI Conversion Buffer Sizes
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
 * buffer at the start of the transfer buffer for that purpose on each call.
 *
 * @{
 */
#define PH_RPC_2_CMD_EXT_DEV_BUFSIZE                PH_RPC_2_CMD_USER_BUFSIZE   ///< Maximum Host Interface user buffer size
#define PH_RPC_2_CMD_EXT_DEV_PREPEND                PH_RPC_2_CMD_PREPEND_LEN    ///< Reserved for further data encapsulation at endpoint
/** @} */

/** \name USB to SPI Conversion, INIT
 * @{
 */
#define PH_RPC_2_CMD_DEV_DISABLE_EXT_INTF          ((uint8_t)0x00)  ///< Switch off the Host Interface
#define PH_RPC_2_CMD_DEV_ENABLE_SPI                ((uint8_t)0x01)  ///< Enable the SPI (SSP1) Host Interface
/** @} */ // name

/** \name USB to SPI Conversion, I/O
 * @{
 * \par SPI
 * The software uses the processor's SSP1 periperal in SPI mode. A set of different operating modes
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
 */

// Attributes
#define PH_RPC_2_CMD_DEV_SPI_CPOL_L               ((uint8_t)0x00)  ///< Clock Polarity idle Low
#define PH_RPC_2_CMD_DEV_SPI_CPOL_H               ((uint8_t)0x01)  ///< Clock Polarity idle High
#define PH_RPC_2_CMD_DEV_SPI_CPHA_1ST             ((uint8_t)0x00)  ///< Clock Phase L, capture data on first clock edge
#define PH_RPC_2_CMD_DEV_SPI_CPHA_2ND             ((uint8_t)0x01)  ///< Clock Phase H, capture data on second clock edge

#define PH_RPC_2_CMD_DEV_R                        ((uint8_t)0x00)  ///< \internal [interrupt + ] Read command for DUT
#define PH_RPC_2_CMD_DEV_W                        ((uint8_t)0x01)  ///< \internal Write command for DUT

/** @} */

/** @} */ // grp Interface Converter

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
#define PH_RPC_2_CMD_DEVINFO_BUFLEN                 ((uint8_t)48)   ///< Maximum length of the Device Information
// Commands
#define PH_RPC_2_CMD_DEVINFO_CPUSNR                 ((uint8_t)0x00) ///< [A] CPU serial number
#define PH_RPC_2_CMD_DEVINFO_CPUID                  ((uint8_t)0x01) ///< [A] CPU ID
#define PH_RPC_2_CMD_DEVINFO_SWID                   ((uint8_t)0x05) ///< [A] Primary Firmware SW identification string
#define PH_RPC_2_CMD_DEVINFO_LOGICAL_ID             ((uint8_t)0x06) ///< [N] Logical device ID, see \ref PH_RPC_IOCTL_MJ_DEV_SET_LOGICAL_ID
#define PH_RPC_2_CMD_DEVINFO_SWITCHSTATE            ((uint8_t)0x12) ///< [N] GP Switch state
#define PH_RPC_2_CMD_DEVINFO_ASYN_MONITOR_ENABLED   ((uint8_t)0x13) ///< [N] Asynchronous task deadline monitoring enable state
#define PH_RPC_2_CMD_DEVINFO_ASYN_MONITOR_TIMEOUT   ((uint8_t)0x14) ///< [N] Asynchronous task deadline monitoring timeout value in ms
#define PH_RPC_2_CMD_DEVINFO_EXT_INT_TIMEOUT        ((uint8_t)0x15) ///< [N] External Interrupt Timeout value in ms

#define PH_RPC_2_CMD_DEVINFO_IOTIME                 ((uint8_t)0x20) ///< [A] I/O time measurement result, serialised as {Status|ID|V0V1V2V3}; {Start|Checkpoint1|..}
/** @} */

/** \name TX/RX Flags
 *
 * RX and TX flags determine the behaviour of the transmit and receive functions.
 *
 * @{
 */

/**
 * \brief Meta Chaining
 *
 * The I/O system can communicate with an external device that is for instance able to receive and to provide more data
 * than the LPC can transfer at a time. Therefore a host meta chaining mechanism is in place that can be controlled with the
 * flag.
 */
#define PH_RPC_2_CMD_TRX_METACHAINING               0x00000001u     ///< Meta chaining is determined by this bit

#define PH_RPC_2_CMD_TRX_S_BLOCK                    0x00000080u

#define PH_RPC_2_CMD_TRX_S_BLOCK_ABORT              0x00000082u

#define PH_RPC_2_CMD_TRX_S_BLOCK_RESYNCH            0x00000084u

/** @} */ // Flags

// ________________________________________________________________________________________________
//
// I/O Line Control
// ________________________________________________________________________________________________

/**
 * \defgroup grp_rpc_common_iolnctl_2  I/O Line Control Codes of Channel 2
 * \ingroup grp_rpc_common
 * \n \b Function: \ref phRpc_2_H_DevIoLineCtl
 * \copydoc phRpc_2_H_DevIoLineCtl
 *
 * \section sec_rpc_common_iolnctl_2 Control Codes
 * For control codes please see \ref grp_rpc_common_iolnctl. The same control codes as for channel 1 (but using
 * channel 2's function \ref phRpc_2_H_DevIoLineCtl) apply for the secondary channel.
 *
 * @{
 */

 /** \name Common I/O LineControl (CH 2) Definitions for Optional Parameter
 * \n \b Function: \ref phRpc_2_H_DevIoLineCtl
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
#define PH_RPC_2_IO_LINE_CTL_OPT_NOT_APPLICABLE     0xFFFFFFFFu   //

/** @} */ // Opt Param

/** @} */ // IO Ln Ctrl

/** @} */ // 2nd RPC

#ifdef __cplusplus
}
#endif // CPP

#endif // Guard
