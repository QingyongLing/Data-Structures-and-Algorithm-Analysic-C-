#include "P12.1_T_Splay_Tree.h"

#include <stdio.h>

TST_Splay_Tree   TST_MakeEmpty(TST_Splay_Tree T)
{

}
TST_Splay_Tree   TST_Find(TST_ElementType x, TST_Splay_Tree T)
{

}
TST_Splay_Tree   TST_FindMin(TST_Splay_Tree T)
{

}
TST_Splay_Tree   TST_FindMax(TST_Splay_Tree T)
{

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
}
TST_Splay_Tree   TST_Insert(TST_ElementType x, TST_Splay_Tree T)
{

}
TST_Splay_Tree   TST_Remove(TST_ElementType x, TST_Splay_Tree T)
{

}