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
*/

#include <stdint.h>
#include <stdlib.h>
#include "phSwId.h"

// ________________________________________________________________________________________________
//
// PC-Side
// ________________________________________________________________________________________________

#if (defined AB_PCLIB || defined TESTSUITE || defined DOXYGEN)

#   ifdef SECONDARY_PCLIB
    static const uint8_t  PCLIB_SWID[]      = {0xCD};// PLG PH_SWID_PCLIB2_NAME_REV_TIME;
#   else
    static const uint8_t  PCLIB_SWID[]      = {0xAB};// PLG PH_SWID_PCLIB_NAME_REV_TIME;
#   endif
static const uint8_t  PCLIB_SWIDLength  = (uint8_t)sizeof (PCLIB_SWID);

void phSwId_GetPcLibID(uint8_t **pclibId, uint8_t *pclibIdLen)
{
    if ((NULL != pclibId) && (NULL != pclibIdLen))
    {
        *pclibId    = (uint8_t*)PCLIB_SWID;
        *pclibIdLen = PCLIB_SWIDLength;
    } else { /* Error: Fields will not be updated. */ }
}

#endif // AB_PCLIB, TST

