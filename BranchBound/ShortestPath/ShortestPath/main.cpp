/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
ShortestPath
*/
#include <iostream>
using namespace std;
template<class Type>
class Graph{
	friend void main(void);
public:
	void ShortestPaths(int);
private:
	int n;
	int* prev;
	Type** c;
	Type* dist;
};
template<class Type>
class MinHeapNode{
	friend Graph<Type>;
public:
	operator int() const
	{
		return length;
	}
private:
	int i;
	Type length;
};
template<class Type>
void Graph<Type>::ShortestPaths(int v)
{
	MinHeap<MinHeapNode<Type>> H(1000);
	MinHeapNode<Type> E;
	E.i = v;
	E.length = 0;
	dist[v] = 0;
	//Search the Solution space
	while (true)
	{
		for (int j = 1; j <= n; j++)
		{
			if ((c[E.i][j] < inf) && (E.length + c[E.i][j] < dist[j])){
				dist[j] = E.length + c[E.i][j];
				prev[j] = E.i;
				MinHeapNode<Type> N;
				N.i = j;
				N.length = dist[j];
				H.Insert(N);
			}
		}
	}
	try{
		H.DeleteMin(E);
	}
	catch (OutOfBounds)
	{
		break;
	}
}
int main(int argc, char* argv[])
{

}