/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MatrixChain
*/
#include <iostream>
using namespace std;
void MatrixChain(int* p, int n, int** m, int** s)
{
	for (int i = 1; i <= n; i++)
	{
		m[i][i] = 0;
	}
	for (int r = 2; r <= n; r++)
	{
		for (int i = 1; i <= n - r + 1; i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for (int k = i + 1; k < j; k++)
			{
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]){
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}
void Traceback(int i, int j, int** s)
{
	if (i == j) return;
	Traceback(i, s[i][j], s);
	Traceback(s[i][j] + 1, j, s);
	cout << "Multiply A " << i << ", " << s[i][j];
	cout << "and A " << (s[i][j] + 1) << ", " << j << endl;
}
//--------------MemorizedMatrixChain
int MemorizedMatrixChain(int n, int** m, int** s)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
			m[i][j] = 0;
	}
	return LookupChain(1, n);
}
int LookupChain(int i, int j)
{
	if (m[i][j] > 0)
		return m[i][j];
	if (i == j)
		return 0;
	int u = LookupChain(i, i) + LookupChain(i + 1, j) + p[i - 1] * p[i] * p[j];
	s[i][j] = i;
	for (int k = i + 1; k < j; k++)
	{
		int t = LookupChain(i, k) + LookupChain(k + 1, j) + p[i - 1] * p[k] * p[j];
		if (t < u){
			u = t;
			s[i][j] = k;
		}
	}
	m[i][j] = u;
	return u;
}
int main(int argc, char* argv[])
{

}