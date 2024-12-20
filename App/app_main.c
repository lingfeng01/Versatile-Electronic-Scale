#include "app_main.h"

char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#"; // 可以自定义
char LCDstr[] = {"LZK"};
void app_main()
{

    // 扩展寄存器(XFR)访问使能
    P_SW2 |= 0x80;
    usb_init();
    Timer0_Init();
    EA = 1;
    P0M0 = 0x00;
    P0M1 = 0x00;
    P2M0 = 0x00;
    P2M1 = 0x00;

    while (DeviceState != DEVSTATE_CONFIGURED)
    {
    }
    LCD1602_Init();
    LCD1602_Display_String(1, 5, LCDstr);
    while (1)
    {

        P20 = ~P20;
        printf("HX711 = %d\n", 23u);
        DelayTick(1000);
        printf("LCDDATA = %s\n", LCDstr);
    }
}

BOOL usb_OUT_callback()
{
    // 接收字节数保存在OutNumber中
    // 接收数据保存在UsbOutBuffer缓冲区
    USB_SendData("ok", 2);
    return 1;
}