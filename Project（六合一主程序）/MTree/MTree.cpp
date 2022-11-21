#include <stdio.h>
#include <stdlib.h>
#include"MTree.h"



void CreateMG0(MGraph* MG)
{
    int i, j;
    printf("内置图顶点:q,i,u,h,g\n");
    MG->vex[0] = 'q';
    MG->vex[1] = 'i';
    MG->vex[2] = 'u';
    MG->vex[3] = 'h';
    MG->vex[4] = 'g';
    for (i = 0; i < 5; i++)    /* 初始化邻接矩阵 */
        for (j = 0; j < 5; j++)
            MG->edges[i][j] = 10000;
    MG->edges[0][1] = 3;           
    MG->edges[1][0] = 3;
    MG->edges[1][2] = 5;            
    MG->edges[2][1] = 5;
    MG->edges[3][1] = 7;            
    MG->edges[1][3] = 7;
    MG->edges[3][4] = 1;            
    MG->edges[4][3] = 1;
    MG->edges[2][3] = 6;            
    MG->edges[3][2] = 6;
    MG->edges[2][3] = 2;            
    MG->edges[3][2] = 2;
    MG->edges[3][4] = 99;            
    MG->edges[4][3] = 99;

}
void CreateMG1(MGraph* MG)
{
    int i = 0, j, k, w;                 // w：权值
    char ch;
    printf("5，7\n");
    printf("以“#”结尾，回车结束输入\n");
    printf("例如：q w e r j#\n");
    printf("请依次输入顶点：");
    getchar();
    while ((ch = getchar()) != '\n')    
    {
        MG->vex[i++] = ch;
        getchar();
    }

    for (i = 0; i < 5; i++)    // 初始化邻接矩阵 
        for (j = 0; j < 5; j++)
            MG->edges[i][j] = 10000;

    printf("顶点 | 下标\n");
    for (i = 0; i < 5; i++)    /* 显示图中顶点及其对应下标 */
    {
        printf("%3c%6d\n", MG->vex[i], i);
    }

    printf("请输入每条边对应的两个顶点下标及边的权值（格式：i j w）：\n");
    for (k = 0; k < 7; k++)   /* 建立邻接矩阵 */
    {
        scanf_s("\n%d%d%d", &i, &j, &w);  // 输入边的两个节点及权值 
        MG->edges[i][j] = w;           // 将矩阵对应位置元素置为权值 
        MG->edges[j][i] = w;
    }
}
void PrintMG(MGraph MG)
{
    int i, j;

    for (i = 0; i < 5; i++)         // 输出邻接矩阵 
    {
        for (j = 0; j < 5; j++)
        {
            if (MG.edges[i][j] == 10000) //节点不连通时，输出'#'代表无穷大 
                printf("%3c", '#');
            else                            // 节点连通时，输出边上权值 
                printf("%3d", MG.edges[i][j]);
        }
        printf("\n");
    }
}
void MiniSpanTree_Prim(MGraph *MG)
{
    int i, j, k, index, mincost;        // index：开始节点下标 */
    int lowcost[5], closevertex[5];
    char ch;                            

    printf("请输入开始节点：");
    getchar();
    scanf_s("%c", &ch);
    printf_s("顶点：%c\n", ch);
    locateVex((*MG), ch, &index);         

    lowcost[index] = 0;
    closevertex[0] = index;             //将开始节点加入集合U 
    for (i = 0; i < 5; i++)     // 辅助数组初始化 
        if (i != index)
            lowcost[i] = (*MG).edges[index][i];

    for (i = 1; i < 5; i++)
    {
        mincost = 10000;
        for (j = 0; j < 5; j++)
        {
            if (lowcost[j] < mincost && lowcost[j] != 0)
            {
                mincost = lowcost[j];   // 最小权值 
                k = j;                  
            }
        }
        //输出当前顶点边中权值最小的边 
        printf("顶点：%c ;权值：%d\n", (*MG).vex[k], mincost);
        (*MG).wl[k] = mincost;
        lowcost[k] = 0;                 // 将当前顶点的权值设为0，表示此顶点已经完成任务 
        closevertex[i] = k;             //与权值最小边关联的节点下标并入集合U 

        for (j = 0; j < 5; j++) 
        {
            if ((*MG).edges[k][j] < lowcost[j])
                lowcost[j] = (*MG).edges[k][j];
        }
    }
}
void locateVex(MGraph MG, char vex, int* index)
{
    int i;

    for (i = 0; i < 5; i++)
    {
        if (MG.vex[i] == vex)
        {
            *index = i;
            return;
        }
    }
    printf("节点定位失败！\n");
}
void Print1(MGraph MG)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("%c   ", MG.vex[i]);
    }
    printf("\n------------------------------\n");
    printf("vexnum = %d ; edgenum = %d\n", 5, 7);
    printf("------------------------------\n");
    PrintMG(MG);
    printf("------------------------------\n");
}
void MiniSpanTree_Prim1(MGraph *MG)
{
    int i;
    for (i = 0; i < 5; i++)
    {
        printf("%c   ", (*MG).vex[i]);
    }
    printf("\n------------------------------\n");
    printf("vexnum = %d ; edgenum = %d\n", 5, 7);
    printf("------------------------------\n");
    PrintMG((*MG));
    printf("------------------------------\n");
    MiniSpanTree_Prim(&(*MG));
}
void File(MGraph MG)
{
    int i = 0;
    FILE* fp;
    if (fopen_s(&fp, "D:\\MTree.txt", "w+") != 0) {
        printf("文件打开失败");
        return;
    }
    for (i; i < 4; i++) {
        fprintf(fp, "%c", MG.vex[i]);
        fprintf(fp, "\n\t%d\n", MG.wl[i + 1]);
    }

    fprintf(fp, "%c", MG.vex[4]);
    printf("保存成功\n");
    fclose(fp);

}
void menu5() {
    printf("************************************************************\n");
    printf("*                       城市最短路径                       *\n");
    printf("************************************************************\n");
    printf("*                         功能列表                         *\n");
    printf("************************************************************\n");
    printf("*     1.创建城市及其间关系                                 *\n");
    printf("*     2.创建图城市（内置城市关系）                         *\n");
    printf("*     3.打印城市相关信息                                   *\n");
    printf("*     4.开始生成最小二叉树（Prim）                         *\n");
    printf("*     5.存入文件                                           *\n");
    printf("*     0.退出本程序(!退出时自动保存）                       *\n");
    printf("************************************************************\n");
}

void Mtree()
{
    int q = 1;
    MGraph G;
    while (q) {
        system("cls");
        menu5();
        printf("请选择要使用的功能编号：");
        switch (getchar()) {
        case '1':
            system("cls");
            CreateMG1(&G);
            if (G.vex != NULL)
                printf("创建成功\n");
            system("pause");
            break;
        case '2':
            system("cls");
            CreateMG0(&G);
            if (G.vex != NULL)
                printf("调用成功\n");
            system("pause");
            break;
        case '3':
            system("cls");
            Print1(G);
            system("pause");
            break;
        case '4':
            system("cls");
            MiniSpanTree_Prim1(&G);
            system("pause");
            break;
        case '5':
            system("cls");
            File(G);
            system("pause");
            break;
        case '0':
            q = 0;

            break;
        }
    }
}

