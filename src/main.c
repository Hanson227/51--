#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"

typedef unsigned char u8;
typedef unsigned int u16;

u8 Date;

int main()
{
    LCD_Init();
    LCD_ShowString(1,1,"Hello");
    AT24C02_WriteByte(1,6);
    Delay(5);
    Date=AT24C02_ReadByte(1);
    LCD_ShowNum(2,1,Date,3);
    while (1)
    {
        
    }
    
}