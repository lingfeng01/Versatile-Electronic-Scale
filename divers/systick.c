#include "systick.h"

ulong tick = 0;

void Timer0_Isr(void) interrupt 1
{
    tick++;
}

void Timer0_Init(void) // 1毫秒@24.000MHz
{
    AUXR &= 0x7F; // 定时器时钟12T模式
    TMOD &= 0xF0; // 设置定时器模式
    TL0 = 0x30;   // 设置定时初始值
    TH0 = 0xF8;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
    ET0 = 1;      // 使能定时器0中断
}

ulong Get_Tikc(void)
{

    return tick;
}

void DelayTick(WORD tk)
{
    ulong t;
    t = tick + tk;
    while (Get_Tikc() < t)
    {
    }
}