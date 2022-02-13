#include <REGX52.H>
#include "I2C.h"

typedef unsigned char u8;
typedef unsigned int  u16;

#define AT24C02_ADDRESS 0xA0

void AT24C02_WriteByte(u8 WordAddress,Date)
{
    I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_SendByte(Date);
	I2C_ReceiveAck();
	I2C_Stop();
}

u8 AT24C02_ReadByte(u8 WordAddress)
{
    u8 Date;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(WordAddress);
	I2C_ReceiveAck();
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Date=I2C_ReceiveByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Date;
}