#include<stdio.h>
#include<assert.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))

/*Question: 求最小子序列和*/

/*method: divide and conquer*/
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

/*method: another way*/
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

void Q_2_12a_Test()
{
	int a[5][10] = { { 1, -2, 3, 4, -8, -1, 5, 2, 4, -5 },
	                 { 1, 2, 3, 4, 5, -2, 3, -4, 9,  2 },
					 { 0, -3, -4, -9, -1, -2, -1, -2, 1, -1},
					 {1,2,3,4,5,6,7,8,9,0},
	                 {1,2,-3,-5,-3,1,3,-1,-4,9},
	};
	int b[] = { -9, -4, -22, 0, -12 };
	for (int i = 0; i < 5; ++i)
	{
		/*int num = find_min_sum_subarray(a[i], 0, 10);*/
		int num = find_min_sum_subarray_2(a[i], 10);
		assert(num == b[i]);
		printf("min_sum_sunarray:  %d\n",num);
	}

}
