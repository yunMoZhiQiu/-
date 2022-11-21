#include <stdio.h>
#include <ctype.h>//isdigit
#include <stdlib.h>
#include "Calculater.h"
//Spos操作符，Spon数字
int PrioriIn[7] = { -1, 3, 3, 5, 5, 1, 0 };        //优先级 栈内(用于判断各种符号优先级)，栈内优先级，符号在栈内的优先级，一般比将 入栈的同等符号优先级高
char tr[7] = { '#', '+', '-', '*', '/', '(', ')' };
int PrioriOut[7] = { -2, 2, 2, 4, 4, 6, 1 }; //优先级 栈外

void InitSopn(SOPN* s)
{
	s->base = (int*)malloc(100 * sizeof(int));
	s->size = 100;
	s->top = 0;
}

void PushToSopn(SOPN* s, int e)//数字入栈，入栈顶，栈顶指向下一个
{
	s->base[s->top] = e;
	s->top += 1;
}
void PopFromSopn(SOPN* s, int* e)
{
	s->top -= 1;
	*e = s->base[s->top];
}
int TopSopn(SOPN* s)//获得栈顶操作符
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

int Compare(int a, int b)  //a内部  
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
	getchar();//吃掉从主菜单过来时输入的字符，保证该部分程序的运行，这部分真的重要
	ch = getchar();
	while (ch != '#' || TopSops(&ops) != '#')
	{
		printf("\nch %c\n", ch);
		if (isdigit(ch))//isdigit函数，判断输入的字符串是否为数字
		{
			while (isdigit(ch))
			{
				num = num * 10 + atoi(&ch);//把字符串转化为数字，这里可以承担多位数
				ch = getchar();
			}
			PushToSopn(&opn, num);//数字入栈
			printf("\nPush  %d\n", num);
			num = 0;
			//continue;
		}


		j = GetPrLocation(ch, tr);//获得优先级代号
		k = GetPrLocation(TopSops(&ops), tr);//获得符号栈中栈顶元素代号

		int re = Compare(PrioriIn[k], PrioriOut[j]);//比较将入栈符号和栈顶符号优先级
		switch (re)
		{
		case -1://入栈，不做任何操作，再取字符串
			PushToSops(&ops, ch);
			printf("Push  %c\n", ch);
			ch = getchar(); break;
		case 0:
			
			PopFromSops(&ops, &c);//取符号栈的栈顶符号于c，相当于一对（）
			printf("\nPop  %c\n", c);
			ch = getchar(); break;
		case 1:
			PopFromSopn(&opn, &b);
			PopFromSopn(&opn, &a);
			PopFromSops(&ops, &s);
			printf("\npop:  %d  %c  %d\n", a, s, b);
			printf("\t%d", b); printf("%c", s); printf("%d\n", a);
			PushToSopn(&opn, calculate1(a, b, s)); //计算后获得的数值入栈
			printf("\nPush  %d\n", calculate1(a, b, s));
			continue;
		default:
			break;
		}

	}

	return TopSopn(&opn);//返回表达式求值最终结果

}
int Calculater()
{
	Print();
	return 0;
}
void Print()
{
	printf("表达式求值部分\n\n");
	printf(" 注：（入栈“push”，出栈“pop”读取的字符“ch”）\n");
	printf("请输入表达式（请以“#”结尾）\n");
	printf("\n*注“*”，“/”请不要省略；\n");
	printf("\n该表达式计算结果为：%d\n", compute());
	printf("\n将回到主菜单；\n");
}

