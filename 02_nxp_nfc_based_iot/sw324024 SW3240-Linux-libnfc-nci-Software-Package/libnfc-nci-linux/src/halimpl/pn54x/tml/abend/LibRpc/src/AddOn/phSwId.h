/*
*                  Copyright (c), NXP Semiconductors
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

/** \file
* Project: SW ID / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision: 29472 $
* $Date: 2014-09-09 09:25:58 +0200 (mar., 09 sept. 2014) $
*
* Created: Feb. 2011 by Gerald Kersch-Koncar
*
*/

#ifndef PHSWID_H
#define PHSWID_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if (defined AB_PCLIB || defined TESTSUITE || defined DOXYGEN)

   /**
     * \brief Get the PC Library ID
     *
     * Gets the PC Library ID. This is a string of characters identifying software release, features,
     * and build time.
     *
     * \param[out]  blId    Pointer to a location within the Bootloader image that stores the ID.
     * \param[out]  blIdLen Pointer to a variable that receives the length of the ID.
     *
     */
    void phSwId_GetPcLibID(uint8_t **pclibId, uint8_t *pclibIdLen);
#else
#endif // AB_PCLIB, TST

/** @} */
#ifdef __cplusplus
}
#endif

#endif // Guard
