#include <GPOut.h>

//Everything you need to work with a general purpose output port XMC4300
// GPOut.cpp v0-08.04.21


//GPout and etc

volatile  PortGPIO* GPIOs [] = {(volatile PortGPIO*) PORT0_BASE, (volatile  PortGPIO*) PORT1_BASE, (volatile  PortGPIO*) PORT2_BASE, (volatile  PortGPIO*) PORT3_BASE,
															 (volatile  PortGPIO*) PORT4_BASE, (volatile  PortGPIO*) PORT5_BASE, (volatile PortGPIO*) PORT14_BASE, (volatile  PortGPIO*) PORT15_BASE};

bool GPOut::GetState()
{
	return ((port->IN & pinMaskOn) == 0)? false : true;
}
void GPOut::SetValue( bool x)
{
	port->OMR = (x == false)? pinMaskOff : pinMaskOn;
}
void GPOut::Toggle ()
{
	port->OMR = pinMaskTogg;
}

GPOut::GPOut(unsigned char portNum, unsigned char pinNum) : 
port(GPIOs[portNum]), pin(pinNum)
{
	pinMaskOn = 1 << pin;
	pinMaskOff = 1 <<(pin+16);
	pinMaskTogg = pinMaskOn | pinMaskOff;
}

void GPOut::Set()
{
	port->OMR = pinMaskOn;
}

void GPOut::Clear()
{
	port->OMR = pinMaskOff;
}

void GPOut::SetSpeed(unsigned int speed)
{
}	


void LED_Off () {

    PORT4->OMR = (led_mask[0] << 16);  //P4.0
    PORT4->OMR = (led_mask[1] << 16);  //P4.1
}

void LED_Init (void)
{
  /* configure PORT P4 pin as output */
  PORT4->IOCR0  &=  0xffffff00;          /* clear P4.0 settings           */
  PORT4->IOCR0  |=  0x00000080;          /* P4.0 output push pull         */
  PORT4->PDR0   &=  0xfffffff8;          /* clear P4.0 output settings    */
  PORT4->PDR0   |=  2;				          /* P4.0 output strong            */

  PORT4->IOCR0  &=  ~(0xFFUL << 8);          /* clear P4.1 settings           */
  PORT4->IOCR0  |=   (0x80UL << 8);          /* P4.1 output push pull         */
  PORT4->PDR0   &=  ~(0x07UL << 4);          /* clear P4.1 output settings    */
  PORT4->PDR0   |=   (0x02UL << 4);          /* P4.1 output strong            */
  LED_Off ();                               /* switch LEDs off               */
}

void LED_On () 
{

    PORT4->OMR = led_mask[0] ;  //P4.0
    PORT4->OMR = led_mask[1] ;  //P4.1

}
