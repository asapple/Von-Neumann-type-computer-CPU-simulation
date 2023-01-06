#include "control.h"
#include"Struct.h"
int control(char* memory, struct Register* Reg, short* s, short* d)
{
    *s = (Reg->ir[1] & 0x0f) % 16;
    *d = (Reg->ir[1] & 0xf0) / 16;
    return 0;
}
