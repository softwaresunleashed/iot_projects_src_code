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
* Project: RPC Host Library Low Level / ARM-Board for PN547 V&V.
* $Author: nxp72238 $
* $Revision: 31965 $
* $Date: 2014-11-25 15:34:21 +0100 (mar., 25 nov. 2014) $
*
*/


// ________________________________________________________________________________________________
//
// Platform-Specifics, Includes, Definitions
// ________________________________________________________________________________________________

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <memory.h>
#include <unistd.h>

#include "phRpc_Platform.h"
#include "phRpc_Types.h"
#include "phRpc_HostIo.h"
#include "phRpc_H.h"
#include "phRpc_H_Diversity.h"
#include "phRpc_HostCtx.h"
#include "phRpc_UFn.h"

// Determine interface compatibility
#include "phSwId.h"

#if defined (PH_RPC_H_PLAT_IOS)
#   include "phRpc_HostIo_iOS.h"
#   include <sys/errno.h>
#elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
#elif defined PH_RPC_H_PLAT_WINDOWS
    // Which underlying I/O lib is used
#   define PH_RPC_H_INTF_CDC        0
#   define PH_RPC_H_INTF_LIBUSB     1
#else
#   error "No platform specified"
#endif

#define PH_RPC_H_MIN_REQ_LEN        4 //
#define PH_RPC_H_MIN_RES_LEN        6 //
#define PH_RPC_H_AUXOUTBUFLEN      (PH_RPC_H_MINDEVBUFLEN + 2u) //

#define PH_RPC_H_CALL_HOOK(_h, _hooktype) if (NULL != _h->HookF) { _h->HookF(h->UserData, _hooktype); } else { } //

// ________________________________________________________________________________________________
//
// Internal Helpers
// ________________________________________________________________________________________________

uint8_t phRpc_H_ReadDataN(void *hdl, uint8_t *buffer, uint16_t *length);
void    phRpc_H_SetEngData(void *hdl, uint8_t *txBuf, uint8_t *rxBuf, uint16_t txLen, uint16_t rxLen, int locId);
void    phRpc_H_ExchangeResetFrame(void *hdl);
void    phRpc_H_DbgPrint(void *hdl, uint8_t *buf, uint16_t len, uint8_t st, char *descr);
void    phRpc_H_GenericInit(void *hdl, pphRpc_H_LogF_t logF, void *userLData,
                            pphRpc_H_EventHook_t hookF, void *userHData,
                            uint32_t optFlags);
void    phRpc_H_GenericDeInit(void *hdl);
int     phRpc_H_MutexInit(phRpc_Mutex_t *hMutex);
int     phRpc_H_MutexDeInit(phRpc_Mutex_t *hMutex);
int     phRpc_H_MutexAcquire(phRpc_Mutex_t *hMutex);
int     phRpc_H_MutexRelease(phRpc_Mutex_t *hMutex);

