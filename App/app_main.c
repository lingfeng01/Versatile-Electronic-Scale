#include "app_main.h"

char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#"; // 可以自定义
char LCDstr[15];
uint weight = 0;
ulong weight_base = 0;

/**
 * @brief 初始化I/O端口，将模式寄存器设置为0。
 *
 * 此函数将所有模式寄存器（P0M0, P0M1, P1M0, P1M1, P2M0, P2M1,
 * P4M0, P4M1, P5M0, P5M1, P6M0, P6M1, P7M0, P7M1）设置为0，
 * 将所有引脚配置为通用I/O，无特殊功能。
 */
void IO_Init()
{
    P0M0 = 0x00;
    P0M1 = 0x00;
    P1M0 = 0x00;
    P1M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;
    P4M0 = 0x00;
    P4M1 = 0x00;
    P5M0 = 0x00;
    P5M1 = 0x00;
    P6M0 = 0x00;
    P6M1 = 0x00;
    P7M0 = 0x00;
    P7M1 = 0x00;
}

void app_main()
{
    // 扩展寄存器(XFR)访问使能
    P_SW2 |= 0x80;
    IO_Init();

    usb_init();
    Timer0_Init();
    EA = 1;

    while (DeviceState != DEVSTATE_CONFIGURED)
    {
    }
    LCD1602_Init();
    sprintf(LCDstr, "%s", "LinZhiKai");
    LCD1602_Display_String(1, 1, LCDstr);
    DelayTick(500);
    sprintf(LCDstr, "%s", "023185");
    LCD1602_Display_String(2, 1, LCDstr);
    DelayTick(1000);
    LCD1602_Wr_Command(0x01);
    weight_base = read_weight_base();
    while (1)
    {
        P20 = ~P20;

        weight = read_weight(400, weight_base);

        sprintf(LCDstr, "%d", weight);
        printf("weight_base = %lu\n", weight_base);
        printf("weight = %d\n", weight);
        LCD1602_Display_String(1, 1, LCDstr);
        DelayTick(1000);
        LCD1602_Wr_Command(0x01);
    }
}

BOOL usb_OUT_callback()
{
    // 接收字节数保存在OutNumber中
    // 接收数据保存在UsbOutBuffer缓冲区
    USB_SendData("ok", 2);
    return 1;
}