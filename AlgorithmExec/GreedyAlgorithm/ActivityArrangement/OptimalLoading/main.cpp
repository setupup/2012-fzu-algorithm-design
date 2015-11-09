/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
OptimalLoading
*/
#include <iostream>
using namespace std;
template<class Type>
void Loading(int x[], Type w[], Type c, int n)
{
	int* t = new int[n + 1];
	Sort(w, t, n);
	for (int i = 1; i <= n; i++)
	{
		x[i] = 0;
	}
	for (int i = 1; i <= n&&w[t[i]] <= c; i++)
	{
		x[t[i]] = 1;
		c -= w[t[i]];
	}
}
int main(int argc, char* argv[])
{

}