// ________________________________________________________________________________________________
//
// Host Specific
// ________________________________________________________________________________________________

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Open(void **hdl, wchar_t *devName, uint8_t devNameLen)
{
    return phRpc_H_OpenL(hdl, devName, devNameLen, NULL, NULL);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenL(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                pphRpc_H_LogF_t logF, void *userLData)
{
    return phRpc_H_OpenLH(hdl, devName, devNameLen, logF, userLData, NULL, NULL);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenLH(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                 pphRpc_H_LogF_t logF, void *userLData,
                                                 pphRpc_H_EventHook_t hookF, void *userHData)
{
    return phRpc_H_OpenLHF(hdl, devName, devNameLen, logF, userLData, hookF, userHData, 0);
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenLHF(void **hdl, wchar_t *devName, uint8_t devNameLen,
                                                  pphRpc_H_LogF_t logF, void *userLData,
                                                  pphRpc_H_EventHook_t hookF, void *userHData,
                                                  uint32_t optFlags)
{
    phRpc_H_Return_t    ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t          *h   = NULL;

#  if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    int32_t         fd      = 0;
#   if !defined (PH_RPC_H_PLAT_IOS)
    struct termios  tios;
    speed_t         speed;
#   endif
    if ((NULL != hdl) && (NULL == *hdl) && (NULL != devName) && (devNameLen < PH_RPC_H_DEVNAMELEN))
    {
        // OK: Now alloc a struct:
        h = phRpc_H_Diversity_Alloc();
        if (NULL != h)
        {
            // We need multibyte, not wchar for the open() function:
            wcstombs((char*)(h->device), devName, PH_RPC_H_DEVNAMELEN);
#  if defined (PH_RPC_H_PLAT_IOS)
            fd = SerialOpen();            // -1 if RedPark cable not connected
#  else
            fd = open((char*)(h->device), O_RDWR | O_NOCTTY | O_NDELAY);
#  endif // non iOS
            if (fd >= 0)
            {
                // This will instruct the device to pad 1 byte to a buffer with exact the MTU len
                // and to insert at least  n  times the minimum TX length!
                // Otherwise the Linux driver may stall. Nasty.
                h->PadPlus1 = 1u;
                h->PadMul   = 1u; // n
                // Handle
                h->fd = fd;
                // COMM Properties
#  if defined (PH_RPC_H_PLAT_IOS)
                //TODO: set baud rate to 57600
                ret = phRpc_H_SetHookF(h, NULL, NULL);
                ret = PH_RPC_H_STATUS_OK;
                *hdl = h;
#  else
                tcgetattr(h->fd, &(h->old_tios)); // Save termios
                memset(&tios, 0, sizeof(struct termios));
                speed = PH_RPC_H_LIN_BD_RATE;
                // Set Speed
                if ((cfsetispeed(&tios, speed) >= 0) &&
                    (cfsetospeed(&tios, speed) >= 0))
                {
                    // Now set Attributes:
                    // C_CFLAG      Control options
                    // CLOCAL       Local line - do not change "owner" of port
                    // CREAD        Enable receiver
                    tios.c_cflag |= (CREAD | CLOCAL);
                    // # Data Bits
                    tios.c_cflag &= ~(CSIZE | PARENB);//&= ~CSIZE;
                    tios.c_cflag |= CS8;
                    // 1 Stop Bit (Just clear flags)
                    tios.c_cflag &=~ CSTOPB;
                    // No parity bit (Just clear flags)
                    tios.c_cflag &=~ PARENB;
                    // Raw input
                    tios.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG); //&= ~(ICANON | ECHO | ECHOE | ISIG);
                    // Input Parity
                    tios.c_iflag &= ~INPCK;
                    // Software flow control OFF
                    tios.c_iflag &= ~(IGNBRK | BRKINT | ICRNL | INLCR |
                                      PARMRK | INPCK | ISTRIP | IXON);//&= ~(IXON | IXOFF | IXANY);
                    // Raw ouput
                    tios.c_oflag &= ~(OCRNL | ONLCR | ONLRET | ONOCR |
#   if defined (PH_RPC_H_PLAT_LINUX)
                    OFILL | OLCUC | OPOST);//&=~ OPOST;
#   else    // PH_RPC_H_PLAT_GNUC but not iOS and not Linux => MacOS
                    OFILL | OPOST);//&=~ OPOST | OLCUC;        olcuc is unknown on MacOS
#   endif
                    // Not needed as opened with NDELAY
                    tios.c_cc[VMIN] = 1;  // 1 byte is enough to signal reception
                    tios.c_cc[VTIME] = 0; // Inter-char timeout disabled

                    // Apply Attr:
                    if (tcsetattr(h->fd, TCSANOW, &tios) >= 0)
                    {   // *** ALL OK ***
                        ret = phRpc_H_SetHookF(h, NULL, NULL);
                        ret = PH_RPC_H_STATUS_OK;
                        *hdl = h;
                    } else { /*Error setting attr. */ }
                } else { /* Error setting speed */ }
#  endif // non iOS
            } else
            {
                /* Open failed */
                ret = PH_RPC_H_STATUS_OPEN_ERROR;
            }
        } else
        {
            /* Alloc Error */
            ret = PH_RPC_H_STATUS_OPEN_ERROR;
        }
    } else
    {
        /* Name too long or invalid */
        ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    }

    if ((PH_RPC_H_STATUS_OK != ret) && (0 != fd))
    {
        // ERROR
        if (NULL != h)
        {
            phRpc_H_Diversity_Free(h);
        } else { }
        *hdl = NULL;
#  if defined (PH_RPC_H_PLAT_IOS)
        SerialClose();
#  else
        close(fd);
#  endif // iOS
    }  else { }
#  elif defined PH_RPC_H_PLAT_WINDOWS
    void *fh = NULL;

    if ((NULL != hdl) && (NULL == *hdl) && (NULL != devName) && (devNameLen < PH_RPC_H_DEVNAMELEN))
    {
        ret = PH_RPC_H_STATUS_OPEN_ERROR;
        fh = CreateFile(devName,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        0,
                        OPEN_EXISTING,
                        FILE_FLAG_OVERLAPPED,
                        0);
        if (INVALID_HANDLE_VALUE != fh)
        {
            // OK: Now alloc a struct:
            h = phRpc_H_Diversity_Alloc();
            if (NULL != h)
            {
                // Padding + 1 workaround is not needed on Windows:
                h->PadPlus1 = 0;
                h->PadMul   = 1u;
                // Go ahead:
                h->CommInterface = PH_RPC_H_INTF_CDC;
                h->hc = fh;
                h->OvR.hEvent = NULL;
                h->OvW.hEvent = NULL;
                memcpy(h->device, devName, (devNameLen * sizeof (wchar_t)));
                // COMM Timeouts
                (void)GetCommTimeouts(fh, &h->OldTimeouts);
                h->Timeouts.ReadIntervalTimeout = MAXDWORD;
                h->Timeouts.ReadTotalTimeoutMultiplier  = MAXDWORD;
                h->Timeouts.ReadTotalTimeoutConstant    = 1000;
                h->Timeouts.WriteTotalTimeoutMultiplier = MAXDWORD;
                h->Timeouts.WriteTotalTimeoutConstant   = 10000;
                if (0 != SetCommTimeouts(fh, &h->Timeouts))
                {
                    // Format (DCB)
                    (void)GetCommState(fh, &(h->OldDcb));
                    FillMemory(&(h->Dcb), sizeof(DCB), 0);
                    h->Dcb.DCBlength = sizeof(DCB);
                    if (0 != BuildCommDCB(PH_RPC_H_WIN_SER_FMT, &(h->Dcb)))
                    {
                        // DCB Tune
                        h->Dcb.fDtrControl = DTR_CONTROL_DISABLE;
                        h->Dcb.fRtsControl = RTS_CONTROL_DISABLE;

                        // Set State
                        if (0 != SetCommState(fh, &(h->Dcb)))
                        {
                            // Send/Receive Events:
                            FillMemory(&(h->OvW), sizeof(OVERLAPPED), 0);
                            FillMemory(&(h->OvR), sizeof(OVERLAPPED), 0);
                            h->OvW.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                            h->OvR.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                            if ((NULL != h->OvW.hEvent) && (NULL != h->OvR.hEvent))
                            {
                                // *** All OK ***
                                (void)SetCommMask(fh, EV_RXCHAR);
                                ret = phRpc_H_SetHookF(h, NULL, NULL);
                                ret = PH_RPC_H_STATUS_OK;
                                *hdl = h;
                            } else { /* Overlapped event creation error. */ }
                        } else { /* Error applying format */ }
                    } else { /* Error setting format */ }
                } else { /* Error setting time-outs */ }
            } else
            {
                /* Alloc Error */
                ret = PH_RPC_H_STATUS_OPEN_ERROR;
            }
        } else
        {
            /* Open failed */
            volatile uint32_t error;
            error = GetLastError();
            (void)error;
        }
    } else
    {
        // USB Lib selected: Auto-detect interface.
        struct  usb_bus *bus;
        struct  usb_device *dev;
        uint8_t enum_ok = 0;

        // Set all unused handles to NULL (I):
        fh              = NULL;

        ret = PH_RPC_H_STATUS_OPEN_ERROR;
        h = phRpc_H_Diversity_Alloc();
        if (NULL != h)
        {
            // This is not needed on Windows:
            h->PadPlus1 = 0;
            h->PadMul   = 1u;
            // Set all unused handles to NULL (II)
            h->OvW.hEvent   = NULL;
            h->OvR.hEvent   = NULL;
            h->CommInterface = PH_RPC_H_INTF_LIBUSB;
            // RPC versions: Set to "New" as this is more likely.
            h->NewRPC = 1u;

            usb_init();
            usb_find_busses();
            usb_find_devices();

            // LIBUSB DEBUG OPTION
            // usb_set_debug(255);

            for (bus = usb_get_busses(); bus; bus = bus->next)
            {
                for (dev = bus->devices; dev; dev = dev->next)
                {
                    if (
                         (PH_RPC_H_VID  == dev->descriptor.idVendor) &&
                         (
                           (PH_RPC_H_PID            == dev->descriptor.idProduct) ||    // Composite (dual interface)
                           (PH_RPC_H_PID_SINGLE     == dev->descriptor.idProduct)       // Allow for non-composite device (single interface)
                         )
                       )
                    {
                        h->dev = usb_open(dev);
                        if (NULL != h->dev)
                        {
                            // Device found:
                            if (usb_set_configuration(h->dev, PH_RPC_H_CONFIG) >= 0)
                            {
                                // OK:
                                int interface_number = phRpc_H_Diversity_GetInterfaceNr();
                                if (usb_claim_interface(h->dev, interface_number) >= 0)
                                {
                                    // OK
                                    enum_ok = 1;
                                    ret = PH_RPC_H_STATUS_OK;
                                    *hdl = h;
                                    break;
                                } else
                                {
                                    // Cannot claim: Continue search as device might be in use (claimed by someone else) already.
                                    usb_close(h->dev); ///\todo Closing appropriate here? -> Side effect on other handle that had been opened before?
                                    ret = PH_RPC_H_STATUS_OPEN_ERROR;
                                }
                            } else
                            {
                                ret = PH_RPC_H_STATUS_IO_LIBERROR;
                            }
                        } else
                        {
                            /* Open Error */
                            ret = PH_RPC_H_STATUS_OPEN_ERROR;
                        }
                    }
                }
                if (0 != enum_ok)
                {
                    // OK, board found. Reset first:
                    (void)usb_resetep(h->dev, phRpc_H_Diversity_GetInEp());
                    (void)usb_resetep(h->dev, phRpc_H_Diversity_GetOutEp());
                    // Get descriptor:
                    uint8_t descr [PH_RPC_COMMON_USBDEVICENAME_LEN * 2]; // Reserve plenty of space
                    int32_t size = PH_RPC_COMMON_USBDEVICENAME_LEN * 2;
                    int32_t gdret;
                    gdret = usb_get_descriptor(h->dev,
                                               USB_DT_STRING,
                                               PH_RPC_COMMON_USBDEVICENAME_POS,
                                               descr,
                                               size - 1);
                    if (gdret > 0)
                    {
                        uint8_t ref_descr[] = {PH_RPC_COMMON_USBDEVICENAME};
                        descr[size - 1] = 0;
                        descr[size - 2] = 0;
                        // wprintf(L"DESCR = [%s] ", descr); // Debug
                        if (NULL != phRpc_H_MemMem(descr, (size_t)gdret, ref_descr, sizeof(ref_descr))) // If reference name is comprised ANYWHERE, it's OK..
                        {
                            // "New" Device
                            // wprintf(L"DESCR = [%s] -> \"New RPC\" Device!", descr); // Debug
                            h->NewRPC = 1u;
                        } else
                        {
                            // Old library, need compatibility mode
                            // wprintf(L"DESCR = [%s] (ref = %s) -> \"Old RPC\" Device!", descr, ref_descr); // Debug
                            h->NewRPC = 0;
                        }
                    } else
                    {
                        // No matching descriptor: Try new (most likely) board:
                        h->NewRPC = 1u;
                    }

                    // End search:
                    break;
                } else
                {
                    // Continue search
                }
            }
        } else
        {
            /* Alloc Error */
            ret = PH_RPC_H_STATUS_OPEN_ERROR;
        }
    }

    if (PH_RPC_H_STATUS_OK != ret)
    {
        // ERROR
        if (NULL != fh) { (void)CloseHandle(fh); } else { }
        if (NULL != h)
        {
            if (NULL != h->OvW.hEvent) { (void)CloseHandle(h->OvW.hEvent); } else { }
            if (NULL != h->OvR.hEvent) { (void)CloseHandle(h->OvR.hEvent); } else { }
            phRpc_H_Diversity_Free(h);
        } else { }
        *hdl = NULL;
    } else { }
#  else // PLATFORM
#  endif

    // Independent from the platform there is common stuff to do. We do it here:
    if (PH_RPC_H_STATUS_OK == ret)
    {
        // All OK, init the common stuff:
        phRpc_H_GenericInit(h, logF, userLData, hookF, userHData, optFlags);

        // Initial cancel in case we open a board where an I/O is still pending
        h->CancelInitial = 1u;
        // Functions for the board:
        if (0 == (h->Flags & PH_RPC_H_OPENPARAM_RAW))
        {
            ret = phRpc_H_BoardInit(h);
        }
        // Cancel flag clear
        h->CancelInitial = 0;

        // Log
        phRpc_H_LogWStr(h, L"phRpc_H_Open[L/LH]");
        phRpc_H_LogPtr(h, h);
        phRpc_H_LogWStr(h, devName);
        phRpc_H_LogInt(h, devNameLen, 10);
        phRpc_H_LogPtr(h, logF);
        phRpc_H_LogPtr(h, userLData);

        // Lib Status
        h->LastError.PcLibStatus = ret;
    } else { };
    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_OpenC(void **hdl, pphRpc_H_Raw_t primaryLibRawCmd, void *primaryLibH)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t  *h   = NULL;

    if ((NULL != hdl) && (NULL == *hdl) && (NULL != primaryLibRawCmd) && (NULL != primaryLibH))
    {
        h = phRpc_H_Diversity_Alloc();
        *hdl = h;
        if (NULL != h)
        {
            phRpc_H_GenericInit(h, NULL, NULL, NULL, NULL, 0);
            h->LowerRawCmd = primaryLibRawCmd;
            h->LowerHandle = primaryLibH;
            ret = PH_RPC_H_STATUS_OK;
        }
    } else
    {
        // Invalid Parameter!
    }

    return ret;
}

phRpc_H_Return_t PH_RPC_H_LIBFUNC phRpc_H_Close(void **hdl)
{
    uint8_t     ret = PH_RPC_H_STATUS_INVALID_PARAMETER;
    phRpc_H_t   *h   = NULL;

    if (NULL != hdl)
    {
        h = (phRpc_H_t*)(*hdl);

        if (NULL != h)
        {
            if (PH_RPC_H_HDL_OK(h))
            {
                phRpc_H_LogWStr(h, L"phRpc_H_Close");

                if (NULL == h->LowerRawCmd)
                {
                    // We are in "real" mode with direct connection to the driver:
#                   if defined (PH_RPC_H_PLAT_IOS)
                    SerialClose();
#                   elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
                    // Restore termios and close interface
                    tcsetattr(h->fd, TCSANOW, &(h->old_tios));
                    close(h->fd);
#                   elif defined PH_RPC_H_PLAT_WINDOWS
                    if (PH_RPC_H_INTF_LIBUSB == h->CommInterface)
                    {
                        if (NULL != h->dev)
                        {
                            usb_release_interface(h->dev, 0);
                            usb_close(h->dev);
                        } else { }
                    } else
                    {
                        // Restore DCB, COMMTIMEOUTS and close events and interface
                        (void)SetCommTimeouts(h->hc, &h->OldTimeouts);
                        (void)SetCommState(h->hc, &(h->OldDcb));
                        (void)CloseHandle(h->OvW.hEvent);
                        (void)CloseHandle(h->OvR.hEvent);
                        (void)CloseHandle(h->hc);
                    }
#                   else
#                   endif
                } else
                {
                    // Cascaded mode, using CH1 library:
                }

                // De-Init
                phRpc_H_GenericDeInit(h);

                // Log:
                phRpc_H_LogWStr(h, L"phRpc_H_Close");
                phRpc_H_LogPtr(h, h);
                //
                // FREE
                phRpc_H_Diversity_Free(h);
                *hdl = NULL;
                ret = PH_RPC_H_STATUS_OK;
            } else
            {
                ret = PH_RPC_H_STATUS_INVALID_HANDLE;
            }
        } else
        {
            /* Handle h was NULL already. */
            ret = PH_RPC_H_STATUS_OK;
        }
    } else { /* Param check error */ }

    return ret;
}

// ________________________________________________________________________________________________
//
// Lower Layer Access Functions
// ________________________________________________________________________________________________

uint8_t phRpc_H_WriteData(void *hdl, uint8_t *buffer, uint16_t length)
{
    volatile uint8_t        ret         = PH_RPC_H_STATUS_IO_LIBERROR;
    phRpc_H_t              *h           = (phRpc_H_t*)hdl;

    ssize_t         bw      = 0;
    size_t          ix      = 0;

# if defined (PH_RPC_H_PLAT_IOS)
# elif defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    int32_t         err;
    int32_t         select_ret;
    struct timeval  tv;
    //    fprintf(stderr, "writing data\n");
# endif
    // Indicate Write Begin
    phRpc_H_SetEngData(h, buffer, NULL, length, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 1u);
    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_PRE_WRITE);

    if (length > phRpc_H_Diversity_GetDeviceBufferSize())
    {
        // Error: Input Overflow
        length = phRpc_H_Diversity_GetDeviceBufferSize();
        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_MISMATCH);
    } else { }

