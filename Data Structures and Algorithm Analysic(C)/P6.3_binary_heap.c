#include "P6.3_binary_heap.h"
#include <stdio.h>
#include <limits.h>
#include "Draw_Heap.h"
#include <stdlib.h>

BH_PriorityQueue BH_Initialize(int MaxElement)
{
	BH_PriorityQueue H;
	if (MaxElement < BH_MINSIZE)
		printf("Priority queue size is too small");
	H = malloc(sizeof(struct BH_HeapStruct));
	if (H == NULL)
		printf("H OUT of Space");
	H->Elements = malloc((MaxElement+1)*sizeof(BH_ElementType));
	if (H->Elements == NULL)
		printf("Out of space ");

	H->Capacity = MaxElement;
	H->Size = 0;
	H->Elements[0]=INT_MIN;
	return H;
}
void             BH_Destory(BH_PriorityQueue H)
{
	if (H != NULL)
	{
		if (H->Elements != NULL)
			free(H->Elements);
		free(H);
	}
}
void             BH_MakeEmpty(BH_PriorityQueue H)
{
	H->Size = 0;
}
void             BH_Insert(BH_ElementType x, BH_PriorityQueue H)
{
	int i;
	if (BH_Full(H))
	{
		printf("Priority queue is full");
		return;
	}
	for (i = ++H->Size; H->Elements[i / 2] > x; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = x;
}
BH_ElementType   BH_DeleteMin(BH_PriorityQueue H)
{
	int i, child;
	BH_ElementType MinElement, LastElement;
	if (BH_IsEmpty(H))
	{
		printf("Priority queue is empty");
		return H->Elements[0];
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = child)
	{
		child = i * 2;
		if (child != H->Size&&H->Elements[child + 1] < H->Elements[child])
			child++;

		if (LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
BH_ElementType   BH_FindMin(BH_PriorityQueue H)
{
	if (BH_IsEmpty(H))
		return H->Elements[1];
	else
		return H->Elements[0];
}
int              BH_IsEmpty(BH_PriorityQueue H)
{
	return H->Size == 0 ? 1 : 0;
}
int              BH_Full(BH_PriorityQueue H)
{
	return H->Size == H->Capacity - 1 ? 1 : 0;
}
void             BH_Test()
{
	BH_PriorityQueue Q = BH_Initialize(22);
	int num[] = { 2, 3, 5, 7, 9, 12, 11, 4, 21, 56, 78, 22, 33, 79, 20, 31, 26, 18, 19, 58, 15 };
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
		BH_Insert(num[i], Q);
	Draw_Binary_Heap(Q,"gif","Heap1.gif");
	for (int i = 0; i < sizeof(num) / sizeof(int) / 2; ++i)
		BH_DeleteMin(Q);
	Draw_Binary_Heap(Q, "gif", "Heap2.gif");
	BH_Destory(Q);
}


