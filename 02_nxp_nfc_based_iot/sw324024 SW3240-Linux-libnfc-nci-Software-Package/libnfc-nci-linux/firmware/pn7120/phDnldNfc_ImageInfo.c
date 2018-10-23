/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Electronics N.V.2012
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/
/**
* \file  phDnldNfc_ImageInfo.c
* \brief Firmware Download Image info like eeprom,flash,bSig & version
*
* Project: NFC MW / HAL
*
* $Date: 2012-11-19 12:08:18 +0530 (Mon, 19 Nov 2012) $
* $Author: nxp33722 $
* $Revision: 14974 $
*
*/
#include <phNfcTypes.h>
#include <phDnldNfc_ImageInfo.h>

/* PN547 New Mw Version to be UPDATED for every new Release made */
//static const uint8_t nxp_nfc_mw_version[] = {
//    NXP_MW_VERSION_MAJ, NXP_MW_VERSION_MIN
//};

#define DLL_EXPORT

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef ANDROID
uint8_t* gphDnldNfc_DlSeq  = &gphDnldNfc_DlSequence[0];
#else
DECLDIR uint8_t* gphDnldNfc_DlSeq  = &gphDnldNfc_DlSequence[0];
#endif

#if 0
DECLDIR uint16_t  phDnldNfc_GetImgInfo(uint8_t **pImgPtr)
{
    uint16_t wLen = 0;

    wLen = gphDnldNfc_DlSeqSz;
    *pImgPtr = gphDnldNfc_DlSequence;

    return wLen;
}

DECLDIR uint16_t  phDnldNfc_GetImgVer(void)
{
    uint16_t wFwVer;

    wFwVer = (((uint16_t)(gphDnldNfc_DlSequence[5]) << 8U) | (gphDnldNfc_DlSequence[4]));

    return wFwVer;
}

DECLDIR uint16_t  phDnldNfc_GetMwVer(void)
{
    uint16_t wMwVer;

    wMwVer = (((uint16_t)(nxp_nfc_mw_version[0]) << 8U) | (nxp_nfc_mw_version[1]));

    return wMwVer;
}
#endif

#ifdef __cplusplus
}
#endif
