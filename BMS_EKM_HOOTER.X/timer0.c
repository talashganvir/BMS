#include"timer0.h"

void initializeTimer0(void)
{
    INTCONbits.TMR0IE = 1;
    T0CONbits.T08BIT = 0; // 16 Bit timer
    T0CONbits.T0CS = 0; // Internal clock
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 6;
    //    T0CONbits.TMR0ON = 1; // Turn Timer0 on.
    TMR0 = 0xFFFF - FOUR_MSEC_COUNT;
}
