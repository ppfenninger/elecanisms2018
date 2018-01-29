/*
** Copyright (c) 2018, Bradley A. Minch
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met: 
** 
**     1. Redistributions of source code must retain the above copyright 
**        notice, this list of conditions and the following disclaimer. 
**     2. Redistributions in binary form must reproduce the above copyright 
**        notice, this list of conditions and the following disclaimer in the 
**        documentation and/or other materials provided with the distribution. 
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
** AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
** ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
** LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
** CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
** SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
** INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
** CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
** POSSIBILITY OF SUCH DAMAGE.
*/
#include "elecanisms.h"

int16_t main(void) {
    init_elecanisms();

    T1CON = 0x0030;         // set Timer1 period to 0.5s
    PR1 = 0x7A11;

    TMR1 = 0;               // set Timer1 count to 0
    IFS0bits.T1IF = 0;      // lower Timer1 interrupt flag
    T1CONbits.TON = 1;      // turn on Timer1

    //Timer 2 to account for the button debouncing
    T2CON = 0X0030;         // set Timer2 period of 0.5 seconds
    PR2 = 0x7A11;
    TMR2 = 0;               // set initial timer count to 0
    IFS0bits.T2IF = 0;      // lower Timer2 interrupt flag
    T2CONbits.TON = 1;      // turn on Timer2

    LED2 = ON;
    int mode = 2;
    int hasbeenup = 1;

    while (1) {
        if (D0 == 1 && IFS0bits.T2IF == 0  && hasbeenup == 1){ // button changes which LED is blinking - and which two are controlled by the switches
            IFS0bits.T1IF == 0;
            hasbeenup = 0; 
            if (mode == 3){
                mode = 1;
                LED1 = ON; //turns on LED 1
            }
            else if (mode == 2){
                mode = 3;
                LED3 = ON; //turns on LED 3
            }

            else {
                mode = 2;
                LED2 = ON; //turns on LED 2
            }
        }   

        if (D0 == 0 && IFS0bits.T2IF == 1){
            hasbeenup = 1;
            IFS0bits.T2IF = 0;
        }

        if (mode == 2){
            if (IFS0bits.T1IF == 1) {
                IFS0bits.T1IF = 0;      // lower Timer1 interrupt flag
                LED2 = !LED2;           // toggle LED2
            }
            LED1 = (SW2 == 0) ? ON : OFF;   // turn LED1 on if SW2 is pressed 
            LED3 = (SW3 == 0) ? ON : OFF;   // turn LED3 on if SW3 is pressed
        }
        else if (mode == 1){
            if (IFS0bits.T1IF == 1) {
                IFS0bits.T1IF = 0;      // lower Timer1 interrupt flag
                LED1 = !LED1;           // toggle LED2
            }
            LED3 = (SW2 == 0) ? ON : OFF;   // turn LED3 on if SW2 is pressed 
            LED2 = (SW3 == 0) ? ON : OFF;   // turn LED2 on if SW3 is pressed
        }
        else {
             if (IFS0bits.T1IF == 1) {
                IFS0bits.T1IF = 0;      // lower Timer1 interrupt flag
                LED3 = !LED3;           // toggle LED2
            }
            LED2 = (SW2 == 0) ? ON : OFF;   // turn LED2 on if SW2 is pressed 
            LED1 = (SW3 == 0) ? ON : OFF;   // turn LED1 on if SW3 is pressed
        }

        
    }
}

