#include <stdio.h>
#include <ctype.h>//isdigit
#include <stdlib.h>
#include "Calculater.h"
//Spos��������Spon����
int PrioriIn[7] = { -1, 3, 3, 5, 5, 1, 0 };        //���ȼ� ջ��(�����жϸ��ַ������ȼ�)��ջ�����ȼ���������ջ�ڵ����ȼ���һ��Ƚ� ��ջ��ͬ�ȷ������ȼ���
char tr[7] = { '#', '+', '-', '*', '/', '(', ')' };
int PrioriOut[7] = { -2, 2, 2, 4, 4, 6, 1 }; //���ȼ� ջ��

void InitSopn(SOPN* s)
{
	s->base = (int*)malloc(100 * sizeof(int));
	s->size = 100;
	s->top = 0;
}

void PushToSopn(SOPN* s, int e)//������ջ����ջ����ջ��ָ����һ��
{
	s->base[s->top] = e;
	s->top += 1;
}
void PopFromSopn(SOPN* s, int* e)
{
	s->top -= 1;
	*e = s->base[s->top];
}
int TopSopn(SOPN* s)//���ջ��������
{
	return s->base[(s->top) - 1];
}


void InitSops(SOPS* s)
{
	s->base = (char*)malloc(100 * sizeof(char));
	s->size = 100;
	s->top = 0;
	PushToSops(s, '#');   //
}

void PushToSops(SOPS* s, char a)
{
	s->base[s->top] = a;
	s->top += 1;
}
void PopFromSops(SOPS* s, char* e)
{
	(s->top) -= 1;
	*e = s->base[s->top];
}
char TopSops(SOPS* s)
{
	return s->base[(s->top) - 1];
}


int calculate1(int a, int b, char s)
{
	switch (s)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '/':
		return a / b;
	case '*':
		return a * b;
	}

}

int Compare(int a, int b)  //a�ڲ�  
{
	int c;
	c = a - b;
	if (c > 1) return 1;
	if (c == 0) return 0;
	if (c < 0) return -1;

}

int GetPrLocation(char e, char a[])
{
	int i;
	for (i = 0; i < 7; i++)
	{
		if (a[i] == e)
			return i;
	}

}

int compute()
{
	SOPN opn;
	SOPS ops;
	InitSopn(&opn);
	InitSops(&ops);
	int j, k;
	int num;
	num = 0;
	int a, b;
	char s;//chuzhan fuhao 
	char ch;
	char c;
	getchar();//�Ե������˵�����ʱ������ַ�����֤�ò��ֳ�������У��ⲿ�������Ҫ
	ch = getchar();
	while (ch != '#' || TopSops(&ops) != '#')
	{
		printf("\nch %c\n", ch);
		if (isdigit(ch))//isdigit�������ж�������ַ����Ƿ�Ϊ����
		{
			while (isdigit(ch))
			{
				num = num * 10 + atoi(&ch);//���ַ���ת��Ϊ���֣�������Գе���λ��
				ch = getchar();
			}
			PushToSopn(&opn, num);//������ջ
			printf("\nPush  %d\n", num);
			num = 0;
			//continue;
		}


		j = GetPrLocation(ch, tr);//������ȼ�����
		k = GetPrLocation(TopSops(&ops), tr);//��÷���ջ��ջ��Ԫ�ش���

		int re = Compare(PrioriIn[k], PrioriOut[j]);//�ȽϽ���ջ���ź�ջ���������ȼ�
		switch (re)
		{
		case -1://��ջ�������κβ�������ȡ�ַ���
			PushToSops(&ops, ch);
			printf("Push  %c\n", ch);
			ch = getchar(); break;
		case 0:
			
			PopFromSops(&ops, &c);//ȡ����ջ��ջ��������c���൱��һ�ԣ���
			printf("\nPop  %c\n", c);
			ch = getchar(); break;
		case 1:
			PopFromSopn(&opn, &b);
			PopFromSopn(&opn, &a);
			PopFromSops(&ops, &s);
			printf("\npop:  %d  %c  %d\n", a, s, b);
			printf("\t%d", b); printf("%c", s); printf("%d\n", a);
			PushToSopn(&opn, calculate1(a, b, s)); //������õ���ֵ��ջ
			printf("\nPush  %d\n", calculate1(a, b, s));
			continue;
		default:
			break;
		}

	}

	return TopSopn(&opn);//���ر��ʽ��ֵ���ս��

}
int Calculater()
{
	Print();
	return 0;
}
void Print()
{
	printf("���ʽ��ֵ����\n\n");
	printf(" ע������ջ��push������ջ��pop����ȡ���ַ���ch����\n");
	printf("��������ʽ�����ԡ�#����β��\n");
	printf("\n*ע��*������/���벻Ҫʡ�ԣ�\n");
	printf("\n�ñ��ʽ������Ϊ��%d\n", compute());
	printf("\n���ص����˵���\n");
}

