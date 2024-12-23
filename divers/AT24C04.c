#include "AT24C04.h"

/**
 * @brief
 *
 * @brief 写入一个字节到AT24C04
 *
 * @param addr 存储地址
 * @param data 要写入的数据
 */
void AT24C04_WriteByte(uchar AT24C04_ADDR, uchar addr, uchar SendData)
{
    I2C_Start();                       // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01); // 发送器件地址和写命令
    Recv_Ack();                        // 接收应答
    I2C_SendData(addr);                // 发送存储地址
    Recv_Ack();                        // 接收应答
    I2C_SendData(SendData);            // 发送数据
    Recv_Ack();                        // 接收应答
    I2C_Stop();                        // 停止I2C
}
/**
 * @brief 从AT24C04读取一个字节
 *
 * @param addr 存储地址
 * @return uchar 读取的数据
 */
uchar AT24C04_ReadByte(uchar AT24C04_ADDR, uchar addr)
{
    uchar ReaData;
    I2C_Start();                       // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01); // 发送器件地址和写命令
    Recv_Ack();                        // 接收应答
    I2C_SendData(addr);                // 发送存储地址
    Recv_Ack();                        // 接收应答
    I2C_Start();                       // 重新启动I2C
    I2C_SendData(AT24C04_ADDR | 0x00); // 发送器件地址和读命令
    Recv_Ack();                        // 接收应答
    ReaData = I2C_RecvData();          // 读取数据
    I2C_SendNAck();                    // 发送非应答信号
    I2C_Stop();                        // 停止I2C
    return ReaData;
}

/**
 * @brief 写入多个字节到AT24C04
 *
 * @param addr 起始存储地址
 * @param data 要写入的数据缓冲区
 * @param length 要写入的数据长度
 */
void AT24C04_WritePage(uchar AT24C04_ADDR, uchar addr, uchar *SendData, uchar length)
{
    uchar i;
    I2C_Start();                       // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01); // 发送器件地址和写命令
    Recv_Ack();                        // 接收应答
    I2C_SendData(addr);                // 发送起始存储地址
    Recv_Ack();                        // 接收应答
    for (i = 0; i < length; i++)
    {
        I2C_SendData(SendData[i]); // 发送数据
        Recv_Ack();                // 接收应答
    }
    I2C_Stop(); // 停止I2C
}

/**
 * @brief 从AT24C04读取多个字节
 *
 * @param addr 起始存储地址
 * @param data 用于存储读取数据的缓冲区
 * @param length 要读取的数据长度
 */
void AT24C04_ReadPage(uchar AT24C04_ADDR, uchar addr, uchar *ReaData, uchar length)
{
    uchar i;
    I2C_Start();                       // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01); // 发送器件地址和写命令
    Recv_Ack();                        // 接收应答
    I2C_SendData(addr);                // 发送起始存储地址
    Recv_Ack();                        // 接收应答
    I2C_Start();                       // 重新启动I2C
    I2C_SendData(AT24C04_ADDR | 0x00); // 发送器件地址和读命令
    Recv_Ack();                        // 接收应答
    for (i = 0; i < length; i++)
    {
        ReaData[i] = I2C_RecvData(); // 读取数据
        if (i < length - 1)
        {
            I2C_SendAck(); // 发送应答信号
        }
        else
        {
            I2C_SendNAck(); // 发送非应答信号
        }
    }
    I2C_Stop(); // 停止I2C
}
