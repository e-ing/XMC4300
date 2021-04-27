#include <ioString.h>
unsigned int InStr::GetStr(char* buff)
{
}

InStr::InStr( unsigned char usicN, unsigned char chan,
				  unsigned long wLen, unsigned long frLen)
{
	USIC_CH_TypeDef* spi = usics[usicN * USICS_NUM + chan];
}

unsigned int InStr::GetDataLen()
{
}