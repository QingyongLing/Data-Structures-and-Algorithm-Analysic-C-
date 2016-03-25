#ifndef BINOMIAL_QUEUE
#define BINOMIAL_QUEUE

struct  BQ_Node;
struct  BQ_Collection;

typedef struct BQ_Node       *BQ_Position;
typedef struct BQ_Collection *BQ_Queue;

#define BQ_ElementType int 
#define BQ_Element_MIN INT_MIN
#define BQ_Element_MAX INT_MAX

BQ_Queue         BQ_Initialize(void);
BQ_Queue         BQ_MakeEmpty(BQ_Queue H);
BQ_ElementType   BQ_FindMin(BQ_Queue H);
int              BQ_IsEmpty(BQ_Queue Q);
BQ_Queue         BQ_Merge(BQ_Queue H1, BQ_Queue H2);

BQ_Queue         BQ_Insert(BQ_ElementType x, BQ_Queue H);
BQ_ElementType   BQ_DeleteMin(BQ_Queue H);

void             BQ_Test();

struct BQ_Node
{
	BQ_ElementType Element;
	BQ_Position    LeftChild;
	BQ_Position    NextSibling;
};

typedef BQ_Position BQ_Tree;
#define BQ_MaxTrees  (10)
#define BQ_Capacity  (1023)
struct BQ_Collection
{
	int      CurrentSize;
	BQ_Tree  TheTrees[BQ_MaxTrees];
};

#endif