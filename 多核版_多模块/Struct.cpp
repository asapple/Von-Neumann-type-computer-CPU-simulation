#include "Struct.h"
short byte2short(char* byte) {
    short value = 0;
    int i;
    for (i = 0; i < 2; i++) {
        value <<= 8;
        value |= (byte[i] & 0xff);
        /*ΪʲôҪ��0xff����&��������Ϊ����Ҫ��֤���8λ��һ�µģ�����λ��Ҫ��0���������ܱ�֤���ݵ�һ���ԡ�*/
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