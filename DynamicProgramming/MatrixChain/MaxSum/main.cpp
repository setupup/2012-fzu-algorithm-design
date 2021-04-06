/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MaxSum
*/
#include <iostream>
using namespace std;
int MaxSum(int n, int* a, int& besti, int& bestj)
{//O(n3) --> O(n2)
	int sum = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			int thissum = 0;
			for (int k = i; k <= j; k++)
				thissum += a[k];
			if (thissum > sum)
			{
				sum = thissum;
				besti = i;
				bestj = j;
			}
		}
		return sum;
	}
}
//Using Divide&Conquer O(nlogn)
int MaxSubSum(int* a, int left, int right)
{
	int sum = 0;
	if (left == right)
		sum = a[left] > 0 ? a[left] : 0;
	else
	{
		int center = (left + right) / 2;
		int leftsum = MaxSubSum(a, left, center);
		int rightsum = MaxSubSum(a, center + 1, right);
		int s1 = 0;
		int lefts = 0;
		for (int i = center; i >= left; i--)
		{
			lefts += a[i];
			if (left > s1)
				s1 = lefts;
		}
		int s2 = 0;
		int rights = 0;
		for (int i = center + 1; i <= right; i++)
		{
			rights += a[i];
			if (rights > s2)
				s2 = rights;
		}
		sum = s1 + s2;
		if (sum < leftsum)
			sum = leftsum;
		if (sum < rightsum)
			sum = rightsum;
	}
	return sum;
}
int MaxSum(int n, int* s)
{
	return MaxSubSum(a, 1, n);
}
//Using Dynamic Programming O(n)
int MaxSum(int n, int* a)
{
	int sum = 0;
	int b = 0;
	for (int i = 1; i <= n; i++)
	{
		if (b > 0)
			b += a[i];
		else
			b = a[i];
		if (b > sum)
			sum = b;
	}
	return sum;
}
//Expand to high-dimension and other specific situation
//
int MaxSum2(int m, int n, int** a)
{
	int sum = 0;
	int* b = new int[n + 1];
	for (int i = 1; i <= m; i++)
	{
		for (int k = 1; k <= n; k++)
			b[k] = 0;
		for (int j = i; j <= m; j++)
		{
			for (int k = 1; k <= n; k++)
				b[k] += a[j][k];
			int max = MaxSum(n, b);
			if (max > sum)
				sum = max;
		}
	}
	return sum;
}
//A problem Variation

int main(int argc, char* argv[])
{

}