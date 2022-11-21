
#include<stdio.h>    
#include<stdlib.h> 
#include<math.h> 
#include"AVLTrees.h"
void InitTree(AVLTree* T, int e, int* TH)
{
	(*T) = (AVLTree)malloc(sizeof(AVLNode));
	(*T)->rcd = NULL;
	(*T)->lcd = NULL;
	(*T)->data = e;
	(*T)->bf = 0;
	*TH = 1;
}
int Insert(AVLTree *T, int e, int* TH)
{
	if (!(*T))
	{
		InitTree(T, e, TH);
	}
	else {
		if (e == (*T)->data)
		{
			//printf("��Ԫ����ASL�����Ѵ���\n");
			*TH = 0;
			return 0;
		}
		else if (e < (*T)->data)
		{
			if (Insert(&(*T)->lcd, e, TH) != 0) return 0;//δ����
			if (*TH)
			{
				switch ((*T)->bf)
				{
				case 1: LBalance(&(*T)); *TH = 0; break;
				case 0:(*T)->bf = 1; *TH = 1; break;
				case -1: (*T)->bf = 0; *TH = 0; break;
				}
			}
		}
		else {
			if (Insert(&(*T)->rcd, e, TH) == 0) return 0;//δ����
			if (TH)//��������ж��Ƿ�Ҫƽ��
			{
				switch ((*T)->bf)
				{
				case 1:
					(*T)->bf = 0;
					TH = 0;
					break;
				case 0:
					(*T)->bf = -1;
					*TH = 1;
					break;
				case -1:
					RBalance(&(*T));
					TH = 0;
					break;
				}
			}

		}
	}
	return 1;
}

void R_R(AVLTree* p)
{
	AVLTree lc = (*p)->lcd;
	(*p)->lcd = lc->rcd;
	lc->rcd = (*p);
	(*p) = lc;
}
void L_R(AVLTree* p)
{
	AVLTree rc = (*p)->rcd;
	(*p)->rcd = rc->lcd;
	rc->lcd = (*p);
	(*p) = rc;
}

void LBalance(AVLTree* T)
{
	AVLTree lc = (*T)->lcd;
	switch (lc->bf)
	{
		//LL��  
	case 1:
		//����֮���������������ƽ��
		(*T)->bf = lc->bf = 0;
		R_R(T);
		break;
		//LR��
	case -1:
		AVLTree rd = lc->rcd;
		switch (rd->bf)
		{  //�޸�*T�������ӵ�ƽ������
		case 1:(*T)->bf = -1;  lc->bf = 0; break;
		case 0:(*T)->bf = 0;  lc->bf = 0; break;
		case -1:(*T)->bf = 0;  lc->bf = 1; break;
		}
		rd->bf = 0;
		L_R(&(*T)->lcd);
		R_R(T);
		break;
	}
}
void RBalance(AVLTree* T)
{
	AVLTree rc = (*T)->rcd;
	switch (rc->bf)
	{
		//RR��
	case -1:
		(*T)->bf = 0;
		rc->bf = 0;
		L_R(T);  //����
		break;
		//RL��                 
	case 1:
		AVLTree og = rc->lcd;
		switch (og->bf)
		{
		case 1:(*T)->bf = 0;  rc->bf = -1; break;
		case 0:(*T)->bf = 0;  rc->bf = 0; break;
		case -1:(*T)->bf = 1;  rc->bf = 0; break;
		}
		og->bf = 0;
		R_R(&(*T)->rcd);
		L_R(T);
		break;
	}
}
int  DeleteAVL(AVLTree* T,int key ,int* SH)
{
	
	if (!(*T))
	{//û�йؼ���  
		*SH = 0;
		printf("��ƽ����������޴˹ؼ��֣�\n");
		return 0;
	}
	else
	{
		if (key == (*T)->data)    //�ҵ�����Ҫɾ���Ľ��  
		{
			//����ý���lcd ��  
			//rcd ������һ��ΪNULL  
			//��󹦸�ɣ����������  
			//�·�����  
			AVLTree q = (*T);
			if (!(*T)->lcd)//����ý���lcd ΪNULL  
			{
				q = (*T);
				(*T) = (*T)->rcd;
				free(q);
				*SH = 1;
				return 1;
			}
			else if (!(*T)->rcd) {//����ý���rcd Ϊ NULL  
				q = (*T);
				(*T) = (*T)->lcd;//�������&�����ã���ǿ���ܣ���仰��û�������  
				free(q);
				*SH = 1;
				return 1;
			}
			else {
				//ɾ��һ�����Һ��Ӷ���Ϊ�յĽ��  
				//ʹ�ý���ֱ��ǰ��p��data�滻�ý���data  
				//Ȼ��ı�key=p.data  
				AVLTree s = (*T)->lcd;
				while (s->rcd)
					s = s->rcd;
				(*T)->data = s->data;
				key = s->data;
			}
		}
		if (key < (*T)->data)
		{
			if (!DeleteAVL(&(*T)->lcd, key, SH)) return 0;
			if (SH)
			{
				switch ((*T)->bf)
				{
				case 1:(*T)->bf = 0; *SH = 1; break;
				case 0:(*T)->bf = -1; *SH = 0; break;
				case -1:RBalance(T);
					if ((*T)->rcd->bf == 0)
						*SH = 0;
					else
						*SH = 1; break;
				}//switch(T->bf)  
			}
		}
		else {
			if (!DeleteAVL(&(*T)->rcd, key, SH)) return 0;
			if (SH)
			{
				switch ((*T)->bf)
				{
				case 1:LBalance(T);
					if ((*T)->lcd->bf == 0)
						*SH = 0;
					else
						*SH = 1; break;
				case 0:(*T)->bf = 1; *SH = 0; break;
				case -1:(*T)->bf = 0; *SH = 1; break;
				}
			}
		}
	}
	return 1;
}

