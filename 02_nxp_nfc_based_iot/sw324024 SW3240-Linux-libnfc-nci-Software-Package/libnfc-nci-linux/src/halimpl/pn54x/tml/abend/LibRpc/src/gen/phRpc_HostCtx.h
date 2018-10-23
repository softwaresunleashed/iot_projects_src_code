
//
// Generated File. Do not edit.
// Generator = C:\Work\pn547_sw\Tools\ARM_Board\trunk\ARMBoard_SW\comps\phRpc\src\cfg\ctx_gen_cfg.py
//


#ifndef PHRPC_HOSTCTX
#define PHRPC_HOSTCTX


typedef enum phRpc_H_E
{
    phRpc_H_E_MinorVersion,
    phRpc_H_E_Retry,
    phRpc_H_E_InBuf,
    phRpc_H_E_LockD,
    phRpc_H_E_MajorVersion,
    phRpc_H_E_LockUserData,
    phRpc_H_E_NewRPC,
    phRpc_H_E_FeatureCode,
    phRpc_H_E_NumSent,
    phRpc_H_E_PadMul,
    phRpc_H_E_LogF,
    phRpc_H_E_CompatInfo,
    phRpc_H_E_Flags,
    phRpc_H_E_CancelFlag,
    phRpc_H_E_device_PH_RPC_H_DEVNAMELEN_,
    phRpc_H_E_CompactRPC,
    phRpc_H_E_LastError,
    phRpc_H_E_HookF,
    phRpc_H_E_MagicID,
    phRpc_H_E_CancelInitial,
    phRpc_H_E_UserData,
    phRpc_H_E_OutBuf,
    phRpc_H_E_TimeoutMillisec,
    phRpc_H_E_PadPlus1,
    phRpc_H_E_LowerHandle,
    phRpc_H_E_NumReceived,
    phRpc_H_E_LowerRawCmd,
    phRpc_H_E_MinIOData,
    phRpc_H_E_Guard,
    phRpc_H_E_IoSysData,
    phRpc_H_E_PropagateDevErrToRetVal,
    phRpc_H_E_TRxMutex,
    phRpc_H_E_SeqNr,
    phRpc_H_E_LogUserData,
    phRpc_H_E_ValLevel,
    phRpc_H_E_IoPdFlag,
    #if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)
    phRpc_H_E_wfds,
    phRpc_H_E_rfds,
    phRpc_H_E_fd,
    phRpc_H_E_old_tios,
    #elif defined PH_RPC_H_PLAT_WINDOWS
    phRpc_H_E_OldTimeouts,
    phRpc_H_E_OvR,
    phRpc_H_E_Dcb,
    phRpc_H_E_OldDcb,
    phRpc_H_E_OvW,
    phRpc_H_E_Timeouts,
    phRpc_H_E_hc,
    phRpc_H_E_CommInterface,
    phRpc_H_E_dev,
    #endif 
    phRpc_H_E_MAX_INDEX
} phRpc_H_E_t;


typedef struct phRpc_H
{
    uint8_t              MinorVersion               ; // Board Data and RPC - Minor Version
    uint8_t              Retry                      ; // 
    uint8_t              *InBuf                     ; // 
    pphRpc_H_LockD_t     LockD                      ; // 
    uint8_t              MajorVersion               ; // Board Data and RPC - Major Version
    void                 *LockUserData              ; // 
    uint8_t              NewRPC                     ; // Board Data and RPC - Is "new" RPC
    uint8_t              FeatureCode                ; // Board Data and RPC - Feature
    uint16_t             NumSent                    ; // 
    uint8_t              PadMul                     ; // Pad in multiples of the min transfer length
    pphRpc_H_LogF_t      LogF                       ; // 
    uint16_t             CompatInfo                 ; // Board Data and RPC - Compatibility
    uint32_t             Flags                      ; // 
    uint8_t              CancelFlag                 ; // When set there was an attempt to cancel the ongoing I/O
    wchar_t              device[PH_RPC_H_DEVNAMELEN]; // 
    uint8_t              CompactRPC                 ; // Board Data and RPC - Uses "Compact" RPC
    phRpc_Status_t       LastError                  ; // 
    pphRpc_H_EventHook_t HookF                      ; // 
    uint32_t             MagicID                    ; // 
    uint8_t              CancelInitial              ; // Cancel request, if host app was killed and is re-opened while I/O on device is pending
    void                 *UserData                  ; // 
    uint8_t              *OutBuf                    ; // 
    uint16_t             TimeoutMillisec            ; // 
    uint8_t              PadPlus1                   ; // Pad one extra byte
    void                 *LowerHandle               ; // Primary Lib Handle
    uint16_t             NumReceived                ; // 
    pphRpc_H_Raw_t       LowerRawCmd                ; // Primary Lib RAW command
    phRpc_H_MinIO_t      MinIOData                  ; // 
    uint32_t             Guard                      ; // 
    phRpc_IoSystemData_t IoSysData                  ; // Engineering data
    uint8_t              PropagateDevErrToRetVal    ; // 
    phRpc_Mutex_t        TRxMutex                   ; // Transmit/Receive Mutex
    uint8_t              SeqNr                      ; // 
    void                 *LogUserData               ; // 
    uint8_t              ValLevel                   ; // Board Data and RPC - Validation level
    uint8_t              IoPdFlag                   ; // When set we have an ongoing I/O
    #if defined (PH_RPC_H_PLAT_GNUC) || defined (PH_RPC_H_PLAT_LINUX)//
    fd_set               wfds                       ; // 
    fd_set               rfds                       ; // 
    int32_t              fd                         ; // 
    struct termios       old_tios                   ; // 
    #elif defined PH_RPC_H_PLAT_WINDOWS//
    COMMTIMEOUTS         OldTimeouts                ; // 
    OVERLAPPED           OvR                        ; // 
    DCB                  Dcb                        ; // 
    DCB                  OldDcb                     ; // 
    OVERLAPPED           OvW                        ; // 
    COMMTIMEOUTS         Timeouts                   ; // 
    void                 *hc                        ; // 
    uint8_t              CommInterface              ; // 
    usb_dev_handle       *dev                       ; // 
    #endif //
} phRpc_H_t;


void phRpc_H_ToString(phRpc_H_t *compCtx, int index, wchar_t *txtBuf, size_t *txtBufLen);

#endif // Guard


