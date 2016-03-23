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
	for (i = (3 + o) / 2; !is_prime(x); x += i)
		i ^= 6;
	return x;
}

SC_HashTable SC_InitalizeTable(int SC_TableSize)
{
	SC_HashTable H;
	int i;
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
    
}
void         SC_DestroyTable(SC_HashTable H)
{

}
SC_Position  SC_Find(SC_Element_Type key, SC_HashTable H)
{

}
void         SC_Insert(SC_Element_Type key, SC_HashTable H)
{

}