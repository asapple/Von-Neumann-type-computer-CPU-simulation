#pragma once
#define CMD_LEN 32  //指令字符长度
#define MEM_SIZE 32768 //主存规模，字节数
#define REG_LEN 2		//寄存器字节长度
#define CODE_GROUP 4	//代码输出的字节组长度
#define DATA_GROUP 2	 //数据输出的字节组长度
#define OUT_LINES 16	//输出行数
#define CODES_LINE 8	 //代码每行输出个数
#define DATAS_LINE 16	//数据每行输出个数
#define CODE_HEAD 256   //第二段代码开始的地址
struct Register
{
    /* data */
    unsigned short ip;
    short flag;
    char ir[REG_LEN];
    short ax[9];
    short numReg;//立即数寄存器

    unsigned short id;//存储线程id
};
short byte2short(char* byte);
int byte2int(char* byte);
short numR(char* memory, struct Register Reg, short n);