#ifndef SPLAY_TREE
#define SPLAY_TREE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "CommonNode.h"

typedef struct Node ST_Node;
typedef ST_Node *ST_Position;
typedef ST_Node *ST_Tree;

ST_Tree     ST_MakeEmpty(ST_Tree T);
ST_Position ST_Find(ElementType x, ST_Tree T);
ST_Position ST_FindMin(ST_Tree T);
ST_Position ST_FindMax(ST_Tree T);
ST_Tree     ST_Insert(ElementType x, ST_Tree T);
ST_Tree     ST_Delete(ElementType x, ST_Tree T);
void        ST_Display(ST_Tree p);

static ST_Position SplayingLeft(ST_Position k2);
static ST_Position SplayingLeftLeft(ST_Position k3);
static ST_Position SplayingLeftRight(ST_Position k3);
static ST_Position SplayingRight(ST_Position k2);
static ST_Position SplayingRightLeft(ST_Position k3);
static ST_Position SplayingRightRight(ST_Position k3);

int  ST_Num_In_Array(int* a, int num, int n);
void ST_Tree_Rightful_Test(ST_Tree p);
void ST_Test();

#endif