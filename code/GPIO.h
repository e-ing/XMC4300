#ifndef GPIO_H
#define GPIO_H

#include <Bits.h>
#include <AbstractIfcs.h>
#include <XMC4300.h>

//Everything you need to work with a general purpose output port XMC4300
// GPIO.h v0-09.04.21

//#pragma pack(push, 1)
struct PortGPIO
{
	unsigned long  OUT;                               // (@ 0xBASEX000) Port Output Register                  
  unsigned long  OMR;                               // (@ 0xBASEX004) Port Output Modification Register
  unsigned long  RESERVED[2];
  unsigned long  IOCR[4]; 
//  unsigned long  IOCR0; 															// (@ 0xBASEX010) Port Input/Output Control Register 0
//  unsigned long  IOCR4;                             // (@ 0xBASEX014) Port Input/Output Control Register 4
//  unsigned long  IOCR8;                             // (@ 0xBASEX018) Port Input/Output Control Register 8 
//  unsigned long  IOCR12;                            // (@ 0xBASEX01C) Port Input/Output Control Register 12 
  unsigned long  RESERVED1;
  unsigned long  IN;                                // (@ 0xBASEX024) Port Input Register 
  unsigned long  RESERVED2[6];
  unsigned long  PDR0;                              // (@ 0xBASEX040) Port  Pad Driver Mode 0 Register  
  unsigned long  PDR1;                              // (@ 0xBASEX044) Port  Pad Driver Mode 1 Register 
  unsigned long  RESERVED3[6];
  unsigned long  PDISC;                             // (@ 0xBASEX060) Port  Pin Function Decision Control Register 
  unsigned long  RESERVED4[3];
  unsigned long  PPS;                               // (@ 0xBASEX070) Port  Pin Power Save Register 
  unsigned long  HWSEL;                             // (@ 0xBASEX074) Port  Pin Hardware Select Register
};
//#pragma pack(pop)

enum GPPORRTs
{
	GPP0,
	GPP1,
	GPP2,
	GPP3,
	GPP4,
	GPP5,
	GPP14,
	GPP15,
	GPPNUM
};



extern volatile PortGPIO* GPIOs [GPPNUM];// = {(PortGPIO*) PORT0_BASE, (PortGPIO*) PORT1_BASE, (PortGPIO*) PORT2_BASE, (PortGPIO*) PORT3_BASE,
															 //(PortGPIO*) PORT4_BASE, (PortGPIO*) PORT5_BASE, (PortGPIO*) PORT14_BASE, (PortGPIO*) PORT15_BASE};

class GPin : public Abstract_iBit
{
protected:
	volatile PortGPIO* port;
	unsigned char pin;
	unsigned long pinMaskIn;
	virtual bool GetState();
	virtual void ResetPin();
public:
	GPin(GPPORRTs portNum, unsigned char pinNum);
	virtual void PullH();
	virtual void PullD();
	virtual void PushPull();
	virtual void SetSpeed(unsigned int speed);
	virtual ~GPin() {}
};


class GPOut : public   Abstract_oBit
{
protected:
	volatile PortGPIO* port;
	unsigned char pin;
	unsigned long pinMaskOn;
	unsigned long pinMaskOff;
	unsigned long pinMaskTogg;

	virtual bool GetState();
	virtual void SetValue( bool x);
	virtual void Toggle ();
public:
	GPOut(GPPORRTs portNum, unsigned char pinNum);
	virtual void Set();
	virtual void Clear();
	virtual void SetSpeed(unsigned int speed);	
	virtual ~GPOut() {}
};
															 
															 
//const unsigned long led_mask[2] = {1UL << 0, 1UL << 1};      /*  GPIO P4.0, GPIO P4.1       */

//void LED_Off ();
//void LED_Init (void);

//void LED_On () ;
#endif





