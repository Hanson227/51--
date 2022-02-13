/**
 * @file DS1302.c
 * @author Hanson
 * @brief 时钟芯片写入读出
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <REGX52.H>

sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

typedef unsigned int u16;
typedef unsigned char u8;

#define DS1302_SECOND 0x80
#define DS1302_MINUTE 0x82
#define DS1302_HOUR   0x84
#define DS1302_DATE   0x86
#define DS1302_MONTH  0x88
#define DS1302_DAY    0x8A
#define DS1302_YEAR   0x8C
#define DS1302_WP     0x8E

u8 DS1302_Times[]={22,2,11,17,19,00,5,};//年月日时分秒星期

/**
 * @brief 初始化
 * 
 */
void DS1302_Init(void)
{
    DS1302_CE=0;
    DS1302_SCLK=0;
}
/**
 * @brief 写入
 * 
 * @param command 命令字
 * @param date 写入的数据
 */
void DS1302_WriteByte(u8 command,u8 date)
{
    u8 i;
    DS1302_CE=1;
    for(i=0;i<8;i++)//写入命令字
    {
        DS1302_IO=command&(0x01<<i);
        DS1302_SCLK=1;
        DS1302_SCLK=0;
    }
    for(i=0;i<8;i++)
    {
        DS1302_IO=date&(0x01<<i);
        DS1302_SCLK=1;
        DS1302_SCLK=0;
    }
    DS1302_CE=0;
}

/**
 * @brief 读出
 * 
 * @param command 命令字 
 * @return 读出的数据 
 */
u8 DS1302_ReadByte(u8 command)
{
    u8 i,Date=0x00;
    command|=0x01;
    DS1302_CE=1;
    for(i=0;i<8;i++)
    {
        DS1302_IO=command&(0x01<<i);
        DS1302_SCLK=0;
        DS1302_SCLK=1;
    }
    for(i=0;i<8;i++)
    {
        DS1302_SCLK=1;
        DS1302_SCLK=0;
        if(DS1302_IO){Date|=(0x01<<i);}
    }
    DS1302_CE=0;
    DS1302_IO=0;
    return Date;
}

/**
 * @brief 设置时间
 * 
 */
void DS1302_SetTime(void)
{
    DS1302_WriteByte(DS1302_WP,0x00);
    DS1302_WriteByte(DS1302_YEAR,DS1302_Times[0]/10*16+DS1302_Times[0]%10);
    DS1302_WriteByte(DS1302_MONTH,DS1302_Times[1]/10*16+DS1302_Times[1]%10);
    DS1302_WriteByte(DS1302_DATE,DS1302_Times[2]/10*16+DS1302_Times[2]%10);
    DS1302_WriteByte(DS1302_HOUR,DS1302_Times[3]/10*16+DS1302_Times[3]%10);
    DS1302_WriteByte(DS1302_MINUTE,DS1302_Times[4]/10*16+DS1302_Times[4]%10);
    DS1302_WriteByte(DS1302_SECOND,DS1302_Times[5]/10*16+DS1302_Times[5]%10);
    DS1302_WriteByte(DS1302_DAY,DS1302_Times[6]/10*16+DS1302_Times[6]%10);
    DS1302_WriteByte(DS1302_WP,0x80);
}

/**
 * @brief 读取时间
 * 
 */
void DS1302_ReadTime(void)
{
    u8 temp;
    temp=DS1302_ReadByte(DS1302_YEAR);
    DS1302_Times[0]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_MONTH);
    DS1302_Times[1]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_DATE);
    DS1302_Times[2]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_HOUR);
    DS1302_Times[3]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_MINUTE);
    DS1302_Times[4]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_SECOND);
    DS1302_Times[5]=temp/16*10+temp%16;
    temp=DS1302_ReadByte(DS1302_DAY);
    DS1302_Times[6]=temp/16*10+temp%16;
}