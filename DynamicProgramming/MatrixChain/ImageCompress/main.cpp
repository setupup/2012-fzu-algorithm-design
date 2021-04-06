/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
ImageCompress
*/
#include <iostream>
using namespace std;
void Compress(int n, int p[], int s[], int l[], int b[])
{//O(n)
	int Lmax = 256;
	int header = 11;
	s[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		b[i] = length(p[i]);
		int bmax = b[i];
		s[i] = s[i - 1] + bmax;
		l[1] = 1;
		for (int j = 2; j <= i&&j <= Lmax; j++)
		{
			if (bmax < b[i - j + 1])
				bmax = b[i - j + 1];
			if (s[i]>s[i - j] + j*bmax)
			{
				s[i] = s[i - j] + j*bmax;
				l[i] = j;
			}
		}
		s[i] += header;
	}
}
int length(int i)
{
	int k = 1;
	i = i / 2;
	while (i > 0)
	{
		k++;
		i = i / 2;
	}
	return k;
}
//How to find the optimal solution
void Traceback(int n, int& i, int s[], int l[])
{
	if (n == 0)
		return;
	Traceback(n - l[n], i, s, l);
	s[i++] = n - l[n];
}
void Output(int s[], int l[], int b[], int n)
{
	cout << "The optimal value is " << s[n] << endl;
	int m = 0;
	Traceback(n, m, s, l);
	s[m] = n;
	cout << "Decompose into " << m << " segments" << endl;
	for (int j = 1; j <= m; j++)
	{
		l[j] = l[s[j]];
		b[j] = b[s[j]];
	}
	for (int j = 1; j <= m; j++)
	{
		cout << l[j] << ' ' << b[j] << endl;
	}
}
int main(int argc, char* argv[])
{

}