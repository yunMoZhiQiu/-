
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
			//printf("该元素在ASL树中已存在\n");
			*TH = 0;
			return 0;
		}
		else if (e < (*T)->data)
		{
			if (Insert(&(*T)->lcd, e, TH) != 0) return 0;//未插入
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
			if (Insert(&(*T)->rcd, e, TH) == 0) return 0;//未插入
			if (TH)//插入后在判断是否要平衡
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
		//LL型  
	case 1:
		//右旋之后根和左子树都的平衡
		(*T)->bf = lc->bf = 0;
		R_R(T);
		break;
		//LR型
	case -1:
		AVLTree rd = lc->rcd;
		switch (rd->bf)
		{  //修改*T及其左孩子的平衡因子
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
		//RR型
	case -1:
		(*T)->bf = 0;
		rc->bf = 0;
		L_R(T);  //左旋
		break;
		//RL型                 
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
	{//没有关键字  
		*SH = 0;
		printf("该平衡二叉树中无此关键字！\n");
		return 0;
	}
	else
	{
		if (key == (*T)->data)    //找到了需要删除的结点  
		{
			//如果该结点的lcd 和  
			//rcd 至少有一个为NULL  
			//则大功告成，否则请参照  
			//下方解释  
			AVLTree q = (*T);
			if (!(*T)->lcd)//如果该结点的lcd 为NULL  
			{
				q = (*T);
				(*T) = (*T)->rcd;
				free(q);
				*SH = 1;
				return 1;
			}
			else if (!(*T)->rcd) {//如果该结点的rcd 为 NULL  
				q = (*T);
				(*T) = (*T)->lcd;//如果不是&（引用）的强大功能，这句话是没有意义的  
				free(q);
				*SH = 1;
				return 1;
			}
			else {
				//删除一个左右孩子都不为空的结点  
				//使该结点的直接前驱p的data替换该结点的data  
				//然后改变key=p.data  
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

//销毁平衡二叉树
void DestroyAVL(AVLTree* T)
{	
	if (NULL == *T) {
		//printf("无可销毁平衡二叉树，请查看问题\n");
		return;
	}
	DestroyAVL(&(*T)->lcd);
	DestroyAVL(&(*T)->rcd);
	free(*T);
}

//输出平衡二叉树中的所有的元素（小->大，中序遍历）  
void TeraversAVL(AVLTree* T)
{			
	if (NULL == *T) {
		//printf("无平衡二叉树，请创建平衡二叉树\n");
		return;
	}
	TeraversAVL(&(*T)->lcd);
	printf("%d  ", (*T)->data);
	TeraversAVL(&(*T)->rcd);
}

//统计树的叶子结点个数
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

//平均查找长度
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
	printf("*                       平衡二叉树                         ********\n");
	printf("*******************************************************************\n");
	printf("*****                         功能列表                         ****\n");
	printf("*******************************************************************\n");
	printf("*     1.输入关键字，构建平衡二叉树(构建第二棵二叉树时需销毁二叉树)*\n");
	printf("*     2.插入结点                                           ********\n");
	printf("*     3.删除结点                                           ********\n");
	printf("*     4.平均查找长度                                       ********\n");
	printf("*     5.遍历平衡二叉树                                     ********\n");
	printf("*     6.销毁平衡二叉树                                     ********\n");
	printf("*     0.退出本程序（退出前请销毁平衡二叉树）               ********\n");
	printf("*******************************************************************\n");
}
void Insert2(AVLTree *T,int TH)
{
	int n;
	TeraversAVL(&(*T));
	printf("\n");
	printf("请输入插入的结点:");
	scanf_s("%d", &n);
	Insert(&(*T), n, &TH);
	printf("插入成功！\n");
}
void Insert1(AVLTree* T, int TH)
{
	int n;
	printf("请输入数据 ，在输入0结束:\n");
			while (scanf_s("%d", &n))
			{
				if (n == 0) break;
				else  Insert(&(*T), n, &TH);
			}
			printf("平衡二叉树建立成功！\n");
			printf("读取成功!\n");
}
void  DeleteAVL1(AVLTree* T,int* SH)
{
	int key;
	TeraversAVL(&(*T));
	printf("\n");
	printf("请输入需要删除的结点:");
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
		printf("请选择要使用的功能编号：");
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
			printf("平均查找长度为:\n");
			printf("ASL=%5.2f\n", c);
			system("pause");
			break;
		case '5':
			system("cls");
			printf("其结果为：\n");
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