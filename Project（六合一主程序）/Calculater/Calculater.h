#pragma once

//pop取出
//栈 数字
typedef struct
{
	int* base;
	int top;
	int size;
}SOPN;

//栈 操作符
typedef struct
{
	char* base;
	int top;
	int size;
}SOPS;

void InitSopn(SOPN* s);
void PushToSopn(SOPN* s, int e);
void PopFromSopn(SOPN* s, int* e);
int TopSopn(SOPN* s);
void InitSops(SOPS* s);
void PushToSops(SOPS* s, char e);
void PopFromSops(SOPS* s, char* e);
char TopSops(SOPS* s);
int Compare(int a, int b); //优先级比较 > 1; < -1 ;= 0
int calculate1(int a, int b, char e);
int GetPrLocation(char e, char sg[]);
int compute();
int Calculater();//主程序
void Print();
