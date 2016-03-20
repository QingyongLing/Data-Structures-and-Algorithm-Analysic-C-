#include "P4.5_Splay_Tree.h"

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
ST_Position ST_FindGrandson(ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	if (T->Element == x)
		return T;

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
ST_Position ST_Find(ElementType x, ST_Tree T)
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
		return ST_Find(T->Element, root);
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
ST_Tree     ST_Insert(ElementType x, ST_Tree T)
{
	if (T == NULL)
	{
		T = (ST_Tree)malloc(sizeof(ST_Node));
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
ST_Tree     ST_Delete(ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	T = ST_Find(x, T);
	if (T->Element == x)
	{
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
	return T;
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
int ST_Num_In_Array(int* a, int num, int n)
{
	int in = 0;
	for (int i = 0; i < n; ++i)
	{
		if (num == a[i])
		{
			in = 1;
			break;
		}
	}
	return in;
}
void ST_Tree_Rightful_Test(ST_Tree p)
{
	if (p != NULL)
	{
		if (p->Left != NULL)
			assert(p->Element>p->Left->Element);
		if (p->Right != NULL)
			assert(p->Element < p->Right->Element);
		ST_Tree_Rightful_Test(p->Left);
		ST_Tree_Rightful_Test(p->Right);
	}
}

void ST_Test()
{
	srand((unsigned)time(0));
#define AVL_N 100 
	int num[AVL_N];
	int maxnum, minnum;
	for (int i = 0; i < AVL_N;)
	{
		int temp = rand() % 300 + 1;
		if (i == 0)
		{
			maxnum = minnum = temp;
		}
		if (ST_Num_In_Array(num, temp, i) == 0)
			num[i++] = temp;
		maxnum = temp > maxnum ? temp : maxnum;
		minnum = temp < minnum ? temp : minnum;
	}

	ST_Tree p = NULL;
	for (int i = 0; i < AVL_N; ++i)
	{
		p = ST_Insert(num[i], p);
		ST_Tree_Rightful_Test(p);
	}
	ST_Display(p);
	printf("\n");

	for (int i = 0; i < 100; ++i)
	{
		int temp = rand() % 300 + 400;
		int lastroot = p->Element;
		p = ST_Find(temp, p);
		assert(lastroot == p->Element);
	}

	for (int i = 0; i < 100; ++i)
	{
		int temp = rand() % 100;
		p = ST_Find(num[temp], p);
		assert(num[temp] == p->Element);
		p = ST_FindMax(p);
		assert(maxnum == p->Element);
		p = ST_FindMin(p);
		assert(minnum == p->Element);
	}

	for (int i = 0; i < 100; ++i)
	{
		int temp = rand() % 300 + 400;
		int lastroot = p->Element;
		p = ST_Delete(temp, p);
		assert(lastroot == p->Element);
	}

	for (int i = 0; i < AVL_N; ++i)
	{
		p = ST_Delete(num[i], p);
		ST_Tree_Rightful_Test(p);
	}
	p = ST_MakeEmpty(p);
	assert(p == NULL);
}