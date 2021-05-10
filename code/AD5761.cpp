#include <AD5761.h>
//	unsigned char slN;
//	Abstract_oBit* pinLoad;
//	USIC_CH_TypeDef* spi;
bool AD5761::SetVal(int val)
{
	bool ret =  WriteReg(val, AD5761_WR_AND_UPDATE);
	lastVal = ret? val : lastVal;
	return ret;
}
	
bool AD5761::WriteReg(unsigned long val,  AD5761Rgs rgAdr)
{
	//configure DAC CS
//configure CS polarity
	//configure word and faramen lenght	
	bool ret;
	if(SPIdeviceConf(spi, FRAME_L, WORD_L, slN, CSPOL_LOW, MSB_FIRST))
	{
		//TX Buffer ready check
		unsigned short txData[2];
		txData[0] = (unsigned short)(val >> 12) | rgAdr << 4;
		txData[1] = (unsigned short)(val & 0xFFF);
		FastUSICTxw(spi, txData, 2);
		ret = true;
	}
	else
		ret = false;
	return ret;
}
	
unsigned long AD5761::ReadReg()
{
	return 0;
}

AD5761::AD5761(unsigned char usicN, unsigned char chan, unsigned char sSelNum, AbstrBitOut &loadPin ):
slN(sSelNum),
pinLoad(loadPin)
{
	pinLoad = loadPin;
	spi = usics[usicN * USICS_NUM + chan];
	SPIini(usicN, chan, 12, 2 );
	OffSlaveSel(spi, slN);
	pinLoad = false;// sync Mode
}

AbstrIntOut&  AD5761::operator = (const char* cmd)
{
	return *this;
}




