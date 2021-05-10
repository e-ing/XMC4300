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


OutStr::OutStr ( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen)
{
	uart = usics[usicN * USICS_NUM + chan];
	UARTini(usicN, chan, wLen, frLen);
}

void OutStr::PushBuffer(QuickStr &qst)
{	
	unsigned int fullSz = qst.Size();
	const char* chStr = qst;
	unsigned int realSz = ASyncUSICTxb(uart, chStr, fullSz);
	qst.CutOff(fullSz - realSz);
}

unsigned int OutStr::GetBuffLen()
{
	return GetTxBuffLenght(uart);
}