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
* Project: RPC Host Library Common Definitions / ARM-Board for PN547 V&V.
* $Author:  $
* $Revision:  $
* $Date: $
*
* Created: Gerald Kersch-Koncar, June 2012
*
*/

#ifndef PHRPC_COMMON_H
#define PHRPC_COMMON_H

// ________________________________________________________________________________________________
//
// Device IDs
// ________________________________________________________________________________________________

#define PH_RPC_COMMON_VID           0xFFFF  // Vendor ID
#define PH_RPC_COMMON_PID           0x0006  // Dual-Channel software PID
#define PH_RPC_COMMON_PID_SINGLE    0x0005  // Revival of single channel.

// ________________________________________________________________________________________________
//
// Primary RPC
// ________________________________________________________________________________________________

#define PH_RPC_COMMON_INTERFACE_COMM        0       ///< Interface 0 used for primary channel

#define PH_RPC_COMMON_INT_IN_EP             0x81u   ///< LPC Phy 3,    Log 1
#define PH_RPC_COMMON_BULK_OUT_EP           0x05u   ///< LPC Phy 10,   Log 5
#define PH_RPC_COMMON_BULK_IN_EP            0x82u   ///< LPC Phy 5,    Log 2

// ________________________________________________________________________________________________
//
// SECONDARY RPC
// ________________________________________________________________________________________________

#define PH_RPC_COMMON_INTERFACE_COMM_2      2u      ///< Interface 2 used for secondary channel

#define PH_RPC_COMMON_2_INT_IN_EP           0x87u   ///< LPC Phy 15,   Log 7
#define PH_RPC_COMMON_2_BULK_OUT_EP         0x0Bu   ///< LPC Phy 22,   Log 11
#define PH_RPC_COMMON_2_BULK_IN_EP          0x88u   ///< LPC Phy 17,   Log 8

// ________________________________________________________________________________________________
//
// DESCRIPTORS
// ________________________________________________________________________________________________

#define PH_RPC_COMMON_USBDEVICENAME_POS     2       ///< \internal Device name descriptor position
#define PH_RPC_COMMON_USBDEVICENAME_POS_2   4       ///< \internal Secondary device name descriptor position
//                                          01  02  03  04  05  06  07  08  09  0A  0B  0C  0D  0E  0f  10  11  12  13  14  15  16  17  18
#define PH_RPC_COMMON_USBDEVICENAME         'U', 0, 'S', 0, 'B', 0, '2', 0, 'S', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0                      /// \internal Device Name
#define PH_RPC_COMMON_USBDEVICENAME_2       'U', 0, 'S', 0, 'B', 0, '2', 0, 'S', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0, '_', 0, '2', 0      /// \internal Secondary Device Name
#define PH_RPC_COMMON_USBDEVICENAME_LEN     0x14    ///< \internal Length
#define PH_RPC_COMMON_USBDEVICENAME_LEN_2   0x18    ///< \internal Secondary device name length


#endif // GUARD
