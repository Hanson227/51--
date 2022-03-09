#include <REGX52.H>

unsigned int  Tem;           //温度
float objTemp,envTemp;         //物体温度和环境温度

int main()
{
    Tem1=ReadObjectTemp();         //读取实物温度
    objTemp=(float)(Tem)*0.02-273.15;
       
    Tem2=ReadEnvironTemp();         //读取环境温度
    envTemp=(float)(Tem)*0.02-273.15;
    LCD_Write_String(0,0,dis0);//显示
    LCD_Write_String(0,1,dis1);//显示


}