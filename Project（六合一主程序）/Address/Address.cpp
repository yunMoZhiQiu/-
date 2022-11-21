#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"address.h"



void menu2() {
	printf("************************************************************\n");
	printf("*                       班级通讯录                         *\n");
	printf("************************************************************\n");
	printf("*                         功能列表                         *\n");
	printf("************************************************************\n");
	printf("*     1.读取文件(!请先读取文件!)                           *\n");
	printf("*     2.展示当前通讯录信息                                 *\n");
	printf("*     3.按姓名搜索                                         *\n");
	printf("*     4.按序号搜索                                         *\n");
	printf("*     5.顺序后添加                                         *\n");
	printf("*     6.位置前添加                                         *\n");
	printf("*     7.姓名前添加                                         *\n");
	printf("*     8.删除指定序号信息                                   *\n");
	printf("*     9.删除指定姓名信息                                   *\n");
	printf("*     0.退出本程序(!退出时自动保存）                       *\n");
	printf("************************************************************\n");
}

int InputFile(LinkList L)
{
	int i;
	LinkList p, q;
	FILE* fp;
	char str[35];//第一排内容
	p = L;
	q = (LNode*)malloc(sizeof(LNode));

	if (fopen_s(&fp, "D:\\stuinfo.txt", "r+") != 0) return -1;//判断读取成功
	fgets(str, sizeof(str) - 1, fp);//读取第一排内容
	for (i = 0; i < 12; i++) {
		fscanf_s(fp, "%s%s%s%s%s", &q->data.id, 8, &q->data.name, 20, &q->data.sex, 5, &q->data.dorm, 5, &q->data.tel, 12);
		p->next = q;
		p = p->next;
		p->next = NULL;
		q = (LNode*)malloc(sizeof(LNode));
	}
	fclose(fp);
	return 0;
}



int OutputFile(LinkList L)
{
	FILE* fp;
	LinkList p = L;
	printf("0");
	if (ListEmpty(p) != 0)
		return -1;
	if (fopen_s(&fp, "D:\\stuinfo.txt", "w") != 0) {
		printf("文件读取失败");
		return -2;
	}
	fprintf(fp, "学号 \t姓名 \t性别 \t宿舍 \t电话号码\n");
	p = p->next;
	while (p->next != NULL) {
		fprintf(fp, "%s \t%s \t%s \t%s \t%s\n", p->data.id, p->data.name, p->data.sex, p->data.dorm, p->data.tel);
		p = p->next;
	}
	fprintf(fp, "%s \t%s \t%s \t%s \t%s", p->data.id, p->data.name, p->data.sex, p->data.dorm, p->data.tel);
	fclose(fp);
	return 0;
}



int LinkListInit(LinkList* L)
{
	(*L) = (LNode*)malloc(sizeof(LNode));
	if ((*L) == NULL) {
		printf("空间分配失败");//判断内存收分配成功
		return -1;
	}
	(*L)->next = NULL;
	return 0;
}



int DestroyList(LinkList* L) {
	LinkList p = NULL;
	if (ListEmpty(*L) != 0)
		return -1;
	while (*L) {
		p = (*L);
		*L = (*L)->next;
		free(p);
	}
	return 0;
}



int Traverse1(LinkList L) {
	LinkList p = L->next;
	int c;
	c = ListEmpty(p);
	if (c != 0)
		return -1;
	printf("学号 \t姓名 \t性别 \t宿舍 \t电话号码\n");
	while (p != NULL) {
		printf("%s \t%s \t%s \t%s \t%s\n", p->data.id, p->data.name, p->data.sex, p->data.dorm, p->data.tel);
		p = p->next;
	}
	return 0;
}



int numSearch(LinkList L) {
	int i = 0;
	int n = 0;
	int c;
	printf("请输入要搜索的序号：");
	scanf_s("%d", &n);
	LinkList p = L;
	c = ListEmpty(p);
	if (c != 0)
		return -1;
	while (i != n && p != NULL) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		printf("输入的序号已超出\n");
		return -1;
	}
	printf("学号 \t姓名 \t性别 \t宿舍 \t电话号码\n");
	printf("%s \t%s \t%s \t%s \t%s\n", p->data.id, p->data.name, p->data.sex, p->data.dorm, p->data.tel);
	return 0;
}


int NameSearch(LinkList L) {
	int c;
	LinkList q, p = (LNode*)malloc(sizeof(LNode));
	q = L->next;
	printf("请输入想搜索的姓名：");
	c = ListEmpty(q);
	if (c != 0)
		return -1;
	scanf_s("%s", &p->data.name, 20);
	while (q != NULL && strcmp(q->data.name, p->data.name) != 0) {
		q = q->next;
	}
	if (q == NULL) {
		printf("通讯录中没有该姓名!\n");
		return -2;
	}
	printf("学号 \t姓名 \t性别 \t宿舍 \t电话号码\n");
	printf("%s \t%s \t%s \t%s \t%s\n", q->data.id, q->data.name, q->data.sex, q->data.dorm, q->data.tel);
	return 0;
}



