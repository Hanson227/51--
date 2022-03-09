/**
 * @file UART.c
 * @author Hanson 
 * @brief 串口
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <REGX52.H>
/**
 * @brief 端口初始化
 * 
 */
void UART_Init()		//4800bps@11.0592MHz
{
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF4;		//设置定时初始值
	TH1 = 0xF4;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
}
/**
 * @brief 给串口发送口令
 * 
 * @param Byte 命令
 */
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}