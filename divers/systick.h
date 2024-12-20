#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <stc8h.h>
#include "./divers/command.h"

void Timer0_Init(void);
ulong Get_Tikc(void);
void DelayTick(uint tk);

#endif