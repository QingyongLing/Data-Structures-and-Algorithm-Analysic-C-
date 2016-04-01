#include "P12.2_Red_Black_Tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

RB_Position NullNode = NULL;
static RB_Position SingleRotateWithLeft(RB_Position k2)
{
	RB_Position k1;
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;
	return k1;
}
static RB_Position SingleRotateWithRight(RB_Position k2)
{
	RB_Position k1;
	k1 = k2->Right;
	k2->Right = k1->Left;
	k1->Left = k2;
	return k1;
}
static RB_Position Rotate(RB_ElementType x, RB_Position Parent)
{
	if (x < Parent->Element)
		return Parent->Left = x < Parent->Left->Element ?
		SingleRotateWithLeft(Parent->Left) :
		SingleRotateWithRight(Parent->Left);
	else
		return Parent->Right = x < Parent->Right->Element ?
		SingleRotateWithLeft(Parent->Right) :
		SingleRotateWithRight(Parent->Right);
}
static RB_Position X, P, GP, GGP;
static void HandleReorient(RB_ElementType x, RedBlackTree T)
{
	X->Color = RB_Red;
	X->Left->Color = RB_Black;
	X->Right->Color = RB_Black;

	if (P->Color == RB_Red)
	{
		GP->Color = RB_Red;
		if ((x < GP->Element) != (x < P->Element))
			P = Rotate(x, GP);
		X = Rotate(x, GGP);
		X->Color = RB_Black;
	}
	T->Right->Color = RB_Black;
}
RedBlackTree  RB_Initialize(void)
{
	RedBlackTree T;
	if (NullNode = NULL)
	{
		NullNode == malloc(sizeof(struct RB_Tree_Node));
		if (NullNode == NULL)
			printf("Out of space!");
		NullNode->Left = NullNode->Right = NullNode;
		NullNode->Color = RB_Black;
		NullNode->Element = RB_Element_MIN;
	}
	T = malloc(sizeof(struct RB_Tree_Node));
	if (T = NULL)
		printf("Out of space!");
	T->Element = RB_Element_MIN;
	T->Left = T->Right = NullNode;
	T->Color = RB_Black;
	return T;
}
RedBlackTree  RB_MakeEmpty(RedBlackTree T)
{

}
RedBlackTree  RB_Insert(RB_ElementType x, RedBlackTree T)
{
	X = P = GP = T;
	NullNode->Element = x;
	while (X->Element != x)
	{
		GGP = GP;
		GP = P;
		P = X;
		if (x < X->Element)
			X = X->Left;
		else
			X = X->Right;
		if (X->Left->Color == RB_Red&&X->Right->Color == RB_Red)
			HandleReorient(x, T);
	}

	if (X != NullNode)
		return NullNode;
	X = malloc(sizeof(struct RB_Tree_Node));
	if (X == NULL)
		printf("Out of Space!");
	X->Element = x;
	X->Left = X->Right = NullNode;

	if (x < P->Element)
		P->Left = X;
	else
		P->Right = X;
	HandleReorient(x, T);
	return T;
}
RedBlackTree  RB_Delete(RB_ElementType x, RedBlackTree T)
{

}