#include <stdio.h>
#include <stdlib.h>

struct AVL_Node;
typedef struct AVL_Node *AVL_Position;
typedef struct AVL_Node *AVL_Tree;
#define AVL_ElementType int

AVL_Tree     AVL_MakeEmpty(AVL_Tree T);
AVL_Position AVL_Find(AVL_ElementType x, AVL_Tree T);
AVL_Position AVL_FindMin(AVL_Tree T);
AVL_Position AVL_FindMax(AVL_Tree T);
AVL_Tree     AVL_Insert(AVL_ElementType x, AVL_Tree T);
AVL_Tree     AVL_Delete(AVL_ElementType x, AVL_Tree T);
void         AVL_Display(AVL_Tree p);

static int AVL_Height(AVL_Position P);
static AVL_Position SingleRotateWithLeft(AVL_Position k2);
static AVL_Position SingleRotateWithRight(AVL_Position k2);
static AVL_Position DoubleRotateWithLeft(AVL_Position k3);
static AVL_Position DoubleRotateWithRight(AVL_Position k3);

struct AVL_Node
{
	AVL_ElementType Element;
	AVL_Tree        Left;
	AVL_Tree        Right;
	int             Height;
};

AVL_Tree     AVL_MakeEmpty(AVL_Tree T)
{
	if (T != NULL)
	{
		AVL_MakeEmpty(T->Left);
		AVL_MakeEmpty(T->Right);
		free(T);
	}
	
	return NULL;
}
AVL_Position AVL_Find(AVL_ElementType x, AVL_Tree T)
{
	if (T == NULL)
		return NULL;
	if (x < T->Element)
		return AVL_Find(x, T->Left);
	else if (x>T->Element)
		return AVL_Find(x, T->Right);
	else
		return T;
}
AVL_Position AVL_FindMin(AVL_Tree T)
{
	if (T != NULL)
		while (T->Left != NULL)
			T = T->Left;
	return T;
}
AVL_Position AVL_FindMax(AVL_Tree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}

