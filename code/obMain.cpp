/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): Blinky example for XMC4300
 *----------------------------------------------------------------------------
 * Blink LED connected with P4.0, P4.1
 * XMC4300 Relax kit
 *
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <XMC4300.h>
#include <GPIO.h>

volatile unsigned long msTicks;                      /* counts 1ms timeTicks       */

void SysTick_Handler(void) {
  msTicks++;
}

void Delay (uint32_t dlyTicks)
{
  unsigned long curTicks = msTicks;
	unsigned long residue = 0xffffffff - curTicks;
	if(residue >= dlyTicks)
		while ((msTicks - curTicks) < dlyTicks)
			__NOP();
	else
	{ 
		unsigned long tail = dlyTicks - residue - 1;
		while ( msTicks >= curTicks)
			__NOP();
		while (msTicks < tail)
			__NOP();
	}
}




int main (void) {

  SystemCoreClockUpdate();                      /* update SystemCoreClock     */
  if (SysTick_Config(SystemCoreClock / 1000)) 
	{ 																						/* SysTick 1 msec interrupts  */
    while (1) __NOP();                          /* Capture error              */
  }

 // LED_Init();
//	GPout hbBit(GPP5, 3);
	Abstract_oBit* hbBit = new GPout (GPP2, 7);
	Abstract_oBit* indBit = new GPout (GPP2, 8);
	Abstract_iBit* tst = new GPin (GPP2, 9);
	bool x = true;
//SPI
	Abstract_oBit* adCS = new GPout(GPP2, 3);
	*adCS = 1;
	Abstract_oBit* daCS = new GPout(GPP1, 13);
	*daCS = 1;
	Abstract_oBit* ldac = new GPout(GPP1, 14);
	*ldac = 1;
	Abstract_oBit* mosi = new GPout(GPP2, 5);
	Abstract_oBit* sclk = new GPout(GPP2, 4);
	Abstract_iBit* miso = new GPin(GPP2, 2);
	
	
	adCS->SetAltFn(2);
	daCS->SetAltFn(2);
	mosi->SetAltFn(2);
	sclk->SetAltFn(2);

	
	
  while(true)
	{                               
 //   LED_On ();
		*hbBit = 1;
    Delay(500);                              
		!*hbBit;
    //LED_Off();                               
    Delay(500);                              
		*hbBit << &x;
		Delay(100);
		*hbBit = false;
		Delay(200);
		*indBit = !tst;	
  }

}



//#include <Bits.h>
//#include <AbstractIfcs.h>

//#pragma pack(push, 1)
//struct PortGPIO
//{
//	unsigned long  OUT;                               /*!< (@ 0x48028000) Port 0 Output Register                                 */
//  unsigned long  OMR;                               /*!< (@ 0x48028004) Port 0 Output Modification Register                    */
//  unsigned long  RESERVED[2];
//  unsigned long  IOCR0;                             /*!< (@ 0x48028010) Port 0 Input/Output Control Register 0                 */
//  unsigned long  IOCR4;                             /*!< (@ 0x48028014) Port 0 Input/Output Control Register 4                 */
//  unsigned long  IOCR8;                             /*!< (@ 0x48028018) Port 0 Input/Output Control Register 8                 */
//  unsigned long  IOCR12;                            /*!< (@ 0x4802801C) Port 0 Input/Output Control Register 12                */
//  unsigned long  RESERVED1;
//  unsigned long  IN;                                /*!< (@ 0x48028024) Port 0 Input Register                                  */
//  unsigned long  RESERVED2[6];
//  unsigned long  PDR0;                              /*!< (@ 0x48028040) Port 0 Pad Driver Mode 0 Register                      */
//  unsigned long  PDR1;                              /*!< (@ 0x48028044) Port 0 Pad Driver Mode 1 Register                      */
//  unsigned long  RESERVED3[6];
//  unsigned long  PDISC;                             /*!< (@ 0x48028060) Port 0 Pin Function Decision Control Register          */
//  unsigned long  RESERVED4[3];
//  unsigned long  PPS;                               /*!< (@ 0x48028070) Port 0 Pin Power Save Register                         */
//  unsigned long  HWSEL;                             /*!< (@ 0x48028074) Port 0 Pin Hardware Select Register                    */
//};
//#pragma pack(pop)

//volatile PortGPIO* GPIOs [] = {(PortGPIO*) PORT0_BASE, (PortGPIO*) PORT1_BASE, (PortGPIO*) PORT2_BASE, (PortGPIO*) PORT3_BASE,
//															 (PortGPIO*) PORT4_BASE, (PortGPIO*) PORT5_BASE, (PortGPIO*) PORT14_BASE, (PortGPIO*) PORT15_BASE};



//															 
//															 //GPout and etc
//class GPout : public   Abstract_oBit
//{
//protected:
//	virtual bool GetState();
//	virtual void SetValue( bool x);
//	virtual void Toggle ();
//public:
//	GPout(unsigned char port, unsigned char pin);
//	virtual void Set();
//	virtual void Clear();
//	virtual void SetSpeed(unsigned int speed);
//	
//	virtual Abstract_oString& operator << (void* any)
//	{
//		SetState(any);
//		return *this;
//	}
//	virtual operator bool() { return GetState(); }
//	virtual operator int() { return (GetState() == false) ? 0 : 1; };
//	virtual Abstract_oBit&  operator = (bool val) 
//	{
//		SetValue(val);
//		return *this;
//	} 
//	virtual Abstract_oBit& operator = (int val) 
//	{
//		SetValue((val==0)? false : true);
//		return *this;
//	}

//	virtual ~GPout() {}
//};
//															 
//															 
//const unsigned long led_mask[2] = {1UL << 0, 1UL << 1};      /*  GPIO P4.0, GPIO P4.1       */

//void LED_Off () {

//    PORT4->OMR = (led_mask[0] << 16);  //P4.0
//    PORT4->OMR = (led_mask[1] << 16);  //P4.1
//}

//void LED_Init (void)
//{
//  /* configure PORT P4 pin as output */
//  PORT4->IOCR0  &=  0xffffff00;          /* clear P4.0 settings           */
//  PORT4->IOCR0  |=  0x00000080;          /* P4.0 output push pull         */
//  PORT4->PDR0   &=  0xfffffff8;          /* clear P4.0 output settings    */
//  PORT4->PDR0   |=  2;				          /* P4.0 output strong            */

//  PORT4->IOCR0  &=  ~(0xFFUL << 8);          /* clear P4.1 settings           */
//  PORT4->IOCR0  |=   (0x80UL << 8);          /* P4.1 output push pull         */
//  PORT4->PDR0   &=  ~(0x07UL << 4);          /* clear P4.1 output settings    */
//  PORT4->PDR0   |=   (0x02UL << 4);          /* P4.1 output strong            */
//  LED_Off ();                               /* switch LEDs off               */
//}

//void LED_On () {

//    PORT4->OMR = led_mask[0] ;  //P4.0
//    PORT4->OMR = led_mask[1] ;  //P4.1

//}



