#include <USIC.h>
#include <GPIO.h>

const unsigned char USICS_NUM = 2;
//BRG
const unsigned long PASSIV_CLK_HIGH = 30 << 1;
//SCTR
//const unsigned long WORD_LENGTH = 16;
//const unsigned long FRAME_LENGTH = 1;
const unsigned long SHIFT_CLK_ACTIV_LEVEL = 1;
const unsigned long MS_BIT_FIRST = 1;
const unsigned long LS_BIT_FIRST = 0;
const unsigned long PASSIV_DATA_LOW = 0;
const unsigned long PASSIV_DATA_HIGH = 1 << 1;
//TCSR
const unsigned long SINGLE_SHOT_MODE = 1 << 8;
const unsigned long TX_START = 1 << 10;;
//PCR
const unsigned long GENERATE_SLAVE_SEL = 1;
const unsigned long DIRECT_SLAVE_SEL = 2;
const unsigned long ACTIV_LOW_SLAVE_SEL = 4;
//CCR
const unsigned long NO_PARITY = 0;
const unsigned long SPI_MODE = 1;
const unsigned long UART_MODE = 2;
//FIFO
const unsigned long FIFO_SZ_2 = 1 << 24;
const unsigned long FIFO_SZ_4 = 2 << 24;
const unsigned long FIFO_SZ_8 = 3 << 24;
const unsigned long FIFO_SZ_16 = 4 << 24;
const unsigned long FIFO_SZ_32 = 5 << 24;
const unsigned long FIFO_SZ_64 = 6 << 24;
const unsigned long TX_FIFO_LIMIT = 1 << 8;
const unsigned long RX_FIFO_LIMIT = 30 << 8;
const unsigned long FIFO_TRIG_EN = 1 << 15;
const unsigned long FIFO_TRIG_MODE = 1 << 14;
const unsigned long CLR_STD_TX_BF_EV = 1 << 8;
const unsigned int  STD_TX_BF_EV_TR = 1 << 14;

USIC_CH_TypeDef* usics[] = {USIC0_CH0, USIC0_CH1, USIC1_CH0, USIC1_CH1}; 


void DisableAllSlavesSel(USIC_CH_TypeDef* s)
{
	s->PCR &= 0xFF00FFFF;
}

void SlaveSelMask(USIC_CH_TypeDef* s, unsigned char mask)//mask 0 - 0xff b0 - slave0, b1 - slave1.. 1 - active, 0 - off.
{
	s->PCR = mask << 16;
}

void ActivateSlaveSel(USIC_CH_TypeDef* s, unsigned char slaveNum)// num = 0-7;
{
	unsigned long mask = 1 << (slaveNum + 16);
	s->PCR |= mask;
}

void SPIini(unsigned char usicN, unsigned char chan, unsigned long wLen, unsigned long frLen)
{	
	Abstract_iBit* MISO = new GPin (GPP2, 2);
	SCU_CLK->CGATCLR0 = 1 << 11; //disable USIC0 clock gating;	
	USIC_CH_TypeDef* spi = usics[usicN * USICS_NUM + chan];
	spi->KSCFG = 3; // Module enable & bit protection
//==Clock==
	spi->CCR &= 0xFFFFFFFF00;//usic disable
	spi->FDR = 1 << 14 | 0x3FE; //0x3fe == 115200
	spi->BRG &= 0xFFFC0083EF;
	spi->BRG = PASSIV_CLK_HIGH | 0xf << 10;// | 0 << 16; //Time Quanta = 15, divider = 1;
//==Shift control	
	spi->SCTR = (wLen  - 1) << 24 | (frLen - 1) << 16 | SHIFT_CLK_ACTIV_LEVEL << 8 | PASSIV_DATA_HIGH | MS_BIT_FIRST;
//Tx control
	spi->TCSR = 1 << 12 | TX_START | SINGLE_SHOT_MODE;	
//SPI protocol
	spi->PCR = ACTIV_LOW_SLAVE_SEL | DIRECT_SLAVE_SEL | GENERATE_SLAVE_SEL;		
//Clear Flags
	spi->PSCR = 0xFFFFFFFF;
	spi->CCR = NO_PARITY;
	spi->DX0CR = 0x40;// MISO = P22 = DX0A, rising edge is active	
	spi->TBCTR &= 0xF8FFC0C0;
	spi->TBCTR = TX_FIFO_LIMIT | FIFO_TRIG_MODE | FIFO_TRIG_EN ;	
	spi->RBCTR = 32 |  RX_FIFO_LIMIT | FIFO_TRIG_MODE | FIFO_TRIG_EN;
	spi->TBCTR |= FIFO_SZ_32;
	spi->RBCTR |= FIFO_SZ_32;
	spi->CCR |= SPI_MODE;//usic start in SPI mode
}

bool IsTxFIFOFilled(USIC_CH_TypeDef* usic)
{
	static const unsigned long MASK =  0x0000003F;
	unsigned long ptrs =  usic->TRBPTR;
	unsigned long top = ptrs &  MASK;
	unsigned long bot = (ptrs >> 5) & MASK;
	return ((top - bot) < 31)? false : true; 
}	

bool IsRxFIFOEmpty(USIC_CH_TypeDef* usic)
{
}

static void DoNoth()//USIC_CH_TypeDef* usic, unsigned short data)
{
}

static void Tx(USIC_CH_TypeDef* usic, unsigned short data)
{
	usic->IN[0] = data;
}


static const unsigned int LIMIT = 10000000;
//Works until it transmit or puts all the data in the FIFO or completes on a timeout
//Returns the number of words actually transferred and puts to the FIFO
unsigned int SyncTxSPI(unsigned char usicN, unsigned char chan, unsigned short* data, unsigned int len)
{
	USIC_CH_TypeDef* spi = usics[usicN * USICS_NUM + chan];
	signed int timeout = LIMIT;
	int nTx;
	for (nTx = 0; (nTx < len) && (timeout > 0) ; )
	{
		timeout = LIMIT;
		while ( IsTxFIFOFilled(spi) && (--timeout > 0) )
		{
		}
			//timeIsUp = (--timeout > 0)? false : true; 
		(timeout == 0)? DoNoth() : Tx(spi, data[nTx++]); 
	}
	return nTx;
}

//Works until it fills the FIFO. 
//After the buffer is filled, returns the number of words that could be transferred and placed in the FIFO.
unsigned int AsyncTxSPI(unsigned char usicN, unsigned char chan, unsigned short* data, unsigned int len)
{
	USIC_CH_TypeDef* spi = usics[usicN * USICS_NUM + chan];
	int nTx;
	for (nTx = 0; (nTx < len) && !IsTxFIFOFilled(spi) ; )
		Tx(spi, data[nTx++]); 
	return nTx;
}

unsigned char RxSPI(unsigned char usicN, unsigned char chan, unsigned short* data)
{
	USIC_CH_TypeDef* spi = usics[usicN * USICS_NUM + chan];	
}






























