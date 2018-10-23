
// File: phRpc_HostIo_iOS.h

#ifndef PHRPC_HOSTIO_IOS_H
#define PHRPC_HOSTIO_IOS_H

int		SerialOpen();		// returns 1 if cable present, 0 if not
int		SerialClose();		// 

int		SerialWrite(uint8_t *data, uint16_t length);
int		SerialRead(uint8_t *data, uint16_t length);
int		SerialBytesAvailable();
int		SerialWait(struct timeval * tv);

#endif // Guard
