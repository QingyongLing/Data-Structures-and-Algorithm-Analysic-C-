#ifndef AVL_TREE
#define AVL_TREE

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
void         AVL_BalanceTest(AVL_Tree T);
void         AVL_Test();

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

#endif
