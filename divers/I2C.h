#ifndef __I2C_H__
#define __I2C_H__

#include <stc8h.h>
#include "./divers/command.h"
#include <stdio.h>
#include "systick.h"

sbit SDA = P1 ^ 4;
sbit SCL = P1 ^ 5;

static BOOL busy;

void I2C_Start();
void I2C_Stop();

void I2C_SendData(uchar dat);
void Recv_Ack();
char I2C_RecvData();
void I2C_SendAck();
void I2C_SendNAck();
void I2C_Init();

#endif