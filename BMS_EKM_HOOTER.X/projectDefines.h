/* 
 * File:   projectDefines.h
 * Author: talash.ganvir
 *
 * Created on 21 September, 2020, 3:43 PM
 */

#ifndef PROJECTDEFINES_H
#define	PROJECTDEFINES_H

// 'C' source line config statements

// CONFIG1H
#pragma config OSC = HS         // Oscillator Selection bits (HS oscillator)
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))
#pragma config LVP = OFF 

#include <xc.h>
#include "timer0.h"
#include "uart.h"
#include"isr.h"
#include"Modbus_Slave.h"

#define BUZZER LATB0 
#define TX_EN LATC5

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PROJECTDEFINES_H */

