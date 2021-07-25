/*
 * File:   main.c
 * Author: talash.ganvir
 *
 * Created on 21 September, 2020, 3:31 PM
 */

#include"projectDefines.h"

/*void initializeInputs(void);
void initializeOutputs(void);
void initializeSystem(void);
void checkModbusPacket(void);
*/
void main(void)
{
    initializeSystem();
    //    while (1)
    //    {
    //        sendResponse("HELLO ", 6);
    //    }
    while (1)
    {
        if (gModbusHoldingRegisters[0] == 1 || gModbusHoldingRegisters[1] == 1 || gModbusHoldingRegisters[2] == 1 || gModbusHoldingRegisters[3] == 1)
        {
            BUZZER = 1;
        }
        else
        {
            BUZZER = 0;
        }
        checkModbusPacket();
    }
}

void initializeOutputs(void)
{
    TRISB0 = 0;
    TRISC4 = 0;
    LATC4 = 1;
    LATB0 = 0;
}

void initializeInputs(void)
{
    TRISC6 = 1;
    TRISC7 = 1;
}

void initializeSystem(void)
{
    initializeOutputs();
    initializeInputs();
    initializeTimer0();
    initializeUART();

    INTCONbits.INT0IE = 1;

    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;
    INTCONbits.GIE = 1;
    INTCONbits.GIEL = 1;
}

void checkModbusPacket(void)
{
    if (gflag4mSec == 1)
    {
        gflag4mSec = 0;
        getParsePacket();
        gcModbusPacketArrayIndex = 0;
        TMR0ON = 0;
    }
}