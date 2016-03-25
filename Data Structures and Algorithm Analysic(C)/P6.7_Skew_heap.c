#include "P6.7_Skew_Heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "Draw_Heap.h"


SH_PriorityQueue SH_Initialize(void)
{
	return NULL;
}
void             SH_MakeEmpty(SH_PriorityQueue H)
{
	if (H != NULL)
	{
		SH_MakeEmpty(H->Left);
		SH_MakeEmpty(H->Right);
		free(H);
	}
}
SH_ElementType   SH_FindMin(SH_PriorityQueue H)
{
	return H == NULL ? SH_ElementType_MIN : H->Element;
}
int              SH_IsEmpty(SH_PriorityQueue H)
{
	return H == NULL ? 1 : 0;
}
SH_PriorityQueue SH_Merge(SH_PriorityQueue H1, SH_PriorityQueue H2)
{
	if (H1 == NULL)
		return H2;
	if (H2 == NULL)
		return H1;
	if (H1->Element < H2->Element)
		return SH_Merge1(H1, H2);
	else
		return SH_Merge1(H2, H1);
}

SH_PriorityQueue SH_Insert1(SH_ElementType x, SH_PriorityQueue H)
{
	SH_PriorityQueue n = malloc(sizeof(struct SH_Heap_Node));
	if (n == NULL)
	{
		printf("Out of space");
	}
	else
	{
		n->Element = x;
		n->Left = NULL;
		n->Right = NULL;
		H = SH_Merge(n, H);
	}
	return H;
}
SH_PriorityQueue SH_DeleteMin1(SH_PriorityQueue H)
{
	if (H != NULL)
	{
		SH_PriorityQueue Left, Right;
		Left = H->Left;
		Right = H->Right;
		free(H);
		return SH_Merge(Left, Right);
	}
	else
	{
		printf("Priority queue is empty!");
		return H;
	}
}
static SH_PriorityQueue SH_Merge1(SH_PriorityQueue H1, SH_PriorityQueue H2)
{
	if (H1->Left == NULL)
		H1->Left = H2;
	else
	{
		H1->Right = SH_Merge(H1->Right, H2);
		SH_PriorityQueue temp = H1->Left;
		H1->Left = H1->Right;
		H1->Right = temp;
	}
	return H1;
}

void SH_Skew_Heap_Test()
{
	SH_PriorityQueue H = SH_Initialize();
	int num[] = { 2, 3, 5, 7, 9, 12, 11, 4, 21, 56, 78, 22, 33, 79, 20, 31, 26, 18, 19, 58, 15 };
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
		SH_Insert(num[i], H);

	int others[] = { 76, 88, 43, 55, 90 };
	SH_PriorityQueue H2 = SH_Initialize();
	for (int i = 0; i < sizeof(others) / sizeof(int); ++i)
		SH_Insert(others[i], H2);
	H = SH_Merge(H, H2);

	/*in fact you can use the Draw_Leftist_Heap to draw the Heap(Lazy...) */
	//Draw_Leftist_Heap((SH_PriorityQueue)H, "gif", "Skew_heap.gif");
	for (int i = 0; i < sizeof(num) / sizeof(int) / 2; ++i)
		SH_DeleteMin(H);
	//Draw_Leftist_Heap((SH_PriorityQueue)H, "gif", "Skew_heap2.gif");
	SH_MakeEmpty(H);
}
