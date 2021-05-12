#ifndef AD8694_H
#define AD8694_H
#include <AbstractIfcs.h>
#include <USIC.h>
#include <vector>
//#include <array>

class AD8694 : public I_ADC < vector <int> , int>
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
	virtual int GetValue() const;
	static const unsigned long WORD_L = 12;
	static const unsigned long FRAME_L = 24;
	unsigned char slN;
	USIC_CH_TypeDef* spi;
	virtual bool WriteReg(unsigned long val, Regs rg);
	virtual bool ReadReg(Regs rg, unsigned long &data);
	
public:
	AD8694(unsigned char usicN, unsigned char chan, unsigned char sSelNum);
	virtual void CnvStart();
	virtual bool IsCnvReadY();
};



//class AD8694// : public //AbstrIntIn 
//{
//protected:
//	virtual int GetValue() const;
//	static const unsigned long WORD_L = 12;
//	static const unsigned long FRAME_L = 24;
//	unsigned char slN;
//	USIC_CH_TypeDef* spi;
////	virtual bool WriteReg(unsigned long val, Regs rgAdr);
////	virtual bool ReadReg(Regs rgAd, unsigned long &data);
//public:
//	AD8694(unsigned char usicN, unsigned char chan, unsigned char sSelNum);
//	virtual ~AD8694() {}
//};


#endif
