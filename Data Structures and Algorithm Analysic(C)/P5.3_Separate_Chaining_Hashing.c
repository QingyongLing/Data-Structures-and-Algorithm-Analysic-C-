#include "P5.3_Separate_Chaining_Hashing.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SC_bool  char
#define SC_true  1
#define SC_false 0

/* this code from: http://stackoverflow.com/questions/4475996/given-prime-number-n-compute-the-next-prime */
SC_bool is_prime(int x)
{
	int o = 4;
	for (int i = 5; SC_true; i += o)
	{
		int q = x / i;
		if (q < i)
			return SC_true;
		if (x == q * i)
			return SC_false;
		o ^= 6;
	}
	return SC_true;
}
int next_prime(int x)
{
	switch (x)
	{
	case 0:
	case 1:
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
	case 5:
		return 5;
	}
	unsigned int k = x / 6;
	unsigned int i = x - 6 * k;
	unsigned int o = i < 2 ? 1 : 5;
	x = 6 * k + o;
	/*only send 6k+{1,5} to is_prime*/
	for (i = (3 + o) / 2; !is_prime(x); x += i)
		i ^= 6;
	return x;
}

SC_HashTable SC_InitalizeTable(int SC_TableSize)
{
	SC_HashTable H;
	if (SC_TableSize < SC_MIN_TABLESIZE)
	{
		printf("Table is too small");
		return NULL;
	}
	H = malloc(sizeof(struct SC_HashTbl));
	if (H == NULL)
	{
		printf("Out of space!");
		return NULL;
	}
	H->TableSize = next_prime(SC_TableSize);
    
	H->TheLists = malloc(H->TableSize*sizeof(SC_List));
	if (H->TheLists == NULL)
	{
		printf("Out of space!");
		return H;
	}
	for (int i = 0; i < H->TableSize; ++i)
	{
		H->TheLists[i] = malloc(sizeof(struct SC_ListNode));
		if (H->TheLists[i] == NULL)
			printf("Out of Space!");
		else
			H->TheLists[i]->Next = NULL;
	}
	return H;
}
void         SC_DestroyTable(SC_HashTable H)
{
	for (int i = 0; i < H->TableSize; ++i)
	{
		SC_Position p = H->TheLists[i];
		while (p != NULL)
		{
			SC_Position temp = p->Next;
			free(p);
			p = temp;
		}
	}
	free(H->TheLists);
	free(H);
}
SC_Position  SC_Find(SC_Element_Type key, SC_HashTable H)
{
	SC_Position p;
	SC_List     L;
	L = H->TheLists[SC_Hash(key, H->TableSize)];
	p = L->Next;
	while (p != NULL&&p->Element != key)
		p = p->Next;
	return p;
}
void         SC_Insert(SC_Element_Type key, SC_HashTable H)
{
	SC_Position Pos, NewCell;
	SC_List     L;
	Pos = SC_Find(key, H);
	if (Pos == NULL)
	{
		NewCell = malloc(sizeof(struct SC_ListNode));
		if (NewCell == NULL)
		{
			printf("Out of space!");
		}
		else
		{
			L = H->TheLists[SC_Hash(key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = key;
			L->Next = NewCell;
		}
	}
}
int          SC_Hash(SC_Element_Type key, int TableSizle)
{
	return key%TableSizle;
}
void         SC_Test()
{
	SC_HashTable H = SC_InitalizeTable(10);
	int num[] = { 1, 4, 3, 2, 6, 7, 3, 9, 23, 4, 5, 67, 43, 69, 90 };
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		SC_Insert(num[i], H);
	}
	for (int i = 0; i < H->TableSize; ++i)
	{
		for (SC_Position temp = H->TheLists[i]->Next; temp != NULL; temp = temp->Next)
		{
			printf(" %d  ", temp->Element);
		}
		printf("\n");
	}
	printf("%d", SC_Find(69, H)->Element);
	SC_DestroyTable(H);
}