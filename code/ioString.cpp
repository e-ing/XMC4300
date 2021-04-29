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

//const string OutStr::PushBuffer(const string str)
//{	
//	unsigned int fullSz = str.size();
//	const char* chStr = str.c_str();
//	unsigned int realSz = ASyncUSICTxb(uart, chStr, fullSz);
//	unsigned int remSz = fullSz - realSz;
//	cashBf = str.substr(realSz);
//	return cashBf;
//}

const char* OutStr::PushBuffer(const char* str)
{	
//	unsigned int fullSz = str.size();
//	const char* chStr = str.c_str();
//	unsigned int realSz = ASyncUSICTxb(uart, chStr, fullSz);
//	unsigned int remSz = fullSz - realSz;
//	cashBf = str.substr(realSz);
	return cashBuff;
}

unsigned int OutStr::GetBuffLen()
{
	
}