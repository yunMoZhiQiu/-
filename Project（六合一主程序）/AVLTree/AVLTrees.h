#pragma once
typedef struct AVLNode
{
	int data;
	int bf;
	struct AVLNode* lcd, * rcd;
}AVLNode, * AVLTree;
void InitTree(AVLTree* T, int e, int* TH);
void R_R(AVLTree* p);
int Insert(AVLTree* T, int e, int* TH);
void L_R(AVLTree* p);
void LBalance(AVLTree* T);
void RBalance(AVLTree* T);
int  DeleteAVL(AVLTree* T,int key, int* SH);
void DestroyAVL(AVLTree* T);
void TeraversAVL(AVLTree* T);
int CountLeafs(AVLTree T);
float ASL(AVLTree T);
void menu();
void AVLtree();
void Insert2(AVLTree* T, int TH);
void Insert1(AVLTree* T, int TH);
void  DeleteAVL1(AVLTree* T,int* SH);