/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
TravellingSalesman
*/
#include <iostream>
using namespace std;
template<class Type>
class Traveling{
	friend Type TSP(int**, int[], int, Type);
private:
	void Backtrack(int i);
	int n;
	int* x;
	int* bestx;
	Type** a;
	Type cc;
	Type bestc;
	Type NoEdge;
};
template<class Type>
void Traveling<Type>::Backtrack(int i)
{
	if (i == n)
	{
		if (a[x[n - 1]][x[n]] != NoEdge&&a[x[n]][1] != NoEdge &&
			(cc + a[x[n - 1]][x[n]] + a[x[n]][1] < bestc || bestc == NoEdge))
		{
			for (int j = 1; j <= n; j++)
				bestx[j] = x[j];
			bestc = cc + a[x[n - 1]][x[n]] + a[x[n]][1];
		}
	}
	else
	{
		for (int j = i; j <= n; j++)
		{// Is it OK to enter the x[j] subtree?
			if (a[x[i - 1]][x[j]] != NoEdge && (cc + a[x[i - 1]][x[i]] < bestc ||
				bestc == NoEdge)){
				Swap(x[i], x[j]);
				cc += a[x[i - 1]][x[i]];
				Backtrack(i + 1);
				cc -= a[x[i - 1]][x[i]];
				Swap(x[i], x[j]);
			}
		}
	}
}
template<class Type>
Type TSP(Type** a, int v[], int n, Type NoEdge)
{
	Traveling<Type> Y;
	//Initialize the Y
	Y.x = new int[n + 1];
	for (int i = 1; i <= n; i++)
	{
		Y.x[i] = 1;
		Y.a = a;
		Y.n = n;
		Y.bestc = NoEdge;
		Y.bestx = v;
		Y.cc = 0;
		Y.NoEdge = NoEdge;
		//Search all the x[2:n] permutation
		Y.Backtrack(2);
		delete[] Y.x;
		return Y.bestc;
	}
}
int main(int argc, char* argv[])
{

}