#ifndef DRAWHEAP
#define DRAWHEAP

#include "P6.3_binary_heap.h"
#include "P6.5_D_Heap.h"
#include "P6.6_Leftist_Heap.h"
#include "P6.8_Binomial_Queue.h"

void Draw_Binary_Heap(BH_PriorityQueue H, char *format, char *name);
void Draw_D_Heap(DH_PriorityQueue H, char *format, char *name);
void Draw_Leftist_Heap(LH_PriorityQueue H, char *format, char *name);
void Draw_Binomial_Queue(BQ_Queue H, char *format, char *name);
#endif

