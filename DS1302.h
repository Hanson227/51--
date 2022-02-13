#ifndef __DS1302_H__
#define __DS1302_H__

typedef unsigned char u8;
typedef unsigned int u16;

extern u8 DS1302_Times[];//extern声明为外部数组

void DS1302_Init(void);
void DS1302_WriteByte(u8 command,u8 date);
u8 DS1302_ReadByte(u8 command);
void DS1302_SetTime(void);
void DS1302_ReadTime(void);

#endif