/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
CircuitBoardArrangement
*/
#include <iostream>
using namespace std;
class BoardNode{
	friend int BBArrangement(int**, int, int, int*&);
public:
	operator int() const
	{
		return cd;
	}
private:
	int* x;
	int s;
	int cd;
	int* now;
};
int BBArrangement(int** B, int n, int m, int* &bestx)
{
	MinHeap<BoardNode> H(1000);
	BoardNode E;
	E.x = new int[m + 1];
	int* total = new int[m + 1];
	for (int i = 1; i <= m; i++)
	{
		E.x[i] = i;
		for (int j = 1; j <= m; j++)
			total[j] += B[i][j];
	}
	int bestd = m + 1;
	bestx = 0;
	do{
		if (E.s == n - 1)
		{
			int ld = 0;
			for (int j = 1; j <= m; j++)
				ld += B[E.x_n]_[j];
			if (ld < bestd)
			{
				delete[] bestx;
				bestx = E.x;
				bestd = max(ld, E.cd);
			}
			else
			{
				delete[] E.x;
				delete[] E.now;
			}
				
		}
		else
		{
			for (int i = E.s + 1; i <= n; i++)
			{
				BoardNode N;
				N.now = new int[m + 1];
				for (int j = 1; j <= m; j++) //newly insert-circuit board
					N.now[j] = E.now[j] + B[E.x[i]][j];
				int ld = 0; //density for the newly insert board
				for (int j = 1; j <= m; j++)
				{
					if (N.now[j] > 0 && total[j] != N.now[j])
						ld++;
				}
				N.cd = max(ld, E.cd);
				if (N.cd < bestd)
				{
					N.x = new int[n + 1];
					N.s = E.s + 1;
					for (int j = 1; j <= n; j++)
						N.x[j] = E.x[j];
					N.x[N.s] = E.x[i];
					N.x[i] = E.x[N.s];
					H.Insert(N);
				}
				else
				{
					delete[] N.now;
				}
				
			}
			delete[] E.x;
		}
		try{
			H.DeleteMin(E);
		}
		catch (OutOfBounds)
		{
			return bestd;
		}

	} while (E.cd < bestd);
	do{
		delete[] E.x;
		delete[] E.now;
		try{
			H.DeleteMin(E);
		}
		catch (...)
		{
			break;
		}
	} while (true);
	return bestd;
}
int main(int argc, char* argv[])
{

}