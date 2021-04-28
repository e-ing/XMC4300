#include <ioString.h>
#include <string.h>

unsigned int InStr::GetStr(char* buff)
{
	return USICRxb(uart, buff);
}

InStr::InStr( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen)
{
	uart = usics[usicN * USICS_NUM + chan];
	UARTini(usicN, chan, wLen, frLen);
	bfr = new char [MAX_BUFF_SZ];
}

unsigned int InStr::GetDataLen()
{
	return GetRxBuffLenght(uart);
}

const char* OutStr::PushBuffer(const char* str)
{	
	unsigned int fullSz = strlen(str);
	unsigned int realSz = ASyncUSICTxb(uart, str, fullSz);
	unsigned int remSz = fullSz - realSz;
	return (remSz > 0)? str + realSz : NULL;
}