//����ƽ�������
void DestroyAVL(AVLTree* T)
{	
	if (NULL == *T) {
		//printf("�޿�����ƽ�����������鿴����\n");
		return;
	}
	DestroyAVL(&(*T)->lcd);
	DestroyAVL(&(*T)->rcd);
	free(*T);
}

//���ƽ��������е����е�Ԫ�أ�С->�����������  
void TeraversAVL(AVLTree* T)
{			
	if (NULL == *T) {
		//printf("��ƽ����������봴��ƽ�������\n");
		return;
	}
	TeraversAVL(&(*T)->lcd);
	printf("%d  ", (*T)->data);
	TeraversAVL(&(*T)->rcd);
}

//ͳ������Ҷ�ӽ�����
int CountLeafs(AVLTree T)
{
	int i, j;
	if (T)
	{
		i = CountLeafs(T->lcd);
		j = CountLeafs(T->rcd);
		return i + j + 1;
	}
	else
		return 0;
}

//ƽ�����ҳ���
float ASL(AVLTree T)
{
	float n;
	float A;
	n = CountLeafs(T);
	A = ((n + 1) / n) * (log10(n + 1) / log10(2)) - 1;
	return A;
}
void menu() {
	printf("*******************************************************************\n");
	printf("*                       ƽ�������                         ********\n");
	printf("*******************************************************************\n");
	printf("*****                         �����б�                         ****\n");
	printf("*******************************************************************\n");
	printf("*     1.����ؼ��֣�����ƽ�������(�����ڶ��ö�����ʱ�����ٶ�����)*\n");
	printf("*     2.������                                           ********\n");
	printf("*     3.ɾ�����                                           ********\n");
	printf("*     4.ƽ�����ҳ���                                       ********\n");
	printf("*     5.����ƽ�������                                     ********\n");
	printf("*     6.����ƽ�������                                     ********\n");
	printf("*     0.�˳��������˳�ǰ������ƽ���������               ********\n");
	printf("*******************************************************************\n");
}
void Insert2(AVLTree *T,int TH)
{
	int n;
	TeraversAVL(&(*T));
	printf("\n");
	printf("���������Ľ��:");
	scanf_s("%d", &n);
	Insert(&(*T), n, &TH);
	printf("����ɹ���\n");
}
void Insert1(AVLTree* T, int TH)
{
	int n;
	printf("���������� ��������0����:\n");
			while (scanf_s("%d", &n))
			{
				if (n == 0) break;
				else  Insert(&(*T), n, &TH);
			}
			printf("ƽ������������ɹ���\n");
			printf("��ȡ�ɹ�!\n");
}
void  DeleteAVL1(AVLTree* T,int* SH)
{
	int key;
	TeraversAVL(&(*T));
	printf("\n");
	printf("��������Ҫɾ���Ľ��:");
	scanf_s("%d", &key);
	DeleteAVL(&(*T), key, SH);
}
void AVLtree()
{
	AVLTree T = NULL;
	int TH = 0;//taller
	int SH;//shorter
	float c;
	int s = 1;
	while (s) {
		system("cls");
		menu();
		printf("��ѡ��Ҫʹ�õĹ��ܱ�ţ�");
		switch (getchar()) {
		case '1':
			system("cls");
			Insert1(&T, TH);
			system("pause");
			break;
		case '2':
			system("cls");
			Insert2(&T, TH);
			system("pause");
			break;
		case '3':
			system("cls");
			DeleteAVL1(&T, &SH);
			system("pause");
			break;
		case '4':
			system("cls");
			c = ASL(T);
			printf("ƽ�����ҳ���Ϊ:\n");
			printf("ASL=%5.2f\n", c);
			system("pause");
			break;
		case '5':
			system("cls");
			printf("����Ϊ��\n");
			TeraversAVL(&T);
			system("pause");
			break;
		case '6':
			system("cls");
			printf("\n");
			DestroyAVL(&T);
			system("pause");
			break;
		case '0':
			s = 0;
			break;
			
		}








	}
}