#ifndef SORTED
#define SORTED

#define Sort_Element_Type int

void    Insertion_Sort(Sort_Element_Type A[], int N);
void    Shell_Sort(Sort_Element_Type A[], int N);
void    Heap_Sort(Sort_Element_Type A[], int N);
void    Merge_Sort(Sort_Element_Type A[], int N);
void    Quick_Sort(Sort_Element_Type A[], int N);
void    Quick_Select(Sort_Element_Type A[], int k, int Left ,int Right);
#endif