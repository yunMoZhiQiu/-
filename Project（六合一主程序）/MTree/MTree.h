#pragma once
typedef struct              
{
    char vex[100];                 // 图中节点 
   int edges[100][100]; // 邻接矩阵 
    int wl[100];//边的权值
}MGraph;

void CreateMG1(MGraph* MG);         //邻接矩阵法创建无向图 
void PrintMG(MGraph MG);            //邻接矩阵形式输出图MG 
void MiniSpanTree_Prim(MGraph* MG);  // Prim算法建立最小生成树 
void locateVex(MGraph MG, char vex, int* index);
// 定位节点vex的下标并赋给index 
void CreateMG0(MGraph* MG);
void menu5();
void Mtree();//主程序
void MiniSpanTree_Prim1(MGraph *MG);
void Print1(MGraph MG);
void File(MGraph MG);