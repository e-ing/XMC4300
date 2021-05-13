#include <AD8694.h>
AD8694::AD8694(unsigned char usicN, unsigned char chan, unsigned char sSelNum):	
I_ADC<vector<int>,int>(), 	
slN(sSelNum)
{
	data.resize(4, 0);
	spi = usics[usicN * USICS_NUM + chan];
	SPIini(usicN, chan, 17, 34 );
	OffSlaveSel(spi, slN);
	while(! WriteReg (AUTO_SEQ_EN, 0xf) );//+-10V operations, 5% overrange, 2 comliment code, to midscale after reset.
//	USICRxFIFOClean(spi);
	while(! WriteReg (FEATURE, ALARM_EN | FULL_INFO));
//	USICRxFIFOClean(spi);
	while(! WriteReg (CH0_RANGE, 0)); 	// +-2.5*4.096V
//	USICRxFIFOClean(spi);
	while(! WriteReg (CH1_RANGE, 0));		// +-2.5*4.096V
//	USICRxFIFOClean(spi);
	while(! WriteReg (CH2_RANGE, 0));		// +-2.5*4.096V
//	USICRxFIFOClean(spi);
	while(! WriteReg (CH3_RANGE, 0));		// +-2.5*4.096V
	USICRxFIFOClean(spi);
}

void AD8694::CnvStart()
{
	unsigned long tmp;
	while (! WriteCmd(AUTO_CH, tmp));
	//vector <int>::iterator it = data.begin();
	for(int i = 0; i < 4; ++i)
	{
		while(!WriteCmd(NOP, tmp));
		data[i] = tmp;
	}
	ready =  DONE;
}

Success AD8694::IsCnvReady()
{
	return ready;
}

bool AD8694::WriteReg(Regs rg, unsigned long val )
{
	bool ret;
	if(SPIdeviceConf(spi, PR_WORD_L << 1, PR_WORD_L, slN, CSPOL_LOW, MSB_FIRST))//TX Buffer ready check
	{
		unsigned short tmp = rg;
		unsigned short data[2] = {tmp << 5 | B4 | (unsigned short) val >> 4,
															(val & 0xf) << 8	} ;
		USICRxFIFOClean(spi);
		FastUSICTxw(spi, data, 2);
		ret = true;
	}
	else
		ret = false;
	return ret;
}

bool AD8694::WriteCmd(Commandos cmd, unsigned long &rxData)
{
	bool ret;
	if(SPIdeviceConf(spi, CMD_FRAME_L, CMD_WORD_L, slN, CSPOL_LOW, MSB_FIRST))//TX Buffer ready check
	{
		unsigned short data[3] = {cmd, 0, 0};
		USICRxFIFOClean(spi);
		FastUSICTxw(spi, data, 2);
		while( ! IsTxBuffEmpty(spi))
		{//wait the ent of Tx Empty frame 
		}
		//Read RxFIFO
		unsigned short rxW[3];
		unsigned int nWords = USICRxw(spi, rxW);
		rxData = rxW[1];
		rxData <<= 2;
		rxData |= rwW;
		ret = (nWords == 3)? true;
	}
	else
		ret = false;
	return ret;
}

bool AD8694::ReadReg(Regs rg, unsigned long &data)
{
	bool ret = false;
	return ret;
}
	