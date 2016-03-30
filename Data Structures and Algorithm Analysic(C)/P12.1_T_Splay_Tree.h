#ifndef T_SPLAY_TREE
#define T_SPLAY_TREE

#include <stdlib.h>
#include "CommonNode.h"

typedef struct Node TST_Splay_Node;
typedef TST_Splay_Node *TST_Splay_Tree;
typedef TST_Splay_Node *TST_Position;
static  TST_Position NullNode = NULL;

#define TST_ElementType int

TST_Splay_Tree   TST_MakeEmpty(TST_Splay_Tree T);
TST_Splay_Tree   TST_Find(TST_ElementType x, TST_Splay_Tree T);
TST_Splay_Tree   TST_FindMin(TST_Splay_Tree T);
TST_Splay_Tree   TST_FindMax(TST_Splay_Tree T);
TST_Splay_Tree   TST_Initialize(void);
TST_Splay_Tree   TST_Insert(TST_ElementType x, TST_Splay_Tree T);
TST_Splay_Tree   TST_Remove(TST_ElementType x, TST_Splay_Tree T);
void             TST_Display(TST_Splay_Tree T);

void             TST_Test();
#endif