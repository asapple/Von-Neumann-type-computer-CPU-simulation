#include "io.h"
#include"Struct.h"
#include <stdio.h>
#include<Windows.h>
extern HANDLE hMutex_print;
int readCmdFile(FILE* infile, char* memory,unsigned int head)
{
    char buffer[35]; int buffLen = 34;
    int k = -1 + head;
    while (fgets(buffer, buffLen, infile) != NULL)
    {
        int i;
        for (i = 0; i < CMD_LEN; i++)
        {
            if (i % 8 == 0)
                k++;
            memory[k] = (memory[k] << 1) + (buffer[i] - '0');
        }
    }
    return 0;
}
int getCmd(struct Register* Reg, char* memory)
{
    Reg->ir[0] = memory[Reg->ip];
    Reg->ir[1] = memory[Reg->ip + (short)1];
    Reg->numReg = byte2short(&memory[Reg->ip + (short)2]);
    return 0;
}
int outInfo(struct Register Reg)
{
    WaitForSingleObject(hMutex_print, INFINITE);
    printf("id = %hd\n", Reg.id);
    printf("ip = %hd\n", Reg.ip);
    printf("flag = %hd\n", Reg.flag);
    printf("ir = %hd\n", byte2short(Reg.ir));
    printf("ax1 = %hd ax2 = %hd ax3 = %hd ax4 = %hd\n", Reg.ax[1], Reg.ax[2], Reg.ax[3], Reg.ax[4]);
    printf("ax5 = %hd ax6 = %hd ax7 = %hd ax8 = %hd\n", Reg.ax[5], Reg.ax[6], Reg.ax[7], Reg.ax[8]);
    ReleaseMutex(hMutex_print);
    return 0;
}
int end(char* memory)
{
    printf("\ncodeSegment :\n");
    for (int i = 0; i < 512; i += 4)
    {
        int num = 0;
        num = byte2int(&memory[i]);
        printf("%d", num);
        if (i % 32 == 28)
            printf("\n");
        else
            printf(" ");
    }
    printf("\ndataSegment :\n");
    for (int i = 16384; i < 16896; i += 2)
    {
        short num = 0;
        num = byte2short(&memory[i]);
        printf("%hd", num);
        if (i % 32 == 30)
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
    return 0;
}