/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
WiringProblem
*/
#include <iostream>
using namespace std;
bool FindPath(Position start, Position finish, int& PathLen, Position* & path)
{
	if ((start.row == finish.row) && (start.col == finish.col))
	{
		PathLen = 0;
		return true;
	}
	for (int i = 0; i <= m + 1; i++)
	{
		grid[0][i] = grid[n + 1][i] = 1;
	}
	for (int i = 0; i <= n + 1; i++)
	{
		grid[i][0] = grid[i][m + 1] = 1;
	}
	Position offset[4];
	offset[0].row = 0; offset[0].col = 1;
	offset[1].row = 1; offset[1].col = 0;
	offset[2].row = 0; offset[2].col = -1;
	offset[3].row = -1; offset[3].col = 0;
	int NumOfNbrs = 4;
	Position here, nbr;
	here.row = start.row;
	here.col = start.col;
	grid[start.row][start.col] = 2;

	LinkedQueue<Positon> Q;
	do{
		for (int i = 0; i < NumOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == 0)
			{
				grid[nbr.row][nbr.col] = grid[here.row][here.col] + 1;
				if ((nbr.row == finish.row) && (nbr.col == finish.col))
					break;
				Q.add(nbr);
			}
		}
		//Has it arrived at the position finish?
		if ((nbr.row == finish.row) && (nbr.col == finish.col))
			break;
		if (Q.IsEmpth())
			return false;
		Q.Delete(here);
	} while (true);
	//construct the shortest path
	PathLen = grid[finish.row][finish.col] - 2;
	path = new Position[PathLen];
	here = finish;
	for (int j = PathLen - 1; j >= 0; j--)
	{
		path[j] = here;
		for (int i = 0; i < NumOfNbrs; i++)
		{
			nbr.row = here.row + offset[i].row;
			nbr.col = here.col + offset[i].col;
			if (grid[nbr.row][nbr.col] == j + 2)
				break;
		}
		here = nbr;
	}
	return true;
}
int main(int argc, char* argv[])
{

}