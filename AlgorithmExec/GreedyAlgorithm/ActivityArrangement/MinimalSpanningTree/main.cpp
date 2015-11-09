/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MinimalSpanningTree MST(Prim,Kruskal)
*/
#include <iostream>
using namespace std;
template<class Type>
void Prim(int n, Type** c)
{ //O(n2)
	Type lowcost[maxint];
	int closest[maxint];
	bool s[maxint];
	s[1] = true;
	for (int i = 2; i <= n; i++)
	{
		lowcost[i] = c[1][i];
		closest[i] = 1;
		s[i] = false;
	}
	for (int i = 1; i < n; i++)
	{
		Type min = inf;
		int j = 1;
		for (int k = 2; k <= n; k++)
		{
			if ((lowcost[k] < min) && (!s[k]))
			{
				min = lowcost[k];
				j = k;
			}
		}
		cout << j << ' ' << closest[j] << endl;
		s[j] = ture;
		for (int k = 2; k <= n; k++)
		{
			if ((c[j][k] < lowcost[k]) && (!s[k]))
			{
				lowcost[k] = c[j][k];
				closest[k] = j;
			}
		}
	}
}
//Kruskal
template<class Type>
class EdgeNode{
	friend ostream& operator<<(ostream&, EdgeNode<Type>);
	friend bool Kruskal(int, int, EdgeNode<Type>*, EdgeNode<Type>*);
	friend void main(void); //in main function need to access the content
public:
	operator Type() const
	{
		return weight;
	}
private:
	Type weight;
	int u, v;
};
template<class Type>
bool Kruskal(int n, int e, EdgeNode<Type> E[], EdgeNode<Type> t[])
{
	MinHeap<EdgeNode<Type>> H(1);
	H.Initialize(E, e, e);
	UnionFind U(n);
	int k = 0;
	while (e&&k < n - 1)
	{
		EdgeNode<int> x;
		H.DeleteMin(x);
		e--;
		int a = U.Find(x.u);
		int b = U.Find(x.v);
		if (a != b)
		{
			t[k++] = x;
			U.Union(a, b);
		}
		H.Deactivate();
		return (k == n - 1);
	}
}
int main(int argc, char* argv[])
{

}