#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct ST_Node;
typedef struct ST_Node *ST_Position;
typedef struct ST_Node *ST_Tree;
#define SPLAY_ElementType int

ST_Tree     ST_MakeEmpty(ST_Tree T);
ST_Position ST_Find(SPLAY_ElementType x, ST_Tree T);
ST_Position ST_FindMin(ST_Tree T);
ST_Position ST_FindMax(ST_Tree T);
ST_Tree     ST_Insert(SPLAY_ElementType x, ST_Tree T);
ST_Tree     ST_Delete(SPLAY_ElementType x, ST_Tree T);
void        ST_Display(ST_Tree p);

static ST_Position SplayingLeft(ST_Position k2);
static ST_Position SplayingLeftLeft(ST_Position k3);
static ST_Position SplayingLeftRight(ST_Position k3);
static ST_Position SplayingRight(ST_Position k2);
static ST_Position SplayingRightLeft(ST_Position k3);
static ST_Position SplayingRightRight(ST_Position k3);

struct ST_Node
{
	SPLAY_ElementType  Element;
	ST_Tree         Left;
	ST_Tree         Right;
};

ST_Tree     ST_MakeEmpty(ST_Tree T)
{
	if (T != NULL)
	{
		ST_MakeEmpty(T->Left);
		ST_MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}
ST_Position ST_FindGrandson(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	if (T->Element == x)
		return T;

	//ST_Position pos;
	if (x > T->Element)
		T->Right = ST_FindGrandson(x, T->Right);
	else
		T->Left = ST_FindGrandson(x, T->Left);
	
	if (T->Left != NULL)
	{
		if (T->Left->Element == x)
			return T;
		else if (T->Left->Left != NULL&&T->Left->Left->Element == x)
			return SplayingLeftLeft(T);
		else if (T->Left->Right != NULL&&T->Left->Right->Element == x)
			return SplayingLeftRight(T);
	}
	if (T->Right != NULL)
	{
		if (T->Right->Element == x)
			return T;
		else if (T->Right->Right != NULL&&T->Right->Right->Element == x)
			return SplayingRightRight(T);
		else if (T->Right->Left != NULL&&T->Right->Left->Element == x)
			return SplayingRightLeft(T);
	}
	return T;
}
ST_Position ST_Find(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	if (T->Element == x)
		return T;
	T = ST_FindGrandson(x, T);
	if (T->Left != NULL&&T->Left->Element == x)
		return SplayingLeft(T);
	else if (T->Right != NULL&&T->Right->Element == x)
		return SplayingRight(T);
	return T;
}
ST_Position ST_FindMin(ST_Tree T)
{
	if (T != NULL)
	{
		ST_Position root = T;
		while (T->Left != NULL)
			T = T->Left;
		return ST_Find(T->Element,root);
	}
	return T;
}
ST_Position ST_FindMax(ST_Tree T)
{
	if (T != NULL)
	{
		ST_Position root = T;
		while (T->Right != NULL)
			T = T->Right;
		return ST_Find(T->Element, root);
	}
	return T;
}
ST_Tree     ST_Insert(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
	{
		T = (ST_Tree)malloc(sizeof(struct ST_Node));
		if (T == NULL)
		{
			printf("Out of space");
		}
		else
		{
			T->Element = x;
			T->Left = T->Right = NULL;
		}
	}
	else if (x < T->Element)
		T->Left = ST_Insert(x, T->Left);
	else if (x>T->Element)
		T->Right = ST_Insert(x, T->Right);
	return T;
}
ST_Tree     ST_Delete(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	T = ST_Find(x, T);
	ST_Tree L = T->Left, R = T->Right;
	free(T);
	if (L != NULL)
	{
		L = ST_FindMax(L);
		L->Right = R;
		return L;
	}
	else if (R != NULL)
	{
		R = ST_FindMin(R);
		R->Left = L;
		return R;
	}
	else
		return NULL; 
}
void           ST_Display(ST_Tree p)
{
	if (p != NULL)
	{
		printf("%d ", p->Element);
		ST_Display(p->Left);
		ST_Display(p->Right);
	}
}

static ST_Position SplayingLeft(ST_Position k2)
{
	/*×óµ¥Ðý×ª*/
	ST_Position k1;
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;
	return k1;
}
static ST_Position SplayingLeftLeft(ST_Position k3)
{
	/*        k3                 k1                 */
	/*       /  \               /  \                */
	/*      k2   d             a    k2              */
	/*     /  \                    /  \             */
	/*    k1   c       -->        b    k3           */
	/*   /  \                         / \           */
	/*  a    b                       c   d          */
	/*                                              */
	ST_Position k2 = k3->Left;
	ST_Position k1 = k3->Left->Left;
	k3->Left = k2->Right;
	k2->Right = k3;
	k2->Left = k1->Right;
	k1->Right = k2;
	return k1;
}
static ST_Position SplayingLeftRight(ST_Position k3)
{
	/*                                                     */
	/*        k3         --                 k2             */
	/*       /  \                          /  \            */
	/*      k1   d       --              k1    k3          */
	/*     /  \                         /  \   / \         */
	/*    a    k2        --            a   b  c   d        */
	/*        /  \                                         */
	/*       b    c      --                                */
	ST_Position k1 = k3->Left;
	ST_Position k2 = k3->Left->Right;
	k1->Right = k2->Left;
	k3->Left = k2->Right;
	k2->Left = k1;
	k2->Right = k3;
	return k2;
}
static ST_Position SplayingRight(ST_Position k2)
{
	ST_Position k1;
	k1 = k2->Right;
	k2->Right = k1->Left;
	k1->Left = k2;
	return k1;
}
static ST_Position SplayingRightLeft(ST_Position k3)
{
	/*                                                  */
	/*        k3                         k2             */
	/*       /  \                       /  \            */
	/*      d   k1        -->          k3   k1          */
	/*          / \                   / \   / \         */
	/*         k2  a                 d   b c   a        */
	/*        /  \                                      */
	/*       b    c                                     */
	ST_Position k1 = k3->Right;
	ST_Position k2 = k3->Right->Left;
	k3->Right = k2->Left;
	k1->Left = k2->Right;
	k2->Left = k3;
	k2->Right = k1;
	return k2;
}
static ST_Position SplayingRightRight(ST_Position k3)
{
	/*        k1                 k3                 */
	/*       /  \               /  \                */
	/*      k2   d             a    k2              */
	/*     /  \         <--        /  \             */
	/*    k3   c                  b    k1           */
	/*   /  \                         / \           */
	/*  a    b                       c   d          */
	/*                                              */
	ST_Position k2 = k3->Right;
	ST_Position k1 = k3->Right->Right;
	k3->Right = k2->Left;
	k2->Left = k3;
	k2->Right = k1->Left;
	k1->Left = k2;
	return k1;
}
int Num_in_Array(int* a, int num, int N)
{
	int in = 0;
	for (int i = 0; i < N; ++i)
	{
		if (num == a[i])
		{
			in = 1;
			break;
		}
	}
	return in;
}


void ST_Test()
{
	srand((unsigned)time(0));
#define N 100 
	//int num[7] = { 7, 6, 5, 4, 3, 2, 1 };
	int num[N];
	for (int i = 0; i < N; )
	{
		int temp = rand() % 300 + 1;
		if (Num_in_Array(num, temp, i) == 0)
			num[i++] = temp;
	}
	ST_Tree p = NULL;
	for (int i = 0; i < N; ++i)
		p = ST_Insert(num[i], p);
	ST_Display(p);
	printf("\n");
	for (int i = 0; i < 100; ++i)
	{
		int temp = rand() % 100;
		p = ST_Find(num[temp], p);
		p = ST_FindMax(p);
		p = ST_FindMin(p);
	}
	
	ST_Display(p);
	for (int i = 0; i < N; ++i)
		p = ST_Delete(num[i], p);
	p = ST_MakeEmpty(p);
}