#ifndef AD5761_H
#define AD5761_H
//#include <AbstractIfcs.h>
#include <USIC.h>



class AD5761 : public AbstrIntOut
{
enum AD5761Rgs
{
	AD5761_WR_WO_UPDATE = 1,
	AD5761_UPDATE = 2,
	AD5761_WR_AND_UPDATE = 3,
	AD5761_WR_CTL = 4
};
protected:
	static const unsigned long WORD_L = 12;
	static const unsigned long FRAME_L = 24;
	unsigned char slN;
	AbstrBitOut &pinLoad;
	USIC_CH_TypeDef* spi;
	
	
	virtual bool WriteReg(unsigned long val, AD5761Rgs rgAdr);
	virtual unsigned long ReadReg();
public:
	AD5761(unsigned char usicN, unsigned char chan, unsigned char sSelNum, AbstrBitOut &loadPin );
	virtual bool SetVal(int val);
	virtual AbstrIntOut&  operator = (const char* cmd);
	virtual ~AD5761(){}
};

#endif
