#include "AT24C04.h"

/**
 * @brief 写入一个字节到AT24C04
 *
 * @param addr 存储地址
 * @param data 要写入的数据
 */
void AT24C04_WriteByte(uchar AT24C04_ADDR, uchar addr, uchar SendData)
{
    I2C_Start();                        // 启动I2C
    I2C_SendData(AT24C04_ADDR);         // 发送器件地址和写命令
    Recv_Ack();                         // 接收应答
    I2C_SendData((addr & 0xFF));        // 发送存储高位地址
    Recv_Ack();                         // 接收应答
    I2C_SendData(((addr >> 8) & 0xFF)); // 发送存储低位地址
    Recv_Ack();                         // 接收应答
    I2C_SendData(SendData);             // 发送数据
    Recv_Ack();                         // 接收应答
    I2C_Stop();                         // 停止I2C
}
/**
 * @brief 从AT24C04读取一个字节
 *
 * @param addr 存储地址
 * @return uchar 读取的数据
 */
uchar AT24C04_ReadByte(uchar AT24C04_ADDR, uchar addr)
{
    uchar ReadData;
    I2C_Start();                        // 启动I2C
    I2C_SendData(AT24C04_ADDR);         // 发送器件地址和写命令
    Recv_Ack();                         // 接收应答
    I2C_SendData((addr & 0xFF));        // 发送存储高位地址
    Recv_Ack();                         // 接收应答
    I2C_SendData(((addr >> 8) & 0xFF)); // 发送存储低位地址
    Recv_Ack();                         // 接收应答
    I2C_Start();                        // 重新启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01);  // 发送器件地址和读命令
    Recv_Ack();                         // 接收应答
    ReadData = I2C_RecvData();          // 读取数据
    I2C_SendNAck();                     // 主机非应答
    I2C_Stop();                         // 停止I2C
    return ReadData;
}

/**
 * @brief 页写入方式
 * @brief 写入多个字节到AT24C04
 * @param addr 起始存储地址
 * @param SendData 要写入的数据缓冲区
 * @param length 要写入的数据长度
 */
void AT24C04_WritePage(uchar AT24C04_ADDR, uchar addr, uchar *SendData)
{
    uchar length = sizeof(SendData);
    uchar i;
    I2C_Start();                                                     // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x00 | (((addr >> 8) & 0x07) << 1)); // 发送器件地址和写命令
    Recv_Ack();                                                      // 接收应答
    I2C_SendData((addr & 0xFF));                                     // 发送存储低位地址
    Recv_Ack();                                                      // 接收应答
    for (i = 0; i < length; i++)
    {
        I2C_SendData(SendData[i]); // 发送数据
        Recv_Ack();                // 接收应答
    }
    I2C_Stop(); // 停止I2C
}

/**
 * @brief 页读取方式
 * @brief 从AT24C04读取一页数据
 * @param addr 起始存储地址
 * @param ReadData 读取数据缓冲区
 * @param length 读取数据长度
 */
void AT24C04_ReadPage(uchar AT24C04_ADDR, uchar addr, uchar *ReadData, uchar length)
{
    uchar i;
    I2C_Start();                                                     // 启动I2C
    I2C_SendData(AT24C04_ADDR | 0x00 | (((addr >> 8) & 0x07) << 1)); // 发送器件地址和读命令
    Recv_Ack();                                                      // 接收应答
    I2C_SendData((addr & 0xFF));                                     // 发送存储低位地址
    Recv_Ack();                                                      // 接收应答
    I2C_Start();                                                     // 重新启动I2C
    I2C_SendData(AT24C04_ADDR | 0x01);                               // 发送器件地址和读命令
    Recv_Ack();                                                      // 接收应答

    for (i = 0; i < length; i++)
    {
        *(ReadData + i) = I2C_RecvData(); // 读取数据
        I2C_SendAck();                    // 主机应答
    }
    I2C_SendNAck(); // 主机非应答
    I2C_Stop();     // 停止I2C
}