#include <stdio.h>
#include <stdlib.h>

struct BT_Node;
typedef struct BT_Node *BT_Position;
typedef struct BT_Node *BT_Tree;

#define M 4
#define BT_ElementType int
#define BT_bool  char
#define BT_true  1
#define BT_false 0

struct BT_Node
{
	/*the num of keyword*/
	unsigned char   Num;
	BT_Position     Parent;
	BT_Position     Son[M];
	BT_ElementType  Keyword[M-1];
};

BT_bool     BT_Is_leaf(BT_Position T);
BT_Position BT_Make_BT_Node();
BT_Tree     BT_MakeEmpty(BT_Tree T);
BT_Position BT_Leaf_Split(BT_Position p);
void        BT_Add_Keyword(BT_ElementType x, BT_Position p);
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T);
BT_Tree     BT_Delete(BT_ElementType x, BT_Tree T);

BT_bool     BT_Is_leaf(BT_Position T)
{
	if (T != NULL)
	{
		if (T->Son[0] == NULL)
			return BT_true;
	}
	return BT_false;
}
BT_Position BT_Make_BT_Node()
{
	BT_Position T = (BT_Position)malloc(sizeof(struct BT_Node));
	if (T == NULL)
	{
		printf("Out of space");
	}
	else
	{
		T->Num = 0;
		T->Parent = NULL;
		for (int i = 0; i < M; ++i)
			T->Son[i] = NULL;
	}
	return T;
}
BT_Tree     BT_MakeEmpty(BT_Tree T)
{
	if (T != NULL)
	{
		for (int i = 0; i < T->Num; ++i)
			if (T->Son[i] != NULL)
				T->Son[i] = BT_MakeEmpty(T->Son[i]);
		free(T);
		T = NULL;
	}
	return T;
}
BT_Position BT_Leaf_Split(BT_Position p)
{
	if (p->Parent == NULL)
	{

	}
}
void        BT_Add_Keyword(BT_ElementType x, BT_Position p)
{
	int index = 0;
	for (int i = p->Num-1; i>-1; --i)
	{
		if (p->Keyword[i] < x)
		{
			index = i;
			break;
		}
	}
	for (int i = p->Num - 1; i > index - 1; --i)
		p->Keyword[i + 1] = p->Keyword[i];
	p->Keyword[index] = x;
	p->Num++;
}
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T)
{
	if (T == NULL|BT_Is_leaf(T)==BT_true)
	{
		T = BT_Make_BT_Node();
		BT_Add_Keyword(x, T);
		/*split*/
		if (T->Num == M)
			T = BT_Leaf_Split(T);
	}
}