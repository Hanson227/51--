#include <REGX52.H>
#include "LCD1602.h"
#include "DS1302.h"
#include "Timer0.h"
#include "Key.h"
#include "Delay.h"

#define unsigned char u8;
#define int  u16;

u8 Keynum,MODEL,TimeSetSelect,TimeSetFlashFlag=0;


/**
 * @brief 设置时间函数
 * 
 */
void SetNum()
{
    if(Keynum==2)
    {
        TimeSetSelect++;
        TimeSetSelect%=6;
    }
    if(Keynum==3)//加
    {
        DS1302_Times[TimeSetSelect]++;
        if(DS1302_Times[0]>99){DS1302_Times[0]=0;}//年
        if(DS1302_Times[1]>12){DS1302_Times[1]=1;}//月
        if(DS1302_Times[1]==1||DS1302_Times[1]==3||DS1302_Times[1]==5||DS1302_Times[1]==7
        ||DS1302_Times[1]==8||DS1302_Times[1]==10||DS1302_Times[1]==12)
        {
            if(DS1302_Times[2]>31){DS1302_Times[2]=0;}
        }
        else if(DS1302_Times[1]==4||DS1302_Times[1]==6||DS1302_Times[1]==9
        ||DS1302_Times[1]==11)
        {
            if(DS1302_Times[2]>30){DS1302_Times[2]=0;}
        }
        else if(DS1302_Times[1]==2)
        {
            if(DS1302_Times[0]%4==0)//闰年
            {
                if(DS1302_Times[2]>29){DS1302_Times[2]=1;}
            }
            else//非闰年
            {
                if(DS1302_Times[2]>28){DS1302_Times[2]=1;}
            }
        }//日判断
        if(DS1302_Times[3]>23){DS1302_Times[3]=1;}//时
        if(DS1302_Times[4]>59){DS1302_Times[4]=0;}//分
        if(DS1302_Times[5]>59){DS1302_Times[5]=0;}//秒
    }
    if(Keynum==4)//减
    {
        DS1302_Times[TimeSetSelect]--;
        if(DS1302_Times[0]==255){DS1302_Times[0]=99;}//年
        if(DS1302_Times[1]==255){DS1302_Times[1]=12;}//月
        if(DS1302_Times[1]==1||DS1302_Times[1]==3||DS1302_Times[1]==5||DS1302_Times[1]==7
        ||DS1302_Times[1]==8||DS1302_Times[1]==10||DS1302_Times[1]==12)
        {
            if(DS1302_Times[2]>31&&DS1302_Times[2]<255){DS1302_Times[2]=1;}
            if(DS1302_Times[2]==255){DS1302_Times[2]=31;}
        }
        else if(DS1302_Times[1]==4||DS1302_Times[1]==6||DS1302_Times[1]==9
        ||DS1302_Times[1]==11)
        {
            if(DS1302_Times[2]>30&&DS1302_Times[2]<255){DS1302_Times[2]=1;}
            if(DS1302_Times[2]==255){DS1302_Times[2]=30;}
        }
        else if(DS1302_Times[1]==2)
        {
            if(DS1302_Times[0]%4==0)//闰年
            {
                if(DS1302_Times[2]>29&&DS1302_Times[2]<255){DS1302_Times[2]=1;}
                if(DS1302_Times[2]==255){DS1302_Times[2]=29;}
            }
            else//非闰年
            {
                if(DS1302_Times[2]>28&&DS1302_Times[2]<255){DS1302_Times[2]=1;}
                if(DS1302_Times[2]==255){DS1302_Times[2]=28;}
            }
        }//日判断
        if(DS1302_Times[3]==255){DS1302_Times[3]=1;}//时
        if(DS1302_Times[4]==255){DS1302_Times[4]=0;}//分
        if(DS1302_Times[5]==255){DS1302_Times[5]=0;}//秒
    }
    if(TimeSetSelect==0&&TimeSetFlashFlag==0){LCD_ShowString(1,1,"  ");}
    else{LCD_ShowNum(1,1,DS1302_Times[0],2);}
    if(TimeSetSelect==1&&TimeSetFlashFlag==0){LCD_ShowString(1,4,"  ");}
    else{LCD_ShowNum(1,4,DS1302_Times[1],2);}
    if(TimeSetSelect==2&&TimeSetFlashFlag==0){LCD_ShowString(1,7,"  ");}
    else{LCD_ShowNum(1,7,DS1302_Times[2],2);}
    if(TimeSetSelect==3&&TimeSetFlashFlag==0){LCD_ShowString(2,1,"  ");}
    else{LCD_ShowNum(2,1,DS1302_Times[3],2);}
    if(TimeSetSelect==4&&TimeSetFlashFlag==0){LCD_ShowString(2,4,"  ");}
    else{LCD_ShowNum(2,4,DS1302_Times[4],2);}
    if(TimeSetSelect==5&&TimeSetFlashFlag==0){LCD_ShowString(2,7,"  ");}
    else{LCD_ShowNum(2,7,DS1302_Times[5],2);}
}

/**
 * @brief 将显示时间
 * 
 */

void ShowNum()
{   
    DS1302_ReadTime();
    LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");
    LCD_ShowNum(1,1,DS1302_Times[0],2);
    LCD_ShowNum(1,4,DS1302_Times[1],2);
    LCD_ShowNum(1,7,DS1302_Times[2],2);
    LCD_ShowNum(2,1,DS1302_Times[3],2);
    LCD_ShowNum(2,4,DS1302_Times[4],2);
    LCD_ShowNum(2,7,DS1302_Times[5],2);
}

void main()
{
    LCD_Init();
    DS1302_Init();
    LCD_ShowString(1,1,"  -  -  ");//静态字符初始化显示
	LCD_ShowString(2,1,"  :  :  ");
    DS1302_SetTime();//设置时间
    Timer0Init();
    while(1)
    {
        //DS1302_ReadTime();
        Keynum= Key();
        if(Keynum==1)
        {
          if(MODEL==0){MODEL=1;}
          else if(MODEL==1){MODEL=0;DS1302_SetTime();}   
        }
        switch (MODEL)
        {
            case 0:ShowNum();break;
            case 1:SetNum();break;
        }
    }   
} 

/**
 * @brief 运用中断定时器来实现相隔500ms选中闪烁的功能
 * 
 */
void Timer0_Routine() interrupt 1
{
	static u16  T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		TimeSetFlashFlag=!TimeSetFlashFlag;
	}
}