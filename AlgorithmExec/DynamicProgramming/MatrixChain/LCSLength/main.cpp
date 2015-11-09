/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
LCSLength
*/
#include <iostream>
using namespace std;
template<class Type>
void LCSLength(int m, int n, char* x, char* y, int** c, Type** b)
{
	int i, j;
	for (i = 1; i <= m; i++)
		c[i][0] = 0;
	for (i = 1; i <= n; i++)
		c[0][i] = 0;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = '↖';
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = '↑';
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = '←';
			}
		}
	}
}
template<class Type>
void LCS(int i, int j, char* x, Type** b)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == '↖'){
		LCS(i - 1, j - 1, x, b);
		cout << x[i];
	}
	else if (b[i][j] == '↑')
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}
int main(int argc, char* argv[])
{

}