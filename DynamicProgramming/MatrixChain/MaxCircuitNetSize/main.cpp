/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MaxCircuitNetSize
*/
#include <iostream>
using namespace std;
void MNS(int C[], int n, int** size)
{ //Time O(n2) Space O(n2)
	for (int j = 0; j < C[1]; j++)
	{
		size[1][j] = 0;
	}
	for (int j = C[1]; j <= n; j++)
	{
		size[1][j] = 1;
	}
	for (int i = 2; i < n; i++)
	{
		for (int j = 0; j < C[i]; j++)
			size[i][j] = size[i - 1][j];
		for (int j = C[i]; j <= n; j++)
		{
			size[i][j] = max(size[i - 1][j], size[i - 1][C[i] - 1] + 1);
		}
	}
	size[n][n] = max(size[n - 1][n], size[n - 1][C[n] - 1] + 1);
}
void Traceback(int C[], int** size, int n, int Net[], int& m)
{ //Time O(n)
	int j = n;
	int m = 0;
	for (int i = n; i > 1; i--)
	{
		if (size[i][j] != size[i - 1][j]){
			Net[m++] = i;
			j = C[i] - 1;
		}
	}
	if (j >= C[1])
		Net[m++] = 1;
}
int main(int argc, char* argv[])
{

}