AVL_Tree     AVL_Insert(AVL_ElementType x, AVL_Tree T)
{
	if (T == NULL)
	{
		T = (struct AVL_Node *)malloc(sizeof(struct AVL_Node));
		if (T == NULL)
			printf("Out of Space!!!");
		else
		{
			T->Element = x;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (x < T->Element) 
	{
		T->Left = AVL_Insert(x, T->Left);
		if (AVL_Height(T->Left) - AVL_Height(T->Right) == 2)
			if (x < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else if (x > T->Element)
	{
		T->Right = AVL_Insert(x, T->Right);
		if (AVL_Height(T->Right) - AVL_Height(T->Left) == 2)
			if (x < T->Right->Element)
				T = DoubleRotateWithRight(T);
			else
				T = SingleRotateWithRight(T);
	}
	T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;
	return T;
}
void AVL_BalanceTest(AVL_Tree T)
{
	if (T != NULL)
	{
		AVL_BalanceTest(T->Left);
		AVL_BalanceTest(T->Right);
		if (T->Height != (max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1))
			printf("The Height is Not the Max %d\n", T->Element);
		if (abs(AVL_Height(T->Left)-AVL_Height(T->Right))>1)
			printf("This Node Not Balance %d\n", T->Element);
	}
}
AVL_Tree     AVL_Delete(AVL_ElementType x, AVL_Tree T)
{
	if (T == NULL)
		return NULL;
	if (x == T->Element)
	{
		if (T->Left != NULL&&T->Right != NULL)
		{                          
			AVL_Tree temp = T->Right;
			while (temp->Left != NULL)
				temp = temp->Left;
			T->Element = temp->Element;
			T->Right = AVL_Delete(temp->Element, T->Right);     
		}
		else
		{
			AVL_Tree temp = T;
			T = T->Left == NULL ? T->Right : T->Left;
			free(temp);
			return T;
		}
		/*
		if (T->Left != NULL&&T->Right != NULL)
		{
			AVL_Tree temp = T->Left;
			while (temp->Right != NULL)
				temp = temp->Right;
			T->Element = temp->Element;
			T->Left = AVL_Delete(temp->Element, T->Left);
		}
		else
		{
		    AVL_Tree temp = T;
		    T = T->Left == NULL ? T->Right : T->Left;
		    free(temp);
		    return T;
		}
		*/
	}
	else if (x < T->Element)
	{
		T->Left = AVL_Delete(x ,T->Left);
	}
	else
	{
		T->Right = AVL_Delete(x, T->Right);
	}

	T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;

	if (AVL_Height(T->Left) - AVL_Height(T->Right) == 2)
	{
		if (AVL_Height(T->Left->Left) < AVL_Height(T->Left->Right))
			T = DoubleRotateWithLeft(T);
		else
			T = SingleRotateWithLeft(T);
	}
	if (AVL_Height(T->Right) - AVL_Height(T->Left) == 2)
	{
		if (AVL_Height(T->Right->Right) < AVL_Height(T->Right->Left))
			T = DoubleRotateWithRight(T);
		else
			T = SingleRotateWithRight(T);
	}
	return T;
}
void         AVL_Display(AVL_Tree p)
{
	if (p != NULL)
	{
		printf("%d ", p->Element);
		AVL_Display(p->Left);
		AVL_Display(p->Right);
	}
}
static int AVL_Height(AVL_Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}
static AVL_Position SingleRotateWithLeft(AVL_Position k2)
{
	/*         k2         --                k1             */
	/*        /  \                         /  \            */
	/*       k1   a       --              c    k2          */
	/*      /  \               ->        /    /  \         */
	/*     c    b         --            a    b    a        */
	/*    /                                                */
	/*   d                --                               */
	AVL_Position k1;
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;
	k2->Height = max(AVL_Height(k2->Left), AVL_Height(k2->Right)) + 1;
	k1->Height = max(AVL_Height(k1->Left), k2->Height) + 1;
	return k1;
}
static AVL_Position SingleRotateWithRight(AVL_Position k2)
{
	/*         k2          --                   k1         */
	/*        /  \                             /  \        */
	/*       a    k1       --                k2    c       */
	/*           /  \           ->          /  \    \      */
	/*          b    c     --              a    b    d     */
	/*                \                                    */
	/*                 d   --                              */
	AVL_Position k1; 
	k1 = k2->Right;
	k2->Right = k1->Left;
	k1->Left = k2;
	k2->Height = max(AVL_Height(k2->Left), AVL_Height(k2->Right)) + 1;
	k1->Height = max(k2->Height, AVL_Height(k1->Right)) + 1;
	return k1;
}
static AVL_Position DoubleRotateWithLeft(AVL_Position k3)
{
	/* Left-Right b or c single_right(k1)+single_left(k3)  */
	/*                                                     */
	/*        k3         --                 k2             */
	/*       /  \                          /  \            */
	/*      k1   d       --              k1    k3          */
	/*     /  \                         /  \   / \         */
	/*    a    k2        --            a   b? c?  d        */
	/*        /  \                                         */
	/*       b?  c?      --                                */
	k3->Left = SingleRotateWithRight(k3->Left);
	return SingleRotateWithLeft(k3);
}
static AVL_Position DoubleRotateWithRight(AVL_Position k3)
{
	/*similar to DoubleRotateWithLeft*/
	k3->Right = SingleRotateWithLeft(k3->Right);
	return SingleRotateWithRight(k3);
}

void AVL_Test()
{
	int num[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	AVL_Tree p = NULL;
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		p = AVL_Insert(num[i], p);
		AVL_BalanceTest(p);
	}
	for (int i = sizeof(num) / sizeof(int);i!=0; --i)
	{
		p = AVL_Delete(num[i], p);
		AVL_BalanceTest(p);
	}
	p = AVL_MakeEmpty(p);
}

