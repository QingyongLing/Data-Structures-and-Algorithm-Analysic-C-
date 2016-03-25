#ifndef LEFTIST_HEAP
#define LEFTIST_HEAP

struct LH_Heap_Node;
typedef struct LH_Heap_Node *LH_PriorityQueue;


#define LH_ElementType int
#define LH_ElementType_MIN INT_MIN

#define LH_Insert(x,H) (H=LH_Insert1((x),H))
#define LH_DeleteMin(H) (H=LH_DeleteMin1(H))

LH_PriorityQueue LH_Initialize(void);
void             LH_MakeEmpty(LH_PriorityQueue H);
LH_ElementType   LH_FindMin(LH_PriorityQueue H);
int              LH_IsEmpty(LH_PriorityQueue Q);
LH_PriorityQueue LH_Merge(LH_PriorityQueue H1, LH_PriorityQueue H2);

LH_PriorityQueue LH_Insert1(LH_ElementType x, LH_PriorityQueue H);
LH_PriorityQueue LH_DeleteMin1(LH_PriorityQueue H);
static LH_PriorityQueue LH_Merge1(LH_PriorityQueue H1, LH_PriorityQueue H2);

void LH_Leftist_Heap_Test();

struct LH_Heap_Node
{
	LH_ElementType     Element;
	LH_PriorityQueue   Left;
	LH_PriorityQueue   Right;
	int                Npl;
};

#endif