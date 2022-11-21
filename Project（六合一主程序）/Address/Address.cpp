#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include"address.h"



void menu2() {
	printf("************************************************************\n");
	printf("*                       �༶ͨѶ¼                         *\n");
	printf("************************************************************\n");
	printf("*                         �����б�                         *\n");
	printf("************************************************************\n");
	printf("*     1.��ȡ�ļ�(!���ȶ�ȡ�ļ�!)                           *\n");
	printf("*     2.չʾ��ǰͨѶ¼��Ϣ                                 *\n");
	printf("*     3.����������                                         *\n");
	printf("*     4.���������                                         *\n");
	printf("*     5.˳������                                         *\n");
	printf("*     6.λ��ǰ���                                         *\n");
	printf("*     7.����ǰ���                                         *\n");
	printf("*     8.ɾ��ָ�������Ϣ                                   *\n");
	printf("*     9.ɾ��ָ��������Ϣ                                   *\n");
	printf("*     0.�˳�������(!�˳�ʱ�Զ����棩                       *\n");
	printf("************************************************************\n");
}

int InputFile(LinkList L)
{
	int i;
	LinkList p, q;
	FILE* fp;
	char str[35];//��һ������
	p = L;
	q = (LNode*)malloc(sizeof(LNode));

	if (fopen_s(&fp, "D:\\stuinfo.txt", "r+") != 0) return -1;//�ж϶�ȡ�ɹ�
	fgets(str, sizeof(str) - 1, fp);//��ȡ��һ������
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
		printf("�ļ���ȡʧ��");
		return -2;
	}
	fprintf(fp, "ѧ�� \t���� \t�Ա� \t���� \t�绰����\n");
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
		printf("�ռ����ʧ��");//�ж��ڴ��շ���ɹ�
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
	printf("ѧ�� \t���� \t�Ա� \t���� \t�绰����\n");
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
	printf("������Ҫ��������ţ�");
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
		printf("���������ѳ���\n");
		return -1;
	}
	printf("ѧ�� \t���� \t�Ա� \t���� \t�绰����\n");
	printf("%s \t%s \t%s \t%s \t%s\n", p->data.id, p->data.name, p->data.sex, p->data.dorm, p->data.tel);
	return 0;
}


int NameSearch(LinkList L) {
	int c;
	LinkList q, p = (LNode*)malloc(sizeof(LNode));
	q = L->next;
	printf("��������������������");
	c = ListEmpty(q);
	if (c != 0)
		return -1;
	scanf_s("%s", &p->data.name, 20);
	while (q != NULL && strcmp(q->data.name, p->data.name) != 0) {
		q = q->next;
	}
	if (q == NULL) {
		printf("ͨѶ¼��û�и�����!\n");
		return -2;
	}
	printf("ѧ�� \t���� \t�Ա� \t���� \t�绰����\n");
	printf("%s \t%s \t%s \t%s \t%s\n", q->data.id, q->data.name, q->data.sex, q->data.dorm, q->data.tel);
	return 0;
}



int ListEmpty(LinkList L) {
	if (L == NULL) return -1;//0Ϊ�ձ�
	else if (L->next != NULL) return 0;//1Ϊ�ǿձ�
	return 0;
}



int AddInfo(LinkList* L) {
	int c;
	LinkList p, q;
	q = (*L)->next;
	printf("������Ҫ�������Ϣ��������ѧ�� ���� �Ա�(f/m) ���� �绰����):\n");
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
	printf("��Ҫ�ڼ���Ԫ��ǰ���룿\n");

	scanf_s("%d", &n);
	c = ListEmpty(p);
	if (c != 0)
		return -1;
	while (i != (n - 1) && p != NULL) {
		p = p->next;
		i++;
	}
	if (p == NULL) {
		printf("�޷��ڳ��������ǰ�������ݣ�\n");
		return -1;
	}
	printf("������Ҫ�������Ϣ��������ѧ�� ���� �Ա� ���� �绰����):\n");
	q = (LNode*)malloc(sizeof(LNode));
	scanf_s("%s%s%s%s%s", &q->data.id, 8, &q->data.name, 20, &q->data.sex, 5, &q->data.dorm, 5, &q->data.tel, 12);
	q->next = p->next;
	p->next = q;
	q = NULL;
	return 0;
}



int NameInsert(LinkList* L) {
	LinkList q = (*L), p, t;
	printf("��Ҫ����һλͬѧǰ������Ϣ��\n");
	printf("����:");
	char n[20];

	scanf_s("%s", n,sizeof(n));//���������ӱ߽�
	
	p = q->next;
	while (strcmp(p->data.name, n) != 0 && q != NULL)
	{
		q = q->next;
		if (q->next == NULL) {
			printf("�����ͬѧ���Ʋ�����!!\n");
			return -2;
		}
		p = q->next;
	}
	if (p == NULL) {
		printf("�����ͬѧ���Ʋ�����!!\n");
		return -1;
	}
	printf("������Ҫ�������Ϣ��������ѧ�� ���� �Ա� ���� �绰����):\n");
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
	printf("��������Ҫɾ�������:");
	scanf_s("%d", &n);
	while (p != NULL && i != (n - 1))
	{
		p = p->next;
		i++;
	}
	if (p == NULL) {
		printf("�������ų�����Χ!!!\n");
		return -2;
	}
	q = p->next;
	p->next = q->next;
	q = NULL;
	return 0;
}


int NameDelete(LinkList* L) {
	char n[20];
	printf("��Ҫɾ��������:");
	scanf_s("%s", n,sizeof(n));//��ӻ�����
	LinkList q = (*L), p;
	p = q->next;
	while (q != NULL && (strcmp(n, p->data.name) != 0))
	{
		q = q->next;
		if (q->next == NULL) {
			printf("�����ͬѧ���Ʋ�����!!\n");
			return -2;
		}
		p = q->next;
	}
	if (p == NULL) {
		printf("��ͬѧ����ͨѶ¼��!!!\n");
		return -2;
	}
	q->next = p->next;
	p = NULL;
	return 0;
}
//������
void Address_s() {
	LinkList L;
	int a = 1;
	LinkListInit(&L);
	while (a) {
		system("cls");
		menu2();
		printf("��ѡ��Ҫʹ�õĹ��ܱ�ţ�");
		switch (getchar()) {
		case '1':
			system("cls");
			if (InputFile(L) == -1) {
				printf("��ȡʧ��!\n");
				system("pause");
				break;
			}
			printf("��ȡ�ɹ�!\n");
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
			printf("�˳��ɹ����������˵�\n");
			//system("pause");
			break;
			
		}
	}
}
