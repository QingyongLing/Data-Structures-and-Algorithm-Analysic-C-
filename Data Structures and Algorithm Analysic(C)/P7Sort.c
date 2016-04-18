#include "P7Sort.h"
#include <stdlib.h>
#include <stdio.h>

void    Insertion_Sort(Sort_Element_Type A[], int N)
{
	int j, p;
	Sort_Element_Type Tmp;
	/*(1)loop p=1:1:N                                                             */
	/*(2)loop j=p:-1:0                                                            */
	/*(3)find the insert place of Tmp,and move the bigger one back                */
	/*p=1: A[0] A[1] in order  p=2: A[0] A[1] A[2] in order  ...                  */
	for (p = 1; p < N; p++)
	{
		Tmp = A[p];
		for (j = p; j > 0 && A[j - 1] > Tmp; j--)
			A[j] = A[j - 1];
		A[j] = Tmp;
	}
}
void    Shell_Sort(Sort_Element_Type A[], int N)
{
	int i, j, Increment;
	Sort_Element_Type Tmp;
	/*(1) divide A into Increment part,then use Insertion_Sort*/
	for (Increment = N / 2; Increment > 0; Increment /= 2)
	{
		for (i = Increment; i < N; i++)
		{
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			A[j] = Tmp;
		}
	}
}
#define Heap_Sort_Left_Child(i) (2*(i)+1)
static void PerDown(Sort_Element_Type A[], int i, int N)
{
	int Child;
	Sort_Element_Type Tmp;
	for (Tmp = A[i]; Heap_Sort_Left_Child(i) < N; i = Child)
	{
		Child = Heap_Sort_Left_Child(i); 
		if (Child != N - 1 && A[Child + 1] > A[Child])
			Child++;
		if (Tmp < A[Child])
			A[i] = A[Child];
		else 
			break;
	}
	A[i] = Tmp;
}
void    Heap_Sort(Sort_Element_Type A[], int N)
{
	int i;
	/*Build Heap*/  
	for (i = N / 2; i >= 0; i--)
		PerDown(A, i, N);
	/*Delete Max*/
	for (i = N - 1; i > 0; i--)
	{
		Sort_Element_Type temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		PerDown(A, 0, i);
	}
}
static void Merge(Sort_Element_Type A[], Sort_Element_Type TmpArray[], int Lpos, int Rpos, int RightEnd)
{
	int i, LeftEnd, NumElements, TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	/*main loop*/
	while (Lpos <= LeftEnd&&Rpos <= RightEnd)
		if (A[Lpos] <= A[Rpos])
			TmpArray[TmpPos++] = A[Lpos++];
		else
			TmpArray[TmpPos++] = A[Rpos++];

	/*Copy rest of first half*/
	while (Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	/*Copy rest of second half*/
	while (Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];
	/*Copy TmpArray back*/
	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
}
static void Msort(Sort_Element_Type A[], Sort_Element_Type TmpArray[], int Left, int Right)
{
	int Center;
	if (Left < Right)
	{
		Center = (Left + Right) / 2;
		Msort(A, TmpArray, Left, Center);
		Msort(A, TmpArray, Center + 1, Right);
		Merge(A, TmpArray, Left, Center + 1, Right);
	}
}
void    Merge_Sort(Sort_Element_Type A[], int N)
{
	Sort_Element_Type *TmpArray;
	TmpArray = malloc(N*sizeof(Sort_Element_Type));
	if (TmpArray != NULL)
	{
		Msort(A, TmpArray, 0, N - 1);
		free(TmpArray);
	}
	else
	{
		printf("No space for tmp Array");
	}
}
static void Sort_Swap(Sort_Element_Type *a, Sort_Element_Type *b)
{
	Sort_Element_Type temp = *a;
	*a = *b;
	*b = temp;
}
static Sort_Element_Type Median3(Sort_Element_Type A[], int Left, int Right)
{
	int Center = (Left + Right) / 2;
	if (A[Left] > A[Center])
		Sort_Swap(&A[Left], &A[Center]);
	if (A[Left] > A[Right])
		Sort_Swap(&A[Left], &A[Right]);
	if (A[Center] > A[Right])
		Sort_Swap(&A[Center], &A[Right]);

	/*Invariant: A[Left]<=A[Center]<=A[Right] */
	Sort_Swap(&A[Center], &A[Right - 1]);
	return A[Right - 1];
}
#define Cutoff (3)
static void Qsort(Sort_Element_Type A[], int Left, int Right)
{
	int i, j;
	Sort_Element_Type Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot){}
			while (A[--j] > Pivot){}
			if (i < j)
				Sort_Swap(&A[i], &A[j]);
			else
				break;
		}
		Sort_Swap(&A[i], &A[Right - 1]);
		Qsort(A, Left, i - 1);
		Qsort(A, i + 1, Right);
	}
	else
		Insertion_Sort(A + Left, Right - Left + 1);
}
void    Quick_Sort(Sort_Element_Type A[], int N)
{
	Qsort(A, 0, N - 1);
}
void    Quick_Select(Sort_Element_Type A[], int k, int Left, int Right)
{
	int i, j;
	Sort_Element_Type Pivot;

	if (Left + Cutoff <= Right)
	{
		Pivot = Median3(A, Left, Right);
		i = Left;
		j = Right - 1;
		for (;;)
		{
			while (A[++i] < Pivot){}
			while (A[--j] < Pivot){}
			if (i < j)
				Sort_Swap(&A[i], &A[j]);
			else
				break;
		}
		Sort_Swap(&A[i], &A[Right - 1]);

		if (k <= i)
			Quick_Select(A, k, Left, i - 1);
		else if (k > i + 1)
			Quick_Select(A, k, i + 1, Right);
	}
	else
		Insertion_Sort(A + Left, Right - Left + 1);
}