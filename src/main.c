#include <REGX52.H>
#include "mlx90614.h"
#include "LCD1602.h"
#include "UART.h"
#include "Buzzer.h"
#include "Delay.h"
#include <STDIO.H>

unsigned int  Temp1;           //温度
float objTemp,T;         //物体温度和环境温度

int main()
{
    LCD_Init();
    Temp1=ReadObjectTemp();
    T=(float)(Temp1)*0.02-273.15;
	if(T<0)				//如果温度小于0
	{
		LCD_ShowChar(2,1,'-');	//显示负号
		T=-T;			//将温度变为正数
	}
	else				//如果温度大于等于0
	{
		LCD_ShowChar(2,1,'+');	//显示正号
	}
	LCD_ShowNum(2,2,T,3);		//显示温度整数部分
	LCD_ShowChar(2,5,'.');		//显示小数点
	LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);//显示温度小数部分
    return 0;
}