#include "P12.1_T_Splay_Tree.h"

#include <stdio.h>
static TST_Position SingleRotateWithLeft(TST_Position K2)
{
	TST_Position K1;
	K1 = K2->Left;
	K2->Left = K1->Right;
	K1->Right = K2;
	return K1;  
}
static TST_Position SingleRotateWithRight(TST_Position K1)
{
	TST_Position K2;
	K2 = K1->Right;
	K1->Right = K2->Left;
	K2->Left = K1;
	return K2;  
}
static TST_Splay_Tree TST_Splay(TST_ElementType x, TST_Position P)
{
	static TST_Splay_Node Header;

	TST_Position LeftTreeMax, RightTreeMin;

	Header.Left = Header.Right = NullNode;
	LeftTreeMax = RightTreeMin = &Header;
	
	NullNode->Element = x;

	while (x != P->Element)
	{
		if (x < P->Element)
		{
			if (x < P->Left->Element)
				P = SingleRotateWithLeft(P);
			if (P->Left == NullNode)
				break;
			RightTreeMin->Left = P;
			RightTreeMin = P;
			P = P->Left;
		}
		else
		{
			if (x>P->Right->Element)
				P = SingleRotateWithRight(P);
			if (P->Right == NullNode)
				break;
			LeftTreeMax->Right = P;
			LeftTreeMax = P;
			P = P->Right;
		}
	}
	LeftTreeMax->Right = P->Left;
	RightTreeMin->Left = P->Right;
	P->Left = Header.Right;
	P->Right = Header.Left;

	return P;
}

TST_Splay_Tree   TST_MakeEmpty(TST_Splay_Tree T)
{
	if (T != NullNode)
	{
		TST_MakeEmpty(T->Left);
		TST_MakeEmpty(T->Right);
		free(T);
	}
	return NullNode;
}
TST_Splay_Tree   TST_Find(TST_ElementType x, TST_Splay_Tree T)
{
	return TST_Splay(x, T);
}
TST_Splay_Tree   TST_FindMin(TST_Splay_Tree T)
{
	if (T != NullNode)
	{
		TST_Position temp = T;
		while (temp->Left != NullNode)
			temp = temp->Left;
		return TST_Splay(temp->Element, T);
	}
	return T;
}
TST_Splay_Tree   TST_FindMax(TST_Splay_Tree T)
{
	if (T != NullNode)
	{
		TST_Position temp = T;
		while (temp->Right != NullNode)
			temp = temp->Right;
		return TST_Splay(temp->Element, T);
	}
	return T;
}
TST_Splay_Tree   TST_Initialize(void)
{
	if (NullNode == NULL)
	{
		NullNode = malloc(sizeof(TST_Splay_Node));
		if (NullNode == NULL)
			printf("Out of Space!");
		NullNode->Left = NullNode->Right = NullNode;
	}
	return NullNode;
}
TST_Splay_Tree   TST_Insert(TST_ElementType x, TST_Splay_Tree T)
{
	static TST_Position NewNode = NULL; 

	if (NewNode == NULL)
	{
		NewNode = malloc(sizeof(TST_Splay_Node));
		if (NewNode == NULL)
			printf("Out of space!");
	}
	NewNode->Element = x;

	if (T == NullNode)
	{
		NewNode->Left = NewNode->Right = NullNode;
		T = NewNode;
	}
	else
	{
		T = TST_Splay(x, T);
		if (x < T->Element)
		{
			NewNode->Left = T->Left;
			NewNode->Right = T;
			T->Left = NullNode;
			T = NewNode;
		}
		else if (T->Element < x)
		{
			NewNode->Right = T->Right;
			NewNode->Left = T; 
			T->Right = NullNode;
			T = NewNode;
		}
		else
			return T;
	}
	NewNode = NULL;
	return T;
}
TST_Splay_Tree   TST_Remove(TST_ElementType x, TST_Splay_Tree T)
{
	TST_Position NewTree;

	if (T != NullNode)
	{
		T = TST_Splay(x, T);
		if (x == T->Element)
		{
			if (T->Left == NullNode)
				NewTree = T->Right;
			else
			{
				NewTree = T->Left;
				NewTree = TST_Splay(x, NewTree);
				NewTree->Right = T->Right;
			}
			free(T);
			T = NewTree;
		}
	}
	return T;
}
void             TST_Display(TST_Splay_Tree T)
{
	if (T != NullNode)
	{
		printf("%d ", T->Element);
		TST_Display(T->Left);
		TST_Display(T->Right);
	}
}
void             TST_Test()
{
	int num[] = { 12, 54, 63, 23, 45, 78, 35, 99, 87, 56, 74 };
	TST_Splay_Tree T = TST_Initialize();
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
		T = TST_Insert(num[i], T);
	printf("%d\n", T->Element);
	printf("%d\n", (T = TST_FindMax(T))->Element);
	TST_Display(T);
	printf("\n");
	printf("%d\n", (T = TST_FindMin(T))->Element);
	T = TST_MakeEmpty(T);
}
