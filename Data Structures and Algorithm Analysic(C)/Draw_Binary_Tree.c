#include "Draw_Binary_Tree.h"

//extern struct Node;
void  Draw_Binary_Tree_int(struct Node *p, char *format, char *filename)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0);

	AddNode_Binary_tree_int(g, p);
	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, filename);

	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);
}
void  Draw_AVL_Tree_int(AVL_Tree p, char *format, char *filename)
{
	Agraph_t *g;
	GVC_t *gvc;

	gvc = gvContext();
	g = agopen("g", Agdirected, 0); 
	
	agsafeset(g, "outputMode", "edgesfirst", "");
	//agsafeset(g, "splines", "line", "");

	AddNode_AVL_tree_int(g, p);
	gvLayout(gvc, g, "dot");
	gvRenderFilename(gvc, g, format, filename);
	
	gvFreeLayout(gvc, g);
	agclose(g);
	gvFreeContext(gvc);
}
void  Draw_ST_Tree_int(struct Node *p, char *format, char *filename)
{
	Draw_Binary_Tree_int(p, format, filename);
}



Agnode_t* AddNode_Binary_tree_int(Agraph_t *g, struct Node *p)
{
	if (p != NULL)
	{
		Agnode_t *L, *R;
		Agedge_t *EL, *ER;
		char element[Element_Length];
		_itoa(p->Element, element, 10);
		Agnode_t *Fa = agnode(g, element, 1);
		L = AddNode_Binary_tree_int(g, p->Left);
		R = AddNode_Binary_tree_int(g, p->Right);
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
Agnode_t* AddNode_AVL_tree_int(Agraph_t *g, AVL_Tree p)
{
	if (p != NULL)
	{
		Agnode_t *L, *R;
		Agedge_t *EL, *ER;
		char element[Element_Length];
		_itoa(p->Element, element, 10);
		Agnode_t *Fa = agnode(g, element, 1);
		//agsafeset(Fa, "shape", "egg", "");

		L = AddNode_AVL_tree_int(g, p->Left);
		R = AddNode_AVL_tree_int(g, p->Right);
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

void  MakeGif(char* format, char* name, int start, int end)
{
	char args[1000]="gifsicle.exe -d 100 ";
	int  head = strlen(args);
	for (int i = start; i < end; ++i)
	{
		strncat(args, name, strlen(name));
		char gif_index_str[10] = "";
		_itoa(i, gif_index_str, 10);
		strncat(args, gif_index_str, strlen(gif_index_str));
		strncat(args, ".", strlen("."));
		strncat(args, format, strlen(format));
		strncat(args, " ", strlen(" "));
	}
	strncat(args, ">", strlen(">"));
	strncat(args, name, strlen(name));
	strncat(args, ".", strlen("."));
	strncat(args, format, strlen(format));
	system(args);
	char *p = args;
	while (*p != '>')++p;
	*p = '\0';
	p = args + head;
	char del[1000] = "del ";
	strncat(del, p, strlen(p));
	system(del);
}