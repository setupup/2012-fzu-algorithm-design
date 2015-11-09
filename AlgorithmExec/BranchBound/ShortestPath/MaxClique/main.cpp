/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MaxClique
*/
#include <iostream>
using namespace std;
class bbnode{
	friend class Clique; //friend class!
private:
	bbnode* parent;
	bool LChild;
};
class CliqueNode{
	friend class Clique;
public:
	operator int() const
	{
		return un;
	}
private:
	int cn;
	int un;
	int level;
	bbnode* ptr;
};
class Clique{
	friend void main(void);
public:
	int BBMaxClique(int[]);
private:
	void AddLiveNode(MaxHeap<CliqueNode>& H, int cn, int un, int level, bbnode E[], bool ch);
	int** a;
	int n;
};
void Clique::AddLiveNode(MaxHeap<CliqueNode>& H, int cn, int un, int level, bbnode E[], bool ch)
{
	bbnode* b = new bbnode;
	b->parent = E;
	b->LChild = ch;
	CliqueNode N;
	N.cn = cn;
	N.ptr = b;
	N.un = un;
	N.level = level;
	H.Insert(N);
}
int Clique::BBMaxClique(int bestx[])
{
	MaxHeap<CliqueNode> H(1000);
	//Initilization
	bbnode* E = 0;
	int i = 1;
	int cn = 0;
	int bestn = 0;
	while (i != n + 1)
	{
		bool OK = true;
		bbnode* B = E;
		for (int j = i - 1; j > 0; B = B->parent, j--)
		{
			if (B->LChild&&a[i][j] == 0)
			{
				OK = false;
				break;
			}
		}
		if (OK)
		{
			if (cn + 1 > bestn)
				bestn = cn + 1;
			AddLiveNode(H, cn + 1, cn + n - i + 1, i + 1, E, true);
		}
		if (cn + n - i >= bestn)
			AddLiveNode(H, cn, cn + n - i, i + 1, E, false);
		CliqueNode N;
		H.DeleteMax(N);
		E = N.ptr;
		cn = N.cn;
		i = N.level;
	}
	for (int j = n; j > 0; j--)
	{
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return bestn;
}
int main(int argc, char* argv[])
{

}