# if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    // Add a file descriptor to the WR set
    FD_ZERO(&(h->wfds));
    FD_SET(h->fd, &(h->wfds));

    // CDC -- LINUX SUPPORTS THIS OUT OF THE BOX
    // ================================================
    do
    {
        // write() will not always write all: Check this and repeat operation if needed!
        // In fact, Linux has shown that it writes typically 128 bytes!
#  if defined (PH_RPC_H_PLAT_IOS)
        bw = SerialWrite( &(buffer[ix]), length - ix);
#  else
        bw = write(h->fd, &(buffer[ix]), length - ix);
#  endif
        ix += bw;
#  if !defined (PH_RPC_H_PLAT_IOS)
        // Wait for write operation to be completed
        tv.tv_sec  = 0;
        tv.tv_usec = h->TimeoutMillisec * 1000;  // in µs (ms * 1000)
#   if defined (PH_RPC_H_PLAT_IOS)
        select_ret = SerialWait(&tv);
#   else
        while ((select_ret = select(h->fd + 1, NULL, &(h->wfds), NULL, &tv)) == -1)
        {
            err = errno;
            if (err == EINTR)
            {
                FD_ZERO(&(h->wfds));
                FD_SET(h->fd, &(h->wfds));
            } else
            {
                bw = 0;
                ret = PH_RPC_H_STATUS_IO_LIBERROR;
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_OVERLAPPED_ERR);
            }
            tv.tv_sec  = 0;
            tv.tv_usec = h->TimeoutMillisec * 1000;  // in µs (ms * 1000)
        }
        err = errno;
