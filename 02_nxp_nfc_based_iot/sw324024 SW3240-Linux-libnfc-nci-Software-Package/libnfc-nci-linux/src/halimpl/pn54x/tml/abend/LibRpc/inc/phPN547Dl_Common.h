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
*                           arising from its use.
*/

/** \file
* Project: External Device Driver / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 3327 $
* $Date: 2011-10-07 15:14:18 +0200 (Fr, 07 Okt 2011) $
*
* Created: Mar. 2011 by Gerald Kersch-Koncar
*
*/

#ifndef PHPN547DL_COMMON_H
#define PHPN547DL_COMMON_H

#ifndef PH_RPC_SKIP_STDINT
#include <stdint.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif // CPP

/**
 * \defgroup grp_comps_pn547_common PN 547 Device I/O Common Definitions
 * \ingroup grp_comps
 *
 * Common definitions used for Access to the Device-Under-Test.
 *
 * @{
 */

// ________________________________________________________________________________________________
//
// DEFINITIONS
// ________________________________________________________________________________________________

/** \name Notification Callback
 *
 * Definitions for the notification callback function.
 *
 * @{
 */

#define PH_PN547DL_CTX_THREAD   0   ///< The call is done from within thread context
#define PH_PN547DL_CTX_ISR      1u  ///< The call is done from within ISR context

/** \brief Notification Callback Function Pointer
 *
 * The notification callback function is a function that is called by the I/O system when an
 * external interrupt or a related event (e.g . external interrupt timeout) occurs. The function must be implemented and
 * registered by the secondary firmware.
 *
 * \par Parameters
 * -    User Context, a pointer to a user-defined structure, provided during callback registration
 * -    Callback status to be evaluated by the user-defined software, providing information whether the reason
 *      for the call is actually an interrupt event or a time-out condition. See \ref PH_RPC_STATUS_OK.
 * -    Call context: In order to invoke the correct variant of an OS function (e.g. to signal a semaphore)
 *      it is necessary to know the context of the call. See \ref PH_PN547DL_CTX_THREAD.
 * .
 *
 * It is not recommended to re-arm the notification within the context of this function call due to limited stack
 * depth of the interrupt stack. If doing so nevertheless, perform careful stack usage evaluation.
 *
 */
typedef void (*pphPN547Dl_Notification_t) (void*, uint16_t, uint8_t);

/** @} */ // Name


/** \name Definitions
 *
 * Definitions that can be used to interpret the mode fields that are listed here
 *
 * @{
 */

#define PH_PN547DL_MODE_VAL_NONE        0   ///< No mode has been set, the I/O system is deactivated
#define PH_PN547DL_MODE_VAL_I2C         1   ///< I2C mode has been selected
#define PH_PN547DL_MODE_VAL_SPI         2   ///< SPI mode has been selected
#define PH_PN547DL_MODE_VAL_HSU         3   ///< HSU mode has been selected

/** @} */ // Name

/** \name Device Mode Page 0
 *
 * I/O System Operating Mode: The I/O system settings can be retrieved using the function
 * \ref phRpc_H_DutGetMode of the PC Library. The output of this function can be analysed
 * using mask and shift operations with the definitions in this section.
 *
 * @{
 */

// Mode Getter Support
#define PH_PN547DL_MODE_MASK                 0x0000000Fu     ///< Mode Bit Mask (I2C, SPI, HSU)
#define PH_PN547DL_MODE_SHIFT                          0     ///< Mode Bits Shift Number
#define PH_PN547DL_DLLMODE_MASK              0x00000070u     ///< Mask for Data Link Mode
#define PH_PN547DL_DLLMODE_SHIFT                       4     ///< Data Link Mode Shift Number
#define PH_PN547DL_LOOPBACK_MASK             0x00000080u     ///< Bit for SPI Loopback Mode
#define PH_PN547DL_RAWMODE_MASK              0x00000100u     ///< Bit for Raw Mode Override
#define PH_PN547DL_AUTONSS_MASK              0x00000200u     ///< Bit for Auto NSS
#define PH_PN547DL_CPOL_MASK                 0x00000400u     ///< Bit for SPI CPOL
#define PH_PN547DL_CPHA_MASK                 0x00000800u     ///< Bit for SPI CPHA
#define PH_PN547DL_CTLBYTE_MASK              0x000FF000u     ///< Control Byte Mask (I2C Address)
#define PH_PN547DL_CTLBYTE_SHIFT                      12     ///< Control Byte Shift Number
#define PH_PN547DL_SPEED_MASK_0              0x000000FFu     ///< Speed Mask
#define PH_PN547DL_SPEED_MASK                0x0FF00000u     ///< Speed Mask, shifted
#define PH_PN547DL_SPEED_SHIFT                        20     ///< Speed Shift Number
#define PH_PN547DL_SPEED_LSB                      50000u     ///< One LSB for speed (resolution)
#define PH_PN547DL_IGNORE_EINT_TIMEOUT_MASK  0x10000000u     ///< Bit for EINT Timeout Ignore
#define PH_PN547DL_ENABLE_EINT_SENSE_MASK    0x20000000u     ///< Bit for EINT Sense Enable
#define PH_PN547DL_ENABLE_CRC_MASK           0x40000000u     ///< Bit for CRC Enable
#define PH_PN547DL_EXPG                      0x80000000u     ///< Bit for Extended Pages

/** @} */ // Name

/** \name Device Mode Extended Pages
 *
 * Extended page definitions for the I/O System Operating Mode: The output of this function can be analysed
 * using mask and shift operations with the definitions in this section.
 *
 * @{
 */

#define PH_PN547DL_EXPG_MASK                0x0000000Fu     ///< Extended Page Mask
#define PH_PN547DL_EXPG_SHIFT                         0     ///< Extended Page Shift Number
#define PH_PN547DL_HW_CTRL_FLOW             0x00000010u     ///< Bit for HW Control Flow
#define PH_PN547DL_FULLDUPLEX               0x00000020u     ///< Bit for Full Duplex Mode
#define PH_PN547DL_TX_SOF_PRESENT           0x00000040u     ///< Bit for TX SOF Presence
#define PH_PN547DL_RX_SOF_PRESENT           0x00000080u     ///< Bit for RX SOF Presence
#define PH_PN547DL_I2C_ATOMIC_TRANSFER      0x00000100u     ///< Bit for I2C W/R Transfer without Intermediate Stop
#define PH_PN547DL_HW_CTRL_FLOW_CTS         0x00000200u     ///< Only CTS is automatic, RTS is always asserted during RX
#define PH_PN547DL_EOF_N_MASK               0x0003C000u     ///< EOF N Mode mask
#define PH_PN547DL_EOF_N_SHIFT                       14     ///< EOF N Mode shift
#define PH_PN547DL_HSUFMT_MASK              0x00FC0000u     ///< HSU Format mask
#define PH_PN547DL_HSUFMT_SHIFT                      18     ///< HSU Format shift

/** @} */ // Name

/** \name Pin Probe Diagnostic Result
 *
 * Pin probing is done on external interface activation.
 *
 * @{
 */

#define PH_PN547DL_PINPROBESTATUS_OK                0x00    ///< Pin Probe OK
#define PH_PN547DL_PINPROBESTATUS_I2C_LOW           0x01    ///< I2C pins stuck low
#define PH_PN547DL_PINPROBESTATUS_HSU_RTS_LOW       0x01    ///< RTS pins stuck low

/** @} */ // Name

/** @} */ // Group

#ifdef __cplusplus
}
#endif // CPP

#endif // Guard
