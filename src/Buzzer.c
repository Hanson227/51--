/**
 * @file Buzzer.c
 * @author Hanson 
 * @brief 蜂鸣器播放提示音
 * @version 0.1
 * @date 2022-02-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "REGX52.H"
#include "Delay.h"

sbit Buzzer=P2^5;

unsigned int a;

/**
 * @brief 播放提示音的长度  
 * 
 * @param ms播放多少ms提示音 
 */
void Buzzer_Time(unsigned int ms)
{
    for(a=0;a<ms;a++)
    {
        Buzzer=!Buzzer;
        Delay(1);
    }
}