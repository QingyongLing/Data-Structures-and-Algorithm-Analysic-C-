#include "P6.6_Leftist_Heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Draw_Heap.h"


LH_PriorityQueue LH_Initialize(void)
{
	return NULL;
}
void             LH_MakeEmpty(LH_PriorityQueue H)
{
	if (!LH_IsEmpty(H))
	{
		LH_MakeEmpty(H->Left);
		LH_MakeEmpty(H->Right);
		free(H);
	}
}
LH_ElementType   LH_FindMin(LH_PriorityQueue H)
{
	if (LH_IsEmpty(H))
		return LH_ElementType_MIN;
	else
		return H->Element;
}
int  LH_IsEmpty(LH_PriorityQueue Q)
{
	return Q == NULL ? 1 : 0;
}
LH_PriorityQueue LH_Merge(LH_PriorityQueue H1, LH_PriorityQueue H2)
{
	if ((H1 == NULL) | (H2 == NULL))
		return H1 == NULL ? H2 : H1;
	if (H1->Element < H2->Element)
		return LH_Merge1(H1, H2);
	else
		return LH_Merge1(H2, H1);
}
LH_PriorityQueue LH_Insert1(LH_ElementType x, LH_PriorityQueue H)
{
	
	LH_PriorityQueue SingleNode;
	SingleNode = malloc(sizeof(struct LH_Heap_Node));
	if (SingleNode == NULL)
		printf("Out of space!");
	else
	{
		SingleNode->Element = x;
		SingleNode->Npl = 0;
		SingleNode->Left = NULL;
		SingleNode->Right = NULL;
		H = LH_Merge(SingleNode, H);	
	}
	return H;
}
LH_PriorityQueue LH_DeleteMin1(LH_PriorityQueue H)
{
	LH_PriorityQueue LeftHeap, RinghtHeap;
	if (LH_IsEmpty(H))
	{
		printf("Priority queue is empty!");
		return H;
	}
	LeftHeap = H->Left;
	RinghtHeap = H->Right;
	free(H);
	return LH_Merge(LeftHeap, RinghtHeap);
}
static LH_PriorityQueue LH_Merge1(LH_PriorityQueue H1, LH_PriorityQueue H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = LH_Merge(H1->Right, H2);
		if (H1->Left->Npl < H1->Right->Npl)
		{
			LH_PriorityQueue temp = H1->Left;
			H1->Left = H1->Right;
			H1->Right = temp;
		}
		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}

void LH_Leftist_Heap_Test()
{
	LH_PriorityQueue H = LH_Initialize();
	int num[] = { 2, 3, 5, 7, 9, 12, 11, 4, 21, 56, 78, 22, 33, 79, 20, 31, 26, 18, 19, 58, 15 };
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
		LH_Insert(num[i], H);

	int others[] = { 76, 88, 43, 55, 90 };
	LH_PriorityQueue H2 = LH_Initialize();
	for (int i = 0; i < sizeof(others) / sizeof(int); ++i)
		LH_Insert(others[i], H2);
	H = LH_Merge(H, H2);

	Draw_Leftist_Heap(H,"gif","Leftist_heap.gif");
	for (int i = 0; i < sizeof(num) / sizeof(int) / 2; ++i)
		LH_DeleteMin(H);
	Draw_Leftist_Heap(H, "gif", "Leftist_heap2.gif");
	LH_MakeEmpty(H);
}