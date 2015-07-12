/*
 * main.c
 */

// Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "interrupt.h"
#include "rom_map.h"
#include "prcm.h"
#include "utils.h"

// Common interface includes
#include "uart_if.h"
#include "display.h"

#include "pin_mux_config.h"


//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif



static void BoardInit(void)
{
/* In case of TI-RTOS vector table is initialize by OS itself */
#ifndef USE_TIRTOS
    //
    // Set vector table base
    //
	#if defined(ccs) || defined(gcc)
		MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
	#endif
	#if defined(ewarm)
		MAP_IntVTableBaseSet((unsigned long)&__vector_table);
	#endif

#endif

    //
    // Enable Processor
    //
    MAP_IntMasterEnable();
    MAP_IntEnable(FAULT_SYSTICK);

    PRCMCC3200MCUInit();
}


int main(void) {
	
	BoardInit();
    PinMuxConfig();

    InitTerm();
	ClearTerm();

	InitDisplay();

    while (1) {
    	MAP_UtilsDelay(10000);
    }
}
