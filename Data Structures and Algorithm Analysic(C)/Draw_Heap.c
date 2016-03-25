#include "Draw_Heap.h"
#include <gvc.h>
#include <stdlib.h>


void Draw_Binary_Heap(BH_PriorityQueue H,char *format,char *name)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);
	agsafeset(g, "rankdir", "TB", "");

	Agnode_t **Node_array = malloc(sizeof(Agnode_t *)*(H->Size+1));
	for (int i = 1; i < H->Size + 1; ++i)
	{
		char gif_index_str[10] = "";
		_itoa(H->Elements[i], gif_index_str, 10);
		Node_array[i] = agnode(g, gif_index_str, 1);
	}
	for (int i = 1; i < H->Size / 2 + 1; ++i)
	{
		Agedge_t *EL = agedge(g, Node_array[i], Node_array[2*i], 0, 1);
		if (2 * i != H->Size)
		{
			Agedge_t *EL = agedge(g, Node_array[i], Node_array[2 * i + 1], 0, 1);
		}
	}
	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, name);

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);

	free(Node_array);
}

void Draw_D_Heap(DH_PriorityQueue H, char *format, char *name)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);
	agsafeset(g, "rankdir", "TB", "");

	Agnode_t **Node_array = malloc(sizeof(Agnode_t *)*(H->Size + 1));
	for (int i = 1; i <= H->Size; ++i)
	{
		char gif_index_str[10] = "";
		_itoa(H->Elements[i], gif_index_str, 10);
		Node_array[i] = agnode(g, gif_index_str, 1);
	}
	for (int i = 1; i * DH_D - DH_D + 2 <= H->Size; ++i)
	{
		int start = i  * DH_D - DH_D + 2;
		for (int j = 0; j < DH_D; ++j)
		{
			if (start + j <= H->Size)
			{
				Agedge_t *EL = agedge(g, Node_array[i], Node_array[start+j], 0, 1);
			}
		}
	}
	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, name);

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);

	free(Node_array);
}

static Agnode_t * Leftist_Heap_Add_Node(Agraph_t *g, LH_PriorityQueue H)
{
	if (H != NULL)
	{
		Agnode_t *L, *R;
		Agedge_t *EL, *ER;
		char element[10];
		_itoa(H->Element, element, 10);
		Agnode_t *Fa = agnode(g, element, 1);
		L = Leftist_Heap_Add_Node(g, H->Left);
		R = Leftist_Heap_Add_Node(g, H->Right);
		if (L != NULL)
		{
			EL = agedge(g, Fa, L, 0, 1);
			agsafeset(EL, "color", "turquoise", "");
			agsafeset(EL, "tailport", "c", "");
			agsafeset(EL, "headport", "ne", "");
		}
		if (R != NULL)
		{
			ER = agedge(g, Fa, R, 0, 1);
			agsafeset(ER, "color", "turquoise", "");
			agsafeset(ER, "tailport", "c", "");
			agsafeset(ER, "headport", "nw", "");
		}
		return Fa;
	}
	return NULL;
}
void Draw_Leftist_Heap(LH_PriorityQueue H, char *format, char *name)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);
	agsafeset(g, "rankdir", "TB", "");
	Leftist_Heap_Add_Node(g, H);

	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, name);

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);
}
static Agnode_t * Binomial_Queue_Add_Node(Agraph_t *g, BQ_Position H)
{
	if (H != NULL)
	{
		Agnode_t *L, *S;
		Agedge_t *EL, *ES;
		char element[10];
		_itoa(H->Element, element, 10);
		Agnode_t *Fa = agnode(g, element, 1);

		L = Binomial_Queue_Add_Node(g, H->LeftChild);
		S = Binomial_Queue_Add_Node(g, H->NextSibling);

		if (L != NULL)
		{
			EL = agedge(g, Fa, L, 0, 1);
			agsafeset(EL, "color", "turquoise", "");
			agsafeset(EL, "tailport", "c", "");
			agsafeset(EL, "headport", "ne", "");
		}
		if (S != NULL)
		{
			ES = agedge(g, Fa, S, 0, 1);
			agsafeset(ES, "color", "turquoise", "");
			agsafeset(ES, "tailport", "e", "");
			agsafeset(ES, "headport", "w", "");
		}
		return Fa;
	}
	return NULL;
}
void Draw_Binomial_Queue(BQ_Queue H, char *format, char *name)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);
	agsafeset(g, "rankdir", "TB", "");

	for (int i = 0; i < BQ_MaxTrees; ++i)
	{
		if (H->TheTrees[i])
		{
		    Binomial_Queue_Add_Node(g, H->TheTrees[i]);
		}
	}

	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, name);

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);
}

