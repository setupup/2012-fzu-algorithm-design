/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
RandomNumber
*/
#include <iostream>
using namespace std;
const unsigned long maxshort = 65536L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder = 12345L;
class RandomNumber{
private:
	unsigned long randSeed;
public:
	//generate the seeds
	RandomNumber(unsigned long s = 0);
	unsigned short Random(unsigned long n);
	double fRandom(void);
};
RandomNumber::RandomNumber(unsigned long s)
{
	if (s == 0)
		randSeed = time(0);
	else
		randSeed = s;
}
//generate a integer between 0:n-1
unsigned short RandomNumber::Random(unsigned long n)
{
	randSeed = multiplier*randSeed + adder;
	return (unsigned short)((randSeed >> 16) % n);
}
double RandomNumber::fRandom(void)
{
	return Random(maxshort) / double(maxshort);
}
int TossCoins(int numberCoins)
{
	static RandomNumber coinToss;
	int i, tosses = 0;
	for (i = 0; i < numberCoins; i++)
	{
		tosses += coinToss.Random(2);
	}
	return tosses;
}
//USE the Random number to implement the Numerical Probability algorithm
//7.2.1 throw the dots randomly to compute the pi-value (Darts n./vt.)
double Darts(int n)
{
	static RandomNumber dart;
	int k = 0;
	for (int i = 1; i <= n; i++)
	{
		double x = dart.fRandom();
		double y = dart.fRandom();
		if ((x*x + y*y) <= 1)
			k++;
	}
	return 4 * k / double(n);
}
//7.2.2 USE Darts to compute definite integral
double Darts(int n)
{//use the dart compute the DI
	static RandomNumber dart;
	int k = 0;
	for (int i = 1; i <= n; i++)
	{
		double x = dart.fRandom();
		double y = dart.fRandom();
		if (y <= f(x))
			k++;
	}
	return k / double(n);
}
double Integration(double a, double b, int n)
{//use mean value method to compute the integral
	static RandomNumber rnd;
	double y = 0;
	for (int i = 1; i <= n; i++)
	{
		double x = (b - a)*rnd.fRandom() + a;
		y += g(x);
	}
	return (b - a)*y / double(n);
}
//7.2.3 solve the non-linear equations
bool NonLinear(double* x0, double* dx0, double* x, double a0, double epsilon, double k, int n, int Steps, int M)
{
	static RandomNumber rnd;
	bool success;
	double* dx;
	double* r;
	dx = new double[n + 1];
	r = new double[n + 1];
	int mm = 0;
	int j = 0;
	double a = a0;
	for (int i = 1; i <= n; i++)
	{
		x[i] = x0[i];
		dx[i] = dx0[i];
	}
	double fx = f(x, n);
	double min = fx;
	while ((min > epsilon) && (j < Steps))
	{
		if (fx < min){
			min = fx;
			a *= k;
			success = true;
		}
		else
		{
			mm++;
			if (mm>M)
				a /= k;
			success = false;
		}
		for (int i = 1; i <= n; i++)
		{
			r[i] = 2.0*rnd.fRandom() - 1;
		}
		if (success)
		{
			for (int i = 1; i <= n; i++)
			{
				dx[i] = a*r[i];
			}
		}
		else
		{
			for (int i = 1; i <= n; i++)
				dx[i] = a*r[i] - dx[i];
		}
		for (int i = 1; i <= n; i++)
		{
			x[i] += dx[i];
		}
		fx = f(x, n);
	}
	if (fx <= epsilon)
		return true;
	else
		return false;
}

//here is not a standard main function
void main(void)
{
	const int NCOINS = 10;
	const long NTOSSES = 50000L;
	long i;
	long heads[NCOINS + 1];
	int j;
	int position;
	for (j = 0; j < NCOINS + 1; j++)
	{
		heads[j] = 0;
	}
	for (i = 0; i < NTOSSES; i++)
	{
		heads[TossCoins(NCOINS)]++;
	}
	for (i = 0; i <= NCOINS; i++)
	{
		position = int(float(heads[i]) / NTOSSES * 72);
		cout << setw(6) << i << "  "; //why here's setwidth is invalid
		for (j = 0; j < position - 1; j++)
		{
			cout << " ";
		}
		cout << "*" << endl;
	}
}
//-----------------------------------------above could be used in after algorithms
int main(int argc, char* argv[])
{

}