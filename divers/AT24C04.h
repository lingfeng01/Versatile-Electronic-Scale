#ifndef __AT24C04_H__
#define __AT24C04_H__

#include <stc8h.h>
#include "./divers/command.h"
#include "systick.h"
#include "I2C.h"

void AT24C04_WriteByte(uchar AT24C04_ADDR, uchar addr, uchar SendData);                // 写入一个字节到AT24C04
uchar AT24C04_ReadByte(uchar AT24C04_ADDR, uchar addr);                                // 从AT24C04读取一个字节
void AT24C04_WritePage(uchar AT24C04_ADDR, uchar addr, uchar *SendData, uchar length); // 写入多个字节到AT24C04
void AT24C04_ReadPage(uchar AT24C04_ADDR, uchar addr, uchar *ReaData, uchar length);   // 从AT24C04读取多个字节

#endif