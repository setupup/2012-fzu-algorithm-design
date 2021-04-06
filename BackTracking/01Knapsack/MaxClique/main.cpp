/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MaxClique
*/
#include <iostream>
using namespace std;
class Clique{
	friend MaxClique(int**, int[], int);
private:
	void Backtrack(int i);
	int** a;
	int n;
	int* x;
	int* bestx;
	int cn;
	int bestn;
};
void Clique::Backtrack(int i)
{
	if (i > n){
		for (int j = 1; j <= n; j++)
			bestx[j] = x[j];
		bestn = cn;
		return;
	}
	int OK = 1;
	for (int j = 1; j < i; j++)
	{
		if (x[j] && a[i][j] == 0)
		{
			OK = 0;
			break;
		}
	}
	if (OK){
		x[i] = 1;
		cn++;
		Backtrack(i + 1);
		x[i] = 0;
		cn--;
	}
	if (cn + n - i > bestn)
	{
		x[i] = 0;
		Backtrack(i + 1);
	}
}
int MaxClique(int** a, int v[], int n)
{
	Clique Y;
	Y.x = new int[n + 1];
	Y.a = a;
	Y.n = n;
	Y.cn = 0;
	Y.bestn = 0;
	Y.bestx = v;
	Y.Backtrack(1);
	delete[] Y.x;
	return Y.bestn;
}

int main(int argc, char* argv[])
{

}