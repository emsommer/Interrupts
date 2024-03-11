#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
	
//UPDATE IN LAB
volatile uint32_t * KEYBase = (volatile uint32_t *) 0x00041060;
volatile uint32_t * TimerOne = (volatile uint32_t *) 0x00041020;
volatile uint32_t * TimerTwo = (volatile uint32_t *) 0x00041000;
volatile uint32_t * HEX0 = (volatile uint32_t * ) 0x00041080;
volatile uint32_t * HEX1 = (volatile uint32_t * ) 0x000410A0;
volatile uint32_t * HEX2 = (volatile uint32_t * ) 0x000410C0;
volatile uint32_t * HEX3 = (volatile uint32_t * ) 0x000410E0;
volatile uint32_t * HEX4 = (volatile uint32_t * ) 0x00041100;
volatile uint32_t * HEX5 = (volatile uint32_t * ) 0x00041120;
volatile uint8_t number = 0;
uint16_t timerLow2 = 0;
uint16_t timerHigh2 = 0;
uint32_t timerValue2 = 0;
uint32_t ms = 0;
int outputValue = 0;
int PrintSevenSegment_PIO(uint32_t counter);
uint32_t value(uint32_t counter);


static void handle_timer0_interrupts(void* context)
{
	outputValue++;
	PrintSevenSegment_PIO(outputValue);
	TimerOne[0] = 0x0;
return;
}

static void handle_button_interrupts(void* context)
{
	number++;
	// Clear the interrupt
	KEYBase[3]= 0xF;

	if(number == 1)
	{
		//reset period 
		TimerTwo[2] = 0xFFFFFFFF;
		TimerTwo[3] = 0xFFFFFFFF;

		//start timer 1 and timer 2 in continuous mode
		TimerOne[1] = 0x7;
		TimerTwo[1] = 0x6;
	}

	if(number == 2)
	{
		//stop both timers
		TimerOne[1] = 0x9;
		TimerTwo[1] = 0x8;

		//snapshot timer 2, calculate difference between start and stop in ms and print to hex
			
		//Request a snapshot (write garbage to snapl).
 		TimerTwo[4] = 0x4242;
 		TimerTwo[5] = 0x4242;
			
		//Read snapl and snaph and combine into 32 bit value.
  		timerLow2 = (uint16_t) TimerTwo[4];
  		timerHigh2 = (uint16_t) TimerTwo[5];
  		timerValue2 = (timerHigh2 << 16) | timerLow2;

		//calculate ms inbetween start and stop
		ms = (0xFFFFFFFF-timerValue2)/50000;

		//print ms 
		PrintSevenSegment_PIO(ms);
		//number  = 0;
	}

	return;
}



int main()
{
	number = 0;
	//clear time out bit
	TimerOne[0] = 0x0;
	TimerTwo[0] = 0x0;
	//stop timers
	TimerOne[1] = 0x9;
	TimerTwo[1] = 0x8;
	//reset period of timer two
	TimerTwo[2] = 0xFFFFFFFF;
	TimerTwo[3] = 0xFFFFFFFF;

	PrintSevenSegment_PIO(0);
	//enable key interrupts
	KEYBase[2] = 0xF;
	//enable timer interrupts
	//TimerOne[1] = 0x1;

	//check for interrupts
	alt_ic_isr_register(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ, handle_button_interrupts, NULL, 0x0);
	alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, handle_timer0_interrupts, NULL, 0x0);


	while(1);

	return 0;
}


int PrintSevenSegment_PIO(uint32_t counter)
{

  //Storage for each counter value
  uint32_t digits = 0;

  //Loop to collect each individual digit from the counter
  for(int i = 0 ; i < 6 ; i++)
    {
      //digit gathers the 6 individual hex digits to be printed to each hex display
      digits = (counter >> (i * 4)) & 0xF;

      //Send digit to HEX0
      if(0 == i)
        {
          *HEX0 = value(digits);
        }
      //Send digits to HEX1
      if(1 == i)
        {
          *HEX1 = value(digits);
        }
      //Send digits to HEX2
      if(2 == i)
        {
          *HEX2 = value(digits);
        }
      if(3 == i)
        {
          *HEX3 = value(digits);
        }
      if(4 == i)
        {
          *HEX4 = value(digits);
        }
      if(5 == i)
        {
          *HEX5 = value(digits);
        }
    }

  return 0;
}

//Method used to convert the decimal value to the hex value to be displayed by the sevenSegDisplays
uint32_t value(uint32_t counter) 
{ 
	uint32_t disp;
	if(counter == 0)
	{
		disp = 0x40;
	}
	
	if(counter == 1)
	{
		disp = 0x79;
	}
	
	if(counter == 2)
	{
		disp = 0x24;
	}
	
	if(counter == 3)
	{
		disp = 0x30;
	}
	
	if(counter == 4)
	{
		disp = 0x19;
	}
	
	if(counter == 5)
	{
		disp = 0x12;
	}
	
	if(counter == 6)
	{
		disp = 0x2;
	}
	
	if(counter == 7)
	{
		disp = 0x78;
	}
	
	if(counter == 8)
	{
		disp = 0x0;
	}
	
	if(counter == 9)
	{
		disp = 0x18;
	}
	
	if(counter == 10)
	{
		disp = 0x8;
	}
	
	if(counter == 11)
	{
		disp = 0x3;
	}
	
	if(counter == 12)
	{
		disp = 0x46;
	}
	
	if(counter == 13)
	{
		disp = 0x21;
	}
	
	if(counter == 14)
	{
		disp = 0x6;
	}
	
	if(counter == 15)
	{
		disp = 0xE;
	}
	
	return disp;
}

