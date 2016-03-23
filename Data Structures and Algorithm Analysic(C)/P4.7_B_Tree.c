#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gvc.h>

#include "P4.7_B_Tree.h"

BT_bool     BT_Is_Full(BT_Position p)
{
	if (p != NULL)
	{
		if (BT_Is_root(p) == BT_true && p->Keyword_Num == KEY_MAX)
			return BT_true;
		else if (BT_Is_leaf(p) == BT_true && p->Keyword_Num == LEAF_N_MAX)
			return BT_true;
		else if (BT_Is_leaf(p) == BT_false && p->Keyword_Num == KEY_MAX)
			return BT_true;
		return BT_false;
	}
	else
	{
		printf("BT_Is_Full: p is NULL");
		return BT_false;
	}

}
BT_bool     BT_Is_leaf(BT_Position T)
{
	if (T != NULL)
	{
		if (T->Son[0] == NULL)
			return BT_true;
	}
	return BT_false;
}
BT_bool     BT_Is_root(BT_Position T)
{
	if (T != NULL&&T->Parent == NULL)
		return BT_true;
	else
		return BT_false;
}
BT_Position BT_Make_BT_Node()
{
	BT_Position T = (BT_Position)malloc(sizeof(struct BT_Node));
	if (T == NULL)
	{
		printf("Out of space");
	}
	else
	{
		T->Keyword_Num = 0;
		T->Parent = NULL;
		for (int i = 0; i < SON_M; ++i)
			T->Son[i] = NULL;
	}
	return T;
}
BT_Tree     BT_MakeEmpty(BT_Tree T)
{
	if (T != NULL)
	{
		for (int i = 0; i < T->Keyword_Num; ++i)
			if (T->Son[i] != NULL)
				T->Son[i] = BT_MakeEmpty(T->Son[i]);
		free(T);
		T = NULL;
	}
	return T;
}

int         Common_Insert_Index(BT_ElementType* a, int Num, BT_ElementType x)
{
	if (a != NULL)
	{
		int index = Num;
		for (int i = 0; i < Num; ++i)
		{
			if (x < a[i])
			{
				index = i;
				break;
			}
		}
		return index;
	}
	else
	{
		printf("Common_Insert_Index: Bad Pointer a");
		return -1;
	}
}
int         Common_Element_Index(BT_ElementType* a, int Num, BT_ElementType x)
{
	if (a != NULL)
	{
		int index = -1;
		for (int i = 0; i < Num; ++i)
		{
			if (a[i] == x)
			{
				index = i;
				break;
			}
		}
		return index;
	}
	else
	{
		printf("Common_Element_Index: Bad Pointer a");
		return -1;
	}
}
void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p)
{
	if (BT_Is_leaf(p) == BT_true)
	{
		int index = Common_Element_Index(p->Keyword, p->Keyword_Num, x);
		if (index != -1)
		{
			for (int i = index; i < p->Keyword_Num; ++i)
				p->Keyword[i] = p->Keyword[i + 1];
			(p->Keyword_Num)--;
		}
		else
		{
			printf("BT_Leaf_Del_Keyword: can not find x");
		}
	}
	else
	{
		printf("BT_Leaf_Del_Keyword: p is not a Leaf");
	}
}
void        BT_Element_Insert(BT_ElementType* Key_array, BT_Position *Son_array, int Key_Num, BT_ElementType key, BT_Position son)
{
	int index = Common_Insert_Index(Key_array, Key_Num, key);
	for (int i = Key_Num; i > index; --i)
	{
		Key_array[i] = Key_array[i - 1];
		if (son != NULL)
			Son_array[i + 1] = Son_array[i];
	}
	Key_array[index] = key;
	if (son != NULL)
		Son_array[index + 1] = son;
}
void        BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son)
{
	if (p != NULL)
	{
		BT_Element_Insert(p->Keyword, p->Son, p->Keyword_Num, key, son);
		if (son != NULL)
			son->Parent = p;
		++p->Keyword_Num;
	}
	else
	{
		printf("BT_Add_Key_or_Son: p is NULL");
	}
}

