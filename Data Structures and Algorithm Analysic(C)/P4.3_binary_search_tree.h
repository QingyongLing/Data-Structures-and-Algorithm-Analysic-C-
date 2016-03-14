#include <stdio.h>
#include <stdlib.h>

struct BST_Node;
typedef struct BST_Node *BST_Postion;
typedef struct BST_Node *BST_SearchTree;

#define BST_ElementType int

enum BST_Traversal
{
	Preorder = 1,
	inorder = 2,
	Postorder = 3
};

BST_SearchTree BST_Makeempty(BST_SearchTree T);
BST_SearchTree BST_Insert(BST_SearchTree T, BST_ElementType e);
BST_SearchTree BST_Delete(BST_SearchTree T, BST_ElementType e);
BST_Postion    BST_Find(BST_ElementType e, BST_SearchTree T);
BST_Postion    BST_FindMin(BST_SearchTree T);
BST_Postion    BST_FindMax(BST_SearchTree T);
void           BST_Display(BST_SearchTree T,enum BST_Traversal b);

struct BST_Node
{
	BST_ElementType     element;
	BST_SearchTree  Left;
	BST_SearchTree  Right;
};

/*NOTE: T=BST_Makeempty(T);*/
BST_SearchTree BST_Makeempty(BST_SearchTree T)
{
	if (T != NULL)
	{
		BST_Makeempty(T->Left);
		BST_Makeempty(T->Right);
		free(T);
	}
	return NULL;
}
/*NOTE: T=BST_Insert(T,e);*/
BST_SearchTree BST_Insert(BST_SearchTree T, BST_ElementType e)
{
	/*T==NULL so we make a Node and return the pointer of this node  (return T)*/
	if (T == NULL)
	{
		T = (BST_SearchTree)malloc(sizeof(struct BST_Node));
		if (T == NULL)
		{
			printf("Out of space");
		}
		else
		{
			T->element = e;
			T->Left = T->Right = NULL;
		}
	}
	/*add the new node to the tree,either Left or Right*/
	else if (e < T->element)
		T->Left = BST_Insert(T->Left, e);
	else if (e>T->element)
		T->Right = BST_Insert(T->Right, e);
	return T;
}
/*NOTE: T=BST_Delete(T,e)*/
BST_SearchTree BST_Delete(BST_SearchTree T, BST_ElementType e)
{
	BST_Postion TmpCell;
	if (T == NULL)
	{
		printf("Element can not find");
	}
	else if (e < T->element)
		T->Left = BST_Delete(T->Left, e);
	else if (e>T->element)
		T->Right = BST_Delete(T->Right, e);
	else if (T->Left&&T->Right)
	{
		TmpCell = BST_FindMin(T->Right);
		T->element = TmpCell->element;
		T->Right = BST_Delete( T->Right,T->element);
	}
	else
	{
		TmpCell = T;
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}
BST_Postion    BST_Find(BST_ElementType e, BST_SearchTree T)
{
	if (T == NULL)
		return NULL;
	if (e < T->element)
		return BST_Find(e, T->Left);
	else if (e>T->element)
		return BST_Find(e, T->Right);
	else
		return T;
}
BST_Postion    BST_FindMin(BST_SearchTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return BST_FindMin(T->Left);
}
BST_Postion    BST_FindMax(BST_SearchTree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}
void           BST_Display(BST_SearchTree T,enum BST_Traversal b)
{
	if (T == NULL)
		return;
	if (b == Preorder)
		printf("%d ", T->element);
	BST_Display(T->Left, b);
	if (b == inorder)
		printf("%d ", T->element);
	BST_Display(T->Right, b);
	if (b == Postorder)
		printf("%d ", T->element);
}

void BST_Test()
{
	int a[] = { 1, 4, 2, 7, 3, 8, 4, 6, 8, 9, 0 };
	BST_SearchTree p = NULL;
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i)
		p=BST_Insert(p,a[i]);
	BST_Display(p, Preorder);
	printf("\n");
	p = BST_Delete(p, 1);
	BST_Display(p, inorder);
	printf("\n");
}

