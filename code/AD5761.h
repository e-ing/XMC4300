#ifndef AD5761_H
#define AD5761_H
#include <USIC.h>



class AD5761 : public AbstrIntOut
{
protected:
	enum Regs
	{
		NOP_RG = 0,
		WR_WO_UPDATE_RG = 1,
		UPDATE_RG = 2,
		WR_AND_UPDATE_RG = 3,
		WR_CTL_RG = 4,
		RD_INPUT_RG = 0xA,
		RD_OUT_RG = 0xB,
		RD_CTL_RG = 0xC
	};

	static const unsigned long WORD_L = 12;
	static const unsigned long FRAME_L = 24;
	unsigned char slN;
	AbstrBitOut &pinLoad;
	USIC_CH_TypeDef* spi;
	
	
	virtual bool WriteReg(Regs rgAdr, unsigned long val);
	virtual bool ReadReg(Regs rgAd, unsigned long &data);
public:
	AD5761(unsigned char usicN, unsigned char chan, unsigned char sSelNum, AbstrBitOut &loadPin );
	virtual bool SetVal(int val);
	virtual  AbstrIntOut&  operator =  (const char* cmd); 
	virtual ~AD5761(){}
};

#endif