int ListEmpty(LinkList L) {
	if (L == NULL) return -1;//0为空表
	else if (L->next != NULL) return 0;//1为非空表
	return 0;
}



int AddInfo(LinkList* L) {
	int c;
	LinkList p, q;
	q = (*L)->next;
	printf("请输入要加入的信息（包括：学号 姓名 性别(f/m) 寝室 电话号码):\n");
	c = ListEmpty(q);
	if (c != 0)
		return -1;
	while (q->next != NULL) {
		q = q->next;
	}
	p = (LNode*)malloc(sizeof(LNode));
	scanf_s("%s%s%s%s%s", &p->data.id, 8, &p->data.name, 20, &p->data.sex, 5, &p->data.dorm, 5, &p->data.tel, 12);
	p->next = NULL;
	q->next = p;
	//printf("12345");
	return 0;
}



int numInsert(LinkList* L) {
	LinkList p = (*L), q;
	int i = 0;
	int n = 0;
	int c;
	printf("需要在几号元素前插入？\n");

	scanf_s("%d", &n);
	c = ListEmpty(p);
	if (c != 0)
		return -1;
	while (i != (n - 1) && p != NULL) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		printf("无法在超出的序号前插入数据！\n");
		return -1;
	}
	printf("请输入要加入的信息（包括：学号 姓名 性别 寝室 电话号码):\n");
	q = (LNode*)malloc(sizeof(LNode));
	scanf_s("%s%s%s%s%s", &q->data.id, 8, &q->data.name, 20, &q->data.sex, 5, &q->data.dorm, 5, &q->data.tel, 12);
	q->next = p->next;
	p->next = q;
	q = NULL;
	return 0;
}



int NameInsert(LinkList* L) {
	LinkList q = (*L), p, t;
	printf("需要在哪一位同学前插入信息？\n");
	printf("姓名:");
	char n[20];

	scanf_s("%s", n,sizeof(n));//解决报错，添加边界
	
	p = q->next;
	while (strcmp(p->data.name, n) != 0 && q != NULL)
	{
		q = q->next;
		if (q->next == NULL) {
			printf("输入的同学名称不存在!!\n");
			return -2;
		}
		p = q->next;
	}
	if (p == NULL) {
		printf("输入的同学名称不存在!!\n");
		return -1;
	}
	printf("请输入要加入的信息（包括：学号 姓名 性别 寝室 电话号码):\n");
	t = (LNode*)malloc(sizeof(LNode));
	scanf_s("%s%s%s%s%s", &t->data.id, 8, &t->data.name, 20, &t->data.sex, 5, &t->data.dorm, 5, &t->data.tel, 12);
	t->next = q->next;
	q->next = t;
	t = NULL;
	return 0;
}



int numDelete(LinkList* L) {
	int i = 0;
	int n = 0;
	LinkList p = (*L), q;
	if (ListEmpty(*L) != 0)
		return -1;
	printf("请输入需要删除的序号:");
	scanf_s("%d", &n);
	while (p != NULL && i != (n - 1))
	{
		p = p->next;
		i++;
	}
	if (p == NULL) {
		printf("输入的序号超出范围!!!\n");
		return -2;
	}
	q = p->next;
	p->next = q->next;
	q = NULL;
	return 0;
}


int NameDelete(LinkList* L) {
	char n[20];
	printf("需要删除的姓名:");
	scanf_s("%s", n,sizeof(n));//添加缓冲区
	LinkList q = (*L), p;
	p = q->next;
	while (q != NULL && (strcmp(n, p->data.name) != 0))
	{
		q = q->next;
		if (q->next == NULL) {
			printf("输入的同学名称不存在!!\n");
			return -2;
		}
		p = q->next;
	}
	if (p == NULL) {
		printf("该同学不在通讯录中!!!\n");
		return -2;
	}
	q->next = p->next;
	p = NULL;
	return 0;
}
//主程序
void Address_s() {
	LinkList L;
	int a = 1;
	LinkListInit(&L);
	while (a) {
		system("cls");
		menu2();
		printf("请选择要使用的功能编号：");
		switch (getchar()) {
		case '1':
			system("cls");
			if (InputFile(L) == -1) {
				printf("读取失败!\n");
				system("pause");
				break;
			}
			printf("读取成功!\n");
			system("pause");
			break;
		case '2':
			system("cls");
			Traverse1(L);
			system("pause");
			break;
		case '3':
			system("cls");
			NameSearch(L);
			system("pause");
			break;
		case '4':
			system("cls");
			numSearch(L);
			system("pause");
			break;
		case '5':
			system("cls");
			AddInfo(&L);
			system("pause");
			break;
		case '6':
			system("cls");
			numInsert(&L);
			system("pause");
			break;
		case '7':
			system("cls");
			NameInsert(&L);
			system("pause");
			break;
		case '8':
			system("cls");
			numDelete(&L);
			system("pause");
			break;
		case '9':
			system("cls");
			NameDelete(&L);
			system("pause");
			break;
		case '0':
			OutputFile(L);
			DestroyList(&L);
			a = 0;
			printf("退出成功，返回主菜单\n");
			//system("pause");
			break;
			
		}
	}
}
