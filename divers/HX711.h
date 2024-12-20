#ifndef __HX711_H__
#define __HX711_H__

#include <stc8h.h>

#include "app_main.h"
#include "systick.h"
#include "./divers/command.h"

sbit ADDO = P1 ^ 1;
sbit ADSK = P4 ^ 7;

ulong ReadCount(void);
#endif