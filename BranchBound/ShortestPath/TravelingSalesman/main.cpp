/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
TraverlingSalesman
*/
#include <iostream>
using namespace std;
template<class Type>
class Traveling{
	friend void main(void);
public:
	Type BBTSP(int v[]);
private:
	int n;
	Type** a;
	Type** NoEdge;
	Type** cc;
	Type** bestc;
};
template<class Type>
class MinHeapNode{
	friend Traveling<Type>;
public:
	operator Type() const
	{
		return lcost;
	}
private:
	Type lcost;
	Type cc;
	Type rcost;
	int s;
	int* x;
};
template<class Type>
Type Traveling<Type>::BBTSP(int v[])
{
	MinHeap<MinHeapNode<Type>> H(1000);
	Type* MinOut = new Type[n + 1];
	Type MinSum = 0;
	for (int i = 1; i <= n; i++)
	{
		Type Min = NoEdge;
		for (int j = 1; j <= n; j++)
		{
			if (a[i][j] != NoEdge && (a[i][j] < Min || Min == NoEdge))
				Min = a[i][j];
		}
		if (Min == NoEdge)
			return NoEdge;
		MinOut[i] = Min;
		MinSum += Min;
	}
	MinHeapNode<Type> E;
	E.x = new int[n];
	for (int i = 0; i < n; i++)
	{
		E.x[i] = i + 1;
		E.s = 0;
		E.cc = 0;
		E.rcost = MinSum;
		Type bestc = NoEdge;
		while (E.s < n - 1)
		{
			if (E.s == n - 2)
			{
				if (a[E.x[n - 2]][E.x[n - 1]] != NoEdge&&
					a[E.x[n - 1]][1] != NoEdge &&
					(E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1] < bestc
					|| bestc == NoEdge)){
					bestc = E.cc + a[E.x[n - 2]][E.x[n - 1]] + a[E.x[n - 1]][1];
					E.cc = bestc;
					E.lcost = bestc;
					E.s++;
					H.Insert(E);
				}
				else
					delete[] E.x;
			}
			else
			{
				for (int i = E.s + 1; i < n; i++)
				{
					if (a[E.x[E.s]][E.x[i]] != NoEdge)
					{
						Type cc = E.cc + a[E.x[E.s]][E.x[i]];
						Type rcost = E.rcost - MinOut[E.x[E.s]];
						Type b = cc + rcost;
						if (b < bestc || bestc == NoEdge)
						{
							MinHeapNode<Type> N;
							N.x = new int[n];
							for (int j = 0; j < n; j++)
								N.x[j] = E.x[j];
							N.x[E.s + 1] = E.x[i];
							N.x[i] = E.x[E.s + 1];
							N.cc = cc;
							N.s = E.s + 1;
							N.lcost = b;
							N.rcost = rcost;
							H.Insert(N);
						}
					}
				}
			}
			delete[] E.x;
		}
		try{
			H.DeleteMin(E);
		}
		catch (OutOfBounds)
		{
			break;
		}
		if (bestc == NoEdge)
			return NoEdge;
		for (int i = 0; i < n; i++)
			v[i + 1] = E.x[i];
		while (true)
		{
			delete[] E.x;
			try{
				H.DeleteMin(E);
			}
			catch (OutOfBounds)
			{
				break;
			}
		}
		return bestc;
	}
}
int main(int argc, char* argv[])
{

}