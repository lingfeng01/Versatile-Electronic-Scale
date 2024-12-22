#ifndef __1602LCD_H__
#define __1602LCD_H__

#include <stc8h.h>
#include "./divers/command.h"
#include "systick.h"

sbit LCD_1602_RS = P2 ^ 5;
sbit LCD_1602_RW = P2 ^ 6;
sbit LCD_1602_E = P2 ^ 7;
#define LCD_1602_Data P0

void LCD1602_RDbf(void);                                           // 读忙状态
void LCD1602_Wr_Data(uchar wrdata);                                // 写数据
void LCD1602_Wr_Command(uchar wrcommand);                          // 写指令
void LCD_SetCursor(uint Line, uint Column);                        // 设置光标位置
void LCD1602_Display_Char(uint Line, uint Column, char Char);      // 指定位置上显示一个字符
void LCD1602_Display_String(uint Line, uint Column, char *String); // 指定位置显示字符串
void LCD1602_Init(void);                                           // 初始化
#endif