#include "HX711.h"

ulong ReadCount(void)
{
    ulong Count;
    uchar i;
    ADSK = 0;
    Count = 0;
    while (ADDO)
    {
    }
    for (i = 0; i < 24; i++)
    {
        ADSK = 1;
        Count = Count << 1;
        ADSK = 0;
        if (ADDO)
        {
            Count++;
        }
    }

    ADSK = 1;
    Count = Count ^ 0x800000;
    ADSK = 0;
    return (Count);
}