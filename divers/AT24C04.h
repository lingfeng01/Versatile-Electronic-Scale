#ifndef __AT24C04_H__
#define __AT24C04_H__
#include <stc8h.h>
#include "./divers/command.h"
#include "systick.h"
#include "I2C.h"

// AT24C04地址
#define Address 0x0A0

void AT24C04_Write_Page(uchar addr, uchar Data[], uchar H_pageaddr, uchar L_pageaddr);

#endif