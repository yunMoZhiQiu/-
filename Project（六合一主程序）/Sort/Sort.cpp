#include "Sort.h"
#include<stdlib.h>
#include<stdio.h>
#include <time.h>

void ClearList(List* data)
{
	data->length = 0;
}
void InitList(List* data)
{
	data->elem = (int*)malloc(INIT_LIST_SIZE * sizeof(int));
	data->size = INIT_LIST_SIZE;
	data->length = 0;
}
void InsertList(List* data, int a)
{
	if (data->length >= data->size) {
		data->elem = (int*)realloc(data->elem, (data->size + INCREMENT_SIZE) * sizeof(int));
		data->size = data->size + INCREMENT_SIZE;
	}

	data->elem[data->length] = a;
	data->length++;
}
void BubbleSort(int a[], int n, int* nCom, int* nMove) {
	int i, j;
	int b[100];

	int temp;
	*nCom = 0;
	*nMove = 0;

	for (i = 0; i < n; i++) {
		b[i] = a[i];
	}

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - i - 1; j++) {
			if (b[j] > b[j + 1]) {
				temp = b[j];
				b[j] = b[j + 1];
				b[j + 1] = temp;
				(*nMove) += 1;//不是执行语句的数量不能加三
			}
			(*nCom)++;
		}
	}

}
void InsertSort(int a[], int n, int* nCom, int* nMove)//书上代码是《=n，与此处不同，测试有点问题
{
	int i, j;
	int b[101];
	//int temp;
	*nCom = 0;
	*nMove = 0;
	for (i = 0; i < n; i++) {
		b[i + 1] = a[i];
	}

	for (i = 2; i < n; i++) {
		b[0] = b[i];
		for (j = i; b[0] < b[j - 1]; j--) {
			b[j] = b[j - 1];
			(*nMove)++;
			(*nCom)++;
		}
		b[j] = b[0];
	}
}
void SelectSort(int a[], int n, int* nCom, int* nMove)//测试有点问题，使用小于n,,,,,未测试，不知对错
{
	int i = 1;
	int k;
	int t, j;
	*nCom = 0;
	*nMove = 0;
	for (i; i < n - 1; i++)
	{
		k = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < a[k])
				k = j;
			*nCom += 1;
		}
		if (k != i)
		{
			t = a[i];
			a[i] = a[k];
			a[k] = t;
			*nMove += 1;
		}
	}
}
void QuickSort(int a[], int n, int* nCom, int* nMove)
{
	*nCom = 0;
	*nMove = 0;
	QSort(a, 1, n, nCom, nMove);
}
void QSort(int a[], int low, int high, int* nCom, int* nMove)
{
	int pivotloc;
	if (low < high)
	{
		pivotloc = Partition(a, low, high, nCom, nMove);
		QSort(a, low, pivotloc - 1, nCom, nMove);
		QSort(a, pivotloc + 1, high, nCom, nMove);
	}
}
int Partition(int a[], int low, int high, int* nCom, int* nMove)
{
	int pivotkey;
	a[0] = a[low];
	pivotkey = a[low];
	while (low < high)
	{	
		while (low < high && a[high] >= pivotkey)
		{
			high--;
			*nCom += 1;
		}
		*nMove += 1;
		a[low] = a[high];
		while (low < high && a[high] <= pivotkey)
		{
			low++;
			//*nCom += 1;
		}
		a[high] = a[low];
		*nMove += 1;
	}*nMove += 1;
	a[low] = a[0]; 
	return low;
}
void ShellSort(int k[], int n, int* nCom, int* nMove)
{
	*nCom = 0;
	*nMove = 0;
	int i, j, temp, gap = n;
	while (gap > 1)
	{
		gap = gap / 2;                /*增量缩小，每次减半*/
		for (i = 0; i < n - gap; i++) //n-gap 是控制上限不让越界
		{
			j = i + gap;    //相邻间隔的前后值进行比较
			if (k[i] > k[j])
			{
				temp = k[i];
				k[i] = k[j];
				k[j] = temp;
				*nMove += 1;

			}*nCom += 1;
		}
	}
}
/*void ShellInsert(int a[],int dk,int n,int *nCom,int *nMove)//有问题找不到
{   int i,j;
	for(i=dk+1;i<=n;i++)
	{
		a[0]=a[i];
		for(j=i-dk;j>0 && a[0]<a[j];j-=dk){
			a[j+dk]=a[j];
			*nCom+=1;
			//printf("%d",dk);
		}
		a[j+dk]=a[0];
		*nMove+=1;
	}
}*/
void HeapSort(int a[], int n, int* nCom, int* nMove)
{
	int i;
	int x;
	*nCom = 0;
	*nMove = 0;
	CreatHeap(a, n, nCom, nMove);
	for (i = n; i > 1; --i)
	{
		x = a[1];
		a[1] = a[i];
		a[i] = x;
		HeapAdjust(a, 1, i - 1, nCom, nMove);
	}
}
void CreatHeap(int a[], int n, int* nCom, int* nMove)
{
	int i;
	for (i = n / 2; i > 0; --i)
	{
		HeapAdjust(a, i, n, nCom, nMove);
	}
}
void HeapAdjust(int a[], int s, int m, int* nCom, int* nMove)
{
	int rc;
	int j;
	rc = a[s];
	for (j = 2 * s; j < m; j *= 2)
	{
		if (j < m && a[j] < a[j + 1])
		{
			j++;
		}
		if (rc > a[j]) break;
		a[s] = a[j]; s = j;
		*nCom += 1;
	}
	a[s] = rc;
	(*nMove)++;
}
void Sort()
{
	float t[12];
	int i, j;
	unsigned int myTime;
	int stat[6][12];
	//	int data[100];
	for (j = 0; j < 12; j++)
		t[j] = 0;
	List data;
	InitList(&data);
	printf("分\t\t\t比较次数\t\t\t\t\t移动次数\n");//五次测试各种算法，每次测试数据一样
	printf("组\tBubble\tInsert\tSelect\tQuick\tShell\tHeap\tBubble\tInsert\tSelect\tQuick\tShell\tHeap\n");
	for (j = 0; j < 5; j++) {
		myTime = (unsigned)time(NULL) + j + 10;
		srand(myTime);
		for (i = 0; i < 100; i++) {
			InsertList(&data, rand() % 1000);//创建测试数据
		}

		BubbleSort(data.elem, 100, &stat[j][0], &stat[j][6]);//冒泡排序测试
		InsertSort(data.elem, 100, &stat[j][1], &stat[j][7]);//插入排序测试
		SelectSort(data.elem, 100, &stat[j][2], &stat[j][8]);//选择排序测试
		QuickSort(data.elem, 100, &stat[j][3], &stat[j][9]);//快速排序测试
		ShellSort(data.elem, 100, &stat[j][4], &stat[j][10]);//希尔排序测试
		HeapSort(data.elem, 100, &stat[j][5], &stat[j][11]);//堆排序测试
		t[0] += stat[j][0]; t[1] += stat[j][1]; t[2] += stat[j][2]; t[3] += stat[j][3]; t[4] += stat[j][4]; t[5] += stat[j][5]; t[6] += stat[j][6]; t[7] += stat[j][7]; t[8] += stat[j][8]; t[9] += stat[j][9]; t[10] += stat[j][10]; t[11] += stat[j][11];
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", j + 1, stat[j][0], stat[j][1], stat[j][2], stat[j][3], stat[j][4], stat[j][5], stat[j][6], stat[j][7], stat[j][8], stat[j][9], stat[j][10], stat[j][11]);
		ClearList(&data);
	}
	printf("平均\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n", t[0] / 5, t[1] / 5, t[2] / 5, t[3] / 5, t[4] / 5, t[5] / 5, t[6] / 5, t[7] / 5, t[8] / 5, t[9] / 5, t[10] / 5, t[11] / 5);
}
