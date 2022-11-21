#include <stdio.h>
#include <stdlib.h>
#include"MTree.h"



void CreateMG0(MGraph* MG)
{
    int i, j;
    printf("����ͼ����:q,i,u,h,g\n");
    MG->vex[0] = 'q';
    MG->vex[1] = 'i';
    MG->vex[2] = 'u';
    MG->vex[3] = 'h';
    MG->vex[4] = 'g';
    for (i = 0; i < 5; i++)    /* ��ʼ���ڽӾ��� */
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
    int i = 0, j, k, w;                 // w��Ȩֵ
    char ch;
    printf("5��7\n");
    printf("�ԡ�#����β���س���������\n");
    printf("���磺q w e r j#\n");
    printf("���������붥�㣺");
    getchar();
    while ((ch = getchar()) != '\n')    
    {
        MG->vex[i++] = ch;
        getchar();
    }

    for (i = 0; i < 5; i++)    // ��ʼ���ڽӾ��� 
        for (j = 0; j < 5; j++)
            MG->edges[i][j] = 10000;

    printf("���� | �±�\n");
    for (i = 0; i < 5; i++)    /* ��ʾͼ�ж��㼰���Ӧ�±� */
    {
        printf("%3c%6d\n", MG->vex[i], i);
    }

    printf("������ÿ���߶�Ӧ�����������±꼰�ߵ�Ȩֵ����ʽ��i j w����\n");
    for (k = 0; k < 7; k++)   /* �����ڽӾ��� */
    {
        scanf_s("\n%d%d%d", &i, &j, &w);  // ����ߵ������ڵ㼰Ȩֵ 
        MG->edges[i][j] = w;           // �������Ӧλ��Ԫ����ΪȨֵ 
        MG->edges[j][i] = w;
    }
}
void PrintMG(MGraph MG)
{
    int i, j;

    for (i = 0; i < 5; i++)         // ����ڽӾ��� 
    {
        for (j = 0; j < 5; j++)
        {
            if (MG.edges[i][j] == 10000) //�ڵ㲻��ͨʱ�����'#'��������� 
                printf("%3c", '#');
            else                            // �ڵ���ͨʱ���������Ȩֵ 
                printf("%3d", MG.edges[i][j]);
        }
        printf("\n");
    }
}
void MiniSpanTree_Prim(MGraph *MG)
{
    int i, j, k, index, mincost;        // index����ʼ�ڵ��±� */
    int lowcost[5], closevertex[5];
    char ch;                            

    printf("�����뿪ʼ�ڵ㣺");
    getchar();
    scanf_s("%c", &ch);
    printf_s("���㣺%c\n", ch);
    locateVex((*MG), ch, &index);         

    lowcost[index] = 0;
    closevertex[0] = index;             //����ʼ�ڵ���뼯��U 
    for (i = 0; i < 5; i++)     // ���������ʼ�� 
        if (i != index)
            lowcost[i] = (*MG).edges[index][i];

    for (i = 1; i < 5; i++)
    {
        mincost = 10000;
        for (j = 0; j < 5; j++)
        {
            if (lowcost[j] < mincost && lowcost[j] != 0)
            {
                mincost = lowcost[j];   // ��СȨֵ 
                k = j;                  
            }
        }
        //�����ǰ�������Ȩֵ��С�ı� 
        printf("���㣺%c ;Ȩֵ��%d\n", (*MG).vex[k], mincost);
        (*MG).wl[k] = mincost;
        lowcost[k] = 0;                 // ����ǰ�����Ȩֵ��Ϊ0����ʾ�˶����Ѿ�������� 
        closevertex[i] = k;             //��Ȩֵ��С�߹����Ľڵ��±겢�뼯��U 

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
    printf("�ڵ㶨λʧ�ܣ�\n");
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
        printf("�ļ���ʧ��");
        return;
    }
    for (i; i < 4; i++) {
        fprintf(fp, "%c", MG.vex[i]);
        fprintf(fp, "\n\t%d\n", MG.wl[i + 1]);
    }

    fprintf(fp, "%c", MG.vex[4]);
    printf("����ɹ�\n");
    fclose(fp);

}
void menu5() {
    printf("************************************************************\n");
    printf("*                       �������·��                       *\n");
    printf("************************************************************\n");
    printf("*                         �����б�                         *\n");
    printf("************************************************************\n");
    printf("*     1.�������м�����ϵ                                 *\n");
    printf("*     2.����ͼ���У����ó��й�ϵ��                         *\n");
    printf("*     3.��ӡ���������Ϣ                                   *\n");
    printf("*     4.��ʼ������С��������Prim��                         *\n");
    printf("*     5.�����ļ�                                           *\n");
    printf("*     0.�˳�������(!�˳�ʱ�Զ����棩                       *\n");
    printf("************************************************************\n");
}

void Mtree()
{
    int q = 1;
    MGraph G;
    while (q) {
        system("cls");
        menu5();
        printf("��ѡ��Ҫʹ�õĹ��ܱ�ţ�");
        switch (getchar()) {
        case '1':
            system("cls");
            CreateMG1(&G);
            if (G.vex != NULL)
                printf("�����ɹ�\n");
            system("pause");
            break;
        case '2':
            system("cls");
            CreateMG0(&G);
            if (G.vex != NULL)
                printf("���óɹ�\n");
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

