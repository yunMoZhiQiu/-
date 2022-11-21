#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  N 256

typedef struct
{
	int weight;
	int parent, lchild, rchild;
}HTNode, * HFTree;//哈夫曼树结构定义

typedef char** HFCode;
char DQFile(char(&t)[N], char(&s)[N], int(&v)[N], int& i);
void select(HFTree Ht, int n, int& s1, int& s2);
void HFCoding(HFTree& HT, HFCode& HC, int* w, int n);
void putout(HFCode HC, char c[], int n);
void Encoding(HFCode HC, char T[], char c[], int& i, int& n);
void Decoding(HFTree HT, char* r, char* c, int& n);
void menu6();
void Hfm();
