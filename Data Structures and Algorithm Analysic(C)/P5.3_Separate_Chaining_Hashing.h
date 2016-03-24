#ifndef SEPARATE_CHAINING_HASHING
#define SEPARATE_CHAINING_HASHING

#define SC_Element_Type int
#define SC_MIN_TABLESIZE (10)

struct SC_ListNode;
typedef struct SC_ListNode *SC_Position;
struct SC_HashTbl;
typedef struct SC_HashTbl *SC_HashTable;

struct SC_ListNode
{
	SC_Element_Type Element;
	SC_Position     Next;
};
typedef SC_Position SC_List;
struct SC_HashTbl
{
	int     TableSize;
	SC_List *TheLists;
};

SC_HashTable SC_InitalizeTable(int SC_TableSize);
void         SC_DestroyTable(SC_HashTable H);
SC_Position  SC_Find(SC_Element_Type key, SC_HashTable H);
void         SC_Insert(SC_Element_Type key, SC_HashTable H);

int          SC_Hash(SC_Element_Type key, int TableSizle);

void         SC_Test();
#endif