#   endif
        if (select_ret == 0)
        {
            bw = 0;
            ret = PH_RPC_H_STATUS_IO_TIMEOUT;
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_TIMEOUT);
        }
#  endif
    } while ((bw > 0) && (ix < length));

    if ((bw > 0) && (ix == length))
    {
        // OK:
#  if !defined (PH_RPC_H_PLAT_IOS)
        (void)fdatasync(h->fd);
        (void)tcdrain(h->fd);
#  endif
        ret = PH_RPC_H_STATUS_OK;
        phRpc_H_SetEngData(h, buffer, NULL, ix, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 2u);
        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_POST_WRITE);
    } else if (bw < 0)
    {
        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_ERROR);
    } else
    {
        // Write length mismatch
        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_MISMATCH);
    }

# elif defined PH_RPC_H_PLAT_WINDOWS
    if (PH_RPC_H_INTF_LIBUSB == h->CommInterface)
    {
        // LIBUSB DEVICE
        // =============
        do
        {
            bw = usb_bulk_write(h->dev,
                                phRpc_H_Diversity_GetOutEp(),
                                (char*)(&(buffer[ix])),
                                length - ix,
                                h->TimeoutMillisec);
            ix += bw;
        } while ((bw > 0) && (ix < length));

        if ((bw > 0) && (ix == length))
        {
            // USB frame sent
            ret = PH_RPC_H_STATUS_OK;
            phRpc_H_SetEngData(h, buffer, NULL, ix, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 3u);
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_POST_WRITE);
        } else
        {
            ret = PH_RPC_H_STATUS_FRAMING_ERROR;
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_ERROR);
        }
    } else
    {
        // CDC - WINDOWS
        // ======================================================================================
        DWORD res;
        DWORD err;
        DWORD bwr = 0;

        res = ResetEvent(h->OvW.hEvent);
        err = GetLastError();

        res = WriteFile(h->hc, buffer, length, &bwr, &(h->OvW));
        if (0 == res)
        {
            err = GetLastError();
            if (ERROR_IO_PENDING == err)
            {
                // Operation ongoing:
                res = WaitForSingleObject(h->OvW.hEvent, INFINITE);
                switch (res)
                {
                    case WAIT_OBJECT_0:
                        if (0 == GetOverlappedResult(h->hc, &(h->OvW), &bwr, FALSE))
                        {
                            // Fail
                            phRpc_H_SetEngData(h, buffer, NULL, (uint16_t)bwr, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 4u);
                            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_OVERLAPPED_ERR);
                        } else
                        {
                            if ((uint16_t)bwr == length)
                            {
                                // Write operation completed successfully
                                phRpc_H_SetEngData(h, buffer, NULL, (uint16_t)bwr, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 5u);

                                (void)FlushFileBuffers(h->hc);
                                ret = PH_RPC_H_STATUS_OK;
                                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_POST_WRITE);
                            } else
                            {
                                // The write operation timed out with not all written
                                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_MISMATCH);
                            }
                        }
                        break;

                    default:
                        // Operation Failed (Wait Single Obj): Problem in OVR struct?
                        ret = PH_RPC_H_STATUS_IO_LIBERROR;
                        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_OVERLAPPED_ERR);
                        break;
                }
            } else
            {
                // Operation failed
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_ERROR);
            }
        } else
        {
            // WriteFile completed immediately

            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_IMM_COMPL);

            if ((uint16_t)bwr == length)
            {
                // OK
                (void)FlushFileBuffers(h->hc);
                ret = PH_RPC_H_STATUS_OK;
                phRpc_H_SetEngData(h, buffer, NULL, (uint16_t)bwr, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 6u);
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_POST_WRITE);
            } else
            {
                // Error, not all written, exit.
                phRpc_H_SetEngData(h, buffer, NULL, (uint16_t)bwr, 0, PH_RPC_H_ENGDATAPOINT_WRITE + 7u);
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_WRITE_MISMATCH);
            }
        }
    } // Comm Intf

# else // PLATFORM
# endif

    phRpc_H_DbgPrint(h, buffer, length, ret, "TX");

    return ret;
}

#define read_started  0 //
#define read_ongoing  1 //
#define read_finished 2 //

