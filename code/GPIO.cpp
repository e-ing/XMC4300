#include <GPIO.h>

//Everything you need to work with a general purpose in & output port XMC4300
// GPIO.cpp v0-09.04.21


volatile  PortGPIO* GPIOs [] = {(volatile PortGPIO*) PORT0_BASE, (volatile  PortGPIO*) PORT1_BASE, (volatile  PortGPIO*) PORT2_BASE, (volatile  PortGPIO*) PORT3_BASE,
															 (volatile  PortGPIO*) PORT4_BASE, (volatile  PortGPIO*) PORT5_BASE, (volatile PortGPIO*) PORT14_BASE, (volatile  PortGPIO*) PORT15_BASE};

void GPin::ResetPin()
{
	port->IOCR[pin >> 2] &= ~(0xf8 << (8 * (pin & 3)));
}	
															 
bool GPin::GetState()
{
	return port->IN & pinMaskIn;
}

GPin::GPin(GPPORRTs portNum, unsigned char pinNum) :
port(GPIOs[portNum]), pin(pinNum)
{
	pinMaskIn = 1 << pin;
	ResetPin();
}

void GPin::PullH()
{
	ResetPin();
	port->IOCR[pin >> 2] |= 0x10 << (8 * (pin & 3));	
}

void GPin::PullD()
{
	ResetPin();
	port->IOCR[pin >> 2] |= 8 << (8 * (pin & 3));
}	

void GPin::PushPull()
{
	ResetPin();
}

void GPin::SetSpeed(unsigned int speed)
{
	//I'll think about it later
}
															 																													 
bool GPout::GetState()
{
	return ((port->IN & pinMaskOn) == 0)? false : true;
}

void GPout::SetValue( bool x)
{
	port->OMR = (x == false)? pinMaskOff : pinMaskOn;
}
void GPout::Toggle ()
{
	port->OMR = pinMaskTogg;
}

GPout::GPout(GPPORRTs portNum, unsigned char pinNum) : 
port(GPIOs[portNum]), pin(pinNum)
{
	pinMaskOn = 1 << pin;
	pinMaskOff = 1 << (pin+16);
	pinMaskTogg = pinMaskOn | pinMaskOff;
	port->IOCR[pin >> 2] &= ~(0xf8 << (8 * (pin & 3)));
	port->IOCR[pin >> 2] |= 0x80 << (8 * (pin & 3));
}

void GPout::Set()
{
	port->OMR = pinMaskOn;
}

void GPout::Clear()
{
	port->OMR = pinMaskOff;
}

void GPout::SetSpeed(unsigned int speed)
{
	//I'll think about it later
}	

void GPout::SetPushPull()
{
	port->IOCR[pin >> 2] &= ~(0x40 << (8 * (pin & 3)));
}

void GPout::SetOpenDr()
{
	port->IOCR[pin >> 2] |= (0x40 << (8 * (pin & 3)));
}

void GPout::SetAltFn(unsigned  long funcN)
{
	port->IOCR[pin >> 2] |= (funcN << (8 * (pin & 3)));
}







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

//void LED_On () 
//{
//    PORT4->OMR = led_mask[0] ;  //P4.0
//    PORT4->OMR = led_mask[1] ;  //P4.1

//}
