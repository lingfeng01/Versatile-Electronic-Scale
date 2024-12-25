#include "Serial4.h"

uchar receivedData;

BOOL Seria_Busy = 0; // 串口忙标志
/**
 * @brief 串口4初始化
 *
 * 串口4初始化，波特率设置为115200bps。
 */
void Uart4_Init(void) // 115200bps@24.000MHz
{
    S4CON = 0x10;   // 8位数据,可变波特率
    S4CON |= 0x40;  // 串口4选择定时器4为波特率发生器
    T4T3M |= 0x20;  // 定时器时钟1T模式
    T4L = BRT;      // 设置定时初始值
    T4H = BRT >> 8; // 设置定时初始值
    T4T3M |= 0x80;  // 定时器4开始计时
    IE2 |= 0x10;    // 使能串口4中断
    P_SW2 |= 0x04;  // 将串口4的RXD4_2/P5.2, TXD4_2/P5.3
}

/**
 * @brief 串口4发送一个字节
 *
 *
 */
void Uart4Send(char dat)
{
    while (Seria_Busy)
    {
    }
    Seria_Busy = 1;
    S4BUF = dat;
}

/**
 * @brief 串口4发送多个字节
 *
 * @param p 发送的字节指针
 */
void Uart4SendStr(char *p)
{

    while (*p)
    {
        Uart4Send(*p++);
    }
}

/**
 * @brief 串口4中断服务函数
 *
 * 串口4中断服务函数，处理串口4的发送和接收中断。
 */
void Uart4_Isr(void) interrupt 18
{
    if (S4CON & 0x02) // 检测串口4发送中断
    {
        S4CON &= ~0x02; // 清除串口4发送中断请求位
        Seria_Busy = 0;
    }
    if (S4CON & 0x01) // 检测串口4接收中断
    {
        S4CON &= ~0x01; // 清除串口4接收中断请求位
        receivedData = S4BUF;
        Uart4Send(receivedData);
    }
}