
#include <stdio.h>

#include "P4.4_AVL_tree.h"
#include "P4.5_Splay_Tree.h"
#include <gvc.h>
#include "Draw_Binary_Tree.h"
#include "P4.7_B_Tree.h"
//#include "P4.7_New_B_Tree.h"
void GraphvizDrawAVL()
{
	srand((unsigned)time(0));
#define AVL_N 20 
	int num[AVL_N];
	int maxnum, minnum;
	for (int i = 0; i < AVL_N;)
	{
		int temp = rand() % 100 + 1;
		if (i == 0)
			maxnum = minnum = temp;
		if (ST_Num_In_Array(num, temp, i) == 0)
			num[i++] = temp;
		maxnum = temp > maxnum ? temp : maxnum;
		minnum = temp < minnum ? temp : minnum;
	}

	AVL_Tree p = NULL;
	int Gif_index = 0;
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		p = AVL_Insert(num[i], p);
		AVL_BalanceTest(p);

		char name[20] = "AVL";
		char gif_index_str[10];
		_itoa(Gif_index++, gif_index_str, 10);

		strncat(name, gif_index_str, strlen(gif_index_str));
		strncat(name, ".gif", strlen(".gif"));
		Draw_AVL_Tree_int(p, "gif", name);
	}
	/* AVL1.gif AVL2.gif...>AVL.gif*/
	MakeGif("gif", "AVL", 0, Gif_index);
	p = AVL_MakeEmpty(p);
}
int main(int argc, char **argv)
{
	//GraphvizDrawAVL();
	B_Tree_Test2();
	system("pause");  
	return 0;
}
