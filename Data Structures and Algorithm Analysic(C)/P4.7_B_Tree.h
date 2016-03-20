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
BT_Position BT_Make_BT_Node();
BT_Tree     BT_MakeEmpty(BT_Tree T);
BT_Tree     BT_Split(BT_Position p);
void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p);
void        BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son);
BT_bool     BT_Add_Leaf_Keyword_Full(BT_ElementType x, BT_Position Father, int index);
BT_bool     BT_KeywordMoveLeft(BT_Position p, int start, int before_end);
BT_bool     BT_KeywordMoveRight(BT_Position p, int start, int before_end);
BT_Tree     BT_Insert(BT_ElementType x, BT_Tree T);
BT_Tree     BT_Delete(BT_ElementType x, BT_Tree T);
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
BT_Tree BT_Split(BT_Position p)
{ 
	if (p->Keyword_Num == KEY_MAX)
	{
		BT_Position Father, Brother;
		Brother = BT_Make_BT_Node();
		int Mid = p->Keyword_Num / 2;

		if (BT_Is_leaf(p) == BT_false)
			Brother->Son[0] = p->Son[Mid + 1];
		for (int i = Mid + 1; i < p->Keyword_Num; ++i)
		{
			if (BT_Is_leaf(p))
				BT_Add_Key_or_Son(Brother, p->Keyword[i], NULL);
			else
				BT_Add_Key_or_Son(Brother, p->Keyword[i], p->Son[i+1]);
		}
		p->Keyword_Num = Mid;

		if (p->Parent == NULL)
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
			BT_Split(p->Parent);
		}
	}
	return p->Parent;

}
/*p is the node(not full),insert key in keyword[index],son in son[index+1]*/
void BT_Add_Key_or_Son(BT_Position p, int key, BT_Position son)
{
	int index = p->Keyword_Num;
	for (int i = 0; i < p->Keyword_Num; ++i)
	{
		if (p->Keyword[i] > key)
		{
			index = i;
			break;
		}
	}
	for (int i = p->Keyword_Num - 1; i > index - 1; --i)
		p->Keyword[i + 1] = p->Keyword[i];
	p->Keyword[index] = key;
	if (son != NULL)
	{
		for (int i = p->Keyword_Num; i > index; --i)
			p->Son[i + 1] = p->Son[i];
		p->Son[index + 1] = son;
	}
	++p->Keyword_Num;
}
/*delete a keyword of a leaf*/
void        BT_Leaf_Del_Keyword(BT_ElementType x, BT_Position p)
{
	if (BT_Is_leaf(p)==BT_false)
		printf("BT_Leaf_Del_Keyword: p is not a Leaf");

	int index = -1;
	for (int i = 0; i < p->Keyword_Num; ++i)
	{
		if (p->Keyword[i] == x)
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		for (int i = index; i < p->Keyword_Num; ++i)
			p->Keyword[i] = p->Keyword[i+1];
		--p->Keyword_Num;
	}
}
/*leaf is  full, p is a leaf index is the index of son*/
BT_bool     BT_Add_Leaf_Keyword_Full(BT_ElementType x, BT_Position Father,int index)
{
	if (BT_KeywordMoveLeft(Father, 0, index) == BT_true )
	{
		BT_Add_Key_or_Son(Father->Son[index], x, NULL);
		if (Father->Son[index]->Keyword[0] < Father->Keyword[index-1])
		{
			int temp = Father->Keyword[index - 1];
			Father->Keyword[index - 1] = Father->Son[index]->Keyword[0];
			Father->Son[index]->Keyword[0] = temp;
		}
		return BT_true;
	}
	if (BT_KeywordMoveRight(Father, index, Father->Keyword_Num) == BT_true)
	{
		BT_Add_Key_or_Son(Father->Son[index], x, NULL);
		if (Father->Son[index]->Keyword[KEY_MAX - 1] > Father->Keyword[index])
		{
			int temp = Father->Keyword[index];
			Father->Keyword[index] = Father->Son[index]->Keyword[KEY_MAX - 1];
			Father->Son[index]->Keyword[KEY_MAX - 1] = temp;
		}
		return BT_true;
	}
	return BT_false;
}
/*this function move one keyword to left brother start before_end is the index of son ,p is the node*/
BT_bool     BT_KeywordMoveLeft(BT_Position p,int start,int before_end)
{
	int move_index = start - 1;
	for (int i = before_end - 1; i > start - 1; --i)
	{
		if (p->Son[i]->Keyword_Num < KEY_MAX)
		{
			move_index = i;
			break;
		}
	}
	if (move_index > start - 1)
	{
		for (int i = move_index; i < before_end; ++i)
		{
			BT_Add_Key_or_Son(p->Son[i], p->Keyword[i], NULL);
			p->Keyword[i] = p->Son[i + 1]->Keyword[0];
			BT_Leaf_Del_Keyword(p->Keyword[i], p->Son[i + 1]);
		}
		return BT_true;
	}
	return BT_false;
}
BT_bool     BT_KeywordMoveRight(BT_Position p, int start, int before_end)
{
	int move_index = start;
	for (int i = start + 1; i < before_end + 1; ++i)
	{
		if (p->Son[i]->Keyword_Num < KEY_MAX)
		{
			move_index = i;
			break;
		}
	}
	if (move_index > start)
	{
		for (int i = move_index; i > start; --i)
		{
			BT_Add_Key_or_Son(p->Son[i], p->Keyword[i-1], NULL);
			p->Keyword[i-1] = p->Son[i-1]->Keyword[KEY_MAX-1];
			BT_Leaf_Del_Keyword(p->Keyword[i-1], p->Son[i - 1]);
		}

		return BT_true;
	}
	return BT_false;
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
		if(BT_Is_leaf(T)==BT_false)
		{
			int index = T->Keyword_Num;
			for (int i = 0; i < T->Keyword_Num; ++i)
			{
				if (x < T->Keyword[i])
					index = i;
			}
			BT_Insert(x, T->Son[index]);
		}
		else
		{
			/*T is the leaf not the root*/
			if (T->Keyword_Num == KEY_MAX&&T->Parent != NULL)
			{
				int index = -1;
				for (int i = 0; i < T->Parent->Keyword_Num + 1; ++i)
				{
					if (T->Parent->Son[i] == T)
					{
						index = i;
						break;
					}
				}
				//if (BT_Add_Leaf_Keyword_Full(x, T->Parent, index) == BT_false)
				{
					T = BT_Split(T);
					BT_Insert(x, T);
				}								
			}
			/*T is the root*/
			else if (T->Keyword_Num == KEY_MAX&&T->Parent == NULL)
			{
				T = BT_Split(T);
				BT_Insert(x, T);                        
			}
			else
			{
				BT_Add_Key_or_Son(T, x, NULL);
			}
		}
		
	}
	return T->Parent==NULL?T:T->Parent;
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
// 	else
// 		printf("-");
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
BT_bool BT_Find(BT_Tree T, BT_ElementType x)
{
	if (T == NULL)
	{
		
	}
	return BT_false;
}
void B_Tree_Test()
{
// 	srand((unsigned)time(0));
// #define B_N  100
// 	int num[B_N];
// 	for (int i = 0; i < B_N;)
// 	{
// 		int temp = rand() % 105 + 1;
// 		if (ST_Num_In_Array(num, temp, i) == 0)
// 			num[i++] = temp;
// 	}
// 
// 	//int num[] = { 1, 23, 6, 7, 8, 9, 0, 21, 33, 25, 22, 3, 4, 5 };
// 	BT_Tree T = NULL;
// 	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
// 	{
// 		T = BT_Insert(num[i], T);
//    		BT_Display(T);
//    		printf("\n");
// 	}
//	BT_Display(T);
	//for (int i = 0; i < B_N; ++i)
	{

	}
//	//T = BT_MakeEmpty(T);
}
Agnode_t * Add_Node(Agraph_t *g, BT_Tree T)
{
	if (T!= NULL)
	{
		//Agnode_t *Fa = agnode(g, "", 1);
		//agsafeset(Fa, "shape", "box", "");
		
		char label[300]="";
		for (int i = 0; i < T->Keyword_Num; ++i)
		{
// 			strncat(label, "<f", strlen("<f"));
// 			char temp[5] = "";
// 			temp[0] = '0' + i;
// 			strncat(label, temp, strlen(temp));
// 			strncat(label, "> ", strlen("> "));
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
#define B_N  20
	int num[B_N];
	for (int i = 0; i < B_N;)
	{
		int temp = rand() % 105 + 1;
		if (ST_Num_In_Array(num, temp, i) == 0)
			num[i++] = temp;
	}

	//int num[] = { 1, 23, 6, 7, 8, 9, 0, 21, 33, 25, 22, 3, 4, 5 };
	BT_Tree T = NULL;
	for (int i = 0; i < sizeof(num) / sizeof(int); ++i)
	{
		T = BT_Insert(num[i], T);
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