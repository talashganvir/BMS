#include"Modbus_Slave.h"

unsigned short gModbusHoldingRegisters[MODBUS_TOTAL_HOLDING_REGISTERS];
unsigned short gModbusInputRegisters[MODBUS_TOTAL_INPUT_REGISTERS];

static unsigned char auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
};
/* Table of CRC values for low?order byte */
static unsigned char auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

/**
 * This function check the slaveID, FunctionCode and CRC for the validating MODBUS packet. 
 * @return Return 0 is validating packet is okay otherwise it has error.
 */
char getParsePacket(void)
{
    unsigned int checkCRC;
    unsigned char CRCHi;
    unsigned char CRCLo;

    checkCRC = getCRC16(gacModbusPacket, gcModbusPacketArrayIndex - 2);
    CRCLo = checkCRC;
    CRCHi = checkCRC >> 8;

    if ((CRCLo == gacModbusPacket[gcModbusPacketArrayIndex - 2]) &&
            (CRCHi == gacModbusPacket[gcModbusPacketArrayIndex - 1]))
    {
        if (gacModbusPacket[INDEX_ID] == SLAVE_ID)
        {
            switch (gacModbusPacket[INDEX_FC])
            {
            case MODBUS_FC_READ_INPUT_REGS:
                modbusReadInputRegisters();
                break;
            case MODBUS_FC_READ_HOLD_REGS:
                modbusReadHoldingRegisters();
                break;
            case MODBUS_FC_WRITE_SINGLE_HOLD_REG:
                modbusWriteSingleRegister();
                break;
            case MODBUS_FC_WRITE_MULT_HOLD_REG:
                modbusWriteMultipleRegisters();
                break;
            default:
                return MODBUS_INVALID_FC;
            }
            return gacModbusPacket[INDEX_FC];
        }
        else
        {
            return MODBUS_INVALID_ID;
        }
    }
    else
    {
        return MODBUS_CRC_ERROR;
    }
}

/**
 * This function check the receive and send packet using CRC method. 
 * @param puchMsg 8bit message that is Receive or send.
 * @param usDataLen it is length of that message.
 * @return it return 16 bit CRC code.
 */
unsigned short getCRC16(unsigned char *puchMsg, unsigned int usDataLen) /* The function returns the CRC as a unsigned short type */
{
    unsigned char uchCRCHi = 0xFF; /* high byte of CRC initialized */
    unsigned char uchCRCLo = 0xFF; /* low byte of CRC initialized */
    unsigned uIndex; /* will index into CRC lookup table */
    while (usDataLen--) /* pass through message buffer */
    {
        uIndex = uchCRCLo ^ *puchMsg++; /* calculate the CRC */
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex];
    }
    return (uchCRCHi << 8 | uchCRCLo);
}

/**
 * This function code is used to read from 1 to 125 contiguous input registers in a remote device.
 * The register data in the response message are packed as two bytes per register.
 * For each register, the first byte contains the high order bits and the second contains the low order bits.
 */
void modbusReadInputRegisters(void)
{
    unsigned short iStartAddress = 0;
    unsigned char iResponsePacket[50];
    unsigned short iQtyRegister = 0;
    unsigned char iResponseIndex = 0;
    unsigned short checkCRC = 0;
    unsigned int iIndex = 0;

    iStartAddress = (gacModbusPacket[MODBUS_RIR_INDEX_START_ADDRESS_HI] << 8) | gacModbusPacket[MODBUS_RIR_INDEX_START_ADDRESS_LO];
    iQtyRegister = (gacModbusPacket[MODBUS_RIR_INDEX_QTY_REG_HI] << 8) | gacModbusPacket[MODBUS_RIR_INDEX_QTY_REG_LO];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_ID];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_FC];
    iResponsePacket[iResponseIndex++] = iQtyRegister * 2;

    for (iIndex = iStartAddress; iIndex < (iQtyRegister + iStartAddress); iIndex++)
    {
        iResponsePacket[iResponseIndex++] = (gModbusInputRegisters[iIndex] >> 8);
        iResponsePacket[iResponseIndex++] = gModbusInputRegisters[iIndex] & 0xFF;
    }

    checkCRC = getCRC16(iResponsePacket, iResponseIndex);
    iResponsePacket[iResponseIndex++] = checkCRC;
    iResponsePacket[iResponseIndex++] = checkCRC >> 8;

    sendResponse(iResponsePacket, iResponseIndex);
}

/**
 * This function code is used to read the contents of a contiguous block of holding registers in a remote device.
 * The register data in the response message are packed as two bytes per register, with the binary contents right justified within each byte.
 */
