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


void menu2();//��ʾ�˵�
int Traverse1(LinkList L);//չʾ����
int InputFile(LinkList L);//��ȡ�ļ�
int OutputFile(LinkList L);//����ļ�
int LinkListInit(LinkList* L);//��������
int DestroyList(LinkList* L);//��������
int numSearch(LinkList L);//�������
int NameSearch(LinkList L);//��������
int ListEmpty(LinkList L);//�ж������Ƿ�Ϊ��
int AddInfo(LinkList* L);//˳�����
int NameInsert(LinkList* L);//����ǰ����
int numInsert(LinkList* L);//���ǰ����
int numDelete(LinkList* L);//���ɾ��
int NameDelete(LinkList* L);//����ɾ��
void Address_s();//������