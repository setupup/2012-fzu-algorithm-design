/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MergeSort
*/
#include <iostream>
using namespace std;
template<class Type>
void MergeSort(Type a[], int left, int right)
{
	if (left < right)
	{
		int i = (left + right) / 2;
		MergeSort(a, left, i);
		MergeSort(a, i + 1, right);
		Merge(a, b, left, i, right);
		Copy(a, b, left, right);
	}
}
//remove recursion
template<class Type>
void MergeSort(Type a[], int n)
{
	Type* b = new Type[n];
	int s = 1;
	while (s < n){
		MergePass(a, b, s, n);
		s += s;
		MergePass(b, a, s, n);
		s += s;
	}
}
template<class Type>
void MergePass(Type x[], Type y[], int s, int n)
{
	int i = 0;
	while (i <= n - 2 * s){
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;

	}
	if (i + s < n) Merge(x, y, i, i + s - 1, n - 1);
	else
	{
		for (int j = i; j <= n - 1; ++j)
			y[j] = x[j];
	}
}
template<class Type>
void Merge(Type c[], Type d[], int l, int m, int r)
{
	int i = 1;
	int j = m + 1;
	int k = l;
	while ((i <= m) && (j <= r))
	{
		if (c[i] <= c[j])
			d[k++] = c[i++];
		else
			d[k++] = c[j++];
	}
	if (i > m)
	{
		for (int q = j; q <= r; ++q)
			d[k++] = c[q];
	}
	else
	{
		for (int q = i; q <= m; ++q)
			d[k++] = c[q];
	}
}
int main(int argc, char* argv[])
{

}