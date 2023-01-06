#pragma once
#define CMD_LEN 32  //ָ���ַ�����
#define MEM_SIZE 32768 //�����ģ���ֽ���
#define REG_LEN 2		//�Ĵ����ֽڳ���
#define CODE_GROUP 4	//����������ֽ��鳤��
#define DATA_GROUP 2	 //����������ֽ��鳤��
#define OUT_LINES 16	//�������
#define CODES_LINE 8	 //����ÿ���������
#define DATAS_LINE 16	//����ÿ���������
#define CODE_HEAD 256   //�ڶ��δ��뿪ʼ�ĵ�ַ
struct Register
{
    /* data */
    unsigned short ip;
    short flag;
    char ir[REG_LEN];
    short ax[9];
    short numReg;//�������Ĵ���

    unsigned short id;//�洢�߳�id
};
short byte2short(char* byte);
int byte2int(char* byte);
short numR(char* memory, struct Register Reg, short n);