#ifndef SKEW_HEAP
#define SKEW_HEAP

struct SH_Heap_Node;
typedef struct SH_Heap_Node *SH_PriorityQueue;

#define SH_ElementType int
#define SH_ElementType_MIN INT_MIN

#define SH_Insert(x,H) (H=SH_Insert1((x),H))
#define SH_DeleteMin(H) (H=SH_DeleteMin1(H))

SH_PriorityQueue SH_Initialize(void);
void             SH_MakeEmpty(SH_PriorityQueue H);
SH_ElementType   SH_FindMin(SH_PriorityQueue H);
int              SH_IsEmpty(SH_PriorityQueue Q);
SH_PriorityQueue SH_Merge(SH_PriorityQueue H1, SH_PriorityQueue H2);

SH_PriorityQueue SH_Insert1(SH_ElementType x, SH_PriorityQueue H);
SH_PriorityQueue SH_DeleteMin1(SH_PriorityQueue H);
static SH_PriorityQueue SH_Merge1(SH_PriorityQueue H1, SH_PriorityQueue H2);

void SH_Skew_Heap_Test();

struct SH_Heap_Node
{
	SH_ElementType     Element;
	SH_PriorityQueue   Left;
	SH_PriorityQueue   Right;
};
#endif