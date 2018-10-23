/*
 *                    Copyright (c), NXP Semiconductors
 *
 *                       (C)NXP Electronics N.V. 2012
 *
 *         All rights are reserved. Reproduction in whole or in part is
 *        prohibited without the written consent of the copyright owner.
 *    NXP reserves the right to make changes without notice at any time.
 *   NXP makes no warranty, expressed, implied or statutory, including but
 *   not limited to any implied warranty of merchantability or fitness for any
 *  particular purpose, or that the use will not infringe any third party patent,
 *   copyright or trademark. NXP must not be liable for any loss or damage
 *                            arising from its use.
 *
 *
 */

/**
 *
 * \file  phTmlNfc_APIWrapper.h
 *
 * Project:  PN547 Middleware
 *
 * $Date$
 * $Author$
 * $Revision$
 *
 */

#ifndef PHTMLNFCABEND_FPGA_API_H
#define PHTMLNFCABEND_FPGA_API_H

#include <phNfcTypes.h>

void *phTmlNfc_AbendOpen(int8_t *pDevName);
uint16_t phTmlNfc_AbendCancelIo(void);
int phTmlNfc_AbendTx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead);
int phTmlNfc_AbendRx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead);
void phTmlNfc_AbendClose(void);
uint16_t phTmlNfc_AbendWaitForIRQ(void);
NFCSTATUS phTmlNfc_AbendEnterDnldMode(void);
NFCSTATUS phTmlNfc_AbendEnterNormalMode(void);
uint8_t phTmlNfc_AbendResetPN547(void);
uint8_t phTmlNfc_AbendPowerOffPN547(void);
uint8_t phTmlNfc_AbendPowerOnPN547(void);

#endif
