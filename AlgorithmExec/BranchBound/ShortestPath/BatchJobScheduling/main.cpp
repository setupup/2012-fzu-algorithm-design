/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
BatchJobScheduling
*/
#include <iostream>
using namespace std;
class Flowshop;
class MinHeapNode{ //the structure node of the heap
	friend Flowshop;
public:
	operator int() const{
		return bb;
	}
private:
	void Init(int);
	void NewNode(MinHeapNode, int, int, int, int);
	int s;
	int f1;
	int f2;
	int sf2;
	int bb;
	int* x;
};
void MinHeapNode::Init(int n)
{
	x = new int[n];
	for (int i = 0; i < n; i++)
	{
		x[i] = i;
	}
	s = 0;
	f1 = 0;
	f2 = 0;
	sf2 = 0;
	bb = 0;
}
void MinHeapNode::NewNode(MinHeapNode E, int Ef1, int Ef2, int Ebb, int n)
{
	x = new int[n];
	for (int i = 0; i < n; i++)
		x[i] = E.x[i];
	f1 = Ef1;
	f2 = Ef2;
	sf2 = E.sf2 + f2;
	bb = Ebb;
	s = E.s + 1;
}
class Flowshop{
	friend void main(void);
public:
	int BBFlow(void);
private:
	int Bound(MinHeapNode, int&, int&, bool**);
	void Sort(void);
	int n;
	int** M;
	int** b;
	int** a;
	int* bestx;
	int bestc;
	bool** y;
};
void Flowshop::Sort(void)
{
	int* c = new int[n];
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < n; i++)
		{
			b[i][j] = M[i][j];
			c[i] = i;
		}
		for (int i = 0; i < n - 1; i++)
		{
			for (int k = n - 1; k>i; k--)
			{
				if (b[k][j] < b[k - 1][j]){
					Swap(b[k][j], b[k - 1][j]);
					Swap(c[k], c[k - 1]);
				}
			}
		}
		for (int i = 0; i < n; i++)
			a[c[i]][j] = i;
	}
	delete[] c;
}
int Flowshop::Bound(MinHeapNode E, int& f1, int& f2, bool** y)
{
	for (int k = 0; k < n; k++)
	{
		for (int j = 0; j < 2; j++)
		{
			y[k][j] = false;
		}
	}
	for (int k = 0; k <= E.s; k++)
	{
		for (int j = 0; j < 2; j++)
		{
			y[a[E.x[k]][j]][j] = true;
		}
	}
	f1 = E.f1 + M[E.x[E.s]][0];
	f2 = ((f1>E.f2) ? f1 : E.f2) + M[E.x[E.s]][1];
	int sf2 = E.sf2 + f2;
	int s1 = 0;
	int s2 = 0;
	int k1 = n - E.s;
	int k2 = n - E.s;
	int f3 = f2;
	for (int j = 0; j < n; j++)
	{
		if (!y[j][0])
		{
			k1--;
			if (k1 == n - E.s - 1)
				f3 = (f2>f1 + b[j][0]) ? f2 : f1 + b[j][0];
			s1 += f2 + k1*b[j][0];
			//compute the s2 value
			for (int j = 0; j < n; j++)
			{
				if (!y[j][1])
					k2--;
				s1 += b[j][1];
				s2 += f3 + k2*b[j][1];
			}
		}
	}
	return sf2 + ((s1>s2) ? s1 : s2);
}
int Flowshop::BBFlow(void)
{
	Sort();
	MinHeap<MinHeapNode> H(1000);
	MinHeapNode E;
	E.Init(n);
	while (E.s <= n)
	{
		if (E.s == n){
			if (E.sf2 < bestc)
			{
				bestc = E.sf2;
				for (int i = 0; i < n; i++)
				{
					bestx[i] = E.x[i];
				}
			}
			delete[] E.x;
		}
		else{
			for (int i = E.s; i < n; i++)
			{
				Swap(E.x[E.s], E.x[i]);
				int f1, f2;
				int bb = Bound(E, f1, f2, y);
				if (bb < Bestc)
				{
					MinHeapNode N;
					N.NewNode(E.f1.f2, bb, n);
					H.Insert(N);

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
	}
	
	return bestc;
}
int main(int argc, char* argv[])
{

}