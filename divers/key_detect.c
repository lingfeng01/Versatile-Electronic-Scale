#include "key_detect.h"

/**
 * @brief 按键消抖取边缘函数，该函数需要循环调用
 *
 * @param key_cnt 按键消抖计数值，注意这是一个指针，可以使用‘&’进行取地址
 * 					为每个按键声明一个变量并赋初值为0，供本函数操作，不要在其他地方修改该变量
 * @param v 按键是否按下，按下输入1，松开输入0
 * @return bit 返回按键事件，只在按键刚按下的时候返回一次1，其他时候返回0
 */
/**
 * @brief 按键消抖取边缘函数，该函数需要循环调用
 *
 * @param key_cnt 按键消抖计数值，注意这是一个指针，可以使用‘&’进行取地址
 * 					为每个按键声明一个变量并赋初值为0，供本函数操作，不要在其他地方修改该变量
 * @param v 按键是否按下，按下输入1，松开输入0
 * @return bit 返回按键事件，只在按键刚按下的时候返回一次1，其他时候返回0
 */
BOOL keyScan(uint8_t *key_cnt, uint8_t v)
{
    if (v == 0)
        *key_cnt = 0;
    else
        *key_cnt = (*key_cnt >= KEY_TH) ? KEY_TH : *key_cnt + 1;

    if (*key_cnt == (KEY_TH - 1))
        return 1;
    else
        return 0;
}
