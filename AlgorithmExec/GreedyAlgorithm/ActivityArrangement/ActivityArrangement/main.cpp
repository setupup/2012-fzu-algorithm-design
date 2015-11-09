/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
Activity Arrangement
*/
#include <iostream>
using namespace std;

template<class Type>
void GreedySelector(int n, Type s[], Type f[], bool A[])
{// array start and finish is ordered by the finish time
	A[1] = true;
	int j = 1;
	for (int i = 2; i <= n; i++)
	{
		if (s[i] >= f[j])
		{
			A[i] = true;
			j = i;
		}
		else
			A[i] = false;
	}
}
int main(int argc, char* argv[])
{

}