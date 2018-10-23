// File: phRpc_HostIo_iOS.m

#include "phRpc_HostIo_iOS.h"
#include "serial/SynchronSerial.h"

// ________________________________________________________________________________________________
static SynchronSerial	*synchronSerial = NULL;
// ________________________________________________________________________________________________
int	SerialOpen()
{	// returns 1 if cable present, -1 if not
	synchronSerial = [[SynchronSerial alloc] init];
	
	return 1;
}
// ________________________________________________________________________________________________
int	SerialClose()
{	// 
	// there's no such thing as RedParkClose(), so we just de-allocate
	synchronSerial = NULL;
	return 0;
}
// ________________________________________________________________________________________________
int	SerialWrite(uint8_t *data, uint16_t length)
{	// returns bytes written
    int     result = 0;
	if (synchronSerial) {
		SerialData		*serialData = [[SerialData alloc] init];
		
		serialData.data = data;
		serialData.length = length;
		serialData.result = 0;
		
		[synchronSerial writeBytesSerial:serialData];
		result = serialData.result;
	}
	return result;
}
// ________________________________________________________________________________________________
int SerialRead(uint8_t *data, uint16_t length)
{	// returns bytes read
    int     result = 0;
	if (synchronSerial) {
		SerialData		*serialData = [[SerialData alloc] init];

		serialData.data = data;
		serialData.length = length;
		serialData.result = 0;
	
		[synchronSerial readBytesSerial:serialData];
		result = serialData.result;
	}
	return result;
}
// ________________________________________________________________________________________________
int	SerialWait(struct timeval * tv)
{	// returns nr of bytes available for reading - 0 means timeout
	if (synchronSerial) {
		NSTimeInterval	timeout = tv->tv_usec/1000000.0f + tv->tv_sec;
	
		return [synchronSerial waitForBytesUntil:timeout];
	}
	return 0;
}
// ________________________________________________________________________________________________
int SerialBytesAvailable()
{
	if (synchronSerial) {
		return synchronSerial.bytesAvailable;
	}
	return 0;		// timeout
}
