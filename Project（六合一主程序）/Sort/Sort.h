#pragma once
#pragma once
#define INIT_LIST_SIZE 100
#define INCREMENT_SIZE 10

typedef struct {
	int* elem;
	int length;
	int size;
}List;

void InitList(List* data);
void DestroyList(List* data);
void InsertList(List* data, int a);
void ClearList(List* data);

void Sort();
void BubbleSort(int a[], int n, int* nCom, int* nMove);
void InsertSort(int a[], int n, int* nCom, int* nMove);
void SelectSort(int a[], int n, int* nCom, int* nMove);
void QuickSort(int a[], int n, int* nCom, int* nMove);
void QSort(int a[], int low, int high, int* nCom, int* nMove);
int Partition(int a[], int low, int high, int* nCom, int* nMove);
void ShellSort(int a[], int n, int* nCom, int* nMove);
//void ShellInsert(int a[], int dk, int n, int* nCom, int* nMove);
void HeapSort(int a[], int n, int* nCom, int* nMove);
void HeapAdjust(int a[], int s, int m, int* nCom, int* nMove);
void CreatHeap(int a[], int n, int* nCom, int* nMove);



#pragma once
