/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
WarehouseRentalProblem
*/
#include <iostream>
#include <fstream>
using namespace std;
void input(char* filename, char* file)
{
	ifstream inFile;
	ofstream outFile;
	int* b;
	int* c;
	int** d;
	int i, j, k, p, q, n, m;
	inFile.open(filename);
	inFile >> n;
	m = n*(n + 1) / 2;
	b = new int[n];
	c = new int[m];
	Make2DArray(d, n, m);
	for (i = 0; i < n; i++)
		inFile >> b[i];
	for (i = 0, k = 0; i < n; i++)
	{
		for (j = 0; j < n - 1; j++)
		{
			inFile >> c[k++];
		}
	}
	inFile.close();
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			d[i][j] = 0;
	}
	for (k = 0; k < n; k++)
	{
		p = n - k;
		q = k*n - k*(k - 1) / 2;
		for (i = 0; i < p; i++)
		{
			d[i + k][q + j] = 1;
		}
	}
	outFile.open(file);
	outFile << -1 << "   " << n << "   " << m << endl;
	outFile << 0 << "   " << 0 << "   " << n << endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
			outFile << d[i][j] << "   " << endl;
		outFile << b[i] << endl;
	}
	for (i = 0; i < m; i++)
		outFile << c[i] << "   ";
	outFile << endl;
	outFile.close();
	delete[] b;
	delete[] c;
	Delete2DArray(d, n);
}
int main(int argc, char* argv[])
{

}