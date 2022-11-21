#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>



typedef struct {
	char id[10];
	char name[20];
	char sex[5];
	char dorm[10];
	char tel[12];
}AddressBook;
typedef struct LNode {
	AddressBook data;
	struct LNode* next;
}LNode, * LinkList;


void menu2();//显示菜单
int Traverse1(LinkList L);//展示链表
int InputFile(LinkList L);//读取文件
int OutputFile(LinkList L);//输出文件
int LinkListInit(LinkList* L);//创建链表
int DestroyList(LinkList* L);//销毁链表
int numSearch(LinkList L);//序号搜索
int NameSearch(LinkList L);//姓名搜索
int ListEmpty(LinkList L);//判断链表是否为空
int AddInfo(LinkList* L);//顺序添加
int NameInsert(LinkList* L);//姓名前插入
int numInsert(LinkList* L);//序号前插入
int numDelete(LinkList* L);//序号删除
int NameDelete(LinkList* L);//姓名删除
void Address_s();//主程序