/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
NearestPairs
*/
#include <iostream>
//using namespace std;
bool Cpair1(S, d)
{
	int n = | S | ;
	if (n < 2){
		d = infinite;
		return false;
	}
}
class PointX{
public:
	int operator<=(PointX a) const
	{
		return (x <= a.x);
	}
	friend bool  Cpair2(PointX X[], int n, PointX& a, PointX& b, float& d);
//private:
	int ID;
	float x, y;
};
class PointY{
public:
	int operator<=(PointY a) const
	{
		return (y <= a.y);
	}
	friend bool  Cpair2(PointX X[], int n, PointX& a, PointX& b, float& d);

//private:
	int p;
	float x, y;
};

template<class Type>
inline float distance(const Type& u, const Type& v)
{
	float dx = u.x - v.x;
	float dy = u.y - v.y;
	return sqrt(dx*dx + dy*dy);
}
bool Cpair2(PointX X[], int n, PointX& a, PointX& b, float& d)
{
	if (n < 2)
		return false;
	MergeSort(X, n);
	PointY* Y = new PointY[n];
	for (int i = 0; i < n; ++i)
	{
		Y[i].p = i;
		Y[i].x = X[i].x;
		Y[i].y = X[i].y;
	}
	MergeSort(Y, n);
	PointY* Z = new PointY[n];
	closest(X, Y, Z, 0, n - 1, a, b, d);
	delete[] Y;
	delete[] Z;
	return true;
}
void closest(PointX X[], PointY Y[], PointY Z[], int l, int r, PointX& a, PointX& b, float& d)
{
	if (r - 1 == 1){
		a = X[l];
		b = X[r];
		d = distance(X[l], X[r]);
		return;
	}
	if (r - 1 == 2)
	{
		float d1 = distance(X[l], X[l + 1]);
		float d2 = distance(X[l + 1], X[r]);
		float d3 = distance(X[l], X[r]);
		if (d1 <= d2&&d1 <= d3){
			a = X[l];
			b = X[l + 1];
			d = d1;
			return;
		}
		if (d2 <= d3){
			a = X[l + 1];
			b = X[r];
			d = d2;
		}
		else
		{
			a = X[l];
			b = X[r];
			d = d3;
		}
		return;
	}
	int m = (l + r) / 2;
	int f = l;
	int g = m + 1;
	for (int i = 1; i <= r; ++i)
	{
		if (Y[i].p > m)
			Z[g++] = Y[i];
		else
			Z[f++] = Y[i];
	}
	closest(X, Z, Y, l, m, a, b, d);
	float dr;
	PointX ar, br;
	closest(X, Z, Y, m + 1, r, ar, br, dr);
	if (dr < d)
	{
		a = ar;
		b = br;
		d = dr;
	}
	Merge(Z, Y, l, m, r);
	int k = l;
	for (int i = l; i <= r; i++)
	{//fabs?
		if (fabs(Y[m].x - Y[i].x) < d)
			Z[k++] = Y[i];
	}
	for (int i = l; i < k;i++)
	for (int j = i + 1; j < k&&Z[j].y - Z[i].y < d; j++)
	{
		float dp = distance(Z[i], Z[j]);
		if (dp < d)
		{
			d = dp;
			a = X[Z[i].p];
			b = X[Z[j].p];
		}
	}
}

int main(int argc, char* argv[])
{

}