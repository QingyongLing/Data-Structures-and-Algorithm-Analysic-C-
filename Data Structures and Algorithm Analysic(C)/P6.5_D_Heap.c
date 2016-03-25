#include "P6.5_D_Heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Draw_Heap.h"

DH_PriorityQueue DH_Initialize(int MaxElement)
{
	DH_PriorityQueue H;
	if (MaxElement < DH_MINSIZE)
		printf("Priority queue size is too small");
	H = malloc(sizeof(struct DH_HeapStruct));
	if (H == NULL)
		printf("H OUT of Space");
	H->Elements = malloc((MaxElement + 1)*sizeof(DH_ElementType));
	if (H->Elements == NULL)
		printf("Out of space ");

	H->Capacity = MaxElement;
	H->Size = 0;
	H->Elements[0] = INT_MIN;
	return H;
}
void             DH_Destory(DH_PriorityQueue H)
{
	if (H != NULL)
	{
		if (H->Elements != NULL)
			free(H->Elements);
		free(H);
	}
}
void             DH_MakeEmpty(DH_PriorityQueue H)
{
	H->Size = 0;
}
void             DH_Insert(DH_ElementType x, DH_PriorityQueue H)
{
	int i;
	if (DH_Full(H))
	{
		printf("Priority queue is full");
		return;
	}
	/*son=[ki-k+2,ki+1] father=i*/
	for (i = ++H->Size; H->Elements[(i + DH_D - 2) / DH_D] > x; i = (i + DH_D - 2) / DH_D)
		H->Elements[i] = H->Elements[(i + DH_D - 2) / DH_D];
 	H->Elements[i] = x;
}
DH_ElementType   DH_DeleteMin(DH_PriorityQueue H)
{
	int i, child;
	DH_ElementType MinElement, LastElement;
	if (DH_IsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * DH_D - DH_D + 2 <= H->Size; i = child)
	{
		int start = i  * DH_D - DH_D + 2;
		child = start;
		for (int j = 1; j < DH_D; ++j)
		{
			if (start+j <= H->Size&&H->Elements[start + j]<H->Elements[child])
			{
				child = start + j;
			}
		}

		if (LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
DH_ElementType   DH_FindMin(DH_PriorityQueue H)
{
	if (DH_IsEmpty(H))
		return H->Elements[1];
	else
		return H->Elements[0];
}
int              DH_IsEmpty(DH_PriorityQueue H)
{
	return H->Size == 0 ? 1 : 0;
}
int              DH_Full(DH_PriorityQueue H)
{
	return H->Size == H->Capacity - 1 ? 1 : 0;
}

void             DH_Test()
{
	DH_PriorityQueue Q = DH_Initialize(22);
	int num[] = { 2, 3, 5, 7, 9, 12, 11, 4, 21, 56, 78, 22, 33, 79, 20, 31, 26, 18, 19, 58, 15 };
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
		DH_Insert(num[i], Q);
	Draw_D_Heap(Q, "gif", "Heap1.gif");
	for (int i = 0; i < sizeof(num) / sizeof(int) / 2; ++i)
		DH_DeleteMin(Q);
	Draw_D_Heap(Q, "gif", "Heap2.gif");
	DH_Destory(Q);
}
