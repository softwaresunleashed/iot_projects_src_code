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
 * \file  phDnldNfc_ImageInfo.h
 * \brief Api's to get Firmware Download Image info & version info
 *
 * Project: NFC MW / HAL
 *
 * $Date: 2012-11-19 12:08:18 +0530 (Mon, 19 Nov 2012) $
 * $Author: nxp33722 $
 * $Revision: 14974 $
 *
 */
#ifndef PHDNLDNFC_IMAGEINFO_H /* */
#define PHDNLDNFC_IMAGEINFO_H/* */

#define ANDROID
//#include <phNfcConfig.h>
#ifndef ANDROID
#define DECLDIR __declspec(dllexport)
#endif

/* PN547 Download Write Frames sequence */
extern uint8_t gphDnldNfc_DlSequence[];

#ifdef ANDROID
extern uint8_t*  gphDnldNfc_DlSeq;
extern uint16_t gphDnldNfc_DlSeqSz;
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef ANDROID
DECLDIR uint8_t*  gphDnldNfc_DlSeq;
DECLDIR uint16_t gphDnldNfc_DlSeqSz;
#endif
/**
 * \ingroup grp_dl_nfc
 *
 * \brief The phDnldNfc_GetImgInfo function returns the fw image data pointer and
 *        length
 *
 * \param[out] pImgPtr      Pointer to Fw Image data.
 *
 *  \retval                 Length of Fw Image data.
 *
 */

#if 0
DECLDIR 
extern
uint16_t  phDnldNfc_GetImgInfo(uint8_t **pImgPtr);

/**
 * \ingroup grp_dl_nfc
 *
 * \brief The phDnldNfc_GetImgVer function returns the new fw image version
 *
 * \param[in]  None
 *
 *  \retval Img Version.
 *
 */
DECLDIR
extern
uint16_t  phDnldNfc_GetImgVer(void);

/**
 * \ingroup grp_dl_nfc
 *
 * \brief The phDnldNfc_GetMwVer function returns the latest Mw version
 *
 * \param[in]  None
 *
 *  \retval Mw Version.
 *
 */
DECLDIR
extern
uint16_t  phDnldNfc_GetMwVer(void);
#endif 

#ifdef __cplusplus
}
#endif

#endif /* PHDNLDNFC_IMAGEINFO_H */
