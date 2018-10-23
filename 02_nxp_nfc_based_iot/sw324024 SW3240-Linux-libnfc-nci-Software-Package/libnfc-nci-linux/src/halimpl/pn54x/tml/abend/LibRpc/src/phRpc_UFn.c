/*
*                   Copyright (c), NXP Semiconductors
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
* Project: RPC Host Library Utility Functions / ARM-Board for PN547 V&V.
* $Author: atp01705 $
* $Revision:  $
* $Date:  $
*
* Created: Nov. 13 by Gerald Kersch-Koncar
*/

#include <stdint.h>
#include <string.h>
#include "phRpc_UFn.h"

void *phRpc_H_MemMem(const void *haystack, size_t n, const void *needle, size_t m)
{
    unsigned char       *hay =(uint8_t*)haystack;
    unsigned char       *ndl =(uint8_t*)needle;
    void                *ret = NULL;
    size_t               i;

    if ((NULL != hay) && (NULL != ndl) && (0 != n) && (0 != m))
    {
        if (n > m)
        {
            for (i = 0; i < (n + 1 - m); i++)
            {
                if (hay[i] == ndl[0])
                {
                    if (0 == memcmp(&(hay[i]), ndl, m))
                    {
                        ret = &(hay[i]);
                        break;
                    }
                }
            }
        } else if (n == m)
        {
            if (0 == memcmp(hay, ndl, m))
            {
                ret = hay;
            }
        } else
        {
            /* needle can not be hidden in haystack as being bigger */
        }
    } else
    {
        // Invalid parameters
    }

    return ret;
}
