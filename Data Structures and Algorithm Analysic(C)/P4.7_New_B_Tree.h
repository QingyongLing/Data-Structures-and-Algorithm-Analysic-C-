#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <gvc.h>

struct BT_Node;
typedef struct BT_Node *BT_Position;
typedef struct BT_Node *BT_Tree;

#define KEY_MAX SON_M-1
#define SON_M 4
#define BT_ElementType int
#define BT_bool  char
#define BT_true  1
#define BT_false 0

struct BT_Node
{
	/*the num of keyword*/
	unsigned char   Keyword_Num;
	BT_Position     Parent;
	BT_Position     Son[SON_M];
	BT_ElementType  Keyword[KEY_MAX];
};

BT_bool     BT_Is_leaf(BT_Position T);
BT_bool     BT_Is_root(BT_Position T);
BT_Position BT_Make_BT_Node();
BT_Tree     BT_MakeEmpty(BT_Tree T);
int         BT_InsertIndex(BT_Position T, BT_ElementType x);
BT_Tree     BT_Split(BT_Position p);
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T);

void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p);
int         BT_Element_Index(BT_ElementType x, BT_Position p);
void        BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son);

BT_bool     BT_Leaf_Key_Move_Insert(BT_ElementType x, BT_Position Father, int index);
BT_bool     BT_KeywordMoveLeft(BT_Position p, BT_ElementType x, int start, int before_end);
BT_bool     BT_KeywordMoveRight(BT_Position p, BT_ElementType x, int start, int before_end);

void        BT_Display(BT_Tree T);

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
int         BT_InsertIndex(BT_Position T, BT_ElementType x)
{
	if (T != NULL)
	{
		int index = T->Keyword_Num;
		for (int i = 0; i < T->Keyword_Num; ++i)
		{
			if (x < T->Keyword[i])
			{
				index = i;
				break;
			}
		}
		return index;
	}
	else
	{
		printf("BT_InsertIndex: Bad Pointer T");
		return -1;
	}
}
int         BT_Element_Index(BT_ElementType x, BT_Position p)
{
	if (p != NULL)
	{
		int index = -1;
		for (int i = 0; i < p->Keyword_Num; ++i)
		{
			if (p->Keyword[i] == x)
			{
				index = i;
				break;
			}
		}
		return index;
	}
	else
	{
		printf("BT_Element_Index: Bad Pointer T");
		return -1;
	}
}
void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p)
{
	if (BT_Is_leaf(p) == BT_true)
	{
		int index = BT_Element_Index(x, p);
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
void        BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son)
{
	if (p != NULL)
	{
		int index = BT_InsertIndex(p,key);
        
		for (int i = p->Keyword_Num; i > index; --i)
			p->Keyword[i] = p->Keyword[i - 1];
		p->Keyword[index] = key;
		if (son != NULL)
		{
			for (int i = p->Keyword_Num; i > index; --i)
				p->Son[i + 1] = p->Son[i];
			p->Son[index + 1] = son;
			/*change the parent*/
			son->Parent = p;
		}
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
			if (p->Son[i]->Keyword_Num < KEY_MAX)
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
			if (p->Son[i]->Keyword_Num < KEY_MAX)
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
				p->Keyword[i - 1] = p->Son[i - 1]->Keyword[KEY_MAX - 1];
				BT_Leaf_Del_Keyword(p->Keyword[i - 1], p->Son[i - 1]);
			}
			BT_Add_Key_or_Son(p->Son[start_index + 1], p->Keyword[start_index], NULL);
			if (x > p->Son[start_index]->Keyword[KEY_MAX - 1])
			{
				p->Keyword[start_index] = x;
			}
			else
			{
				p->Keyword[start_index] = p->Son[start_index]->Keyword[KEY_MAX - 1];
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

BT_Tree     BT_Split(BT_Position p)
{
	if (p != NULL)
	{
		if (p->Keyword_Num == KEY_MAX)
		{
			BT_Position Father, Brother;
			Brother = BT_Make_BT_Node();

			int Mid = p->Keyword_Num / 2;
			if (BT_Is_leaf(p) == BT_false)
			{
				Brother->Son[0] = p->Son[Mid + 1];
				p->Son[Mid + 1]->Parent = Brother;
			}
			for (int i = Mid + 1; i < p->Keyword_Num; ++i)
			{
				if (BT_Is_leaf(p))
					BT_Add_Key_or_Son(Brother, p->Keyword[i], NULL);
				else
					BT_Add_Key_or_Son(Brother, p->Keyword[i], p->Son[i + 1]);
			}
			p->Keyword_Num = Mid;

			if (BT_Is_root(p)==BT_true)
			{
				Father = BT_Make_BT_Node();
				Father->Son[0] = p;
				p->Parent = Father;
				BT_Add_Key_or_Son(Father, p->Keyword[Mid], Brother);
				Brother->Parent = Father;
				return Father;
			}
			else
			{
				BT_Add_Key_or_Son(p->Parent, p->Keyword[Mid], Brother);
				Brother->Parent = p->Parent;
				return BT_Split(p->Parent);
			}
		}
		return p;
	}
	else
	{
		printf("BT_Split: p is NULL");
		return NULL;
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
		BT_Position Pos_insert=T;
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
			if (index != Pos_insert->Keyword_Num)
				if (x>Pos_insert->Keyword[index])
					printf("What The fuck index");
			Pos_insert = Pos_insert->Son[index];
		}
		if (Pos_insert->Keyword_Num < KEY_MAX)
		{
			BT_Add_Key_or_Son(Pos_insert, x, NULL);
		}
		else
		{
			if (BT_Is_root(Pos_insert) == BT_true)
			{
				Pos_insert = BT_Split(Pos_insert);
				BT_Insert(x, Pos_insert);
			}
			else if (BT_Leaf_Key_Move_Insert(x, Pos_insert->Parent, index) == BT_false)
			{
				Pos_insert = BT_Split(Pos_insert);
				BT_Insert(x, Pos_insert);
			}
		}
		BT_Tree temp = T;
		while (temp->Parent != NULL)
	 		temp=temp->Parent;
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
	if (T!= NULL)
	{
		char label[300]="";
		for (int i = 0; i < T->Keyword_Num; ++i)
		{
			char gif_index_str[10] = "";
			_itoa(T->Keyword[i], gif_index_str, 10);
			strncat(label, gif_index_str, strlen(gif_index_str));
			if (i<T->Keyword_Num-1)
				strncat(label, " | ", strlen(" | "));
		}
		//agsafeset(Fa, "label", label, "");
		Agnode_t *Fa = agnode(g, label, 1);
		for (int i = 0; i < T->Keyword_Num + 1; ++i)
		{
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
#define B_N  6
	int num[B_N];
	for (int i = 0; i < B_N;)
	{
		int temp = rand() % 200 + 1;
		if (BT_Num_In_Array(num, temp, i) == 0)
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