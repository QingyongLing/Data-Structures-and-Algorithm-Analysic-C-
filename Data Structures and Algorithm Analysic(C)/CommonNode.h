#ifndef COMMON_NODE
#define COMMON_NODE

#define ElementType int
struct Node
{
	ElementType         Element;
	struct Node*        Left;
	struct Node*        Right;
};

enum Traversal
{
	Preorder = 1,
	inorder = 2,
	Postorder = 3
};

#endif