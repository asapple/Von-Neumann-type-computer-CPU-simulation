#pragma once
#include<stdio.h>
int readCmdFile(FILE* infile, char* memory,unsigned int head);
int getCmd(struct Register* Reg, char* memory);
int outInfo(struct Register Reg);
int end(char* memory);