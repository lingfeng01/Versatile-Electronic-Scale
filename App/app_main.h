#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

#include "./divers/stc32_stc8_usb.h"
#include <stc8h.h>
#include "./divers/command.h"
#include <stdio.h>
#include "systick.h"
#include "HX711.h"
#include "1602LCD.h"
#include "key_detect.h"

// 定义按键
#define Key1 P36
#define Key2 P46
#define Key3 P23
#define Key4 P10

// 定义蜂鸣器
sbit BEEP = P2 ^ 4;

#define Weight_poll_time 500 // 重量轮询时间

void IO_Init();
void Display_PersonInfo();
void LCD_Display_Weight();
void tare_weight();
void Count_weight();
void LCD_Display_Count();
void Page_Switching();
void app_main();

#endif