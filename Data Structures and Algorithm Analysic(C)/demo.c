
#include <stdio.h>

//#include "Q2.12a.h"
//#include "P4.3_binary_search_tree.h"

#include "P4.4_AVL_tree.h"
#include "P4.5_Splay_Tree.h"
#include <gvc.h>

int main(int argc, char **argv)
{
	//Q_2_12a_Test();
	//BST_Test();
	//AVL_Test();
	//ST_Test();
	 
	
	Agraph_t *g;
	Agnode_t *n, *m;
	Agedge_t *e;
	GVC_t *gvc;

	/* set up a graphviz context */
	gvc = gvContext();

	/* parse command line args - minimally argv[0] sets layout engine */
	//gvParseArgs(gvc, argc, argv);

	/* Create a simple digraph */
	g = agopen("g", Agdirected, 0);
	n = agnode(g, "n", 1);
	m = agnode(g, "m", 1);
	e = agedge(g, n, m, 0, 1);

	/* Set an attribute - in this case one that affects the visible rendering */
	agsafeset(n, "color", "red", "");

	/* Compute a layout using layout engine from command line args */
	//gvLayoutJobs(gvc, g);

	gvLayout(gvc, g, "dot");

	
	/* Write the graph according to -T and -o options */
	//gvRenderJobs(gvc, g);

	//gvRenderFilename(gvc, g, "w", "test.gv");
	
	//gvRender(gvc, g, "dot", stdout);

	gvRenderFilename(gvc, g, "jpg", "test.jpg");

	/* Free layout data */
	gvFreeLayout(gvc, g);

	/* Free graph structures */
	agclose(g);

	//system("pause");
	/* close output file, free context, and return number of errors */
	gvFreeContext(gvc);
	system("pause");  
	return 0;
}