uint8_t phRpc_H_ReadData(void *hdl, uint8_t *buffer, uint16_t *length)
{
    const size_t    min_nr_to_read      = PH_RPC_H_MINDEVBUFLEN;    // First 2 comprise length!
    const uint8_t   max_try             = 3u;
    const uint8_t   max_timeout_count   = 3u;

    volatile uint8_t ret        = PH_RPC_H_STATUS_OK;
    uint8_t     state           = read_started;
    phRpc_H_t  *h               = (phRpc_H_t*)hdl;
    size_t      nb              = 0;
    size_t      target_len      = 0;
    size_t      nr_to_read;
    size_t      num_read        = 0;
    uint32_t    read_timeout    = h->TimeoutMillisec; // ms
    uint8_t     loop            = 0;
    uint8_t     timeout_count   = 0;

# if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    int32_t         err;
    int32_t         select_ret;
    struct timeval  tv;
# elif defined PH_RPC_H_PLAT_WINDOWS
    DWORD bytes_read    = 0;
    int32_t br          = 0;
    DWORD res           = 0;
    DWORD err           = 0;
# else // PLATFORM
# endif

    // Reset Engineering data
    phRpc_H_SetEngData(h, NULL, NULL, 0, 0, PH_RPC_H_ENGDATAPOINT_READ + 1u);
    // Select the initial (minimum) receive size.
    nr_to_read  = min_nr_to_read + ((0 == h->PadPlus1) ? 0 : 1u);
    state       = read_started;
    do
    {
#   if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
        // CDC LINUX
        // ---------------------------------------------------------------------------------------------------------

        /* Add a file descriptor to the set: */
        FD_ZERO(&(h->rfds));
        FD_SET(h->fd, &(h->rfds));

        tv.tv_sec  = read_timeout / 1000;
        tv.tv_usec = (read_timeout % 1000) * 1000;  // in µs (ms * 1000)
#    if defined (PH_RPC_H_PLAT_IOS)
        select_ret = SerialWait(&tv);
#    else
        while ((select_ret = select(h->fd + 1, &(h->rfds), NULL, NULL, &tv)) == -1)
        {
            err = errno;
            if (err == EINTR)
            {
                FD_ZERO(&(h->rfds));
                FD_SET(h->fd, &(h->rfds));
            } else
            {
                state = read_finished;
                ret = PH_RPC_H_STATUS_IO_LIBERROR;
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OVERLAPPED_ERR);
            }
            // Linux modifies TV; reinit therefore (from select man pages)
            tv.tv_sec  = read_timeout / 1000;
            tv.tv_usec = (read_timeout % 1000) * 1000;  // in µs (ms * 1000)
        }

        // Add the file descriptor again:
        FD_ZERO(&(h->rfds));
        FD_SET(h->fd, &(h->rfds));
#    endif
        if (select_ret == 0)
        {
            state = read_finished;
            timeout_count++;
            ret = PH_RPC_H_STATUS_IO_TIMEOUT;
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_TIMEOUT);
        }

        if (0 == num_read)
        {
            // Only 1st time (nothing read yet)
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_1ST_READ);
        } else { }

#    if defined (PH_RPC_H_PLAT_IOS)
        nb = SerialRead( &(buffer[num_read]), nr_to_read);
#    else
        nb = read(h->fd, &(buffer[num_read]), nr_to_read);
#    endif
#   elif defined PH_RPC_H_PLAT_WINDOWS
        // CDC WINDOWS
        // -------------------------------------------------------------------------------------------------------------

        if (PH_RPC_H_INTF_LIBUSB != h->CommInterface)
        {
            phRpc_H_SetEngData(h, NULL, NULL, 0, 0, PH_RPC_H_ENGDATAPOINT_READ + 2u);
            res = ResetEvent(h->OvR.hEvent);
            err = GetLastError();
            res = ReadFile(h->hc, &(buffer[num_read]), nr_to_read, &bytes_read, &(h->OvR));
            err = GetLastError();
            if (0 == res)
            {
                if (ERROR_IO_PENDING == err)
                {
                    // Operation Ongoing: Wait for completion
                    res = WaitForSingleObject(h->OvR.hEvent, read_timeout);
                    switch (res)
                    {
                        // Read completed
                        case WAIT_OBJECT_0:
                            if (0 == GetOverlappedResult(h->hc, &(h->OvR), &bytes_read, FALSE))
                            {
                                // Error in communication
                                phRpc_H_SetEngData(h, NULL, &(buffer[num_read]), 0, (uint16_t)bytes_read, PH_RPC_H_ENGDATAPOINT_READ + 3u);
                                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OVERLAPPED_ERR);
                            } else
                            {
                                // Read completed successfully
                                phRpc_H_SetEngData(h, NULL, &(buffer[num_read]), 0, (uint16_t)bytes_read, PH_RPC_H_ENGDATAPOINT_READ + 4u);

                                nb = (uint16_t)bytes_read;

                                err = GetLastError();

                                if (0 == nb)
                                {
                                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_OVREAD_NOTHING_ST_OK);
                                } else { }

                                if (0 == num_read)
                                {
                                    // Only 1st time (nothing read yet)
                                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_1ST_READ);
                                } else
                                {
                                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OK);
                                }
                            }
                            break;

                        case WAIT_TIMEOUT:
                            // Time-out
                            timeout_count++;
                            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_TIMEOUT);
                            break;

                        default:
                            // Error: Problem with the OVERLAPPED structure's event handle?
                            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OVERLAPPED_ERR);
                            break;
                    }
                } else
                {
                    // Operation Failed
                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OVERLAPPED_ERR);
                }
            } else
            {
                // Immediate Completion, OK
                phRpc_H_SetEngData(h, NULL, &(buffer[num_read]), 0, (uint16_t)bytes_read, PH_RPC_H_ENGDATAPOINT_READ + 5u);

                nb = (uint16_t)bytes_read;

                err = GetLastError();
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_IMM_COMPL);

                if (0 == nb)
                {
                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_NOTHING_ST_OK);
                } else { }

                if (0 == num_read)
                {
                    // Only 1st time (nothing read yet)
                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_1ST_READ);
                } else { }
            }
        } else
        {
            // LIBUSB
            // ---------------------------------------------------------------------------------------------------------
            phRpc_H_SetEngData(h, NULL, NULL, 0, 0, PH_RPC_H_ENGDATAPOINT_READ + 6u);
            br = usb_bulk_read(h->dev, phRpc_H_Diversity_GetInEp(), (char*)(&(buffer[num_read])), nr_to_read, h->TimeoutMillisec);
            if (br >= 0)
            {
                // USB frame(s) received
                phRpc_H_SetEngData(h, NULL, &(buffer[num_read]), 0, (uint16_t)br, PH_RPC_H_ENGDATAPOINT_READ + 7u);
                nb = (uint16_t)br;
                ret = PH_RPC_H_STATUS_OK;
                if (0 == num_read)
                {
                    // Only 1st time (nothing read yet)
                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_1ST_READ);
                } else
                {
                    PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OK);
                }
            } else
            {
                ret = PH_RPC_H_STATUS_IO_TIMEOUT;
                nb = 0;
                timeout_count++;
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_TIMEOUT);
            }
        } // Interface
#   else // PLATFORM
#   endif

        if (0 == nb)
        {
            // Nothing read: Error
            state = read_finished;
            ret = PH_RPC_H_STATUS_IO_LIBERROR;
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_NOTHING);
        } else if ((num_read + nb) > (phRpc_H_Diversity_GetDeviceBufferSize()))
        {
            // Read error:
            state = read_finished;
            ret = PH_RPC_H_STATUS_IO_LIBERROR;
            PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_OVERFLOW);
        } else
        {
            loop = 0; // Reset retry, if bytes come in slowly and more loops are required.
            num_read += nb;
        }

        switch (state)
        {
            case read_started:
                if (num_read >= min_nr_to_read)
                {
                    target_len = phRpc_H_Diversity_GetNumBytesFromBuffer(buffer);
                    if ((target_len > (*length)) || (target_len < PH_RPC_H_MIN_RES_LEN))
                    {
                        // Error in determined length
                        state = read_finished;
                        ret = PH_RPC_H_STATUS_FRAMING_ERROR;
                        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_LENERR);
                        break;
                    } else { /* OK, go on*/ }
                } else
                {
                    // There must be more:
                    if (loop < max_try)
                    {
                        state = read_started;
                    } else
                    {
                        // Error: Read n times and still no length information?
                        ret = PH_RPC_H_STATUS_FRAMING_ERROR;
                        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_READ_LENERR);
                        state = read_finished;
                    }
                    break;
                }
                /*@fallthrough*/
            case read_ongoing:
                if (num_read < target_len)
                {
                    nr_to_read = target_len - num_read;
                    state = read_ongoing;
                    break;
                } else
                {
                    state = read_finished;
                }
                /*@fallthrough*/
            default:
            case read_finished:
                *length = (uint16_t)num_read;
                break;
        }

        // When we had n timeouts we give up
        if (timeout_count > max_timeout_count)
        {
            state = read_finished;
        }

        loop++;
    } while (state != read_finished);

    phRpc_H_DbgPrint(h, buffer, *length, ret, "RX");

    return ret;
}

