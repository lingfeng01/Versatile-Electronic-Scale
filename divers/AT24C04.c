#include "AT24C04.h"

void AT24C04_Write_Page(uchar addr, uchar Data[], uchar H_pageaddr, uchar L_pageaddr)
{
    uint i;
    uchar addrs;
    uint Data_size = sizeof(Data);
    if (Data_size > 15)
    {
        Data_size = 15;
    }

    addrs = addr << 1;
    I2C_Start();
    I2C_SendData(addrs);
    Recv_Ack();
    I2C_SendData(H_pageaddr);
    Recv_Ack();
    I2C_SendData(L_pageaddr);
    Recv_Ack();
    for (i = 0; i < Data_size; i++)
    {
        I2C_SendData(Data[i]);
        Recv_Ack();
    }
    I2C_Stop();
}
