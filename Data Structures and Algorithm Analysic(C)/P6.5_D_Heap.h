#ifndef D_HEAP
#define D_HEAP

#define DH_ElementType int
#define DH_MINSIZE     (20)
#define DH_D           (4)

struct         DH_HeapStruct;
typedef struct DH_HeapStruct *DH_PriorityQueue;

DH_PriorityQueue DH_Initialize(int MaxElement);
void             DH_Destory(DH_PriorityQueue H);
void             DH_MakeEmpty(DH_PriorityQueue H);
void             DH_Insert(DH_ElementType x, DH_PriorityQueue H);
DH_ElementType   DH_DeleteMin(DH_PriorityQueue H);
DH_ElementType   DH_FindMin(DH_PriorityQueue H);
int              DH_IsEmpty(DH_PriorityQueue H);
int              DH_Full(DH_PriorityQueue H);

void             DH_Test();
struct DH_HeapStruct
{
	int Capacity;
	int Size;
	DH_ElementType *Elements;
};


#endif