uint8_t phRpc_H_RWData(void *hdl, uint16_t *length)
{
    uint8_t         ret             = PH_RPC_H_STATUS_OK;
    phRpc_H_t      *h               = (phRpc_H_t*)hdl;
    uint8_t         handle_wtx      = 0;
    uint16_t        len;
    uint8_t         wtx_out_buf[PH_RPC_H_AUXOUTBUFLEN];

    // Lock Transfer
    (void)phRpc_H_MutexAcquire(&h->TRxMutex);

    if (NULL == h->LowerRawCmd)
    {
        // We are in "real" mode with direct connection to the driver:

        // Clear count
        h->NumSent      = 0;
        h->NumReceived  = 0;

        // Clear Cancel Flag:
        phRpc_AuxClearCancelFlag(h);
        // Set Pending Flag
        phRpc_AuxSetPendingFlag(h);

        do
        {
            // Clear Communication Length count
            h->LastError.LastRx = 0;
            h->LastError.LastTx = 0;

            // Clear Input Buffer (first bytes are sufficient as all zero is invalid)
            for (len = 0; len < PH_RPC_H_MIN_RES_LEN; len++)
            {
                h->InBuf[len] = 0;
            }

            // SEND data
            if (0 != handle_wtx)
            {
                uint8_t cancel_request;

                // We must send WTX frame as we received one before:
                cancel_request = phRpc_AuxIoCancelCb(h);
                if (0 != h->CancelInitial)
                {
                    cancel_request = 1u;
                } else
                {
                    cancel_request = phRpc_AuxIoCancelCb(h);
                }
                (void)phRpc_H_Diversity_BuildWTX(wtx_out_buf, &len, cancel_request);
                (void)phRpc_H_Diversity_SetSeqNum(wtx_out_buf, h->SeqNr);
                ret = phRpc_H_WriteData(h, wtx_out_buf, len);
                // Diagnosis: Number of bytes written:
                h->LastError.LastTx = *length;
                PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_SENT_WTX);
                handle_wtx = 0;
            } else
            {
                // Regular Operation:
                (void)phRpc_H_Diversity_SetSeqNum(h->OutBuf, h->SeqNr);
                ret = phRpc_H_WriteData(h, h->OutBuf, *length);
                // Diagnosis: Number of bytes written:
                h->LastError.LastTx = *length;
            }

            if (PH_RPC_H_STATUS_OK == ret)
            {
                // OK, now RECEIVE data:
                h->NumSent = *length;
                *length = phRpc_H_Diversity_GetDeviceBufferSize();
                ret = phRpc_H_ReadData(h, h->InBuf, length);
                h->LastError.LastRx = *length;
                if ((PH_RPC_H_STATUS_OK == ret) && (*length > 0))
                {
                    // OK: We assume everything to be OK. Don't even check sequence number.
                    ret = PH_RPC_H_STATUS_OK;
                    // WTX?
                    if (phRpc_H_Diversity_GetWtxFid() == phRpc_H_Diversity_GetFidFromBuffer(h->InBuf))
                    {
                        // It is a WTX:
                        handle_wtx = 1u;
                        PH_RPC_H_CALL_HOOK(h, PH_RPC_H_HOOK_RECEIVED_WTX);
                    } else
                    {
                        handle_wtx = 0;
                    }
                } else
                {
                    ret = phRpc_H_ReadErrorRecovery(h, length);
                }
                if (PH_RPC_H_STATUS_OK == ret)
                {
                    h->NumReceived = *length;
                    h->SeqNr++;
                } else { }
            } else
            {
                // TX Fault:
                h->NumSent = 0;
            }
        } while ((0 != handle_wtx) && (PH_RPC_H_STATUS_OK == ret));

        // Clear Pending Flag
        phRpc_AuxClearPendingFlag(h);
    } else
    {
        // Cascaded mode, using CH1 library:
        uint16_t out_len = *length;
        uint16_t in_len = phRpc_H_Diversity_GetDeviceBufferSize();
        phRpc_H_Diversity_SetCh2Id(h->OutBuf);
        ret = h->LowerRawCmd(h->LowerHandle, h->OutBuf, out_len, h->InBuf, &in_len);
        *length = in_len;
    }

    // Unlock Transfer
    (void)phRpc_H_MutexRelease(&h->TRxMutex);

    return ret;
}

// ________________________________________________________________________________________________
//
// HELPERS, AUX
// ________________________________________________________________________________________________

phRpc_H_Return_t phRpc_H_BoardInit(void *hdl)
{
    const uint8_t compact_rpc_incompatible[] = PH_RPC_H_NO_COMPACT_RPC_AVAILABLE;

    phRpc_H_Return_t ret    = PH_RPC_H_STATUS_OK;
    uint16_t         len    = phRpc_H_Diversity_GetDeviceBufferSize();
    phRpc_H_t       *h      = (phRpc_H_t*)hdl;

    ret = phRpc_H_SetCommParam(h);

    if (PH_RPC_H_STATUS_OK != ret)
    {
        // SW (up until LEO_R2) may not understand reset frames, but try.
        // We could end up here in case the host SW has been killed during a USB transfer.
        // Exchange a 0 frame, USB on device will be reset, but not the params already applied.
        phRpc_H_ExchangeResetFrame(h);
        ret = phRpc_H_SetCommParam(h); // Once again
    }

    if (PH_RPC_H_STATUS_OK == ret)
    {
        ret = phRpc_H_Diversity_GetDevCompatInfo(h->OutBuf, &len, 0); // Info type 0 is default
        if (PH_RPC_H_STATUS_OK == ret)
        {
            ret = phRpc_H_RWData(h, &len);
            if (PH_RPC_H_STATUS_OK == ret)
            {
                // De-Serialise response:
                len = phRpc_H_Diversity_GetDeviceBufferSize();
                ret =  phRpc_D_Diversity_GetDevCompatInfo(h->InBuf, len,
                                                          &(h->LastError.CommStatusM),
                                                          &(h->CompatInfo),
                                                          &(h->FeatureCode),
                                                          &(h->ValLevel),
                                                          &(h->MajorVersion),
                                                          &(h->MinorVersion));
                if ((PH_RPC_H_STATUS_OK == ret) && (PH_RPC_STATUS_OK == (uint8_t)(h->LastError.CommStatusM)))
                {
                    size_t  i;
                    uint8_t nc = 0;
                    // New version of RPC
                    // Queried data fields to be evaluated in the future, when more "new RPC" versions
                    // or board interfaces may become available.
                    h->NewRPC = 1u;
                    // See sw_id_cfg.py (APPLICATION CFG): The configuration of the feature code,
                    // major/minor revisions is there.
                    for (i = 0; i < sizeof(compact_rpc_incompatible); i++)
                    {
                        if (h->FeatureCode == compact_rpc_incompatible[i])
                        {
                            nc++;
                        }
                    }
                    if (0 == nc)
                    {
                        h->CompactRPC = 1u;
                        // It is a SW that will understand reset frames:
                        // This will cancel I/O operations on the device, in case that the host SW has been killed while I/O was ongoing.
                        // Exchange a 0 frame, USB on device will be reset, but not the params already applied
                        phRpc_H_ExchangeResetFrame(h);
                    } else
                    {
                        h->CompactRPC = 0;
                    }
                } else
                {
                    // Old RPC version
                    h->NewRPC = 0;
                    h->CompactRPC = 0;
                    ret = PH_RPC_H_STATUS_OK;
                }
            } else
            {
                // R/W failed
                h->NewRPC = 0;
                h->CompactRPC = 0;
                ret = PH_RPC_H_STATUS_OK;
            }
        } else
        {
            // Function failed, should not happen
            h->NewRPC = 0;
            h->CompactRPC = 0;
        }
    } else { }

    return ret;
}

