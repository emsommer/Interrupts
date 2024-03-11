#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

volatile uint32_t* LEDRBase = (volatile uint32_t*) 0x00041040;
volatile uint32_t * TimerOne = (volatile uint32_t *) 0x00041020;
static void handle_timer0_interrupts(void* context);
int main()
{
	TimerOne[1] = 0x7;
	alt_ic_isr_register(TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID, TIMER_0_IRQ, handle_timer0_interrupts, NULL, 0x0);

	//LEDRBase[0] = 0x3FF;

	while(1);

	return 0;
}

static void handle_timer0_interrupts(void* context)
{
	// Clear the interrupt
	TimerOne[0]= 0x0;

	  if(LEDRBase[0] == 0x0)
	  {
		  LEDRBase[0] = 0x3ff;
	  }
	  else
	  {
		  LEDRBase[0] = 0x0;
	  }

	return;
}


