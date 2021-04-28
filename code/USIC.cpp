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
//PCR SPI
const unsigned long GENERATE_SLAVE_SEL = 1;
const unsigned long DIRECT_SLAVE_SEL = 2;
const unsigned long ACTIV_LOW_SLAVE_SEL = 4;
//PCR UART
const unsigned long SMPL_IS_3 = 1;
const unsigned long SMPL_POINT_IS_8 = 8 << 8;
const unsigned long RX_STAT_EN = 1 << 16;
const unsigned long TX_STAT_EN = 1 << 17;
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
const unsigned long STD_TX_BF_EV_TR = 1 << 14;
const unsigned long RX_DATA_READY = 1 << 14 | 1 << 13;

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
	Abstract_iBit* miso = new GPin (GPP2, 2);//usic0 ch1 DX0A
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

void UARTini(unsigned char usicN, unsigned char chan, unsigned long wLen, unsigned long frLen)
{	
	bool isOk = true;
	Abstract_iBit* rx = new GPin (GPP0, 0);//usic1 Ch1 DX0D
	switch(usicN)
	{
		case 0: 
			SCU_CLK->CGATCLR0 = 1 << 11;  // disable USIC0 clock gating;
			break;
		case 1:
			SCU_CLK->CGATCLR1 = 1 << 7;  //  disable USIC1 clock gating;
			break;
		default:
			isOk = false;
			break;
	}
	if(isOk) //USIC0 & USIC1 only
	{		
		USIC_CH_TypeDef* uart = usics[usicN * USICS_NUM + chan];
		uart->KSCFG = 3; // Module enable & bit protection
	//==Clock==
		uart->CCR &= 0xFFFFFFFF00;//usic disable
		uart->FDR = 1 << 14 | 0x3FE; //0x3fe == 115200
		uart->BRG &= 0xFFFC0083EF;
		uart->BRG = PASSIV_CLK_HIGH | 0xf << 10;// | 0 << 16; //Time Quanta = 15, divider = 1;
	//==Shift control	
		uart->SCTR = (wLen  - 1) << 24 | (frLen - 1) << 16 | SHIFT_CLK_ACTIV_LEVEL << 8 | PASSIV_DATA_HIGH;// | MS_BIT_FIRST;
	//Tx control
		uart->TCSR = 1 << 12 | TX_START | SINGLE_SHOT_MODE;	
	//UART protocol	
		uart->PCR = SMPL_IS_3 | SMPL_POINT_IS_8 | RX_STAT_EN | TX_STAT_EN;		
	//Clear Flags
		uart->PSCR = 0xFFFFFFFF;
		uart->CCR = NO_PARITY;
		uart->DX0CR = 0x103;// Rx = P0.0 = DX0D, async,  inverted polarity	
		uart->TBCTR &= 0xF8FFC0C0;
		uart->TBCTR = TX_FIFO_LIMIT | FIFO_TRIG_MODE | FIFO_TRIG_EN;	
		uart->RBCTR = 32 |  RX_FIFO_LIMIT | FIFO_TRIG_MODE | FIFO_TRIG_EN;
		uart->TBCTR |= FIFO_SZ_32;
		uart->RBCTR |= FIFO_SZ_32;
		uart->CCR |= UART_MODE;//usic start in SPI mode
	}
}

static bool IsTxFIFOFilled(USIC_CH_TypeDef* usic)
{
	static const unsigned long MASK =  0x0000003F;
	unsigned long ptrs =  usic->TRBPTR;
	unsigned long top = ptrs &  MASK;
	unsigned long bot = (ptrs >> 5) & MASK;
	unsigned int delta = (top > bot)? (top - bot) : (bot - top);
	return (delta < 31)? false : true; 
}	

static bool IsRxFIFOEmpty(USIC_CH_TypeDef* usic)
{
	return ( (usic->RBUFSR & RX_DATA_READY) == 0)? true : false; 
}

unsigned int GetRxBuffLenght(USIC_CH_TypeDef* usic)
{
	static const unsigned long MASK =  0x0000003F;
	unsigned long ptrs =  usic->TRBPTR;
	unsigned long top = (ptrs >> 16) &  MASK;
	unsigned long bot = (ptrs >> 24) & MASK;
	unsigned int ret = (top > bot)? (top - bot) : (bot - top);
	return ret; 
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
unsigned int SyncUSICTx(USIC_CH_TypeDef* usic, const unsigned short* data, unsigned int len)
{
	signed int timeout = LIMIT;
	int nTx;
	for (nTx = 0; (nTx < len) && (timeout > 0) ; )
	{
		timeout = LIMIT;
		while ( IsTxFIFOFilled(usic) && (--timeout > 0) )
		{
		}
			//timeIsUp = (--timeout > 0)? false : true; 
		(timeout == 0)? DoNoth() : Tx(usic, data[nTx++]); 
	}
	return nTx;
}

//Works until it fills the FIFO. 
//After the buffer is filled, returns the number of words that could be transferred and placed in the FIFO.
unsigned int ASyncUSICTxw(USIC_CH_TypeDef* usic, const unsigned short* data, unsigned int len)
{
	int nTx;
	for (nTx = 0; (nTx < len) && !IsTxFIFOFilled(usic) ; )
		Tx(usic, data[nTx++]); 
	return nTx;
}

unsigned int ASyncUSICTxb(USIC_CH_TypeDef* usic, const char* data, unsigned int len)
{
	int nTx;
	for (nTx = 0; (nTx < len) && !IsTxFIFOFilled(usic) ; )
		Tx(usic, data[nTx++]); 
	return nTx;
}

unsigned int USICRxw(USIC_CH_TypeDef* usic, unsigned short* data)
{
	
	unsigned int num = 0;
	while (!IsRxFIFOEmpty(usic))
		data[num++] = usic->OUTR;
	return num;
}

unsigned int USICRxb(USIC_CH_TypeDef* usic, char* data)
{
	
	unsigned int num = 0;
	while (!IsRxFIFOEmpty(usic))
		data[num++] = (char) (usic->OUTR  & 0xff);
	return num;
}































