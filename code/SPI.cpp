#include <SPI.h>
#include <GPIO.h>



void SPIini()
{
	Abstract_iBit* MISO = new GPin (GPP2, 2);
	SCU_CLK->CGATCLR0 = 1 << 11; //disable USIC0 clock gating;
	
	USIC_CH_TypeDef* u01 = USIC0_CH1;
	u01->KSCFG = 3; // Module enable & bit protection
	u01->CCR &= 0xFFFFFFFF00;
	
}
