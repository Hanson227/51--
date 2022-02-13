#include <REGX52.H>
#include "Delay.h"
#include "LCD1602.h"
#include "Key.h"
#include "AT24C02.h"

int main()
{
    LCD_Init();
    LCD_ShowString(1,1,"Hello");
    AT24C02_WriteByte(0,0);
    while (1)
    {
        
    }
    
}