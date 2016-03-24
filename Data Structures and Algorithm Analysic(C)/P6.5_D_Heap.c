#include "P6.5_D_Heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

DH_PriorityQueue DH_Initialize(int MaxElement)
{
	DH_PriorityQueue H;
	if (MaxElement < DH_MINSIZE)
		printf("Priority queue size is too small");
	H = malloc(sizeof(struct DH_HeapStruct));
	if (H == NULL)
		printf("H OUT of Space");
	H->Elements = malloc((MaxElement + 1)*sizeof(DH_ElementType));
	if (H->Elements == NULL)
		printf("Out of space ");

	H->Capacity = MaxElement;
	H->Size = 0;
	H->Elements[0] = INT_MIN;
	return H;
}
void             DH_Destory(DH_PriorityQueue H)
{
	if (H != NULL)
	{
		if (H->Elements != NULL)
			free(H->Elements);
		free(H);
	}
}
void             DH_MakeEmpty(DH_PriorityQueue H)
{
	H->Size = 0;
}
void             DH_Insert(DH_ElementType x, DH_PriorityQueue H)
{
	int i;
	if (DH_Full(H))
	{
		printf("Priority queue is full");
		return;
	}
	/*son=[ki-k+2,ki+1] father=i*/
// 	for (i = ++H->Size; H->Elements[i / 2] > x; i /= 2)
// 		H->Elements[i] = H->Elements[i / 2];
// 	H->Elements[i] = x;
}
DH_ElementType   DH_DeleteMin(DH_PriorityQueue H)
{

}
DH_ElementType   DH_FindMin(DH_PriorityQueue H)
{

}
int              DH_IsEmpty(DH_PriorityQueue H)
{

}
int              DH_Full(DH_PriorityQueue H)
{

}

void             DH_Test()
{

}
