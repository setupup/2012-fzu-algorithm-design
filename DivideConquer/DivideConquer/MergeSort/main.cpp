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
	Type* b = new Type[n];
	if (left < right)
	{
		int i = (left + right) / 2; // i is the divide point, left and right is the bound of the array
		MergeSort(a, left, i); //from left to i become ordered
		MergeSort(a, i + 1, right); //from i+1 to right become ordered
		Merge(a, b, left, i, right); //when merge they need B to contain the merge result
		Copy(a, b, left, right); //finally move the B content back to A
	}
}
//remove recursion //by divide the array in advance //kan po! 
template<class Type>
void MergeSort(Type a[], int n)
{
	Type* b = new Type[n];
	int s = 1;
	while (s < n){//s=1 s=4
		MergePass(a, b, s, n); //s is a counter//here to merge the ordered daoguolaidaoguoqu
		s += s;
		MergePass(b, a, s, n);//s=2 s=8
		s += s;
	}
}
template<class Type>
void MergePass(Type x[], Type y[], int s, int n) // n is the array length
{//merge the length s subarray
	int i = 0;
	while (i <= n - 2 * s){ //merge the s subarray
		Merge(x, y, i, i + s - 1, i + 2 * s - 1);
		i = i + 2 * s;
	}
	//remaining element less than 2s
	if (i + s < n)
		Merge(x, y, i, i + s - 1, n - 1);
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