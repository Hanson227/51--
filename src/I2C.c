/**
 * @file I2C.c
 * @author Hanson 
 * @brief 实现I2C六种基本通讯
 * @version 0.1
 * @date 2022-02-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <REGX52.H>

sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;

typedef unsigned char u8;
typedef unsigned int u16;

/**
 * @brief 起始条件
 * 
 */
void I2C_Start(void)
{
    I2C_SDA=1;
    I2C_SCL=1;
    I2C_SDA=0;
    I2C_SCL=0;
}

/**
 * @brief 终止条件
 * 
 */
void I2C_Stop(void)
{
    I2C_SDA=0;
    I2C_SCL=1;
    I2C_SDA=1;
}

/**
 * @brief 发送一个字节
 * 
 * @param Byte 要发送的一个字节
 */
void I2C_SendByte(u8 Byte)
{
    u8 i;
    for (i=0; i < 8; i++)
    {
        I2C_SDA=Byte&(0x80>>i);
        I2C_SCL=1;
        I2C_SCL=0;
    } 
}

/**
 * @brief 接受一个字节
 * 
 * @return u8 接受的数据
 */

u8 I2C_ReceiveByte(void)
{
    u8 i,Byte=0x00;
    I2C_SDA=1;
    for(i=0;i<8;i++)
    {
        I2C_SCL=1;
        if(I2C_SDA){Byte|=(0x80>>i);}
        I2C_SCL=0;
    }
    return Byte;
}
/**
 * @brief 由主机发送应答到从机，表示发出数据
 * 
 * @param AckBit 0或者1，bit为51特有类型类似于bool，0为有应答
 */
void I2C_SendAck(bit AckBit)
{
    I2C_SDA=AckBit;
    I2C_SCL=1;
    I2C_SCL=0;
}
/**
 * @brief 由从机发送应答到主机，表示收到数据
 * 
 * @return Ackbit 返回，0为有应答，1为无应答
 */
u8 I2C_ReceivedAck(void)
{
    u8 AckBit;
    I2C_SDA=1;//
    I2C_SCL=1;
    AckBit=I2C_SDA;
    I2C_SCL=0;
    return AckBit;
}