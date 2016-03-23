#ifndef B_TREE
#define B_TREE

struct BT_Node;
typedef struct BT_Node *BT_Position;
typedef struct BT_Node *BT_Tree;

/*The Min SON_M is 4*/
#define KEY_MAX SON_M-1
#define LEAF_N_MAX SON_M
#define SON_M 4
#define BT_ElementType int
#define BT_bool  char
#define BT_true  1
#define BT_false 0

struct BT_Node
{
	/*the num of keyword*/
	unsigned char   Keyword_Num;
	BT_Position     Parent;
	BT_Position     Son[SON_M];
	BT_ElementType  Keyword[KEY_MAX + 1];
};

BT_bool     BT_Is_leaf(BT_Position T);
BT_bool     BT_Is_root(BT_Position T);
BT_bool     BT_Is_Full(BT_Position p);
BT_Position BT_Make_BT_Node();
BT_Tree     BT_MakeEmpty(BT_Tree T);
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T);
void        BT_Display(BT_Tree T);

BT_Tree     BT_Add_And_Split(BT_Position p, int add_key, BT_Position add_son);

void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p);
void        BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son);
int         Common_Insert_Index(BT_ElementType* a, int Num, BT_ElementType x);
int         Common_Element_Index(BT_ElementType* a, int Num, BT_ElementType x);
void        BT_Element_Insert(BT_ElementType* Key_array, BT_Position *Son_array, int Num, BT_ElementType key, BT_Position son);

BT_bool     BT_Leaf_Key_Move_Insert(BT_ElementType x, BT_Position Father, int index);
BT_bool     BT_KeywordMoveLeft(BT_Position p, BT_ElementType x, int start, int before_end);
BT_bool     BT_KeywordMoveRight(BT_Position p, BT_ElementType x, int start, int before_end);

void B_Tree_Test2();
#endif
