#ifndef __KEY_DETECT_H__
#define __KEY_DETECT_H__
#include <stc8h.h>
#include "./divers/command.h"

#define KEY_TH 10 /// 按键消抖计数阈值

BOOL keyScan(uint8_t *key_cnt, uint8_t v);

#endif