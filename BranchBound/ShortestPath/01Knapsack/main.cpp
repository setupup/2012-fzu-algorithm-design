/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
0-1Knapsack
*/
#include <iostream>
using namespace std;
class Object{
	friend int Knapsack(int*, int*, int, int, int);
public:
	int operator<=(Object a) const
	{
		return(d >= a.d);
	}
private:
	int ID;
	float d;
};
template<class Typew, class Typep> class Knap;
class bbnode{
	friend Knap<int, int>;
	friend int Knapsack(int*, int*, int, int, int*);
private:
	bbnode* parent;
	bool LChild;
};
template<class Typew,class Typep>
class HeapNode{
	friend Knap<Typew, Typep>;
public:
	operator Typep() const
	{
		return uprofit;
	}
private:
	Typep uprofit;
	Typep profit;
	Typew weight;
	int level;
	bbnode* ptr;
};
template<class Typew,class Typep>
class Knap{
	friend Typep Knapsack(Typep*, Typew*, int, int*);
public:
	Typep MaxKnapsack();
private:
	MaxHeap<HeapNode<Typep, Typew>>* H;
	Typep Bound(int i);
	void AddLiveNode(Typep up, Typep cp, Typew cw, bool ch, int level);
	bbnode* E;
	Typew c;
	int n;
	Typew* w;
	Typep* p;
	Typew cw;
	Typep cp;
	int* bestx;
};
template<class Typew,class Typep>
Typep Knap<Typew, Typep>::Bound(int i)
{
	Typew cleft = c - cw;
	Typep b = cp;
	while (i <= n&&w[i] <= cleft)
	{
		cleft -= w[i];
		b += p[i];
		i++;
	}
	if (i <= n)
		b += p[i] / w[i] * cleft;
	return b;
}
template<class Typep,class Typew>
void Knap<Typep, Typew>::AddLiveNode(Typep up, Typep cp, Typew cw, bool ch, int lev)
{
	bbnode* b = new bbnode;
	b->parent = E;
	b->LChild = ch;
	HeapNode<Typep, Typew> N;
	N.uprofit = up;
	N.profit = cp;
	N.weight = cw;
	N.level = lev;
	N.ptr = b;
	H->Insert(N);
}
template<class Typew,class Typep>
Typep Knap<Typew, Typep>::MaxKnapsack()
{
	H = new MaxHeap<HeapNode<Typep, Typew>>(1000);
	bestx = new int[n + 1];
	int i = 1;
	E = 0;
	cw = cp = 0;
	Typep bestp = 0;
	Typep up = Bound(1);
	while (i != n + 1){
		Typew wt = cw + w[i];
		if (wt <= c){
			if (cp + p[i] > bestp)
				bestp = cp + p[i];
			AddLiveNode(up, cp + p[i], cw, w[i], true, i + 1);
		}
		up = Bound(i + 1);
		if (up >= bestp)
			AddLiveNode(up, cp, cw, false, i + 1);
		HeapNode<Typep, Typew> N;
		H->DeleteMax(N);
		E = N.ptr;
		cw = N.weight;
		cp = N.profit;
		up = N.uprofit;
		i = N.level;
	}
	for (int j = n; j > 0; j--)
	{
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return cp;
}
template<class Typew,class Typep>
Typep Knapsack(Typep p[], Typew w[], Typew c, int n, int bestx[])
{
	Typew W = 0;
	Typep P = 0;
	Object* Q = new Object[n];
	for (int i = 1; i <= n; i++)
	{
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}
	if (W <= c)
		return P;
	Sort(Q, n);
	//create the class Knap data member
	Knap<Typew, Typep> K;
	K.p = new Typep[n + 1];
	K.w = new Typew[n + 1];
	for (int i = 1; i <= n; i++)
	{
		K.p[i] = p[Q[i - 1].ID];
		K.w[i] = w[Q[i - 1].ID];
	}
	K.cp = 0;
	K.cw = 0;
	K.c = c;
	K.n = n;
	Typep bestp = K.MaxKnapsack();
	for (int j = 1; j <= n; j++)
	{
		bestx[Q[j - 1].ID] = K.bestx[j];
	}
	delete[] Q;
	delete[] K.w;
	delete[] K.p;
	delete[] K.bestx;
	return bestp;
}
int main(int argc, char* argv[])
{

}