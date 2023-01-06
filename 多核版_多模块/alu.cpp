#define _CRT_SECURE_NO_WARNINGS
#include "alu.h"
#include"Struct.h"
#include<stdio.h>
#include<Windows.h>
#include<time.h>
extern HANDLE hMutex_print;
extern HANDLE hMutex_sub[MEM_SIZE];
int state_trans(char* memory, struct Register* Reg, short s, short d)
{
    short k;
    switch (Reg->ir[0])
    {
    case 1:
        if (s == 0)
            Reg->ax[d] = numR(memory, *Reg, s);
        else if (s >= 5)
            Reg->ax[d] = numR(memory, *Reg, s);
        else
        {
            memory[Reg->ax[d] + (short)1] = numR(memory, *Reg, s) & 0x00ff;
            memory[Reg->ax[d]] = (numR(memory, *Reg, s) & 0xff00) / 256;
        }

        break;
    case 2:
        Reg->ax[d] += numR(memory, *Reg, s);
        break;
    case 3:
        Reg->ax[d] -= numR(memory, *Reg, s);
        break;
    case 4:
        Reg->ax[d] *= numR(memory, *Reg, s);
        break;
    case 5:
        Reg->ax[d] /= numR(memory, *Reg, s);
        break;
    case 6:
        Reg->ax[d] = Reg->ax[d] && numR(memory, *Reg, s);
        break;
    case 7:
        Reg->ax[d] = Reg->ax[d] || numR(memory, *Reg, s);
        break;
    case 8:
        if (s == 0)
            Reg->ax[d] = !Reg->ax[d];
        else
        {
            memory[Reg->ax[s]] = (!numR(memory, *Reg, s)) / 256;
            memory[Reg->ax[s] + (short)1] = (!numR(memory, *Reg, s)) % 256;
        }

        break;
    case 9:
        if (Reg->ax[d] == numR(memory, *Reg, s))
            Reg->flag = 0;
        if (Reg->ax[d] > numR(memory, *Reg, s))
            Reg->flag = 1;
        if (Reg->ax[d] < numR(memory, *Reg, s))
            Reg->flag = -1;

        break;
    case 10:
        if (Reg->ir[1] == 0)
        {
            Reg->ip += Reg->numReg;
            break;
        }
        if (Reg->ir[1] == 1 && Reg->flag == 0)
        {
            Reg->ip += Reg->numReg;
            break;
        }
        if (Reg->ir[1] == 2 && Reg->flag == 1)
        {
            Reg->ip += Reg->numReg;
            break;
        }
        if (Reg->ir[1] == 3 && Reg->flag == -1)
        {
            Reg->ip += Reg->numReg;
            break;
        }
        Reg->ip += 4;
        break;
    case 11:
        printf("in:\n");
        scanf("%hd", &k);
        Reg->ax[d] = k;
        break;
    case 12:
        printf("id = %hd    out: %hd\n", Reg->id, Reg->ax[d]);
        break;
    case 13:    //����������ɫ���֣�Ϊ�ڴ��ַ�����󻥳����������ס��������ָ�����ڴ档������������ռ�ã���һֱ�ȴ���
        WaitForSingleObject(hMutex_sub[Reg->numReg], INFINITE);
        break;
    case 14:    //����������ɫ���֣�Ϊ�ڴ��ַ���ͷŻ�������ͷŵ���ס��������ָ�����ڴ�Ļ����������һ��ָ���Ӧ��
        ReleaseMutex(hMutex_sub[Reg->numReg]);
        break;
    case 15:    //��������������ɫ���֣����롣
        Sleep(Reg->numReg);
        break;
    default:
        break;
    }
    return 0;
}