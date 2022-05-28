/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

void App_TimerCallback(TC_TIMER_STATUS status, uintptr_t context);

static bool TimerElapsed;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    TimerElapsed = false;
    TC0_TimerCallbackRegister(App_TimerCallback, 0);
    TC0_TimerStart();
    //TC0_TimerCommandSet(TC_COMMAND_START_RETRIGGER);

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );

        if (TimerElapsed == true)
        {
            TimerElapsed = false;
            LED_Toggle();
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void App_TimerCallback(TC_TIMER_STATUS status, uintptr_t context)
{
    TimerElapsed = true;
}


/*******************************************************************************
 End of File
*/

