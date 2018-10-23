/*
 *         Copyright (c), NXP Semiconductors
 *
 *                       (C)NXP Electronics N.V.2011
 *         All rights are reserved. Reproduction in whole or in part is
 *        prohibited without the written consent of the copyright owner.
 *    NXP reserves the right to make changes without notice at any time.
 *   NXP makes no warranty, expressed, implied or statutory, including but
 *   not limited to any implied warranty of merchantability or fitness for any
 *  particular purpose, or that the use will not infringe any third party patent,
 *   copyright or trademark. NXP must not be liable for any loss or damage
 *                            arising from its use.
 *
 */

/**
 * \file  phTmlNfc_Utils.c
 * \brief TML Utility function provided to other layers.
 */

/** \addtogroup grp_tml_nfc
 @{
 */
#include <phTmlNfc.h>
#include <phLog_Tml.h>
/**
 * CRC computed shall be inverted */
#define INVERT_CRC
/**
 *
 * This function shall calculate CRC on the input byte and store
 *  pointer passed to the function
 * \param[in] bCrcByte  Byte on which CRC needs to be be calculated.
 * \param[in] pCrc      Location where CRC value to be updated.
 *
 * \retval None
 *
 */
static void phTmlNfc_H_UpdateCrc(uint8_t bCrcByte,
    uint16_t *pCrc)
{
    PH_LOG_TML_FUNC_ENTRY();
    bCrcByte = (bCrcByte ^ (uint8_t) ((*pCrc) & 0x00FF));
    bCrcByte = (bCrcByte ^ (uint8_t) (bCrcByte << 4));
    *pCrc = (*pCrc >> 8) ^ ((uint16_t) bCrcByte << 8) ^
        ((uint16_t) bCrcByte << 3) ^
        ((uint16_t) bCrcByte >> 4);
    PH_LOG_TML_FUNC_EXIT();
}

void phTmlNfc_ComputeCrc(uint8_t *pData,
    uint8_t bLength,
    uint8_t *pCrc1,
    uint8_t *pCrc2)
{
    uint8_t bCrc_byte = 0;
    uint8_t bIndex = 0;
    uint16_t wCrc = 0;

#ifdef CRC_A
    wCrc = 0x6363; /* ITU-V.41 */
#else
    wCrc = 0xFFFF; /* ISO/IEC 13239 (formerly ISO/IEC 3309) */
#endif /* #ifdef CRC_A */

    PH_LOG_TML_FUNC_ENTRY();
    PH_LOG_TML_INFO_HEXDATA("phTmlNfc_ComputeCrc", pData, bLength);
    do
    {
        bCrc_byte = pData[bIndex];
        phTmlNfc_H_UpdateCrc(bCrc_byte, &wCrc);
        bIndex++;
    } while (bIndex < bLength);

#ifdef INVERT_CRC
    wCrc = ~wCrc; /* ISO/IEC 13239 (formerly ISO/IEC 3309) */
#endif /* #ifndef INVERT_CRC */

    *pCrc1 = (uint8_t) (wCrc & 0xFF);
    *pCrc2 = (uint8_t) ((wCrc >> 8) & 0xFF);
    PH_LOG_TML_INFO_HEXDATA("phTmlNfc_ComputeCrc : Computed CRC 1->", pCrc1, bLength);
    PH_LOG_TML_INFO_HEXDATA("phTmlNfc_ComputeCrc : Computed CRC 2->", pCrc2, bLength);
    PH_LOG_TML_FUNC_EXIT();
    return;
}
/** @} */
