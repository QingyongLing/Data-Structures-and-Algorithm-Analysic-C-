#ifndef BINARY_HEAP
#define BINARY_HEAP

#define BH_ElementType int
#define BH_MINSIZE     (20)

struct         BH_HeapStruct;
typedef struct BH_HeapStruct *BH_PriorityQueue;

BH_PriorityQueue BH_Initialize(int MaxElement);
void             BH_Destory(BH_PriorityQueue H);
void             BH_MakeEmpty(BH_PriorityQueue H);
void             BH_Insert(BH_ElementType x, BH_PriorityQueue H);
BH_ElementType   BH_DeleteMin(BH_PriorityQueue H);
BH_ElementType   BH_FindMin(BH_PriorityQueue H);
int              BH_IsEmpty(BH_PriorityQueue H);
int              BH_Full(BH_PriorityQueue H);

void             BH_Test();
struct BH_HeapStruct
{
	int Capacity;
	int Size;
	BH_ElementType *Elements;
};

#endif