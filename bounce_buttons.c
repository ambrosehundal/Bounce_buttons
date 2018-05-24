// **** Include libraries here ****
// Standard libraries

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "leds.h"
#include "Buttons.h"

// **** Set macros and preprocessor directives ****

// **** Declare any datatypes here ****

// **** Define global, module-level, or external variables here ****
static uint8_t bEvent;
// **** Declare function prototypes ****

int main(void) {
    BOARD_Init();

    // Configure Timer 1 using PBCLK as input. This default period will make the LEDs blink at a
    // pretty reasonable rate to start.
    OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_8, 0xFFFF);

    // Set up the timer interrupt with a priority of 4.
    INTClearFlag(INT_T1);
    INTSetVectorPriority(INT_TIMER_1_VECTOR, INT_PRIORITY_LEVEL_4);
    INTSetVectorSubPriority(INT_TIMER_1_VECTOR, INT_SUB_PRIORITY_LEVEL_0);
    INTEnable(INT_T1, INT_ENABLED);

    /***************************************************************************************************
     * Your code goes in between this comment and the following one with asterisks.
     **************************************************************************************************/
    LEDS_INIT();
    ButtonsInit(); //initialize buttons library
    static uint8_t display;
    while (1) {
        bEvent = ButtonsCheckEvents();
        if (bEvent) {
            //check for button1
            if ((SW1 == 1) && (bEvent & BUTTON_EVENT_1UP) == BUTTON_EVENT_1UP) {
                display = bEvent;
            } else if ((SW1 == 0) && (bEvent & BUTTON_EVENT_1DOWN) == BUTTON_EVENT_1DOWN) {
                if ((LATE & 0x3) == 0x3) {
                    display &= (0xFC);
                } else {
                    display = bEvent;
                }
            }
            
            //check for button2
            if ((SW2 == 1) && (bEvent & BUTTON_EVENT_2UP) == BUTTON_EVENT_2UP) {
                display = bEvent;
            } else if ((SW2 == 0) && (bEvent & BUTTON_EVENT_2DOWN) == BUTTON_EVENT_2DOWN) {
                if ((LATE & 0xC) == 0xC) {
                    display &= (0xF3);
                } else {
                    display = bEvent;
                }
            }
            
            //check for button3
            if ((SW3 == 1) && (bEvent & BUTTON_EVENT_3UP) == BUTTON_EVENT_3UP) {
                display = bEvent;
            } else if ((SW3 == 0) && (bEvent & BUTTON_EVENT_3DOWN) == BUTTON_EVENT_3DOWN) {
                if ((LATE & 0x30) == 0x30) {
                    display &= (0xCF);
                } else {
                    display = bEvent;
                }
            }
            
            //check for button4
            if ((SW4 == 1) && (bEvent & BUTTON_EVENT_4UP) == BUTTON_EVENT_4UP) {
                display = bEvent;
            } else if ((SW4 == 0) && (bEvent & BUTTON_EVENT_4DOWN) == BUTTON_EVENT_4DOWN) {
                if ((LATE & 0xC0) == 0xC0) {
                    display = bEvent & (0x3F);
                } else {
                    display = bEvent;
                }
            }


            bEvent = BUTTON_EVENT_NONE;

        }
        LEDS_SET(display);
    }


    /***************************************************************************************************
     * Your code goes in between this comment and the preceding one with asterisks
     **************************************************************************************************/

    while (1);
}

/**
 * This is the interrupt for the Timer1 peripheral. It checks for button events and stores them in a
 * module-level variable.
 */
void __ISR(_TIMER_1_VECTOR, IPL4AUTO) Timer1Handler(void) {
    // Clear the interrupt flag.
    INTClearFlag(INT_T1);
    


}
