/* 
 * File:   ISR.h
 * Author: talash.ganvir
 *
 * Created on 12 January, 2020, 9:46 AM
 */

#ifndef ISR_H
#define	ISR_H

#include <xc.h>
#include"timer0.h"
#include"Modbus_Slave.h"

#define MODBUS_RECEIVED_PACKET_BYTE 32

extern unsigned short gcModbusPacketArrayIndex;
extern unsigned char gacModbusPacket[MODBUS_RECEIVED_PACKET_BYTE];
extern unsigned char gflag4mSec;

void __interrupt(high_priority)isr(void);

#endif	/* ISR_H */

