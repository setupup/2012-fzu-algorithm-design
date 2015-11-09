/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
QuickSort
*/
#include <iostream>
using namespace std;
template<class Type>
void QuickSort(Type a[], int p, int r)
{
	if (p < r){
		int q = Partition(a, p, r);
		QuickSort(a, p, q - 1);
		QuickSort(a, q + 1, r);
	}
}
template<class Type>
int Partition(Type a[], int p, int r)
{
	int i = p;
	int j = r + 1;
	Type x = a[p];
	while (true)
	{
		while (a[++i] < x);
		while (a[--j]>x);
		if (i >= j) break;
		Swap(a[i], a[j]);
	}
	a[p] = a[j];
	a[j] = x;
	return j;
}
template<class Type>
int RandomizePartition(Type a[], int p, int r)
{
	int i = Random(p, r);
	Swap(a[i], a[p]);
	return Partition(a, p, r);
}
template<class Type>
void RandomizeQuickSort(Type a[], int p, int r)
{
	if (p < r){
		int q = RandomizePartition(a, p, r);
		RandomizeQuickSort(a, p, q - 1);
		RandomizeQuickSort(a, q + 1, r);
	}
}
//------------------LinearTimeSelect-------------------------
template<class Type>
Type RandomizedSelect(Type a[], int p, int r, int k)
{
	if (p == r)
		return a[p];
	int i = RandomizedPartition(a, p, r);
	int j = i - p + 1;
	if (k <= j)
		return RandomizedSelect(a, p, i, k);
	else
		return RandomizedSelect(a, i + 1, r, k - j);
}
template<class Type>
Type Select(Type a[], int p, int r, int k){
	if (r - p < 75){
		//USE some sort Algorithm here
		return a[p + k - 1];
	}
	for (int i = 0; i <= (r - p - 4) / 5; ++i)
	{
		Type x = Select(a, p, p + (r - p - 4) / 5, (r - p - 4) / 10);
		int i = Partition(a, p, r, x);
		int j = i - p + 1;
		if (k <= j)
			return Select(a, p, i, k);
		else
			return Select(a, i + 1, r, k - j);
	}
}
int main(int argc, char* argv[])
{

}