BT_bool     BT_Leaf_Key_Move_Insert(BT_ElementType x, BT_Position Father, int Leaf_index)
{
	if (BT_KeywordMoveLeft(Father, x, 0, Leaf_index) == BT_true)
		return BT_true;
	if (BT_KeywordMoveRight(Father, x, Leaf_index, Father->Keyword_Num) == BT_true)
		return BT_true;
	return BT_false;
}
BT_bool     BT_KeywordMoveLeft(BT_Position p, BT_ElementType x, int start_index, int before_end_index)
{
	if (p != NULL)
	{
		int move_index = start_index - 1;
		for (int i = before_end_index - 1; i > start_index - 1; --i)
		{
			if (p->Son[i]->Keyword_Num < LEAF_N_MAX)
			{
				move_index = i;
				break;
			}
		}
		if (move_index > start_index - 1)
		{
			/*stop before insert place*/
			for (int i = move_index; i < before_end_index - 1; ++i)
			{
				BT_Add_Key_or_Son(p->Son[i], p->Keyword[i], NULL);
				p->Keyword[i] = p->Son[i + 1]->Keyword[0];
				BT_Leaf_Del_Keyword(p->Keyword[i], p->Son[i + 1]);
			}
			BT_Add_Key_or_Son(p->Son[before_end_index - 1], p->Keyword[before_end_index - 1], NULL);
			if (x < p->Son[before_end_index]->Keyword[0])
			{
				p->Keyword[before_end_index - 1] = x;
			}
			else
			{
				p->Keyword[before_end_index - 1] = p->Son[before_end_index]->Keyword[0];
				BT_Leaf_Del_Keyword(p->Keyword[before_end_index - 1], p->Son[before_end_index]);
				BT_Add_Key_or_Son(p->Son[before_end_index], x, NULL);
			}
			return BT_true;
		}
	}
	else
	{
		printf("BT_KeywordMoveLeft: p is NULL");
	}
	return BT_false;
}
BT_bool     BT_KeywordMoveRight(BT_Position p, BT_ElementType x, int start_index, int before_end_index)
{
	if (p != NULL)
	{
		int move_index = start_index;
		for (int i = start_index + 1; i < before_end_index + 1; ++i)
		{
			if (p->Son[i]->Keyword_Num < LEAF_N_MAX)
			{
				move_index = i;
				break;
			}
		}
		if (move_index > start_index)
		{
			for (int i = move_index; i > start_index + 1; --i)
			{
				BT_Add_Key_or_Son(p->Son[i], p->Keyword[i - 1], NULL);
				p->Keyword[i - 1] = p->Son[i - 1]->Keyword[LEAF_N_MAX - 1];
				BT_Leaf_Del_Keyword(p->Keyword[i - 1], p->Son[i - 1]);
			}
			BT_Add_Key_or_Son(p->Son[start_index + 1], p->Keyword[start_index], NULL);
			if (x > p->Son[start_index]->Keyword[LEAF_N_MAX - 1])
			{
				p->Keyword[start_index] = x;
			}
			else
			{
				p->Keyword[start_index] = p->Son[start_index]->Keyword[LEAF_N_MAX - 1];
				BT_Leaf_Del_Keyword(p->Keyword[start_index], p->Son[start_index]);
				BT_Add_Key_or_Son(p->Son[start_index], x, NULL);
			}
			return BT_true;
		}
	}
	else
	{
		printf("BT_KeywordMoveRight: p is NULL");
	}
	return BT_false;
}

BT_Tree     BT_Add_And_Split(BT_Position p, int add_key, BT_Position add_son)
{
	if (p != NULL)
	{
		if (BT_Is_Full(p))
		{
			BT_Position     Son[SON_M + 1];
			BT_ElementType  Keyword[LEAF_N_MAX + 1];

			for (int i = 0; i < p->Keyword_Num; ++i)
			{
				Keyword[i] = p->Keyword[i];
				if (BT_Is_leaf(p) == BT_false)
					Son[i] = p->Son[i];
			}
			if (BT_Is_leaf(p) == BT_false)
				Son[p->Keyword_Num] = p->Son[p->Keyword_Num];
			BT_Element_Insert(Keyword, Son, p->Keyword_Num, add_key, add_son);

			int Mid = (p->Keyword_Num + 1) / 2;

			int Key_Num = p->Keyword_Num;
			p->Keyword_Num = 0;
			if (BT_Is_leaf(p) == BT_false)
			{
				p->Son[0] = Son[0];
				Son[0]->Parent = p;
			}
			for (int i = 0; i < Mid; ++i)
			{
				if (BT_Is_leaf(p) == BT_false)
					BT_Add_Key_or_Son(p, Keyword[i], Son[i + 1]);
				else
					BT_Add_Key_or_Son(p, Keyword[i], NULL);
			}
			BT_Position  Brother = BT_Make_BT_Node();
			if (BT_Is_leaf(p) == BT_false)
			{
				Brother->Son[0] = Son[Mid + 1];
				Son[Mid + 1]->Parent = Brother;
			}
			for (int i = Mid + 1; i < Key_Num + 1; ++i)
			{
				if (BT_Is_leaf(p) == BT_false)
					BT_Add_Key_or_Son(Brother, Keyword[i], Son[i + 1]);
				else
					BT_Add_Key_or_Son(Brother, Keyword[i], NULL);
			}


			if (BT_Is_root(p) == BT_true)
			{
				BT_Position Father = BT_Make_BT_Node();
				Father->Son[0] = p;
				p->Parent = Father;
				BT_Add_Key_or_Son(Father, Keyword[Mid], Brother);
				Brother->Parent = Father;
				return Father;
			}
			else
			{
				return BT_Add_And_Split(p->Parent, Keyword[Mid], Brother);
			}
		}
		else
		{
			BT_Add_Key_or_Son(p, add_key, add_son);
			return p;
		}
	}
	else
	{
		printf("BT_Add: p is NULL");
		return p;
	}
}
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T)
{
	if (T == NULL)
	{
		BT_Tree root = BT_Make_BT_Node();
		BT_Add_Key_or_Son(root, x, NULL);
		return root;
	}
	else
	{
		BT_Position Pos_insert = T;

		int index;
		while (BT_Is_leaf(Pos_insert) == BT_false)
		{
			index = Pos_insert->Keyword_Num;
			for (int i = 0; i < Pos_insert->Keyword_Num; ++i)
			{
				if (x < Pos_insert->Keyword[i])
				{
					index = i;
					break;
				}
			}
			Pos_insert = Pos_insert->Son[index];
		}

		if (BT_Is_Full(Pos_insert) == BT_false)
		{
			BT_Add_Key_or_Son(Pos_insert, x, NULL);
		}
		else if (BT_Is_root(Pos_insert) && BT_Is_Full(Pos_insert) == BT_true)
		{
			Pos_insert = BT_Add_And_Split(Pos_insert, x, NULL);
		}
		else
		{
			if (BT_Leaf_Key_Move_Insert(x, Pos_insert->Parent, index) == BT_false)
			{
				Pos_insert = BT_Add_And_Split(Pos_insert, x, NULL);
			}
		}
		BT_Tree temp = T;
		while (temp->Parent != NULL)
			temp = temp->Parent;
		return temp;
	}
}
void        BT_Display(BT_Tree T)
{
	if (T != NULL)
	{
		for (int i = 0; i < T->Keyword_Num + 1; ++i)
		{
			BT_Display(T->Son[i]);
			if (i < T->Keyword_Num)
			{
				if (BT_Is_leaf(T))
					printf(" %d", T->Keyword[i]);
				else
					printf(" (%d) ", T->Keyword[i]);
			}
		}
	}
}

