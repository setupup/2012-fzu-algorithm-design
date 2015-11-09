/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
FlowShopScheduling
*/
#include <iostream>
using namespace std;
int FlowShop(int n, int a[], int b[], int c[])
{
	class Jobtype{
	public:
		int operator<=(Jobtype a) const
		{
			return (key <= a.key);
		}
		int key;
		int index;
		bool job;
	};
	Jobtype* d = new Jobtype[n];
	for (int i = 0; i < n; i++)
	{
		d[i].key = a[i]>b[i] ? b[i] : a[i];
		d[i].job = a[i] <= b[i];
		d[i].index = i;
	}
	sort(d, n);
	int j = 0;
	int k = n - 1;
	for (int i = 0; i < n; i++)
	{
		if (d[i].job)
			c[j++] = d[i].index;
		else
			c[k--] = d[i].index;
	}
	j = a[c[0]];
	k = j + b[c[0]];
	for (int i = 1; i < n; i++)
	{
		j += a[c[i]];
		k = j < k ? k + b[c[i]] : b[c[i]];
	}
	delete d;
	return k;
}
int main(int argc, char* argv[])
{

}