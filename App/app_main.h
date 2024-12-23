#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

#include "./divers/stc32_stc8_usb.h"
#include <stc8h.h>
#include "./divers/command.h"
#include <stdio.h>
#include "systick.h"
#include "HX711.h"
#include "1602LCD.h"
#include "I2C.h"
#include "key_detect.h"

// 定义按键
sbit Key1 = P3 ^ 6;
sbit Key2 = P4 ^ 6;
sbit Key3 = P2 ^ 3;
sbit Key4 = P1 ^ 0;

// 定义LED
sbit LED1 = P2 ^ 0;
sbit LED2 = P5 ^ 0;
sbit LED3 = P3 ^ 4;

// 定义蜂鸣器
sbit BEEP = P2 ^ 4;

#define poll_time 0         // 重量轮询时间
#define weigh_poll_time 500 // 重量轮询时间

void IO_Init();
void Display_PersonInfo();
void LCD_Display_Weight();
void tare_weight();
void Count_weight();
void LCD_Display_Count();
void Overweight_alarm();
void Weight_threshold();
void Page_Switching();
void usb_set_weight_K(BYTE UsbOut[], BYTE *size_t);

void app_main();

#endif