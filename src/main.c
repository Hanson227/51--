#include <REGX52.H>
#include "mlx90614.h"
#include "LCD1602.h"
#include "UART.h"
#include "Buzzer.h"
#include "Delay.h"



unsigned int  Temp1,Temp2;           //温度
float objTemp,envTemp;         //物体温度和环境温度

int main()
{
    Temp1=ReadObjectTemp();         //读取实物温度
    objTemp=(float)(Temp1)*0.02-273.15;
       
    Temp2=ReadEnvironTemp();         //读取环境温度
    envTemp=(float)(Temp2)*0.02-273.15;
    LCD_ShowNum(1,1,objTemp,5);
    LCD_ShowNum(2,1,envTemp,5);


}