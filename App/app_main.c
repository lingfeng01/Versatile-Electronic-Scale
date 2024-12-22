#include "app_main.h"

char *USER_DEVICEDESC = NULL;
char *USER_PRODUCTDESC = NULL;
char *USER_STCISPCMD = "@STCISP#"; // 可以自定义
char LCDstr[15];

uint weight = 0;            // 显示重量
uint weight_tare = 0;       // 皮重量
uint weight_tare_after = 0; // 去皮后重量
uint weight_count = 0;      // 计数重量
ulong weight_base = 0;      // 基准重量
ulong weight_neg_t = 0;     // 重量负值时间

uchar Key_cnt = 0;   // 按键消抖计数值
BOOL Key1_event = 0; // 按键事件
BOOL Key2_event = 0; // 按键事件
BOOL Key3_event = 0; // 按键事件
BOOL Key4_event = 0; // 按键事件

uint Item_Count = 0; // 计数

uint Page = 1; // 页面

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

/**
 * @brief 任务一
 * 显示个人信息在LCD1602屏幕上
 *
 * 该函数LCD1602屏幕上显示个人信息。
 * 首先显示学号“20235603023185”，然后延迟500毫秒。
 * 接着显示姓名“LinZhiKai”，再延迟2000毫秒。
 * 最后清除屏幕显示。
 */
void Display_PersonInfo()
{
    sprintf(LCDstr, "%s", "20235603023185");
    LCD1602_Display_String(1, 2, LCDstr);
    DelayTick(500);
    sprintf(LCDstr, "%s", "LinZhiKai");
    LCD1602_Display_String(2, 4, LCDstr);
    DelayTick(2000);
    LCD1602_Wr_Command(0x01);
}
/**
 * @brief 任务三
 * 显示重量信息在LCD1602屏幕上
 *
 * 该函数LCD1602屏幕上显示重量信息。
 * 首先显示标志和单位“Weight :”，“g”。
 * 接着显示重量值“weight”，延迟500毫秒。
 * 如果重量值为0，则清除重量值。
 */
void LCD_Display_Weight()
{

    if (weight_neg_t + Weight_poll_time < Get_Tikc())
    {
        weight_neg_t = Get_Tikc();
        LCD1602_Display_String(1, 1, "Pi :");                            // 显示标志
        LCD1602_Display_String(1, 10, "g");                              // 显示单位
        sprintf(LCDstr, "%4d", weight_tare);                             // 格式化字符串
        LCD1602_Display_String(1, 5, LCDstr);                            // LCD显示去皮重量值
        LCD1602_Display_String(2, 1, "Weight :");                        // 显示标志
        LCD1602_Display_String(2, 15, "g");                              // 显示单位
        weight_tare_after = read_weight(400, weight_base) - weight_tare; // 读取重量
        printf("weight_base = %lu\n", weight_base);                      // Log打印基准重量
        printf("weight = %d\n", weight_tare_after);                      // Log打印重量
        sprintf(LCDstr, "%4d", weight_tare_after);                       // 格式化字符串
        LCD1602_Display_String(2, 10, LCDstr);                           // LCD显示重量值
        if (weight_tare_after <= 0)
        {
            LCD1602_Display_String(2, 10, "   0"); // 清除重量值
        }
    }
}
/**
 * @brief 任务三
 * 去皮
 * 该函数去皮。
 */
void tare_weight()
{

    if (Key3_event == 1 && Page == 1)
    {
        weight_tare = read_weight(400, weight_base); // 读取重量
        printf("weight_tare = %d\n", weight_tare);   // Log打印去皮重量
    }
}

void Count_weight()
{
    if (Key1_event == 1 && Page == 2)
    {
        weight_count = weight;
    }
}

/**
 * @brief 任务四
 * 显示计数信息在LCD1602屏幕上
 *
 * 该函数LCD1602屏幕上显示计数信息。
 * 首先显示标志“Count :”。
 * 接着显示计数值“Item_Count”。
 * 如果计数值大于100，则计数值为100。
 * 最后显示单位“g”。
 */
void LCD_Display_Count()
{
    LCD1602_Display_String(2, 1, "Weight :"); // 显示标志
    LCD1602_Display_String(2, 15, "g");       // 显示单位
    LCD1602_Display_String(1, 1, "Count :");  // 显示标志
    LCD1602_Display_String(1, 12, "x");       // 显示标志
    LCD1602_Display_String(1, 16, "g");       // 显示单位

    weight = read_weight(400, weight_base); // 读取重量
    sprintf(LCDstr, "%4d", weight);         // 格式化字符串
    LCD1602_Display_String(2, 10, LCDstr);  // LCD显示重量值
    if (weight <= 0)
    {
        LCD1602_Display_String(2, 10, "   0"); // 清除重量值
    }
    sprintf(LCDstr, "%3d", weight_count);  // 格式化字符串
    LCD1602_Display_String(1, 13, LCDstr); // 显示个重量值
    if (weight_count == 0)
    {
        LCD1602_Display_String(1, 13, "  0"); // 清除重量值
    }
    if (weight_count == 0) // 判断计数值是否为0
    {
        Item_Count = 0;
    }
    else
    {
        Item_Count = weight / weight_count; // 计数
    }
    printf("weight = %d\n", weight);             // Log打印重量值
    printf("weight_count = %d\n", weight_count); // Log打印计数重量值
    printf("Item_Count = %d\n", Item_Count);     // Log打印计数值
    if (Item_Count >= 100)
    {
        Item_Count = 100;
    }
    sprintf(LCDstr, "%3d", Item_Count);   // 格式化字符串
    LCD1602_Display_String(1, 8, LCDstr); // LCD显示计数值
    if (Item_Count == 0)
    {
        LCD1602_Display_String(1, 8, "  0"); // 清除计数值
    }
}

void Page_Switching()
{
    if (Key4_event == 1)
    {
        LCD1602_Wr_Command(0x01);
        Page++;
        if (Page > 2)
        {
            Page = 1;
        }
    }
}
void app_main()
{
    // 扩展寄存器(XFR)访问使能
    P_SW2 |= 0x80;
    IO_Init(); // 初始化I/O端口

    usb_init();    // USB初始化
    Timer0_Init(); // 定时器0初始化
    EA = 1;        // 开启总中断

    while (DeviceState != DEVSTATE_CONFIGURED) // 等待USB配置完成
    {
    }
    LCD1602_Init();                   // 初始化LCD1602
    Display_PersonInfo();             // 显示个人信息
    weight_base = read_weight_base(); // 读取基准重量
    while (1)
    {
        Key1_event = keyScan(&Key_cnt, Key1); // 按键扫描
        Key2_event = keyScan(&Key_cnt, Key2); // 按键扫描
        Key3_event = keyScan(&Key_cnt, Key3); // 按键扫描
        Key4_event = keyScan(&Key_cnt, Key4); // 按键扫描

        Page_Switching(); // 页面切换
        switch (Page)
        {
        case 1:
            tare_weight();        // 去皮
            LCD_Display_Weight(); // 显示重量
            break;
        case 2:
            Count_weight();
            LCD_Display_Count(); // 显示计数
            break;

        default:
            LCD1602_Wr_Command(0x01);
            break;
        }
        P20 = ~P20;
    }
}

BOOL usb_OUT_callback()
{
    // 接收字节数保存在OutNumber中
    // 接收数据保存在UsbOutBuffer缓冲区
    USB_SendData("ok", 2);
    return 1;
}