### 数据结构与算法分析（C语言）

注：使用数据结构与算法分析（C语言描述）的笔记

#### 1. 基本结构
#### 1.1 数组
数组是最为常用的结构，包括一维数组和多维数组，数组的一个优点是它在实际的物理内存中是连续的，因此存取时可以直接按照计算地址的方式进行操作，因此存取速度快。

对于C语言来说，在使用数组时，数组变量会进行隐式转换，例如：一维数组转换为指向第一个元素的指针，二维数组转换为指向一个数组的指针。
对于二维数组，将其作为参数传递时，需要指明二维数组的列数，例如`int b[][2]={1,2,3,4}; foopp(b,4);`中，在调用`foopp(b,4)`时，`p`转换成为一个`int (*)[2]`,如果函数参数是一个`int **p`类型，那么这是无法匹配的。

Tip： 关于`int *[2]` 和 `int (*)[2]` 的区别见相关书籍
```c
#include <stdio.h>
void foop(int *p,int num)
{
    for(int i=0;i<num;++i)
        printf("%d ",*(p+i));
    for(int i=0;i<num;++i)
        printf("%d ",p[i]);
}
void foopp(int p[][2],int num)
{
    for(int i=0;i<num;++i)
        printf("%d ",(*p)[i]);
    for(int i=0;i<num;++i)
        printf("%d ",*((*p)+i));
}
int main()
{
    int a[3]={1,2,3};
    int b[2][2]={1,2,3,4};
    foop(a,3);
    foopp(b,4);
    return 0;
}
```
Question： 计算最小子序列和，即在一个序列中找到和最小的子序列        
Method：   分治法 O(NlogN)      

将序列分为两部分,那么所需的子序列可能在左子序列、者右子序列、一部分在左子序列另一部分在右子序列，所以可以先分别求出左子序列的最小子序列和，然后在两者的交界处分别向两边遍历两个子序列，分别算出最小的子序列后相加。得出了上述三种情况下的最小子序列和，保留最小值。    
```c
//end is the index of last element+1 ,for example start=0,end=the number of element
int find_min_sum_subarray(const int a[],const int start,const int end)
{
	int min_left_sum, min_right_sum;
	int temp_left_sum=0, temp_right_sum=0, keep_left_sum, keep_right_sum;

	if (start == end-1)
		return a[start];

	int mid = (start + end) / 2;
	min_left_sum = find_min_sum_subarray(a, start, mid);
	min_right_sum = find_min_sum_subarray(a, mid, end);

	keep_left_sum = a[mid - 1];
	for (int i = mid - 1; i >= start; --i)
	{
		temp_left_sum += a[i];
		if (temp_left_sum < keep_left_sum)
			keep_left_sum = temp_left_sum;
	}

	keep_right_sum = a[mid];
	for (int i = mid; i < end; ++i)
	{
		temp_right_sum += a[i];
		if (temp_right_sum < keep_right_sum)
			keep_right_sum = temp_right_sum;
	}
	return min(min(min_left_sum, min_right_sum), keep_left_sum + keep_right_sum);
}
```
Tip： 递归的思想，以及递归的基本法则     
1. 基准情形。必须总有某些基准情形，它无须递归既可以解出。      
2. 不断推进。对于那些需要递归求解的情形，每一次递归调用都必须要使求解状况朝接近基准情形的方向推进。       
3. 设计法则。假设所有的递归都能运行。       
4. 合成效益法则。在求解一个问题的同一实例时，切勿在不同的递归调用中做重复性的工作。     

Method:    遍历法 O(N)     
题目要求查找最小和的子序列，那么在一个序列中让和越来越小的是负数。分情况讨论：         
如果一个序列没有负数，那么找出序列中最小的正数     
如果序列中存在负数，那么在序列中的最小和不应该大于0，因此当和大于0时重新计算      
```c
int find_min_sum_subarray_2(const int a[], const int n)
{
	int Keep_min=a[0], temp_min=0;
	for (int i = 0; i < n; ++i)
	{
		temp_min += a[i];
		if (temp_min < Keep_min)
			Keep_min = temp_min;
		else if (temp_min > 0)
			temp_min = 0;
	}
	return Keep_min;
}
```
#### 1.2 链表
链表是一种不连续存储的结构，它由一系列不必要在内存中相连的结构组成。每一个节点均含有节点的数据和指向下一个节点的的指针。链表包含单向链表、双向链表、循环表、多重表等。       

![img](/img/ch1/list-img.jpg)

