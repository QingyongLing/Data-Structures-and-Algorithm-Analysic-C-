#include "P6.3_binary_heap.h"
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


