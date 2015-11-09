/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MachinesScheduling
*/
#include <iostream>
using namespace std;
class JobNode{
	friend void Greedy(JobNode*, int, int);
	friend void main(void);
public:
	operator int() const
	{
		return time;
 	}
private:
	int ID;
	int time;
};
class MachineNode{
	friend void Greedy(JobNode*, int, int);
public:
	operator int() const
	{
		return avail;
	}
private:
	int ID;
	int avail;
};
template<class Type>
void Greedy(Type a[], int n, int m)
{
	if (n <= m)
	{
		cout << "assign one machine one task." << endl;
		return;
	}
	Sort(a, n);
	MinHeap<MachineNode> H(m);
	MachineNode x;
	for (int i = 1; i <= m; i++)
	{
		x.avail = 0;
		x.ID = i;
		H.Insert(x);
	}
	for (int i = n; i >= 1; i--)
	{
		H.DeleteMin(x);
		cout << "let the Machine" << x.ID << "from" << x.avail << "to" << (x.avail + a[i].time)
			<< "'s time slice for the task" << a[i].ID << endl;
		x.avail += a[i].time;
		H.Insert(x);
	}
}
int main(int argc, char* argv[])
{

}