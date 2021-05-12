#ifndef USIC_H
#define USIC_H
#include <XMC4300.h>
#include <ioString.h>
#include <string.h>

enum CSpol
{
	CSPOL_HIGH = 0,
	CSPOL_LOW = 1 << 3
};

enum BitOrder
{
	LSB_FIRST = 0,
	MSB_FIRST = 1
};

//BRG
extern const unsigned long PASSIV_CLK_HIGH;
//SCTR
extern const unsigned char USICS_NUM;
extern const unsigned long WORD_LENGTH;
extern const unsigned long FRAME_LENGTH;
extern const unsigned long FRAME_LENGTH;
extern const unsigned long SHIFT_CLK_ACTIV_LEVEL;
extern const unsigned long MS_BIT_FIRST;
extern const unsigned long LS_BIT_FIRST;
extern const unsigned long PASSIV_DATA_LOW;
extern const unsigned long PASSIV_DATA_HIGH;
//TCSR
extern const unsigned long SINGLE_SHOT_MODE;
extern const unsigned long TX_START;
//PCR SPI
extern const unsigned long GENERATE_SLAVE_SEL;
extern const unsigned long DIRECT_SLAVE_SEL;
extern const unsigned long ACTIV_LOW_SLAVE_SEL;
//PCR UART
extern const unsigned long SMPL_IS_3;
extern const unsigned long SMPL_POINT_IS_8;
extern const unsigned long RX_STAT_EN;
extern const unsigned long TX_STAT_EN;
//CCR
extern const unsigned long NO_PARITY;
extern const unsigned long SPI_MODE;
extern const unsigned long UART_MODE;
//FIFO
extern const unsigned long RX_FIFO_SZ;
extern const unsigned long TX_FIFO_SZ;
extern const unsigned long FIFO_SZ_2;
extern const unsigned long FIFO_SZ_4;
extern const unsigned long FIFO_SZ_8;
extern const unsigned long FIFO_SZ_16;
extern const unsigned long FIFO_SZ_32;
extern const unsigned long FIFO_SZ_64;
extern const unsigned long TX_FIFO_LIMIT;
extern const unsigned long RX_FIFO_LIMIT;
extern const unsigned long FIFO_TRIG_EN;
extern const unsigned long FIFO_TRIG_MODE;
extern const unsigned long CLR_STD_TX_BF_EV;
extern const unsigned long  STD_TX_BF_EV_TR;
extern const unsigned long  STD_TX_BF_EV_TR;
extern const unsigned long RX_DATA_READY;

extern const unsigned long CS_CODE[];
extern USIC_CH_TypeDef* usics[];

void SPIini(unsigned char usicN, unsigned char chan, unsigned long wLen, unsigned long frLen );
void UARTini(unsigned char usicN, unsigned char chan, unsigned long wLen, unsigned long frLen );
void DisableAllSlavesSel(USIC_CH_TypeDef* s);
void SlaveSelMask(USIC_CH_TypeDef* s, unsigned char mask);//mask 0 - 0xff b0 - slave0, b1 - slave1.. 1 - active, 0 - off.
void ActivateSlaveSel(USIC_CH_TypeDef* s, unsigned char slaveNum);// num = 0-7; 
void OffSlaveSel(USIC_CH_TypeDef* s, unsigned char slaveNum);// num = 0-7;

unsigned int GetRxBuffLenght(USIC_CH_TypeDef* usic);
unsigned int GetTxBuffLenght(USIC_CH_TypeDef* usic);
bool IsTxBuffEmpty(USIC_CH_TypeDef* usic);

//Works until it transmit or puts all the data in the FIFO or completes on a timeout
//Returns the number of bytes actually transferred and puts to the FIFO
unsigned int SyncUSICTx(USIC_CH_TypeDef* usic, const unsigned short* data, unsigned int len);
//Works until it fills the FIFO. 
//After the buffer is filled, returns the number of bytes that could be transferred and placed in the FIFO.
unsigned int ASyncUSICTxw(USIC_CH_TypeDef* usic, const unsigned short* data, unsigned int len);
unsigned int ASyncUSICTxb(USIC_CH_TypeDef* usic, const char* data, unsigned int len);
unsigned int USICRxw(USIC_CH_TypeDef* usic, unsigned short* data);
void USICRxFIFOClean(USIC_CH_TypeDef* usic);
unsigned int USICRxb(USIC_CH_TypeDef* usic, char* data);
bool SPIdeviceConf(USIC_CH_TypeDef* usic, unsigned long frLen, unsigned long wLen, unsigned char csNum, CSpol csPolar, BitOrder btOrder  );
void  FastUSICTxw(USIC_CH_TypeDef* usic, const unsigned short* data, unsigned int len);

#endif
