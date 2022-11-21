#define  _CRT_SECURE_NO_WARNINGS 1
#include "HFM.h"
//��ȡ�ļ�
char DQFile(char(&t)[N], char(&s)[N], int(&v)[N], int& i)//t��Ŷ�ȡ�ַ��� s��Ų�ͬ���ַ�����v��Ų�ͬ�ַ������ַ�������i����ַ���Ŀ
{
	int	x = 0;
	int k = 0, j = 0, n = 0;
	FILE* fp;
	//���ļ�
	if ((fp = fopen("D:\\SourceTextFile.txt", "r")) == NULL)
	{
		printf("�޷����ļ�");
		exit(0);
	}
	t[i] = fgetc(fp);//���ı����ݵ���
	printf("��ȡ�ļ����ݣ�");
	while (t[i] != EOF)
	{
		printf("%c", t[i]);
		i++;
		t[i] = fgetc(fp);

	}
	printf("����%d���ַ�\n", i);
	fclose(fp);
	while (k < i - 1)//���ַ���ֵ�в�ͬ���ַ���ֵ��s
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
		x = 0;//�ŵüӸ����
	}
	printf("\n���ַ�����������\n");
	//��ӡ��ͬ�ַ��Ͷ�Ӧ�ĸ���
	for (j = 0; j < n; j++)
	{
		printf("%c--%d\n", s[j], v[j]);
	}
	return n;

}


//ѡ������Ȩֵ��С����
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

//�������������������ַ��Ĺ���������
void HFCoding(HFTree& HT, HFCode& HC, int* w, int n)
{
	int i, m, s1, s2, start;
	char* cd;
	int c, f;
	if (n <= 1) return;
	m = 2 * n - 1;  //����Ҫm���ڵ�
	HT = (HFTree)malloc((m + 1) * sizeof(HTNode));
	for (i = 1; i <= n; i++) { //��ʼ��ǰn���ڵ�,youci
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

	for (i = n + 1; i <= m; i++) {  // ����������
		select(HT, i - 1, s1, s2);
		HT[s1].parent = i;  HT[s2].parent = i;
		HT[i].lchild = s1;  HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}

	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
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

		strcpy(HC[i], &cd[start]);    // ��cd���Ʊ���(��)��HC
	}
	free(cd);

}
//�������������
void putout(HFCode HC, char c[], int n)
{
	FILE* fp;
	int i;
	printf("��Ӧ�Ĺ���������Ϊ:\n");
	for (i = 1; i <= n; ++i)
	{
		printf("%c:%s\n", c[i - 1], HC[i]);
	}
	//���ļ�
	if ((fp = fopen("D://HFMCodeFile.txt", "w+")) == NULL)
	{
		printf("�޷����ļ�");
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
//����
//�������ù�����������ı��ļ�SourceTextFile.txt���б���
void Encoding(HFCode HC, char T[], char c[], int& i, int& n)
{
	FILE* fp;
	int j, k = 1, s = 0;
	if ((fp = fopen("D://EncodedFile.txt", "w+")) == NULL)
	{
		printf("�޷����ļ�");
		exit(0);
	}
	printf("1.�ı��ļ����ݣ�");
	for (j = 0; j < i; j++)
	{
		printf("%c", T[j]);
	}
	printf("\n���ı��ļ����ݽ��б���:");
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
//����
//��EncodedFile.txt�е����ݽ������룬������뵽DecodedFile.txt�У�Ȼ�����
void Decoding(HFTree HT, char* r, char* c, int& n)
{
	FILE* fp, * fp1;
	int p = 2 * n - 1;
	int i = 0, j = 0, len = 0;
	char k[N];
	if ((fp = fopen("D://EncodedFile.txt", "r")) == NULL)
	{
		printf("�޷����ļ�");
		exit(0);
	}
	printf("\n5.��ȡ�ļ����ݣ�");
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
			p = 2 * n - 1;//p����ָ����ڵ�
		}
		i++;
		//p = 2 * n - 1;
	}
	r[j] = '\0';//������Ľ�����
	if ((fp1 = fopen("D://DecodedFile.txt", "w")) == NULL)
	{
		printf("�޷����ļ�");
		exit(0);
	}
	printf("\n6.�����ļ����ݣ�");
	for (i = 0; i <= j; i++)
	{
		printf("%c", r[i]);
		fputc(r[i], fp);
	}
	fclose(fp1);
}
void menu6() {
	printf("************************************************************\n");
	printf("*                       ����������                         *\n");
	printf("************************************************************\n");
	printf("*                         �����б�                         *\n");
	printf("************************************************************\n");
	printf("*     1.��ȡ�ĵ�����ȡ�����Ϣ(������˳�����)             *\n");
	printf("*     2.�������������������                               *\n");
	printf("*     3.�������������                                     *\n");
	printf("*     4.����                                               *\n");
	printf("*     5.����                                               *\n");
	printf("*     0.�˳�������(!�˳�ʱ�Զ����棩                       *\n");
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
		printf("��ѡ��Ҫʹ�õĹ��ܱ�ţ�");
		switch (getchar()) {
		case '1':
			system("cls");
			n = DQFile(t, S, v, i);//nΪ��ͬ�ַ�����Ŀ
			system("pause");
			break;
		case '2':
			system("cls");
			HFCoding(HT, HC, w, n);//�������������������ַ��Ĺ���������
			printf("�����ɹ�\n");
			system("pause");
			break;
		case '3':
			system("cls");
			putout(HC, c, n);//�������������
			printf("����ɹ�\n");
			system("pause");
			break;
		case '4':
			system("cls");
			Encoding(HC, T, c, i, n);//����
			system("pause");
			break;
		case '5':
			system("cls");
			Decoding(HT, r, c, n);//����
			system("pause");
			break;
		case '0':
			q = 0;
			break;
		}
	}
}

