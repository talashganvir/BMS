#include "isr.h"

unsigned short gcModbusPacketArrayIndex = 0;
unsigned char gacModbusPacket[MODBUS_RECEIVED_PACKET_BYTE];
unsigned char gflag4mSec = 0;

void __interrupt(high_priority)isr(void)
{
    if (RCIE == 1 && PIR1bits.RCIF == 1) //The EUSART receive buffer, RCREG1, is full (cleared when RCREG1 is read)
    {
        TMR0ON = 1;
        TMR0IE = 1;
        INTCONbits.TMR0IF = 0;
        TMR0 = 0xFFFF - FOUR_MSEC_COUNT;
        gacModbusPacket[ gcModbusPacketArrayIndex++] = RCREG;
//                TXREG = RCREG;
//                while (TXSTAbits.TRMT == 0);
        PIR1bits.RCIF = 0;
    }
    if (INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1)
    {
        gflag4mSec = 1;
        INTCONbits.TMR0IF = 0;
    }
}