#### 1.3 栈
栈的规则是先进后出，只允许`push`和`pop`操作。栈可以由数组或者链表等方式实现。栈的一个常见应用是将中缀表达式转化为后缀表达式。    
中缀表达式转化为后缀表达式的方式为：将一个表达式（字符串）输入，从左到右，如果遇到一个操作数，则放到输出中，操作符放入栈中。将运算符压入栈的时候，弹出栈元素知道发现优先级更低的元素为止，如果栈顶的元素优先级低于该操作符，则直接压入。     
有一个例外情况是除非在处理一个“)”的时候，否则我们绝不弹出“(”，但其他运算符依然要满足优先级条件。 
#### 1.4 队列
队列要求先进先出，队列可以分为双向队列和单向队列。       
#### 2. 树
根节点：没有父节点的节点      
叶子节点：没有子节点的节点       
深度：节点n的深度为从根节点到n的唯一路径的长        
高：节点n的高是从n到叶子节点的最长路径的长      
前序遍历：先对元素操作，再遍历左右子树             
中序遍历：先遍历左子树，然后操作元素，最后遍历右子树          
后序遍历：先遍历左右子树，然后操作元素              
#### 2.1 二叉树
二叉树的一个节点至多有两个子节点，其形式为：           
```c
struct TreeNode;
typdef struct TreeNode* PtrToNode;
typdef struct PtrToNode Tree;
struct TreeNode
{
    ElementType Element;
    Tree        Left;
    Tree        Right;   
} 
```
二叉树的一个例子，表达式树。上文中提到了将中缀表达式变为后缀表达式的算法，此处我们将后缀表达式生成表达式树。         
一次一个地读入表达式，如果符号是操作数，那么建立一个单节点并将一个指向它的指针压入栈中，如果符号是操作符，那么建立一个节点，在栈中弹出两个两个指针，假设先弹出T1然后弹出T2，将操作符的右儿子指向T1，左儿子指向T2，再将该操作符的指针压入栈中。       

#### 2.2 二叉查找树
二叉查找树常用于查找应用中，其原则是，将小于自身的数值的节点放在左边，大于自身的节点放在右边。二叉查找树的平均深度是O(logN)。     
二叉查找树的接口及结构：    
```c
struct BST_Node;
typedef struct BST_Node *BST_Postion;
typedef struct BST_Node *BST_SearchTree;

#define BST_ElementType int
enum BST_Traversal
{
	Preorder = 1,
	inorder = 2,
	Postorder = 3
};
struct BST_Node
{
	BST_ElementType     element;
	BST_SearchTree  Left;
	BST_SearchTree  Right;
};
BST_SearchTree BST_Makeempty(BST_SearchTree T);
BST_SearchTree BST_Insert(BST_SearchTree T, BST_ElementType e);
BST_SearchTree BST_Delete(BST_SearchTree T, BST_ElementType e);
BST_Postion    BST_Find(BST_ElementType e, BST_SearchTree T);
BST_Postion    BST_FindMin(BST_SearchTree T);
BST_Postion    BST_FindMax(BST_SearchTree T);
void           BST_Display(BST_SearchTree T,enum BST_Traversal b);
```
BST_makeempty用于释放内存，返回`NULL`在`T`为`NULL`保持`T`不变，或者释放完成后更新`T`      
```c
/*T=BST_Makeempty(T);*/
BST_SearchTree BST_Makeempty(BST_SearchTree T)
{
	if (T != NULL)
	{
		BST_Makeempty(T->Left);
		BST_Makeempty(T->Right);
		free(T);
	}
	return NULL;
}
```
插入操作，当插入是`T`为`NULL`，那么有两种情况，第一是对空树插入，第二是找到了相应的叶子节点进行插入。        
按照流程，将值与数据对比，若小于则插入到左子树，若大于则插入到右子树，插入操作完成后返回该新节点的指针。        
在该函数中，返回的是根节点指针。返回值有两个作用，第一是在空树插入时返回根节点指针，第二是对一颗树递归插入时用返回值更新节点关系，如`T->Left = BST_Insert(T->Left, e);`这种形式递归中，在建立新节点后返回该节点指针，也就是相应的子树的根节点指针，然后赋值给`T->Left'或者`T->Right`。       
```c
/*NOTE: T=BST_Insert(T,e);*/
BST_SearchTree BST_Insert(BST_SearchTree T, BST_ElementType e)
{
	if (T == NULL)
	{
		T = (BST_SearchTree)malloc(sizeof(struct BST_Node));
		if (T == NULL)
		{
			printf("Out of space");
		}
		else
		{
			T->element = e;
			T->Left = T->Right = NULL;
		}
	}
	else if (e < T->element)
		T->Left = BST_Insert(T->Left, e);
	else if (e>T->element)
		T->Right = BST_Insert(T->Right, e);
	return T;
}
```
删除操作，要删除一个节点，跟插入是类似的，如果大于当前节点的值，那往右边搜索，如果小于当前节点的值，那么往左边搜索，递归结束的条件也就是未找到元素（`T==NULL`）或者找到了元素并将其删除了。   
删除的情况分成三种，第一，该节点有两个子树；第二，节点有一个子树；第三，节点为叶子节点，没有子树。   
对应操作分别是：   
1. 有两个子树：找出该节点的左子树最大值，用该值代替当前节点的值，然后再左子树中删除该子树最大值（最右）；或者用右子树的最小值代替该节点，然后再右子树删除该最小值。对于有两个子树的情况，实质上删除的是子树的节点（递归到第二和第三种情况中操作）。        
2. 有一个子树：直接删除该节点，然后返回该节点的子树的指针     
3. 没有子树：直接删除，返回`NULL`       

删除后更新节点指向的操作是由返回值进行的，返回值即树（子树）的根节点指针，原理与插入操作是类似的。     
```c
/*NOTE: T=BST_Delete(T,e)*/
BST_SearchTree BST_Delete(BST_SearchTree T, BST_ElementType e)
{
	BST_Postion TmpCell;
	if (T == NULL)
	{
		printf("Element can not find");
	}
	else if (e < T->element)
		T->Left = BST_Delete(T->Left, e);
	else if (e>T->element)
		T->Right = BST_Delete(T->Right, e);
	else if (T->Left&&T->Right)
	{
		TmpCell = BST_FindMin(T->Right);
		T->element = TmpCell->element;
		T->Right = BST_Delete( T->Right,T->element);
	}
	else
	{
        /*包含有一个子树或者没有子树的操作*/
		TmpCell = T;
        /*下面的if else 语句等价于：T = T->Left == NULL ? T->Right : T->Left;*/
		if (T->Left == NULL)
			T = T->Right;
		else if (T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}
```
对于查找和显示那就很简单了     
```c
BST_Postion    BST_Find(BST_ElementType e, BST_SearchTree T)
{
	if (T == NULL)
		return NULL;
	if (e < T->element)
		return BST_Find(e, T->Left);
	else if (e>T->element)
		return BST_Find(e, T->Right);
	else
		return T;
}
BST_Postion    BST_FindMin(BST_SearchTree T)
{
	if (T == NULL)
		return NULL;
	else if (T->Left == NULL)
		return T;
	else
		return BST_FindMin(T->Left);
}
BST_Postion    BST_FindMax(BST_SearchTree T)
{
	if (T != NULL)
		while (T->Right != NULL)
			T = T->Right;
	return T;
}
void           BST_Display(BST_SearchTree T,enum BST_Traversal b)
{
	if (T == NULL)
		return;
	if (b == Preorder)
		printf("%d ", T->element);
	BST_Display(T->Left, b);
	if (b == inorder)
		printf("%d ", T->element);
	BST_Display(T->Right, b);
	if (b == Postorder)
		printf("%d ", T->element);
}
```
#### 2.3 二叉平衡树
AVL(Adelson-Velskii和Landis)树是带有平衡条件的二叉查找树，它要求每个节点的左右子树的高度最多相差1，这种树可以保证树的深度是O(logN)。     
在此处提供一个AVL树的在线可视化网址：[AVL树](http://www.cs.usfca.edu/~galles/visualization/AVLtree.html)       
我们这么定义AVL树的节点：   
```c
struct AVL_Node;
typedef struct AVL_Node *AVL_Position;
typedef struct AVL_Node *AVL_Tree;
#define AVL_ElementType int
struct AVL_Node
{
	AVL_ElementType Element;
	AVL_Tree        Left;
	AVL_Tree        Right;
	int             Height;
};
```
但是在插入一个节点后，从插入节点到根节点的节点平衡会被破坏，这破坏了树的平衡特性，为此我们需要对树进行简单的修正，这种修正称为旋转。    
我们沿着插入点到根节点的方向上行，更新树中节点的高度信息，找到破坏了AVL树平衡条件的节点，并对其修正。     
节点不平衡满足节点左儿子与节点右儿子的高度之差的绝对值为2，对于（左或右）子节点为空的情况，空节点的高度定为-1。      
节点a产生不平衡的情况分四种：     
1. 左左：对a的左儿子的左子树进行一次插入      
2. 左右：对a的左儿子的右子树进行一次插入       
3. 右左：对a的右儿子的左子树进行一次插入      
4. 右右：对a的右儿子的右子树进行一次插入       

（1）左左   
下图是对一个节点的左儿子的左子树的一次插入，插入后节点左儿子的高度为2，右儿子的高度为0，相差2，导致不平衡。       
为此我们需要改变该树的根节点，使整棵树平衡，根据AVL树的节点条件，对节点进行旋转。通过一次调整可以解决的旋转称为单旋转。      
在左左的旋转中，实际上是3和5的变化，3的高度比8大2，因此将3作为根节点，5作为3的右儿子后，树的平衡性得到了纠正，那么如何处理原先根节点左儿子的右子树的？       
根据大小，根节点的左儿子的右子树必然全部小于根节点而且大于左儿子，也就是大于新的根节点（3），小于新的根节点的左子树（5），在本例中即4大于3，小于5，因此将其作为新的根节点的右子树的左儿子是满足大小关系的。完成上述操作后纠正了树的失衡并满足AVL树的大小条件。      

![img](/img/ch2/AVL_insert_LL_1.png)        
对于左左情况调整的代码为：    
注：AVL_Height为获得节点高度的函数      
```c
static AVL_Position SingleRotateWithLeft(AVL_Position k2)
{
	/*         k2         --                k1             */
	/*        /  \                         /  \            */
	/*       k1   a       --              c    k2          */
	/*      /  \               ->        /    /  \         */
	/*     c    b         --            a    b    a        */
	/*    /                                                */
	/*   d                --                               */
	AVL_Position k1;
	k1 = k2->Left;
	k2->Left = k1->Right;
	k1->Right = k2;
	k2->Height = max(AVL_Height(k2->Left), AVL_Height(k2->Right)) + 1;
	k1->Height = max(AVL_Height(k1->Left), k2->Height) + 1;
	return k1;
}
```
根据这种不平衡的情况，我们可以做一个一般情形下的分析：          
对于一个节点，如果是左左情况的失衡，首先满足：`AVL_Height(k2->Left)-AVL_Height(k2->Right)==2`，我们可以画出一般情况的图形：      

![img](/img/ch2/AVL_insert_LL_2.png)       
对于k2来说是不平衡的，左儿子比右儿子高2，那么可以确定，左儿子不为空（不等于NULL）,而且左儿子的左子树插入了新的值也不为空，至于Y和Z的情况我们不得而知，但是X，Y，Z内部是平衡的。     
对于插入来说，只有将高度差从1加到2会导致失衡，因此在插入前，Height(X)==Height(Z),且Height(X)==Height(Y),假设Height(X)=Height(Y)+1,那么先失衡的是K1不是K2，这是不符合的,因此在K1插入新值之后满足：      
Height(X)-Height(Z)==1     
Height(X)-Height(Y)==1    
可以因此左左的情况满足：    
`AVL_Height(k2->Left)-AVL_Height(k2->Right)==2`    
`AVL_Height(k2->Left->Left)>AVL_Height(k2->Left->Right))`    
对于左左的情况，可以看出在旋转之后Y的根节点到整棵树的根节点的距离是不变的，整棵树相当于围绕Y作了旋转。      
左左旋转实际要做的也就是X向上移动一层，Z向下移动一层，同时Y保持相对不变。在旋转之后，整棵树只是改变了一部分的指针，我们依旧得到一颗AVL树，并且：      
X、Y、Z中叶子节点与根节点的最长距离相同     
整棵树的高度与插入之前是相同的，不需要进一步修改    
注：在调整过程中，是在通往根节点的进程中调整的，因此上图的一棵树也许是另一棵树的子树，但是我们可以确定，在进行左左旋转之后这棵树的高度与插入之前的高度一致，因此不需要在进行任何的调整。    

（2）右右    
右右的情况是左左的对称,根据右右的条件可以画出一般图形：  
  
![img](/img/ch2/AVL_insert_RR_1.png)      
在插入数据前，Height(X)==Height(Z)且Height(X)==Height(Y)，因此插入后同样满足：
Height(X)-Height(Z)==1     
Height(X)-Height(Y)==1  
那么右右旋转可以解决的情况是：    
`AVL_Height(k2->Right)-AVL_Height(k2->Left)==2`    
`AVL_Height(k2->Right->Right)>AVL_Height(k2->Right->Left))`        
右右旋转也就可以看成围绕Y做旋转，右右纠正不平衡平衡的方法也是将X往上提升，将Z往下降，Y相对不变。    
与左左类似，调整后整棵树的高度与插入前相等，且X、Y、Z中叶子节点与根节点的最长距离相同。     
右右旋转的代码为：    
```c
static AVL_Position SingleRotateWithRight(AVL_Position k2)
{
	/*         k2          --                   k1         */
	/*        /  \                             /  \        */
	/*       a    k1       --                k2    c       */
	/*           /  \           ->          /  \    \      */
	/*          b    c     --              a    b    d     */
	/*                \                                    */
	/*                 d   --                              */
	AVL_Position k1; 
	k1 = k2->Right;
	k2->Right = k1->Left;
	k1->Left = k2;
	k2->Height = max(AVL_Height(k2->Left), AVL_Height(k2->Right)) + 1;
	k1->Height = max(k2->Height, AVL_Height(k1->Right)) + 1;
	return k1;
}
```
（3）左右    
左右的情况与左左和右右完全不同，此时单旋转已经无法解决问题了，对于左左和右右的旋转方式进行分析可以发现，无论是左左还是右右都是围绕着Y进行旋转，而插入前，插入后，旋转后这三种状态下Y的相对位置都是不变的。     
即Y为根节点的孙节点，旋转前后只是父节点和祖父节点的位置变化了，从根节点到Y的路径变化了，但是Y中的每个节点到根节点的距离不变。       
我们先画出图形，那么对于左右的情况，即在Y中插入了一个新的节点，使Y中叶子节点到根节点的最长距离+1，对于不平衡的K2来说，无论是采用左左还是右右的单旋转都是无法解决问题的（围绕Y旋转）。        
对于这种情况我们可以插入导致不平衡的情况，我们进行分析，在插入后：    
Height(Y)=Height(Z)+1    
Height(Y)=Height(X)+1   
因此插入后Y的高度+1，那么我们将Y拆分，分成K1和两个子树（A、B）的形式，但是我们无法确定插入的点是在A还是B中，但是A、B满足：    
max(Height(A),Height(B))=Height(Z)     
min(Height(A),Height(B))=Height(Z)-1        
如果min(Height(A),Height(B))=Height(Z)-2的话将导致K1不平衡，显然是违背LR的原则的。    
为了纠正K3的不平衡，我们把Y的根节点（K1）作为新的整棵树的根节点（Y大于父节点，小于祖父节点），把Y根节点的左右子树分别放在两侧（A，B）。此时Height(Y)=Height(Z)+1，因此可以将Y等效为图(b)的形式
根据上文的Height(A)和Height(B)的高度，显然这么调整符合平衡的条件，最后调整成图(c)的形式，使整棵树恢复平衡。     
**与单旋转的情形一样，我们可以得出，在双旋转后，整棵树的高度与插入前是相同的。**      
                    
![img](/img/ch2/AVL_insert_LR_1.png)       
根据左右旋转的情况的分析，可以确定左右旋转可以纠正以下条件的节点不平衡：        
`AVL_Height(k3->Left)-AVL_Height(k3->Right)==2`      
`AVL_Height(k2->Left->Right)>AVL_Height(k2->Left->Left))`      
那么左右旋转的实质是什么？我们可以看到在左右旋转后，A成为了K2的子树，B成为了K3的子树，回顾右右与左左的情况，右右将Y移动到根节点的左边，左左将Y移动到根节点的右边。     

![img](/img/ch2/AVL_insert_LR_2.png)       
左右双旋转也就等价于一个右右的单旋转+一个左左的单旋转，先对根节点的左子树进行RR单旋转然后对根节点进行LL单旋转，注意在进行单旋转时更新节点的指向。其代码实现为：     
```c
static AVL_Position DoubleRotateWithLeft(AVL_Position k3)
{
	/* Left-Right b or c single_right(k1)+single_left(k3)  */
	/*                                                     */
	/*        k3         --                 k2             */
	/*       /  \                          /  \            */
	/*      k1   d       --              k1    k3          */
	/*     /  \                         /  \   / \         */
	/*    a    k2        --            a   b? c?  d        */
	/*        /  \                                         */
	/*       b?  c?      --                                */
	k3->Left = SingleRotateWithRight(k3->Left);
	return SingleRotateWithLeft(k3);
}
```
（4）右左     
右左的情况与左右是类似的，同样，单旋转无法解决它的失衡问题，需要用两次单旋转解决。   

![img](/img/ch2/AVL_insert_RL_1.png)      
同理，插入新的节点之后：
max(Height(A),Height(B))=Height(Z)     
min(Height(A),Height(B))=Height(Z)-1    
右左旋转可以解决的条件是：    
`AVL_Height(k2->Right)-AVL_Height(k2->Left)==2`     
`AVL_Height(k2->Right->Left)>AVL_Height(k2->Right->Right))`    
右左旋转可以等价为先对根节点的右子树进行LL单旋转，然后对根节点进行RR单旋转，最后纠正失衡，得到图(c)。     
右左双旋转后整棵树的高度与插入前是相同的。     
其代码为：    
```c
static AVL_Position DoubleRotateWithRight(AVL_Position k3)
{
	/*similar to DoubleRotateWithLeft*/
	k3->Right = SingleRotateWithLeft(k3->Right);
	return SingleRotateWithRight(k3);
}
```

分析完失衡时候的调整策略，我们可以看一下如何插入新节点：     
插入的过程如下：    
1. 如果T为NULL(空树or找到了插入位置），构造一个节点        
2. 否则，对于元素小于当前节点值时，往左子树插入，否则往右子树插入（注意此时其实包含了相等的情况）,进行递归操作       
3. 检查节点是否有失衡的情况，如果有，进行纠正（进行旋转操作时，更新了进行旋转操作的树内相关节点的高度信息）      
4. 更新当前节点的高度(更新旋转之外的高度改变）     
3. 返回根节点的指针    

```c
AVL_Tree     AVL_Insert(AVL_ElementType x, AVL_Tree T)
{
	if (T == NULL)
	{
		T = (struct AVL_Node *)malloc(sizeof(struct AVL_Node));
		if (T == NULL)
			printf("Out of Space!!!");
		else
		{
			T->Element = x;
			T->Height = 0;
			T->Left = T->Right = NULL;
		}
	}
	else if (x < T->Element) 
	{
		T->Left = AVL_Insert(x, T->Left);
		if (AVL_Height(T->Left) - AVL_Height(T->Right) == 2)
			if (x < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else if (x > T->Element)
	{
		T->Right = AVL_Insert(x, T->Right);
		if (AVL_Height(T->Right) - AVL_Height(T->Left) == 2)
			if (x < T->Right->Element)
				T = DoubleRotateWithRight(T);
			else
				T = SingleRotateWithRight(T);
	}
	T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;
	return T;
}
```
注：`T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;`用于更新当前节点的高度信息。    
1. 在恰好进行插入操作（申请内存）时，该操作等价于：T->Height = 0     
2. 刚插入一个节点，那么除去空树的情况外，都需要通过`T->Left = AVL_Insert(x, T->Left);`和`T->Right = AVL_Insert(x, T->Right);`来递归插入。
那么在插入时，如果引发了旋转，那么更新高度信息只需要用旋转操作即可，对于没有引发旋转的操作，用这一语句逐一更新高度。    


删除的操作与插入是由异曲同工之妙的，删除操作可能不改变平衡也可能导致失衡。在插入的失衡中，分成LL、LR、RL、RR四种情况，分别用四种旋转纠正。那么跟插入的失衡相比有什么不同呢?     
我们先不管这个问题先来看一下删除的方式，在这里我们采用的依旧是二叉查找树的删除规则：     
1. 如果对应节点有两个子节点，那么用左子树最大值替代后再左子树删除最大值，或者用右子树的最小值替代后再右子树中删除最小值，然后返回根节点指针          
2. 如果对应节点有一个子节点，那么直接删除，将对应子节点指针返回     
3. 如果对应节点无子节点，直接删除，返回NULL    

删除节点后必然会导致高度变化，因此要注意更新高度，那么现在来说失衡的情况：     
在插入时，节点的高度差是连续变化的，一旦出现有失衡就要马上纠正，那么左右子节点高度相差2的情况肯定来自于原先相差1的情况，但是删除则多了一种情况。        
以右子树高度多出2为例：    
右左双旋转的情况是：    
`AVL_Height(k2->Right)-AVL_Height(k2->Left)==2`       
`AVL_Height(k2->Right->Left)>AVL_Height(k2->Right->Right))`      
那么右右单旋转的情况是：     
`AVL_Height(k2->Right)-AVL_Height(k2->Left)==2`       
`AVL_Height(k2->Right->Right)>AVL_Height(k2->Right->Left))`           
那么会不会出现这种情况：    
`AVL_Height(k2->Right)-AVL_Height(k2->Left)==2`       
`AVL_Height(k2->Right->Right)==AVL_Height(k2->Right->Left))`  
对于插入操作而言，显然是不可能的，因为按照这个条件，在插入之前就已经失衡了，但是对于删除而言这是一种多出来的情况。以下图为例：       

![img](/img/ch2/AVL_delete_1.png)   
根据删除规则，删除实质上分成了删除叶子节点或者是删除含有一个子树的节点，对于含有一个子树的节点，根据平衡条件，该节点的高度必然是1，它要么只有一个左子节点，要么只有一个右子节点。     
对于原本平衡的树，要使其不平衡，必然是原本高度低的子树删除了某个节点，使其高度下降，然后造成了失衡。      
如图，左子树高度比右子树小，从左子树中删除一个节点（k2或k4），本例中假设删除k2，使左子树高度-1，同时我们知道k3的高度为2，单我们并不确定子树情况，只是可以确认k7、k8、k9和k0至少存在一个，因此在图中我们用虚线箭头表示。      
对k1分别运用右左旋转和右右旋转，得出了相应的结果：    
1. 对于`AVL_Height(k1->Right->Right)>AVL_Height(k1->Right->Left))`的情况（k7、k8不存在，k9、k0至少存在一个），即RR单旋转使其恢复平衡。    
2. 对于`AVL_Height(k1->Right->Right)<AVL_Height(k1->Right->Left))`的情况（k9、k0不存在，k7、k8至少存在一个），即RL双旋转使其恢复平衡。      
3. 对于`AVL_Height(k1->Right->Right)==AVL_Height(k1->Right->Left))`的情况（k7、k8至少存在一个，k9、k0至少存在一个），这时我们可以确定，k6是必然有子树的，那么当k7存在而k8不存在时，进行RL双旋转会导致k3失衡，而对于RR单旋转则不会有这个问题。       
所以我们对这种情况采用RL双旋转是无法完全解决的，而采用RR单旋转是可以解决的。    
    
同理，对于删除了右子树节点导致的失衡，采用的纠正方式是类似的，当`AVL_Height(k1->Left->Left)==AVL_Height(k1->Left->Right))`时，采用LL单旋转可以纠正失衡。       
删除操作的代码为：      
```c
AVL_Tree     AVL_Delete(AVL_ElementType x, AVL_Tree T)
{
	if (T == NULL)
		return NULL;
	if (x == T->Element)
	{
		if (T->Left != NULL&&T->Right != NULL)
		{                          
			AVL_Tree temp = T->Right;
			while (temp->Left != NULL)
				temp = temp->Left;
			T->Element = temp->Element;
			T->Right = AVL_Delete(temp->Element, T->Right);     
		}
		else
		{
			AVL_Tree temp = T;
			T = T->Left == NULL ? T->Right : T->Left;
			free(temp);
            /*当T==NULL或者只有一个子树时，直接返回而不需要更新高度*/
		    return T;
		}
		/*
		if (T->Left != NULL&&T->Right != NULL)
		{
			AVL_Tree temp = T->Left;
			while (temp->Right != NULL)
				temp = temp->Right;
			T->Element = temp->Element;
			T->Left = AVL_Delete(temp->Element, T->Left);
		}
		else
		{
		    AVL_Tree temp = T;
		    T = T->Left == NULL ? T->Right : T->Left;
		    free(temp);
		    return T;
		}
		*/
	}
	else if (x < T->Element)
	{
		T->Left = AVL_Delete(x ,T->Left);
	}
	else
	{
		T->Right = AVL_Delete(x, T->Right);
	}
	T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;
	if (AVL_Height(T->Left) - AVL_Height(T->Right) == 2)
	{
		if (AVL_Height(T->Left->Left) < AVL_Height(T->Left->Right))
			T = DoubleRotateWithLeft(T);
		else
			T = SingleRotateWithLeft(T);
	}
	if (AVL_Height(T->Right) - AVL_Height(T->Left) == 2)
	{
		if (AVL_Height(T->Right->Right) < AVL_Height(T->Right->Left))
			T = DoubleRotateWithRight(T);
		else
			T = SingleRotateWithRight(T);
	}
	return T;
}
```
注1： 此处`T->Height = max(AVL_Height(T->Left), AVL_Height(T->Right)) + 1;`放在旋转操作前面，这是因为四种旋转内部均进行了高度信息的调整，所以先后顺序可以无关，即使用max计算错误也会由旋转操作纠正。     
注2： 进行旋转操作的代码与上文中对应，对于`AVL_Height(k1->Right->Right)==AVL_Height(k1->Right->Left))`和`AVL_Height(k1->Left->Left)==AVL_Height(k1->Left->Right))`两种情况分别采用右右单旋转和左左单旋转。     

#### 2.4 伸展树     
伸展树是一种相对简单的数据结构，它保证从空树开始任意连续M次对树的操作最多花费O(MlogN)时间。     
伸展树的基本想法：当一个节点被访问后，它要经过一系列AVL树的旋转被放到根上。注意，如果一个节点很深，那么在其路径上就存在许多节点也相对比较深，通过重新构造可以使对所有这些节点的进一步访问所花费的时间变少。
因此，如果节点过深，那么我们还要求重新构造应具有平衡这棵树（到某种程度）的作用。      
展开（查找时）：     
展开的操作类似于旋转，不过在旋转如何实施上我们有些选择的余地。与AVL树的相比，有些差异。      
1. 如果所查找的节点位于整棵树的根节点的子节点      
对于这种情况采用AVL的单旋转，对于节点为根节点的左子节点情况用左单旋转，对于节点为根节点的右子节点的情况用右单旋转，所查找节点成为新的根节点           
2. 如果所查找的节点含有祖父节点，而且是祖父节点的左子节点的右子节点，或者是祖父节点的右子节点的左子节点     
对于这种情况，采用AVL的双旋转，此时所查找的节点成为旋转后的新树的根节点。         
3. 如果所查找的节点含有祖父节点，而且是祖父节点的左子节点的左子节点，或者是祖父节点的右子节点的右子节点      
对于这种情况，采用一种新的方式，将所查找的节点旋转至新树的根处：     
![img](/img/ch2/ST_Splaying_1.png)   
例如，要查找的节点为G，则旋转为右图形式；要查找的为x则旋转为左图形式          

插入，按照二叉搜索树的插入方式插入     
删除，我们先访问（查找）要删除的节点，将该节点展开至根处，删除该节点，得到两颗子树，在左子树中查找最大值节点，然后将右子树作为左子树根节点的右子树（或者右子树中查找最小值节点，然后将左子树作为右子树根节点的左子树），注意左右子树均为空的情况存在。

插入的代码与二叉搜索树一致，先看展开，采用AVL树单旋转和双旋转的不再赘述，旋转在伸展树中的目的是将查找的节点上移到根节点：          
```c
static ST_Position SplayingLeftLeft(ST_Position k3)
{
	/*        k3                 k1                 */
	/*       /  \               /  \                */
	/*      k2   d             a    k2              */
	/*     /  \                    /  \             */
	/*    k1   c       -->        b    k3           */
	/*   /  \                         / \           */
	/*  a    b                       c   d          */
	/*                                              */
	ST_Position k2 = k3->Left;
	ST_Position k1 = k3->Left->Left;
	k3->Left = k2->Right;
	k2->Right = k3;
	k2->Left = k1->Right;
	k1->Right = k2;
	return k1;
}
static ST_Position SplayingRightRight(ST_Position k3)
{
	/*        k1                 k3                 */
	/*       /  \               /  \                */
	/*      k2   d             a    k2              */
	/*     /  \         <--        /  \             */
	/*    k3   c                  b    k1           */
	/*   /  \                         / \           */
	/*  a    b                       c   d          */
	/*                                              */
	ST_Position k2 = k3->Right;
	ST_Position k1 = k3->Right->Right;
	k3->Right = k2->Left;
	k2->Left = k3;
	k2->Right = k1->Left;
	k1->Left = k2;
	return k1;
}
```
对于查找的过程，可以分成以下几种情况：   
1. 空树 
2. 所查找的节点恰好在根节点     
3. 所查找的节点恰好在根节点的子节点      
4. 所查找的节点与根节点的距离超过2      
5. 所查找的节点不存在   
   
解决方式：  
1. 返回NULL    
2. 在根节点：直接返回根节点      
3. 在根节点子节点：用单旋转，返回新的根节点     
4. 距离超过2：递归，回退到所查找节点的祖父节点（回退到父节点时也不作处理），对四种情况分别进行展开，如果距离为偶数，可以展开至根节点（情况1），如果距离为奇数，那么最后会回到所查找的节点为根节点的子节点的情况（情况2）        
5. 对于界节点不存在的情况不应该对树做任何改动，应直接返回原来的根节点         
  
查找的代码为：
```c
ST_Position ST_FindGrandson(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
        
    /*可以有，也可以没有*/
	if (T->Element == x)
		return T;
	
	if (x > T->Element)
		T->Right = ST_FindGrandson(x, T->Right);
	else
		T->Left = ST_FindGrandson(x, T->Left);
	
	if (T->Left != NULL)
	{
		if (T->Left->Element == x)
			return T;
		else if (T->Left->Left != NULL&&T->Left->Left->Element == x)
			return SplayingLeftLeft(T);
		else if (T->Left->Right != NULL&&T->Left->Right->Element == x)
			return SplayingLeftRight(T);
	}
	if (T->Right != NULL)
	{
		if (T->Right->Element == x)
			return T;
		else if (T->Right->Right != NULL&&T->Right->Right->Element == x)
			return SplayingRightRight(T);
		else if (T->Right->Left != NULL&&T->Right->Left->Element == x)
			return SplayingRightLeft(T);
	}
    
    /*用于找不到相应节点返回T*/
	return T;
}
ST_Position ST_Find(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	if (T->Element == x)
		return T;
	T = ST_FindGrandson(x, T);
	if (T->Left != NULL&&T->Left->Element == x)
		return SplayingLeft(T);
	else if (T->Right != NULL&&T->Right->Element == x)
		return SplayingRight(T);
	return T;
}
ST_Position ST_FindMin(ST_Tree T)
{
	if (T != NULL)
	{
		ST_Position root = T;
		while (T->Left != NULL)
			T = T->Left;
		return ST_Find(T->Element,root);
	}
	return T;
}
ST_Position ST_FindMax(ST_Tree T)
{
	if (T != NULL)
	{
		ST_Position root = T;
		while (T->Right != NULL)
			T = T->Right;
		return ST_Find(T->Element, root);
	}
	return T;
}
```
注1： 用单旋转的情况只存在于所查节点为根节点的儿子的情况，分别是原本就为树的根节点的儿子，或者是经过`ST_FindGrandson`调整，成为了根节点儿子。      
注2： 查找最大最小值，通过找出最大最小值然后调用`ST_Find`的方式进行。       

删除的原理已经说过，代码是:     
```c
ST_Tree     ST_Delete(SPLAY_ElementType x, ST_Tree T)
{
	if (T == NULL)
		return NULL;
	T = ST_Find(x, T);
	if (T->Element == x)
	{
		ST_Tree L = T->Left, R = T->Right;
		free(T);
		if (L != NULL)
		{
			L = ST_FindMax(L);
			L->Right = R;
			return L;
		}
		else if (R != NULL)
		{
			R = ST_FindMin(R);
			R->Left = L;
			return R;
		}
		else
			return NULL;
	}
	return T;
}
```
删除的情况可以有以下划分：   
1. 空树->返回NULL      
2. 仅有根节点->删除后返回NULL      
3. 除根节点外找到了进行删除->查找，删除根节点，按照左右子树是否为空进行处理，返回根节点指针       
4. 找不到的进行删除->直接返回根节点，对于找不到的情况`ST_Find`不会改变树的结构       


#### 2.5 B树
      













