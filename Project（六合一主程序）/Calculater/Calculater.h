#pragma once

//popȡ��
//ջ ����
typedef struct
{
	int* base;
	int top;
	int size;
}SOPN;

//ջ ������
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
int Compare(int a, int b); //���ȼ��Ƚ� > 1; < -1 ;= 0
int calculate1(int a, int b, char e);
int GetPrLocation(char e, char sg[]);
int compute();
int Calculater();//������
void Print();
