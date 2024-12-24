#include "I2C.h"

void Wait()
{

    while (!(I2CMSST & 0x40))
    {
    }
    I2CMSST &= ~0x40;
}
/**
 * @brief I2C启动
 *
 */
void I2C_Start()
{

    I2CMSCR = 0x01;
    Wait();
}

/**
 * @brief I2C停止
 *
 */
void I2C_Stop()
{
    I2CMSCR = 0x86;
    Wait();
}

/**
 * @brief I2C发送数据
 *
 * @param dat
 */
void I2C_SendData(uchar dat)
{
    I2CTXD = dat;
    I2CMSCR = 0x02;
    Wait();
}

/**
 * @brief I2C接收应答
 *
 */
void Recv_Ack()
{
    I2CMSCR = 0x03;
    Wait();
}

/**
 * @brief I2C接收数据
 *
 * @return char
 */
char I2C_RecvData()
{
    I2CMSCR = 0x04;
    Wait();
    return I2CRXD;
}

/**
 * @brief I2C发送ACK
 *
 */
void I2C_SendAck()
{
    I2CMSST = 0x00;
    I2CMSCR = 0x05;
    Wait();
}

/**
 * @brief I2C发送NACK
 *
 */
void I2C_SendNAck()
{
    I2CMSST = 0x01;
    I2CMSCR = 0x05;
    Wait();
}

void I2C_Init()
{
    I2CCFG = 0xe0;
    I2CMSST = 0x00;
}