#include <REGX52.H>
#include "I2C.h"

typedef unsigned char u8;
typedef unsigned int  u16;

#define AT24C02_ADDRESS 0xA0

void AT24C02_WriteByte(u8 WordAddress,Date)
{
    u8 Ack;
    I2C_Start();
    I2C_SendByte(AT24C02_ADDRESS);
    Ack=I2C_ReceivedAck();
    if(Ack==0){P2=0x00;}
}

u8 AT24C02_ReadByte(u8 WordAddress)
{
    u8 Date;
    return Date;
}