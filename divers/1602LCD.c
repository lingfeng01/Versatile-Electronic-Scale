#include "1602LCD.h"

void LCD1602_RDbf(void) // 读忙状态
{
    uchar sta;
    LCD_1602_Data = 0xFF;
    LCD_1602_RS = 0;
    LCD_1602_RW = 1;
    while (1)
    {
        LCD_1602_E = 1;
        DelayTick(1);
        sta = LCD_1602_Data;
        DelayTick(1);
        LCD_1602_E = 0;
        DelayTick(1);
        if ((sta & 0x80) == 0)
        {
            break;
        }
    }
}

void LCD1602_Wr_Data(uchar wrdata) // 写数据
{
    LCD1602_RDbf();
    LCD_1602_RS = 1;
    LCD_1602_RW = 1;
    DelayTick(1);
    LCD_1602_Data = wrdata;
    DelayTick(1);
    LCD_1602_E = 1;
    DelayTick(1);
    LCD_1602_E = 0;
}

void LCD1602_Wr_Command(uchar wrcommand) // 写指令
{
    LCD1602_RDbf();
    LCD_1602_RS = 0;
    LCD_1602_RW = 0;
    DelayTick(1);
    LCD_1602_Data = wrcommand;
    DelayTick(1);
    LCD_1602_E = 1;
    DelayTick(1);
    LCD_1602_E = 0;
}

void LCD1602_Display_String(char *str) // 显示字符
{
    LCD1602_RDbf();
    while (*str)
    {
        LCD1602_Wr_Data(*str++);
    }
}

void LCD1602_Init(void) // 初始化
{
    LCD1602_Wr_Command(0x38);
    LCD1602_Wr_Command(0x38);
    LCD1602_Wr_Command(0x0c);
    LCD1602_Wr_Command(0x01);
    DelayTick(2);
    LCD1602_Wr_Command(0x04);
}