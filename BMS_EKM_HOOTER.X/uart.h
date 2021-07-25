/* 
 * File:   UART.h
 * Author: talash.ganvir
 *
 * Created on 6 October, 2019, 9:30 AM
 */

#ifndef UART_H
#define	UART_H

#include<xc.h>
#include"Modbus_Slave.h"
#include"projectDefines.h"

#define BAUD_RATE_9600 12

void initializeUART(void);
void sendResponse(unsigned char *txData, int length);
void myUARTEnableTransmit(unsigned char status);
#define UART_RE LATG1
#define UART_DE LATG2

#endif	/* UART_H */

