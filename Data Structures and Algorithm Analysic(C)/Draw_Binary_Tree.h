#ifndef DRAW_BINARY_TREE
#define DRAW_BINARY_TREE

#define Element_Length 20

#include <gvc.h>
#include "CommonNode.h"
#include "P4.4_AVL_tree.h"

/*Draw a picture of a binary tree,element is int*/
void  Draw_Binary_Tree_int(struct Node *p, char *format, char *filename);
void  Draw_AVL_Tree_int(AVL_Tree g, char *format, char *filename);
void  Draw_ST_Tree_int(struct Node *p, char *format, char *filename);

Agnode_t* AddNode_Binary_tree_int(Agraph_t *g, struct Node *p);
Agnode_t* AddNode_AVL_tree_int(Agraph_t *g, AVL_Tree p);

void  MakeGif(char* format,char* name, int start, int end);
/*write the function of other type*/

#endif