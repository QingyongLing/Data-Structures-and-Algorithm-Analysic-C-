#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <stdio.h>
#include <stdlib.h>
#include "CommonNode.h"

typedef struct Node BST_Node;
typedef BST_Node *BST_Postion;
typedef BST_Node *BST_SearchTree;

BST_SearchTree BST_Makeempty(BST_SearchTree T);
BST_SearchTree BST_Insert(BST_SearchTree T, ElementType e);
BST_SearchTree BST_Delete(BST_SearchTree T, ElementType e);
BST_Postion    BST_Find(ElementType e, BST_SearchTree T);
BST_Postion    BST_FindMin(BST_SearchTree T);
BST_Postion    BST_FindMax(BST_SearchTree T);
void           BST_Display(BST_SearchTree T,enum Traversal b);
void           BST_Test();

#endif
