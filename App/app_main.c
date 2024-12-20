#include "app_main.h"

char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#"; // 可以自定义

void app_main()
{

    // 扩展寄存器(XFR)访问使能
    P_SW2 |= 0x80;
    usb_init();
    Timer0_Init();
    EA = 1;
    P2M0 = 0x00;
    P2M1 = 0x00;
    while (DeviceState != DEVSTATE_CONFIGURED)
    {
    }

    while (1)
    {

        P20 = ~P20;
        printf("HX711 = %d", 23u);
        DelayTick(1000);
    }
}

BOOL usb_OUT_callback()
{
    USB_SendData("ok", 2);
    return 1;
}