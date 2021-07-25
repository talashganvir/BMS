/* 
 * File:   Modbus_Slave.h
 * Author: talash.ganvir
 *
 * Created on 12 October, 2019, 3:04 PM
 */

#ifndef MODBUS_SLAVE_H
#define	MODBUS_SLAVE_H


#include <xc.h>

#include"uart.h"
#include"isr.h"

#define SLAVE_ID  27        // TODO: CONVERT TO #DEFINE

#define INDEX_ID 0
#define INDEX_FC 1

#define MODBUS_INVALID_FC -1
#define MODBUS_INVALID_ID -2
#define MODBUS_CRC_ERROR -3
#define MODBUS_TOTAL_RECEIVE_BYTES 240

//Defines for all function code for the project
#define MODBUS_FC_READ_INPUT_REGS  4  // TODO: MODBUS_FC_READ_INPUT_REG
#define MODBUS_FC_WRITE_MULT_HOLD_REG 16
#define MODBUS_FC_WRITE_SINGLE_HOLD_REG 6
#define MODBUS_FC_READ_HOLD_REGS 3

// Defines for total number of registers for this project
#define MODBUS_TOTAL_HOLDING_REGISTERS 4
#define MODBUS_TOTAL_INPUT_REGISTERS 20


// Defines for Read Input Registers
#define MODBUS_RIR_INDEX_START_ADDRESS_HI  2 // TODO: MODBUS_RIR_INDEX_START_ADDRESS_HI
#define MODBUS_RIR_INDEX_START_ADDRESS_LO  3
#define MODBUS_RIR_INDEX_QTY_REG_HI        4
#define MODBUS_RIR_INDEX_QTY_REG_LO        5

// Defines for Writing Multiple Holding Registers
#define MODBUS_WMHR_START_ADDRESS_HI       2
#define MODBUS_WMHR_START_ADDRESS_LO       3
#define MODBUS_WMHR_QTY_REG_HI             4
#define MODBUS_WMHR_QTY_REG_LO             5
#define MODBUS_WMHR_BYTE_COUNT             6


// Defines for Writing Single Holding Registers
#define MODBUS_WSHR_START_ADDRESS_HI       2
#define MODBUS_WSHR_START_ADDRESS_LO       3
#define MODBUS_WSHR_REG_VAL_HI             4
#define MODBUS_WSHR_REG_VAL_LO             5
#define MODBUS_WSHR_BYTE_COUNT             6


// Defines for Read Holding Registers
#define MODBUS_RHR_INDEX_NO_REG_ADDRESS_HI     4
#define MODBUS_RHR_INDEX_NO_REG_ADDRESS_LO     5
#define MODBUS_RHR_INDEX_START_ADDRESS_HI      2
#define MODBUS_RHR_INDEX_START_ADDRESS_LO      3

extern unsigned short gModbusHoldingRegisters[MODBUS_TOTAL_HOLDING_REGISTERS];
extern unsigned short gModbusInputRegisters[MODBUS_TOTAL_INPUT_REGISTERS]; //TODO: USE extern

unsigned short getCRC16(unsigned char *puchMsg, unsigned int usDataLen); //getgetCRC16
void modbusWriteMultipleRegisters(void);
void modbusReadHoldingRegisters(void);
void modbusWriteSingleRegister(void);
void modbusReadInputRegisters(void);
char getParsePacket(void);



#endif	/* MODBUS_SLAVE_H */