uint8_t phRpc_H_ReadErrorRecovery(void *hdl, uint16_t *length)
{
    // RX Fault: The only justification for going into here would be a time-out condition.
    // USB guarantees BULK transfers to arrive, but does not guarantee a delivery deadline.
    // Said that, we should in case of time-out try to retrieve the response again.
    // But why is there another heuristic, checking the sequence number of the response?
    // If the device has sent back data with a wrong number we conclude that the previous host TX
    // operation has failed and the device has not received any command, consequently resulting
    // in a host time-out as well.

    uint8_t         ret             = PH_RPC_H_STATUS_OK;
    phRpc_H_t      *h               = (phRpc_H_t*)hdl;
    uint16_t        len;
    uint8_t         aux_out_buf[PH_RPC_H_AUXOUTBUFLEN];

    h->LastError.CommIncidents++;

    // Try to get the response which was badly delayed (RX)
    *length = phRpc_H_Diversity_GetDeviceBufferSize();
    ret = phRpc_H_ReadData(h, h->InBuf, length);

    // IF the second RX was NOT OK OR the SEQ NUM DOES'T MATCH
    if (!phRpc_H_ReadErrorRecoveryAux(h, ret))
    {
        // The last response shall be retrieved again (Prepare and TX)
        len = PH_RPC_H_AUXOUTBUFLEN;
        ret = phRpc_H_Diversity_GetLastResponse(aux_out_buf, &len);
        if (PH_RPC_H_STATUS_OK == ret)
        {
            (void)phRpc_H_Diversity_SetSeqNum(aux_out_buf, h->SeqNr);
            ret = phRpc_H_WriteData(h, aux_out_buf, len);
            // IF TX is OK
            if (PH_RPC_H_STATUS_OK == ret)
            {
                // RX shall be done
                *length = phRpc_H_Diversity_GetDeviceBufferSize();
                ret = phRpc_H_ReadData(h, h->InBuf, length);

                // IF RX was OK AND the SEQ NUM LAGS
                if ((PH_RPC_H_STATUS_OK == ret) && (phRpc_H_Diversity_GetSeqNum(h->InBuf) != h->SeqNr))
                {
                    // Last command (in OutBuf) shall be sent again
                    len = PH_RPC_H_AUXOUTBUFLEN;
                    ret = phRpc_H_WriteData(h, aux_out_buf, len);
                    // RX shall be done
                    *length = phRpc_H_Diversity_GetDeviceBufferSize();
                    h->InBuf = NULL;
                    ret = phRpc_H_ReadData(h, h->InBuf, length);
                    // IF RX is OK AND the SEQ NUM MATCHES
                    if (!phRpc_H_ReadErrorRecoveryAux(h, ret))
                    {
                        // RX ERROR
                    }
                }
                // ELSE IF RX was NOT OK OR the SEQ NUM DOES'T MATCH
                else if (!phRpc_H_ReadErrorRecoveryAux(h, ret))
                {
                    // RX ERROR
                }
            }
            else
            {
                // TX ERROR
            }
        }
    }

    return ret;
}

uint8_t phRpc_H_ReadErrorRecoveryAux(void *hdl, uint8_t ret)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;

    if ((PH_RPC_H_STATUS_OK == ret) && (phRpc_H_Diversity_GetSeqNum(h->InBuf) == h->SeqNr))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


// ________________________________________________________________________________________________
//
// CANCEL
// ________________________________________________________________________________________________

uint8_t phRpc_AuxIsIoPending(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    // Return 1 if the pending flag is set (do this explicitly).
    return (0 != h->IoPdFlag) ? 1u : 0;
}

void phRpc_AuxSetPendingFlag(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    h->IoPdFlag = 1;
}

void phRpc_AuxClearPendingFlag(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    h->IoPdFlag = 0;
}

void phRpc_AuxSetCancelFlag(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    h->CancelFlag = 1;
}

void phRpc_AuxClearCancelFlag(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    h->CancelFlag = 0;
}

uint8_t phRpc_AuxIoCancelCb(void *hdl)
{
    phRpc_H_t  *h   = (phRpc_H_t*)hdl;
    // Return 1 if the cancel flag is set (do this explicitly).
    return (0 != h->CancelFlag) ? 1u : 0;
}

void phRpc_H_SendCancelFrame(void *hdl, uint8_t type)
{
    const uint8_t  rcreset_buffer[PH_RPC_CMD_RESET_FRAME_LEN] = PH_RPC_CMD_RESET_FRAME;
    uint16_t length   = (uint16_t)PH_RPC_CMD_RESET_FRAME_LEN;
    switch (type)
    {
        default:
        case PH_RPC_HOSTIO_RCRESET:
            (void)phRpc_H_WriteData(hdl, (uint8_t*)rcreset_buffer, length);
            break;
    }
}

void phRpc_H_ExchangeResetFrame(void *hdl)
{

    phRpc_H_t *h = (phRpc_H_t*)hdl;
    uint8_t ret;
    uint8_t loop = 0;
    uint16_t in_len = phRpc_H_Diversity_GetDeviceBufferSize();
    uint16_t i;

    if (PH_RPC_H_OPENPARAM_NOCANCELIO == (h->Flags & PH_RPC_H_OPENPARAM_NOCANCELIO))
    {
        // I/O cancel on reconnect is not done
    } else
    {
        // I/O is cancelled on reconnect
        do
        {
            // Reset some fields
            h->SeqNr = 0;
            // Transmit & Receive; Eat response
            phRpc_H_SendCancelFrame(hdl, PH_RPC_HOSTIO_RCRESET);
            ret = phRpc_H_ReadData(hdl, h->InBuf, &in_len);
            if (PH_RPC_H_STATUS_OK  == ret)
            {
                for (i = PH_RPC_H_MIN_RES_LEN; i < in_len; i++)
                {
                    if (0 != h->InBuf[i])
                    {
                        ret = PH_RPC_H_STATUS_FRAMING_ERROR;
                        break;
                    }
                }
            } else
            {
                // Reset response not OK
            }
            loop++;
        } while ((loop < 4u) && (ret != PH_RPC_H_STATUS_OK));
    }
}

