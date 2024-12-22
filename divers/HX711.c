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

uint16_t read_weight(uint16_t k, uint32_t b)
{
    uint32_t w;
    uint16_t r;
    w = ReadCount();
    if (w < b)
    {
        w = b;
    }
    r = (w - b) / k;
    return r;
}

ulong read_weight_base()
{
    uint i;
    ulong w = 0;
    ulong weight_base = 0;
    for (i = 0; i < 4; i++)
    {
        w = ReadCount();
        weight_base += w;
        DelayTick(100);
    }
    weight_base = weight_base / 4;
    return weight_base;
}