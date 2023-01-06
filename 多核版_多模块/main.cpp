#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<windows.h>
#include<string>
#include<time.h>
#include"Struct.h"
#include"io.h"
#include"alu.h"
#include"control.h"
void init_memory(char* memory);
void init_Reg(struct Register* Reg);

HANDLE hMutex_print;//��֤����ָ��ļĴ�����Ϣ����������ģ����ܱ����������Ϣ�ָ�
HANDLE hMutex_sub[MEM_SIZE];//������ס��������ָ�����ڴ档������������ռ�ã���һֱ�ȴ���

struct lpPara   //���ݸ��̵߳�32λ��ָ��
{
    char* memory;   //�ڴ濪ʼ��ַ
    unsigned short ip;  //pc
    unsigned short id;  //id
    unsigned short head;    //���������ַ
};
DWORD WINAPI thread(LPVOID lpParameter)
{
    
    struct lpPara* lt = (struct lpPara*)lpParameter;
    FILE* infile;
    if (lt->id == 0)
        infile = fopen("dict1.txt", "r");
    else
        infile = fopen("dict2.txt", "r");

    readCmdFile(infile, lt->memory, lt->head);/*��ȡָ�������ļ�����������*/
    struct Register Reg;
    init_Reg(&Reg);
    Reg.ip = lt->ip;
    Reg.id = lt->id;

    getCmd(&Reg, lt->memory); /*��ȡָ��*/
    int number = 0;
    while (Reg.ir[0] != 0)
    {
        short s, d;
        control(lt->memory, &Reg, &s, &d); /*����������ָ��*/
        state_trans(lt->memory, &Reg, s, d); /*�Զ�����ִ��ָ��*/
        if (Reg.ir[0] != 10)
            Reg.ip += 4;
        outInfo(Reg);     /*������Ĵ���״̬*/

        getCmd(&Reg, lt->memory); /*��ȡָ��*/
    }
    Reg.ip += 4;
    outInfo(Reg);     /*������Ĵ���״̬*/
    return 0;
}

int main(void)
{
    hMutex_print = CreateMutex(NULL, FALSE, NULL);
    for (int i = 0; i < MEM_SIZE; i++)
        hMutex_sub[i] = CreateMutex(NULL, FALSE, NULL);

    char memory[MEM_SIZE];
    init_memory(memory); /*�����ʼ��*/
    memory[16385] = 10;

    freopen("myoutput.txt","w",stdout);

    struct lpPara lpPara1;
    lpPara1.memory = memory;
    lpPara1.id = 1;
    lpPara1.ip = 0;
    lpPara1.head = 0;
    HANDLE hthread1;//�߳�һ
    hthread1 = CreateThread(NULL, 0, thread, &lpPara1, 0, NULL);

    struct lpPara lpPara2;
    lpPara2.memory = memory;
    lpPara2.id = 2;
    lpPara2.ip = 256;
    lpPara2.head = CODE_HEAD;
    HANDLE hthread2;
    hthread2 = CreateThread(NULL, 0, thread, &lpPara2, 0, NULL);
    WaitForSingleObject(hthread1, INFINITE);
    WaitForSingleObject(hthread2, INFINITE);
    end(memory); /*��������, �������״̬*/
}

void init_memory(char* memory)
{
    for (int i = 0; i < 32768; i++)    memory[i] = 0;
    return;
}
void init_Reg(struct Register* Reg)
{
    Reg->ip = 0;    Reg->flag = 0;
    for (int i = 0; i < 2; i++)    Reg->ir[i] = 0;
    for (int i = 1; i <= 8; i++)    Reg->ax[i] = 0;
}