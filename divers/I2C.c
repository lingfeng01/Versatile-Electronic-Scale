#include "I2C.h"

/**
 * @brief I2C启动
 *
 */
void I2C_Start()
{
    busy = 1;
    I2CMSCR = 0x81;
    while (busy)
    {
    }
}

/**
 * @brief I2C停止
 *
 */
void I2C_Stop()
{

    busy = 1;
    I2CMSCR = 0x86;
    while (busy)
    {
    }
}

/**
 * @brief I2C发送数据
 *
 * @param dat
 */
void I2C_SendData(uchar dat)
{
    I2CTXD = dat;
    busy = 1;
    I2CMSCR = 0x82;
    while (busy)
    {
    }
}

/**
 * @brief I2C接收应答
 *
 */
void Recv_Ack()
{
    busy = 1;
    I2CMSCR = 0x83;
    while (busy)
    {
    }
}

/**
 * @brief I2C接收数据
 *
 * @return char
 */
char I2C_RecvData()
{
    busy = 1;
    I2CMSCR = 0x84;
    while (busy)
    {
    }
    return I2CRXD;
}

/**
 * @brief I2C发送ACK
 *
 */
void I2C_SendAck()
{
    I2CMSST = 0x00;
    busy = 1;
    I2CMSCR = 0x85;
    while (busy)
    {
    }
}

/**
 * @brief I2C发送NACK
 *
 */
void I2C_SendNAck()
{
    I2CMSST = 0x01;
    busy = 1;
    I2CMSCR = 0x85;
    while (busy)
    {
    }
}

void I2C_Init()
{
    I2CCFG = 0xe0;
    I2CMSST = 0x00;
    EA = 1;
}