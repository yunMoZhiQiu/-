#pragma once
typedef struct              
{
    char vex[100];                 // ͼ�нڵ� 
   int edges[100][100]; // �ڽӾ��� 
    int wl[100];//�ߵ�Ȩֵ
}MGraph;

void CreateMG1(MGraph* MG);         //�ڽӾ��󷨴�������ͼ 
void PrintMG(MGraph MG);            //�ڽӾ�����ʽ���ͼMG 
void MiniSpanTree_Prim(MGraph* MG);  // Prim�㷨������С������ 
void locateVex(MGraph MG, char vex, int* index);
// ��λ�ڵ�vex���±겢����index 
void CreateMG0(MGraph* MG);
void menu5();
void Mtree();//������
void MiniSpanTree_Prim1(MGraph *MG);
void Print1(MGraph MG);
void File(MGraph MG);