int BT_Num_In_Array(int* a, int num, int n)
{
	int in = 0;
	for (int i = 0; i < n; ++i)
	{
		if (num == a[i])
		{
			in = 1;
			break;
		}
	}
	return in;
}
Agnode_t * Add_Node(Agraph_t *g, BT_Tree T)
{
	if (T != NULL)
	{
		char label[300] = "";
		for (int i = 0; i < T->Keyword_Num; ++i)
		{
			char gif_index_str[10] = "";
			_itoa(T->Keyword[i], gif_index_str, 10);
			strncat(label, gif_index_str, strlen(gif_index_str));
			if (i < T->Keyword_Num - 1)
				strncat(label, " | ", strlen(" | "));
		}
		//agsafeset(Fa, "label", label, "");
		Agnode_t *Fa = agnode(g, label, 1);
		for (int i = 0; i < T->Keyword_Num + 1; ++i)
		{
			if (BT_Is_leaf(T) == BT_true&&i == T->Keyword_Num)
				break;
			Agnode_t *son = Add_Node(g, T->Son[i]);
			if (son != NULL)
			{
				Agedge_t *EL = agedge(g, Fa, son, 0, 1);
				agsafeset(EL, "color", "turquoise", "");
			}
		}
		return Fa;
	}
	return NULL;
}
void B_Tree_Test2()
{
	srand((unsigned)time(0));
#define B_N  100
	int num[B_N];
	for (int i = 0; i < B_N;)
	{
		int temp = rand() % 100 + 1;
		if (ST_Num_In_Array(num, temp, i) == 0)
			num[i++] = temp;
	}

	//int num[] = { 1, 23, 6, 7, 8, 9, 0, 21, 33, 25, 22, 3, 4, 5 };

	//int num[] = { 10, 55, 15, 23, 17, 19, 92, 81, 95, 93, 7, 80, 11, 27, 75, 12 };
	BT_Tree T = NULL;
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		T = BT_Insert(num[i], T);
// 		Agraph_t *g;
// 		GVC_t *gvc;
// 
// 		gvc = gvContext();
// 		g = agopen("g", Agdirected, 0);
// 		agsafeset(g, "rankdir", "TB", "");
// 
// 		Add_Node(g, T);
// 
// 		gvLayout(gvc, g, "dot");
// 
// 		char name[20] = "BT";
// 		char gif_index_str[10] = "";
// 		_itoa(i, gif_index_str, 10);
// 		strncat(name, gif_index_str, strlen(gif_index_str));
// 		strncat(name, ".gif", strlen(".gif"));
// 
// 		gvRenderFilename(gvc, g, "gif", name);
// 
// 		gvFreeLayout(gvc, g);
// 		agclose(g);
// 		gvFreeContext(gvc);
	}

	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);
	agsafeset(g, "rankdir", "TB", "");

	Add_Node(g, T);

	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, "gif", "Node.gif");

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);

	T = BT_MakeEmpty(T);
}