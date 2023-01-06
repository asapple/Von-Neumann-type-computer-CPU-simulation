#include "Struct.h"
short byte2short(char* byte) {
    short value = 0;
    int i;
    for (i = 0; i < 2; i++) {
        value <<= 8;
        value |= (byte[i] & 0xff);
        /*为什么要和0xff进行&操作？因为我们要保证最后8位是一致的，更高位都要置0，这样才能保证数据的一致性。*/
    }
    return (value);
}
int byte2int(char* byte) {
    int value = 0;
    int i;
    for (i = 0; i < 4; i++) {
        value <<= 8;
        value |= (byte[i] & 0xff);
    }
    return (value);
}
short numR(char* memory, struct Register Reg, short n)
{
    if (n == 0)
        return Reg.numReg;
    if (n < 5)
        return Reg.ax[n];
    return byte2short(&memory[Reg.ax[n]]);
}