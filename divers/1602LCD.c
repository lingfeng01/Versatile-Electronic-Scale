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
/**
 * @brief  LCD1602设置光标位置
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @retval 无
 */
void LCD_SetCursor(uint Line, uint Column)
{
    if (Line == 1)
    {
        LCD1602_Wr_Command(0x80 | (Column - 1));
    }
    else if (Line == 2)
    {
        LCD1602_Wr_Command(0x80 | (Column - 1 + 0x40));
    }
}

/**
 * @brief  在LCD1602指定位置上显示一个字符
 * @param  Line 行位置，范围：1~2
 * @param  Column 列位置，范围：1~16
 * @param  Char 要显示的字符
 * @retval 无
 */
void LCD1602_Display_Char(uint Line, uint Column, char Char) // 指定位置上显示一个字符
{
    LCD_SetCursor(Line, Column);
    LCD1602_Wr_Data(Char);
}

void LCD1602_Display_String(uint Line, uint Column, char *String) // 指定位置显示字符串
{
    uint8_t i;
    LCD_SetCursor(Line, Column);
    for (i = 0; String[i] != '\0'; i++)
    {
        LCD1602_Wr_Data(String[i]);
    }
}

void LCD1602_Init(void) // 初始化
{
    LCD1602_Wr_Command(0x38);
    LCD1602_Wr_Command(0x38);
    LCD1602_Wr_Command(0x0c);
    LCD1602_Wr_Command(0x01);
    LCD1602_Wr_Command(0x04);
}