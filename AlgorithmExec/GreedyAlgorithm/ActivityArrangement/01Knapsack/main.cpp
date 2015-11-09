/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
0-1Knapsack cannot use greedy strategy
Only Knapsack could use the greedy algorithm
*/
#include <iostream>
using namespace std;
void Knapsack(int n, float M, float v[], float w[], float x[])
{
	Sort(n, v, w);
	int i;
	for (i = 1; i <= n; i++)
		x[i] = 0;
	float c = M;
	for (i = 1; i <= n; i++)
	{
		if (w[i] > c)
			break;
		x[i] = 1;
		c -= w[i];
	}
	if (i <= n)
		x[i] = c / w[i];
}
int main(int argc, char* argv[])
{

}