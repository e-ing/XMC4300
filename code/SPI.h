#ifndef SPI_H
#define SPI_H

extern const unsigned long PASSIV_CLK_HIGH;
extern const unsigned char USICS_NUM;
extern const unsigned long WORD_LENGTH;
extern const unsigned long FRAME_LENGTH;
extern const unsigned long FRAME_LENGTH;
extern const unsigned long SHIFT_CLK_ACTIV_LEVEL;
extern const unsigned long MS_BIT_FIRST;
extern const unsigned long LS_BIT_FIRST;
extern const unsigned long PASSIV_DATA_LOW;
extern const unsigned long PASSIV_DATA_HIGH;
extern const unsigned long SINGLE_SHOT_MODE;
extern const unsigned long TX_START;
extern const unsigned long GENERATE_SLAVE_SEL;
extern const unsigned long DIRECT_SLAVE_SEL;
extern const unsigned long ACTIV_LOW_SLAVE_SEL;
extern const unsigned long NO_PARITY;
extern const unsigned long SPI_MODE;
extern const unsigned long UART_MODE;
extern const unsigned long FIFO_SZ_2;
extern const unsigned long FIFO_SZ_4;
extern const unsigned long FIFO_SZ_8;
extern const unsigned long FIFO_SZ_16;
extern const unsigned long FIFO_SZ_32;
extern const unsigned long FIFO_SZ_64;
extern const unsigned long TX_FIFO_LIMIT;


void SPIini(unsigned char usicN, unsigned char chan, unsigned long wLen, unsigned long frLen );
void DisableAllSlavesSel();
void SlaveSelMask(unsigned char mask);//mask 0 - 0xff b0 - slave0, b1 - slave1.. 1 - active, 0 - off.
void ActivateSlaveSel(unsigned char slaveNum);// num = 0-7; 
void TxSPI(unsigned char usicN, unsigned char chan, unsigned short* data, unsigned char len);


#endif
