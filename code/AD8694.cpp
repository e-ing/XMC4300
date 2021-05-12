#include <AD8694.h>
AD8694::AD8694(unsigned char usicN, unsigned char chan, unsigned char sSelNum):
slN(sSelNum)
{
	spi = usics[usicN * USICS_NUM + chan];
	SPIini(usicN, chan, 17, 34 );
	OffSlaveSel(spi, slN);
//	WriteReg (0x3A9, WR_CTL_RG);//+-10V operations, 5% overrange, 2 comliment code, to midscale after reset.
	
}

void AD8694::CnvStart()
{
}

bool AD8694::IsCnvReadY()
{
	return false;
}