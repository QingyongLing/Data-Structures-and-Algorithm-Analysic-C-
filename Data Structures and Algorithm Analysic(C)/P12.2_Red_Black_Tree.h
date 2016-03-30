//#ifndef RED_BLACK_TREE
//#define RED_BLACK_TREE

#define RB_ElementType int
struct  RB_Tree_node;
typedef struct RB_Tree_Node* RedBlackTree;
enum    RB_Color_Type{Red,Black};

RedBlackTree  RB_Initialize(void);
RedBlackTree  RB_MakeEmpty(RedBlackTree T);
RedBlackTree  RB_Insert(RB_ElementType x, RedBlackTree T);
RedBlackTree  RB_Delete(RB_ElementType x, RedBlackTree T);

struct RB_Tree_Node
{
	RB_ElementType   Element;
	RedBlackTree     Left;
	RedBlackTree     Right;
	RB_Color_Type    Color;
};


//#endif