/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\
| * Name: IrqExample.c                                            |
| * Author: Kit Cischke                                           |
| * Purpose: A simple framework for setting up interrupts on the  |
| * Nios II processor using the Nios SBT.                         |
| * You must:                                                     |
| * 1. Update the addresses for                                   |
| * 2. Replace the "XXX_IRQ" and "XXX_IRQ_INTERRUPT_CONTROLLER_ID"|
| *    values based on your own system.h file.                    |
| * Version 1.0                                                   |
| * Created on: Jul 22, 2021                                      |
\*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/* A variable to hold the value of the button pio edge capture register. */
volatile uint32_t* LEDRBase = (volatile uint32_t*) 0x00041040;
volatile uint32_t* SWBase = (volatile uint32_t*) 0x00041070;
volatile uint32_t* KEYBase = (volatile uint32_t*) 0x00041060;

static void handle_button_interrupts(void* context)
{
	// Clear the interrupt
	KEYBase[3]= 0xF;
	volatile uint32_t switchValues;
	switchValues = SWBase[0];
	LEDRBase[0] = switchValues;

	return;
}


int main()
{
	alt_ic_isr_register(KEY_IRQ_INTERRUPT_CONTROLLER_ID, KEY_IRQ, handle_button_interrupts, NULL, 0x0);

	KEYBase[2] = 0xF;

	LEDRBase[1] = 0x3FF;

	while(1);

	return 0;
}
