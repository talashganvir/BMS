#include"uart.h"

/**
 * This function used for initialize of UART.
 */
    void initializeUART(void)
{
    TXSTA = 0x00; // 8-Bit TRASNMISSION, ASYNCHRNOUS MODE  AND LOW BAUD RATE 
    RCSTA = 0x00;
    
    TXSTAbits.TXEN = 1; // TRANSMIT ENABLE 
    RCSTAbits.CREN = 1;
    RCSTA1bits.SPEN = 1; // SREIAL PORT ENABLE
    
    SPBRG = 25;
}

/**
 * This function used for sending response to the user via modbus poll software.
 * @param txData this is the char data address or msg address is to be send. 
 * @param length this is length of of message to be send.
 */
void sendResponse(unsigned char *txData, int length)
{
    // USE YOUR MCU SERIAL TRANSMIT FUNCTION
    int iIndex;
    for (iIndex = 0; iIndex < length; iIndex++)
    {
        TXREG = txData[iIndex];
        while (TXSTAbits.TRMT == 0);
    }
}

void myUARTEnableTransmit(unsigned char status)
{
    if (status == 1)
    {
        LATC = 1;
    }
    else
    {
        LATC = 0;
    }
}