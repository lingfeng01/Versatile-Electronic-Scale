#include "systick.h"

// 全局变量，用于记录系统滴答计数
ulong tick = 0;

// 定时器0中断服务程序，每次中断时tick递增
void Timer0_Isr(void) interrupt 1
{
    tick++;
}

// 初始化定时器0，使其每1毫秒产生一次中断@24.000MHz
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

// 获取当前的滴答计数
ulong Get_Tikc(void)
{
    return tick;
}

// 延迟指定的滴答数
void DelayTick(WORD tk)
{
    ulong t;
    t = tick + tk;         // 计算延迟结束的滴答计数
    while (Get_Tikc() < t) // 等待直到当前滴答计数达到目标值
    {
    }
}