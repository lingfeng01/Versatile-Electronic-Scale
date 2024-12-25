#ifndef __SERIA4_H__
#define __SERIA4_H__

#include <stc8h.h>
#include "./divers/command.h"
#include "systick.h"

#define FOSC 24000000UL
#define BRT (65536 - FOSC / 115200 / 4)

void Uart4_Init(void);      // 串口4初始化
void Uart4Send(char dat);   // 串口4发送一个字节
void Uart4SendStr(char *p); // 串口4发送多个字节

#endif