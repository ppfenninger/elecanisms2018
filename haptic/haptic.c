#include "elecanisms.h"
// #include <stdio.h>
// #define SET_DUTY_VAL        7
// #define GET_DUTY_VAL        8
// #define GET_DUTY_MAX        9


int16_t main(void) {
    uint8_t *RPOR, *RPINR;

    init_elecanisms();

    D8_DIR = OUT;      // configure D8 to be a digital output (IN1)
    D8 = 0;            // set D8 low (IN1)

    D7_DIR = OUT;      // configure D7 to be a digital output (IN2)
    D7 = 0;				// set D8 low (IN1)


    RPOR = (uint8_t *)&RPOR0;		//no idea what these do
    RPINR = (uint8_t *)&RPINR0;

    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR[D8_RP] = OC1_RP;  // connect the OC1 module output to pin D8
    __builtin_write_OSCCONL(OSCCON | 0x40);

    OC1CON1 = 0x1C06;   // configure OC1 module to use the peripheral 
                        //   clock (i.e., FCY, OCTSEL<2:0> = 0b111) and 
                        //   and to operate in edge-aligned PWM mode
                        //   (OCM<2:0> = 0b110)
    OC1CON2 = 0x001F;   // configure OC1 module to syncrhonize to itself
                        //   (i.e., OCTRIG = 0 and SYNCSEL<4:0> = 0b11111)

    OC1RS = (uint16_t)(FCY / 1e4 - 1.);     // configure period register to 
                                            //   get a frequency of 1kHz
    OC1R = OC1RS;  // configure duty cycle to 25% (i.e., period / 4) - controls the duty cycle, change this variable to change how fast the motor moves
    OC1TMR = 0;         // set OC1 timer count to 0

    // }
    while (1) {
        if (SW1 == 0) {
            OC1R = OC1RS / 4; 
        }
        else {
            OC1R = 2*(OC1RS) / 4 ;
        }

    }
}