void modbusReadHoldingRegisters(void)
{
    unsigned short iStartAddress = 0;
    unsigned char iResponsePacket[150];
    unsigned short iQtyRegister = 0;
    unsigned char iResponseIndex = 0;
    unsigned short checkCRC = 0;
    unsigned int iIndex = 0;

    iQtyRegister = (gacModbusPacket[MODBUS_RHR_INDEX_NO_REG_ADDRESS_HI] << 8) | gacModbusPacket[MODBUS_RHR_INDEX_NO_REG_ADDRESS_LO];
    iStartAddress = (gacModbusPacket[MODBUS_RHR_INDEX_START_ADDRESS_HI] << 8) | gacModbusPacket[MODBUS_RHR_INDEX_START_ADDRESS_LO];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_ID];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_FC];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_RHR_INDEX_NO_REG_ADDRESS_LO]*2;

    for (iIndex = iStartAddress; iIndex < iQtyRegister + iStartAddress; iIndex++)
    {

        iResponsePacket[iResponseIndex++] = (gModbusHoldingRegisters[iIndex] >> 8);
        iResponsePacket[iResponseIndex++] = gModbusHoldingRegisters[iIndex] & 0xFF;
    }

    checkCRC = getCRC16(iResponsePacket, iResponseIndex);
    iResponsePacket[iResponseIndex++] = checkCRC;
    iResponsePacket[iResponseIndex++] = checkCRC >> 8;
    sendResponse(iResponsePacket, iResponseIndex);

}

/**
 * This function code is used to write a block of contiguous registers (1 to 123 registers) in a
remote device.
 * The requested written values are specified in the request data field. Data is packed as two
bytes per register.
 * The normal response returns the function code, starting address, and quantity of registers
written.
 */
void modbusWriteMultipleRegisters(void)
{
    unsigned short iStartAddress = 0;
    unsigned char iResponsePacket[20];
    unsigned char iResponseIndex = 0;
    unsigned short checkCRC = 0;
    int iIndex = MODBUS_WMHR_BYTE_COUNT + 1;
    int iHoldingRegistersIndex;

    iStartAddress = (gacModbusPacket[MODBUS_WMHR_START_ADDRESS_HI] << 8) | gacModbusPacket[MODBUS_WMHR_START_ADDRESS_LO];

    for (iHoldingRegistersIndex = iStartAddress; iHoldingRegistersIndex < (gacModbusPacket[MODBUS_WMHR_BYTE_COUNT] / 2) + iStartAddress; iHoldingRegistersIndex++)
    {
        gModbusHoldingRegisters[iHoldingRegistersIndex] = (gacModbusPacket[iIndex] << 8) | gacModbusPacket[iIndex + 1];
        iIndex += 2;

    }
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_ID];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_FC];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WMHR_START_ADDRESS_HI];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WMHR_START_ADDRESS_LO];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WMHR_QTY_REG_HI];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WMHR_QTY_REG_LO ];

    checkCRC = getCRC16(iResponsePacket, iResponseIndex);
    iResponsePacket[iResponseIndex++] = checkCRC;
    iResponsePacket[iResponseIndex++] = checkCRC >> 8;

    sendResponse(iResponsePacket, iResponseIndex);
}

/**
 * This function code is used to write a single holding register in a remote device.
 * The normal response is an echo of the request, returned after the register contents have been
written.
 */
void modbusWriteSingleRegister(void)
{
    unsigned short iStartAddress = 0;
    unsigned char iResponsePacket[150];
    unsigned short iRegisterVal;
    unsigned short checkCRC = 0;
    unsigned char iResponseIndex = 0;

    iStartAddress = (gacModbusPacket[MODBUS_WSHR_START_ADDRESS_HI] << 8) | gacModbusPacket[MODBUS_WSHR_START_ADDRESS_LO];
    iRegisterVal = (gacModbusPacket[MODBUS_WSHR_REG_VAL_HI] << 8) | gacModbusPacket[MODBUS_WSHR_REG_VAL_LO];

    gModbusHoldingRegisters[iStartAddress] = iRegisterVal;

    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_ID];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[INDEX_FC];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WSHR_START_ADDRESS_HI];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WSHR_START_ADDRESS_LO];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WSHR_REG_VAL_HI];
    iResponsePacket[iResponseIndex++] = gacModbusPacket[MODBUS_WSHR_REG_VAL_LO ];

    checkCRC = getCRC16(iResponsePacket, iResponseIndex);
    iResponsePacket[iResponseIndex++] = checkCRC;
    iResponsePacket[iResponseIndex++] = checkCRC >> 8;

    sendResponse(iResponsePacket, iResponseIndex);
}