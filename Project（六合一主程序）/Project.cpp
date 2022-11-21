#include "Sort.h"
#include<stdlib.h>
#include<stdio.h>
#include <time.h>
#include"Address.h"
#include"Calculater.h"
#include"AVLTrees.h"
#include"MTree.h"
#include"HFM.h"
void menu0();
int main()
{
	int a=1;
	while (a) {
		system("cls");
		menu0();
		printf("请选择要使用的功能编号：");
		switch (getchar()) {
		case '1':
			system("cls");
			Sort();
			system("pause");
				break;
		case '2':
			system("cls");
			Address_s();
			system("pause");
			break;
		case '3':
			system("cls");
			Calculater();
			system("pause");
			break;
		case '4':
			system("cls");
			AVLtree();
			system("pause");
			break;
		case '5':
			system("cls");
			Mtree();
			system("pause");
			break;
		case '6':
			system("cls");
			Hfm();
			system("pause");
			break;
		case '0':
			
			a = 0;
			break;
		}
	}
	return 0;
}
void menu0() {
	printf("************************************************************\n");
	printf("*                       数据结构课设                       *\n");
	printf("************************************************************\n");
	printf("*                         功能列表                         *\n");
	printf("************************************************************\n");
	printf("*     1.内部排序算法性能分析                               *\n");
	printf("*     2.基于单链表的班级通讯录                             *\n");
	printf("*     3.表达式求解问题                                     *\n");
	printf("*     4.平衡二叉树及其操作实现                             *\n");
	printf("*     5.最小生成树                                         *\n");
	printf("*     6.哈夫曼编码/译码器                                  *\n");
	printf("*     0.退出本程序(!退出时自动保存）                       *\n");
	printf("************************************************************\n");
}