// ________________________________________________________________________________________________
//
// LOGGING
// ________________________________________________________________________________________________

#define PH_RPC_H_CHKPARM(_hdl_) if ((NULL == _hdl_) || (NULL == (_hdl_->LogF)) || (!PH_RPC_H_HDL_OK(_hdl_)))  return //

void phRpc_H_LogPtr(void *hdl, void *ptr)
{
    const int   len        = 8 + 2 + 1;
    wchar_t     s[len];
    phRpc_H_t *h = (phRpc_H_t*)hdl;

    PH_RPC_H_CHKPARM(h);
    if (NULL != ptr)
    {
        PH_RPC_H_SWPRINTF(s, len, L"%p ", ptr);
    } else
    {
        PH_RPC_H_SWPRINTF(s, len, L"%s ", L"NULL");
    }
    phRpc_H_LogWStr(hdl, s);
}

void phRpc_H_LogInt(void *hdl, int val, int base)
{
    const int   len        = 10 + 2 + 1;
    wchar_t     s[len];
    phRpc_H_t *h = (phRpc_H_t*)hdl;

    PH_RPC_H_CHKPARM(h);
    switch (base)
    {
        case 16:
            PH_RPC_H_SWPRINTF(s, len, L"%X", val);
            break;

        case 10:
        default:
            PH_RPC_H_SWPRINTF(s, len, L"%d", val);
            break;
    }
    phRpc_H_LogWStr(hdl, s);
}

void phRpc_H_LogWStr(void *hdl, wchar_t *logStr)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;
    PH_RPC_H_CHKPARM(h);
    if (NULL != logStr)
    {
        h->LogF(h->LogUserData, logStr);
    } else
    {
        h->LogF(h->LogUserData, L"NULL");
    }
}

phRpc_IoSystemData_t *phRpc_H_GetEngData(void *hdl)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;
    phRpc_IoSystemData_t *sys_data = NULL;

    if (NULL != h)
    {
        sys_data = &(h->IoSysData);
    } else { }

    return sys_data;
}

void phRpc_H_SetEngData(void *hdl, uint8_t *txBuf, uint8_t *rxBuf, uint16_t txLen, uint16_t rxLen, int locId)
{
    phRpc_IoSystemData_t *sd = &(((phRpc_H_t*)hdl)->IoSysData);
    sd->NumTx = txLen;
    sd->NumRx = rxLen;
    sd->TxBuf = txBuf;
    sd->RxBuf = rxBuf;
    sd->LocId = locId;
}

void phRpc_H_DbgPrint(void *hdl, uint8_t *buf, uint16_t len, uint8_t st, char *descr)
{
#   ifdef RPC_DBG_PRINT
    // Debug
    phRpc_H_t *h = (phRpc_H_t*)hdl;
    const uint16_t max_print = 64u;

    if ((NULL != h) && (NULL != buf) && (NULL != descr))
    {
        uint16_t i;
        uint16_t length = (len > max_print) ? max_print : len;

        printf("PCLIB DEBUG %s: Status = %02X, Len = %4d, buffer:", descr, st, len);

        for (i = 0; i < length; i++)
        {
            if (0 == i % 16)
            {
                printf("\n");
            }
            printf("%02X ", buf[i]);
        }

        printf("\n");
    }
#   else
    // Release
    (void)hdl;
    (void)buf;
    (void)len;
    (void)st;
    (void)descr;
#   endif
}

// ________________________________________________________________________________________________
//
// GENERIC HELPERS
// ________________________________________________________________________________________________

void phRpc_H_GenericInit(void *hdl, pphRpc_H_LogF_t logF, void *userLData,
                         pphRpc_H_EventHook_t hookF, void *userHData,
                         uint32_t optFlags)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;

    h->LowerRawCmd = NULL;
    h->LowerHandle = NULL;
    // Magic ID is essential for functions to work:
    h->MagicID = PH_RPC_H_MAGIC_ID;
    // Flags
    h->Flags = optFlags;
    // Further calls, CB functions MUST be set at the beginning:
    (void)phRpc_H_SetLockD(h, NULL, NULL);
    (void)phRpc_H_SetLogF(h, logF, userLData);
    (void)phRpc_H_SetHookF(h, hookF, userHData);
    (void)phRpc_H_SetTimeout(h, PH_RPC_H_DEFAULT_TO);
    // Members:
    memset(&(h->LastError), 0, sizeof(phRpc_Status_t));
    h->Retry = 0;
    h->NumSent = 0;
    h->NumReceived = 0;
    h->SeqNr = 0;
    h->PropagateDevErrToRetVal = 0;
    memset(&(h->MinIOData), 0, sizeof (phRpc_H_MinIO_t));
    // Mutex
    (void)phRpc_H_MutexInit(&h->TRxMutex);
    // Cancel/Pending:
    phRpc_AuxClearCancelFlag(h);
    phRpc_AuxClearPendingFlag(h);
}

void phRpc_H_GenericDeInit(void *hdl)
{
    phRpc_H_t *h = (phRpc_H_t*)hdl;
    // Mutex:
    (void)phRpc_H_MutexDeInit(&h->TRxMutex);
}

int phRpc_H_MutexInit(phRpc_Mutex_t *hMutex)
{
#   if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    return pthread_mutex_init(hMutex, NULL);
#   elif defined PH_RPC_H_PLAT_WINDOWS
    *hMutex = CreateMutex(0, FALSE, 0);
    return ((*hMutex) == 0);
#   elif !defined (PH_RPC_H_PLAT_IOS)
    #   warning MUTEX NOT IMPLEMENTED FOR IOS
    return 1;
#   else
    #   error NO PLATFORM DEFINED
#   endif
}

int phRpc_H_MutexDeInit(phRpc_Mutex_t *hMutex)
{
#   if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    return pthread_mutex_destroy(hMutex);
#   elif defined PH_RPC_H_PLAT_WINDOWS
    (void)CloseHandle(*hMutex);
    return 0;
#   elif !defined (PH_RPC_H_PLAT_IOS)
    #   warning MUTEX NOT IMPLEMENTED FOR IOS
    return 1;
#   else
    #   error NO PLATFORM DEFINED
#   endif
}

int phRpc_H_MutexAcquire(phRpc_Mutex_t *hMutex)
{
#   if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    return pthread_mutex_lock(hMutex);
#   elif defined PH_RPC_H_PLAT_WINDOWS
    return (WaitForSingleObject(*hMutex, INFINITE) == WAIT_FAILED ? 1 : 0);
#   elif !defined (PH_RPC_H_PLAT_IOS)
    #   warning MUTEX NOT IMPLEMENTED FOR IOS
    return 1;
#   else
    #   error NO PLATFORM DEFINED
#   endif
}

int phRpc_H_MutexRelease(phRpc_Mutex_t *hMutex)
{
#   if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    return pthread_mutex_unlock(hMutex);
#   elif defined PH_RPC_H_PLAT_WINDOWS
    return (ReleaseMutex(*hMutex) == 0);
#   elif !defined (PH_RPC_H_PLAT_IOS)
    #   warning MUTEX NOT IMPLEMENTED FOR IOS
    return 1;
#   else
    #   error NO PLATFORM DEFINED
#   endif
}
