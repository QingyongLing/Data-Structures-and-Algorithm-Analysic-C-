#include "P7Sort.h"

void    Insertion_Sort(Sort_Element_Type A[], int N)
{
	int j, p;
	Sort_Element_Type Tmp;
	/*(1)loop p=1:1:N                                                             */
	/*(2)loop j=p:-1:0                                                            */
	/*(3)find the insert place of Tmp,and move the bigger one back                */
	/*p=1: A[0] A[1] in order  p=2: A[0] A[1] A[2] in order  ...                  */
	for (p = 1; p < N; p++)
	{
		Tmp = A[p];
		for (j = p; j > 0 && A[j - 1] > Tmp; j--)
			A[j] = A[j - 1];
		A[j] = Tmp;
	}
}
void    Shell_Sort(Sort_Element_Type A[], int N)
{
	int i, j, Increment;
	Sort_Element_Type Tmp;
	/*(1) divide A into Increment part,then use Insertion_Sort*/
	for (Increment = N / 2; Increment > 0; Increment /= 2)
	{
		for (i = Increment; i < N; i++)
		{
			Tmp = A[i];
			for (j = i; j >= Increment; j -= Increment)
				if (Tmp < A[j - Increment])
					A[j] = A[j - Increment];
				else
					break;
			A[j] = Tmp;
		}
	}
}