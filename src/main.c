/*
     program to control a 7-segment display using a push button
     requirements: 
     - the switch is connected to pin 4 in PORTD
     - the 7-segment is connected to the first 4 pins of PORTC
     condition: 
     if the switch is pressed just increase the number appeared in the 7-segment display 
     and if the maximum number is reached, overflow occurs

*/ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
  uint8_t number=0;
  DDRD &= ~(1<<PD4); // configure pin 4 of PORTD as input pin
  DDRC |= 0x0F;     // configure the first 4 pins of port c as output pins

  // initialize the seven segment display 
  // PORTC &= ~(0x0F<<PC0);
  PORTC &= ~((1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3));


   for(;;)
   {
     // check if the button is pressed
     if(PIND & (1<<PD4))
     {
       _delay_ms(30); // debounce effect
       if(PIND & (1<<PD4)){

         if((PORTC & 0x0F)==9)
         {
         // if overflows occurs
           number=0;
           PORTC = (PORTC & 0xF0) | (number & 0x0F);
				}
				else
				{
					// increment 7-segment every press
					number++;
					PORTC = (PORTC & 0xF0) | (number & 0x0F);
				}      
       }
      		while(PIND & (1<<PD4)){} // wait until the switch is released
     }
   }
}
