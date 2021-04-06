/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
0-1Knapsack
*/
#include <iostream>
using namespace std;
template<class Type>
void Knapsack(Type v, int w, int c, int n, Type** m)
{
	int jMax = min(w[n] - 1, c);
	for (int j = 0; j <= jMax; j++)
	{
		m[n][j] = 0;
	}
	for (int j = w[n]; j <= c; j++)
		m[n][j] = v[n];
	for (int i = n - 1; i > 1; i--)
	{
		jMax = min(w[i] - 1, c);
		for (int j = 0; j <= jMax; j++)
		{
			m[i][j] = m[i + 1][j];
		}
		for (int j = w[i]; j <= c; j++)
		{
			m[i][j] = max(m[i + 1][j], m[i + 1][j - w[i]] + v[i]);
		}
	}
	m[1][c] = m[2][c];
	if (c >= w[1])
		m[1][c] = max(m[1][c], m[2][c - w[1]] + v[1]);
}
template<class Type>
void Traceback(Type** m, int w, int c, int n, int x)
{
	for (int i = 1; i < n; i++)
	{
		if (m[i][c] == m[i + 1][c])
			x[i] = 0;
		else
		{
			x[i] = 1;
			c -= w[i];
		}
	}
	x[n] = (m[n][c]) ? 1 : 0;
}
//0-1 Knapsack algorithm improvement
int main(int argc, char* argv[])
{

}