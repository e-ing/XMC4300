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

const unsigned long led_mask[2] = {1UL << 0, 1UL << 1};      /*  GPIO P4.0, GPIO P4.1       */

void LED_Init(void);
void LED_On  (void);
void LED_Off (void);


volatile uint32_t msTicks;                      /* counts 1ms timeTicks       */

void SysTick_Handler(void) {
  msTicks++;
}

void Delay (uint32_t dlyTicks) {
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) { __NOP(); }
}

int main (void) {

  SystemCoreClockUpdate();                      /* update SystemCoreClock     */
  if (SysTick_Config(SystemCoreClock / 1000)) { /* SysTick 1 msec interrupts  */
    while (1) __NOP();                          /* Capture error              */
  }

  LED_Init();

  while(1) {                                 /* Loop forever      */

    LED_On ();                               /* Turn on LED'         */
    Delay(500);                              /* Delay 500ms       */
    LED_Off();                               /* Turn off LED '       */
    Delay(500);                              /* Delay 500ms       */

  }

}

/*----------------------------------------------------------------------------
  initialize LED Pins
 *----------------------------------------------------------------------------*/
void LED_Init (void) {

  /* configure PORT P4 pin as output */
  PORT4->IOCR0  &=  ~(0xFFUL << 0);          /* clear P4.0 settings           */
  PORT4->IOCR0  |=   (0x80UL << 0);          /* P4.0 output push pull         */
  PORT4->PDR0   &=  ~(0x07UL << 0);          /* clear P4.0 output settings    */
  PORT4->PDR0   |=   (0x02UL << 0);          /* P4.0 output strong            */

  PORT4->IOCR0  &=  ~(0xFFUL << 8);          /* clear P4.1 settings           */
  PORT4->IOCR0  |=   (0x80UL << 8);          /* P4.1 output push pull         */
  PORT4->PDR0   &=  ~(0x07UL << 4);          /* clear P4.1 output settings    */
  PORT4->PDR0   |=   (0x02UL << 4);          /* P4.1 output strong            */

  LED_Off ();                               /* switch LEDs off               */

}


/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On () {

    PORT4->OMR = led_mask[0] ;  //P4.0
    PORT4->OMR = led_mask[1] ;  //P4.1

}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off () {

    PORT4->OMR = (led_mask[0] << 16);  //P4.0
    PORT4->OMR = (led_mask[1] << 16);  //P4.1


}


