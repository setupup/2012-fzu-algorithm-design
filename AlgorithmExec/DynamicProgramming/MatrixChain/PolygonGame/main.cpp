/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
PolygonGame
*/
#include <iostream>
using namespace std;
void MIN_MAX(int n, int i, int s, int j, int& minf, int& maxf)
{
	int e[4];
	int a = m[i][s][0];
	int b = m[i][s][1];
	int r = (i + s - 1) % n + 1;
	int c = m[r][j - s][0];
	int d = m[r][j - s][1];
	if (op[r] == 't')
	{
		minf = a + c;
		maxf = b + d;
	}
	else
	{
		e[1] = a*c;
		e[2] = a*d;
		e[3] = b*c;
		e[4] = b*d;
		minf = e[1];
		maxf = e[1];
		for (int r = 2; r < 5; r++)
		{
			if (minf>e[r])
				minf = e[r];
			if (maxf < e[r])
				maxf = e[r];
		}
	}
}
int Poly_Max(int n)
{ //Time O(n3)
	int minf, maxf;
	for (int j = 2; j <= n; j++)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int s = 1; s < j; s++)
			{
				MIN_MAX(n, i, s, j, minf, maxf, m, op);
				if (m[i][j][0]>minf)
					m[i][j][0] = minf;
				if (m[i][j][1] < maxf)
					m[i][j][1] = maxf;
			}
		}
	}
	int temp = m[1][n][1];
	for (int i = 2; i <= n; i++)
	{
		if (temp < m[i][n][1])
			temp = m[i][n][1];
	}
	return temp;
}
int main(int argc, char* argv[])
{

}