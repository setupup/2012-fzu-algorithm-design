/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
BackTracking's Knapsack
*/
#include <iostream>
using namespace std;
template<class Typew,class Typep>
class Knap{
	friend Type Knapsack(Typep*, Typew*, Typew, int);
private:
	Typep Bound(int i);
	void Backtrack(int i);
	Typew c;
	int n;
	Typew* w;
	Typep* p;
	Typew cw;
	Typep cp;
	Typep bestp;
};
template<class Typew,class Typep>
Typep Knap<Typew, Typep>::Bound(int i){
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
template<class Typew,class Typep>
void Knap<Typew, Typep>::Backtrack(int i)
{
	if (i > n)
	{
		bestp = cp;
		return;
	}
	if (cw + w[i] <= c) //x[i]=1
	{
		cw += w[i];
		cp += p[i];
		Backtrack(i + 1);
		cw -= w[i];
	}
	if (Bound(i + 1) > bestp)// x[i] = 0
		Backtrack(i + 1);
}
class Object{
	friend int Knapsack(int*, int*, int, int);
public:
	int operator<=(Object a) const
	{
		return (d >= a.d);
	}
private:
	int ID;
	float d;
};
template<class Typew,class Typep>
Typep Knapsack(Typep p[], Typew w[], Typew c, int n)
{
	//initialize for Knap::Backtrack
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
	K.bestp = 0;
	K.Backtrack(1);
	delete[] Q;
	delete[] K.w;
	delete[] K.p;
	return K.bestp;
}
int main(int argc, char* argv[])
{

}