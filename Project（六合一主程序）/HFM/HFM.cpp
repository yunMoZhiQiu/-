#define  _CRT_SECURE_NO_WARNINGS 1
#include "HFM.h"
//读取文件
char DQFile(char(&t)[N], char(&s)[N], int(&v)[N], int& i)//t存放读取字符串 s存放不同的字符串，v存放不同字符串中字符个数，i存放字符数目
{
	int	x = 0;
	int k = 0, j = 0, n = 0;
	FILE* fp;
	//打开文件
	if ((fp = fopen("D:\\SourceTextFile.txt", "r")) == NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	t[i] = fgetc(fp);//将文本内容导入
	printf("读取文件内容：");
	while (t[i] != EOF)
	{
		printf("%c", t[i]);
		i++;
		t[i] = fgetc(fp);

	}
	printf("共有%d个字符\n", i);
	fclose(fp);
	while (k < i - 1)//把字符赋值中不同的字符赋值给s
	{
		for (j = 0; j < n && s[j] != t[k]; j++, s + 1);
		if (j == n)
		{
			s[j] = t[k];
			n++;
		}
		k++;
	}
	for (j = 0; j < n; j++) {

		for (k = 0; k <= i - 1; k++)
		{
			if (s[j] == t[k])
				x++;
		}
		v[j] = x;
		x = 0;//着得加个这个
	}
	printf("\n各字符及其数量：\n");
	//打印不同字符和对应的个数
	for (j = 0; j < n; j++)
	{
		printf("%c--%d\n", s[j], v[j]);
	}
	return n;

}


//选择两颗权值较小的树
void select(HFTree Ht, int n, int& s1, int& s2)
{
	int i, m;
	for (i = 1; i <= n; i++)
	{
		if (Ht[i].parent == 0)
		{
			m = i;
			break;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (Ht[i].parent == 0)
		{
			if (Ht[i].weight < Ht[m].weight)
				m = i;
		}
	}
	s1 = m;

	for (i = 1; i <= n; i++)
	{
		if (Ht[i].parent == 0 && i != s1)
		{
			m = i;
			break;
		}
	}
	for (i = 1; i <= n; i++)
	{
		if (Ht[i].parent == 0 && i != s1)
		{
			if (Ht[i].weight < Ht[m].weight)
				m = i;
		}
	}
	s2 = m;
}

//构造哈夫曼树并求出各字符的哈夫曼编码
void HFCoding(HFTree& HT, HFCode& HC, int* w, int n)
{
	int i, m, s1, s2, start;
	char* cd;
	int c, f;
	if (n <= 1) return;
	m = 2 * n - 1;  //共需要m个节点
	HT = (HFTree)malloc((m + 1) * sizeof(HTNode));
	for (i = 1; i <= n; i++) { //初始化前n个节点,youci
		HT[i].weight = w[i - 1];
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++) {
		HT[i].weight = 0;
		HT[i].parent = 0;
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}

	for (i = n + 1; i <= m; i++) {  // 建哈夫曼树
		select(HT, i - 1, s1, s2);
		HT[s1].parent = i;  HT[s2].parent = i;
		HT[i].lchild = s1;  HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//从叶子到根逆向求每个字符的哈夫曼编码
	HC = (HFCode)malloc((n + 1) * sizeof(char*));
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i)
	{
		start = n - 1;
		c = i; f = HT[i].parent;
		while (f != 0)
		{
			--start;
			if (HT[f].lchild == c) cd[start] = '0';
			else cd[start] = '1';
			c = f; 
			f = HT[f].parent;
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));

		strcpy(HC[i], &cd[start]);    // 从cd复制编码(串)到HC
	}
	free(cd);

}
//输出哈夫曼编码
void putout(HFCode HC, char c[], int n)
{
	FILE* fp;
	int i;
	printf("对应的哈夫曼编码为:\n");
	for (i = 1; i <= n; ++i)
	{
		printf("%c:%s\n", c[i - 1], HC[i]);
	}
	//打开文件
	if ((fp = fopen("D://HFMCodeFile.txt", "w+")) == NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%c ", c[i]);
		fputs(HC[i + 1], fp);
		fputc('\n', fp);
	}
	fclose(fp);
}
//编码
//利用所得哈夫曼编码对文本文件SourceTextFile.txt进行编码
void Encoding(HFCode HC, char T[], char c[], int& i, int& n)
{
	FILE* fp;
	int j, k = 1, s = 0;
	if ((fp = fopen("D://EncodedFile.txt", "w+")) == NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	printf("1.文本文件内容：");
	for (j = 0; j < i; j++)
	{
		printf("%c", T[j]);
	}
	printf("\n对文本文件内容进行编码:");
	while (k <= i)
	{
		for (j = 0; j < n; j++)
		{

			if (T[k - 1] == c[j])
			{
				printf("%s", HC[j + 1]);
				fputs(HC[j + 1], fp);
			}

		}
		k++;
	}
	fclose(fp);
	printf("\n");
}
//译码
//对EncodedFile.txt中的内容进行译码，结果存入到DecodedFile.txt中，然后输出
void Decoding(HFTree HT, char* r, char* c, int& n)
{
	FILE* fp, * fp1;
	int p = 2 * n - 1;
	int i = 0, j = 0, len = 0;
	char k[N];
	if ((fp = fopen("D://EncodedFile.txt", "r")) == NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	printf("\n5.读取文件内容：");
	k[len] = fgetc(fp);
	while (k[len] != EOF)
	{
		printf("%c", k[len]);
		len++;
		k[len] = fgetc(fp);
	}
	fclose(fp);
	while (i <= len)
	{
		if (k[i] == '0')
		{
			p = HT[p].lchild;
		}
		if (k[i] == '1')
		{
			p = HT[p].rchild;
		}
		if (HT[p].rchild == 0 && HT[p].lchild == 0)
		{
			r[j] = c[p - 1];
			j++;
			p = 2 * n - 1;//p重新指向根节点
		}
		i++;
		//p = 2 * n - 1;
	}
	r[j] = '\0';//结果串的结束符
	if ((fp1 = fopen("D://DecodedFile.txt", "w")) == NULL)
	{
		printf("无法打开文件");
		exit(0);
	}
	printf("\n6.译码文件内容：");
	for (i = 0; i <= j; i++)
	{
		printf("%c", r[i]);
		fputc(r[i], fp);
	}
	fclose(fp1);
}
void menu6() {
	printf("************************************************************\n");
	printf("*                       哈夫曼编码                         *\n");
	printf("************************************************************\n");
	printf("*                         功能列表                         *\n");
	printf("************************************************************\n");
	printf("*     1.读取文档，提取相关信息(功能请顺序进行)             *\n");
	printf("*     2.构建哈夫曼树并求编码                               *\n");
	printf("*     3.输出哈夫曼编码                                     *\n");
	printf("*     4.编码                                               *\n");
	printf("*     5.译码                                               *\n");
	printf("*     0.退出本程序(!退出时自动保存）                       *\n");
	printf("************************************************************\n");
}
void Hfm()
{
	int n = 0;
	int j = 0;
	int v[N];
	int i = 0;
	int m = 0;
	int q = 1;
	char S[N];
	char t[N];
	char r[N];
	char* c;
	char *T;
	int* w;
	c = S;
	w = v;
	T = t;
	HFTree HT{};
	HFCode HC{};
	while (q) {
		system("cls");
		menu6();
		printf("请选择要使用的功能编号：");
		switch (getchar()) {
		case '1':
			system("cls");
			n = DQFile(t, S, v, i);//n为不同字符的数目
			system("pause");
			break;
		case '2':
			system("cls");
			HFCoding(HT, HC, w, n);//构造哈夫曼树并求出各字符的哈夫曼编码
			printf("构建成功\n");
			system("pause");
			break;
		case '3':
			system("cls");
			putout(HC, c, n);//输出哈夫曼编码
			printf("输出成功\n");
			system("pause");
			break;
		case '4':
			system("cls");
			Encoding(HC, T, c, i, n);//编码
			system("pause");
			break;
		case '5':
			system("cls");
			Decoding(HT, r, c, n);//译码
			system("pause");
			break;
		case '0':
			q = 0;
			break;
		}
	}
}

