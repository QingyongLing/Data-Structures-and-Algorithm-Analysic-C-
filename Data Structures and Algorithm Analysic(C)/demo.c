
#include <stdio.h>

//#include "Q2.12a.h"
//#include "P4.3_binary_search_tree.h"

#include "P4.4_AVL_tree.h"
#include "P4.5_Splay_Tree.h"
#include <gvc.h>
#include "Draw_Binary_Tree.h"

void  GraphvizTest();
int main(int argc, char **argv)
{
	
	GraphvizTest();
	system("pause");  
	return 0;
}
void GraphvizTest()
{



	//int num[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 ,23,4,52,3,4,5,77,5,33,2,12,3,3,44,7,8,9,99,34,56,99,12,34};
	srand((unsigned)time(0));
#define ST_N 20 
	int num[ST_N];
	int maxnum, minnum;
	for (int i = 0; i < ST_N;)
	{
		int temp = rand() % 100 + 1;
		if (i == 0)
		{
			maxnum = minnum = temp;
		}
		if (ST_Num_In_Array(num, temp, i) == 0)
			num[i++] = temp;
		maxnum = temp > maxnum ? temp : maxnum;
		minnum = temp < minnum ? temp : minnum;
	}

	AVL_Tree p = NULL;
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		p = AVL_Insert(num[i], p);
		AVL_BalanceTest(p);
		char name[20]="AVL";

		char int_to_str[10];
		_itoa(i, int_to_str, 10);

		int index = strlen(name);
		char *p_int_to_str = int_to_str;
		while (*p_int_to_str != '\0')
		{
			name[index++] = *p_int_to_str;
			++p_int_to_str;
		}
		name[index++] = '.';
		name[index++] = 'g';
		name[index++] = 'i';
		name[index++] = 'f';
		name[index] = '\0';
		Draw_AVL_Tree_int(p, "gif", name);
	}
	MakeGif("AVL", 0, 20);
	p = AVL_MakeEmpty(p);

}