#include "P6.8_Binomial_Queue.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "Draw_Heap.h"

BQ_Queue         BQ_Initialize(void)
{
	BQ_Queue H = malloc(sizeof(struct BQ_Collection));
	if (H == NULL)
	{
		printf("Out of space!");
		return NULL;
	}
	for (int i = 0; i < BQ_MaxTrees; ++i)
	{
		H->TheTrees[i] = NULL;
	}
	H->CurrentSize = 0;
	return H;
}
static void BQ_MakeTreeEmpty(BQ_Position p)
{
	if (p != NULL)
	{
		BQ_MakeTreeEmpty(p->LeftChild);
		BQ_MakeTreeEmpty(p->NextSibling);
		free(p);
	}
}
BQ_Queue         BQ_MakeEmpty(BQ_Queue H)
{
	if (H != NULL)
	{
		for (int i = 0; i < BQ_MaxTrees; ++i)
			if (H->TheTrees[i] != NULL)
				BQ_MakeTreeEmpty(H->TheTrees[i]);
		free(H);
	}
	return NULL;
}
BQ_ElementType   BQ_FindMin(BQ_Queue H)
{
	
	if (BQ_IsEmpty(H))
	{
		printf("Empty binomial queue");
		return BQ_Element_MIN;
	}
	else
	{
		BQ_ElementType MinItem = BQ_Element_MIN;
		for (int i = 0; i < BQ_MaxTrees; i++)
		{
			if (H->TheTrees[i] && H->TheTrees[i]->Element < MinItem)
				MinItem = H->TheTrees[i]->Element;
		}
		return MinItem;
	}
}
int              BQ_IsEmpty(BQ_Queue Q)
{
	return Q->CurrentSize == 0;
}
static BQ_Tree   BQ_CombineTrees(BQ_Tree T1, BQ_Tree T2)
{
	if (T1->Element > T2->Element)
		return BQ_CombineTrees(T2, T1);
	T2->NextSibling = T1->LeftChild;
	T1->LeftChild = T2;
	return T1;
}
BQ_Queue         BQ_Merge(BQ_Queue H1, BQ_Queue H2)
{
	BQ_Tree T1, T2, Carry = NULL;
	int i, j;
	if (H1->CurrentSize + H2->CurrentSize > BQ_Capacity)
	{
		printf("Merge would exceed capacity!");
		return H1;
	}
	H1->CurrentSize += H2->CurrentSize;

	for (i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2)
	{
		T1 = H1->TheTrees[i];
		T2 = H2->TheTrees[i];

		switch (!!T1+2*!!T2+4*!!Carry)
		{
		case 0:
		case 1:
			break;
		case 2:
			H1->TheTrees[i] = T2;
			H2->TheTrees[i] = NULL;
			break;
		case 4:
			H1->TheTrees[i] = Carry;
			Carry = NULL;
			break;
		case 3:
			Carry = BQ_CombineTrees(T1, T2);
			H1->TheTrees[i] = H2->TheTrees[i] = NULL;
			break;
		case 5:
			Carry = BQ_CombineTrees(T1, Carry);
			H1->TheTrees[i] = NULL;
			break;
		case 6:
			Carry = BQ_CombineTrees(T2, Carry);
			H2->TheTrees[i] = NULL;
			break;
		case 7:
			H1->TheTrees[i] = Carry;
			Carry = BQ_CombineTrees(T1, T2);
			H2->TheTrees[i] = NULL;
			break;
		}
	}
	return H1;
}

BQ_Queue         BQ_Insert(BQ_ElementType x, BQ_Queue H)
{
	BQ_Position NewNode;
	BQ_Queue    OneItem;

	NewNode = malloc(sizeof(struct BQ_Node));
	if (NewNode == NULL)
		printf("Out of space!!!");
	NewNode->LeftChild = NewNode->NextSibling = NULL;
	NewNode->Element = x;

	OneItem = BQ_Initialize();
	OneItem->CurrentSize = 1;
	OneItem->TheTrees[0] = NewNode;

	return BQ_Merge(H, OneItem);
}
BQ_ElementType   BQ_DeleteMin(BQ_Queue H)
{
	int i, j;
	int MinTree;

	BQ_Queue DeletedQueue;
	BQ_Position DeletedTree, OldRoot;
	BQ_ElementType MinItem;

	if (BQ_IsEmpty(H))
	{
		printf("Empty binomial queue");
		return BQ_Element_MIN;
	}

	MinItem = BQ_Element_MAX;
	for (i = 0; i < BQ_MaxTrees; i++)
	{
		if (H->TheTrees[i] && H->TheTrees[i]->Element < MinItem)
		{
			MinItem = H->TheTrees[i]->Element;
			MinTree = i;
		}
	}

	DeletedTree = H->TheTrees[MinTree];
	OldRoot = DeletedTree;
	DeletedTree = DeletedTree->LeftChild;
	free(OldRoot);

	DeletedQueue = BQ_Initialize();
	DeletedQueue->CurrentSize = (1 << MinTree) - 1;
	for (j = MinTree - 1; j >= 0; j--)
	{
		DeletedQueue->TheTrees[j] = DeletedTree;
		DeletedTree = DeletedTree->NextSibling;
		DeletedQueue->TheTrees[j]->NextSibling = NULL;
	}

	H->TheTrees[MinTree] = NULL;
	H->CurrentSize -= DeletedQueue->CurrentSize + 1;

	BQ_Merge(H, DeletedQueue);
	return MinItem;
}

void             BQ_Test()
{
	int num1[] = { 2, 3, 5, 7, 9, 12, 11, 4, 21, 56, 78, 22, 33, 79, 20, 31, 26, 18, 19, 58, 15 };
	int num2[] = { 10, 29, 89, 100, 66, 88, 1, 48 };
	BQ_Queue H1 = BQ_Initialize();
	BQ_Queue H2 = BQ_Initialize();
	for (int i = 0; i < sizeof(num1) / sizeof(int); ++i)
		H1 = BQ_Insert(num1[i], H1);
	for (int i = 0; i < sizeof(num2) / sizeof(int); ++i)
		H2 = BQ_Insert(num2[i], H2);
	Draw_Binomial_Queue(H1, "gif", "H1.gif");
	Draw_Binomial_Queue(H2, "gif", "H2.gif");
	H1 = BQ_Merge(H1, H2);
	Draw_Binomial_Queue(H1, "gif", "H3.gif");
	H1 = BQ_MakeEmpty(H1);
}