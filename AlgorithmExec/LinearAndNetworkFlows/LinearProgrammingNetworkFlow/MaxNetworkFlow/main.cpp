/* Some fundamental exercises
$time$
HU Sheng, Essential C++ Chapter 
MaximumNetworkFlowProblem
*/
#include <fstream>
#include <iostream>
using namespace std;
class EDGE
{
	int pv, pw, pcap, pcost, pflow;
public:
	EDGE(int v, int w, int cap, int cost) :
		pv(v), pw(w), pcap(cap), pcost(cost), pflow(0){};
	int v() const
	{
		return pv;
	}
	int w() const { return pw; }
	int cap() const{ return pcap; }
	int cost() const{ return pcost; }
	int wt(int v) const{ return from(v) ? -pcost : pcost; }
	int flow() const { return pflow; }
	bool from(int v) const
	{
		return pv == v;
	}
	bool residual(int v) const
	{
		return (pv == v&&pcap - pflow > 0 || pw == v&&pflow > 0);
	}
	int other(int v) const
	{
		return from(v) ? pw : pv;
	}
	int capRto(int v) const
	{
		return from(v) ? pflow : pcap - pflow;
	}
	int costRto(int v) const
	{
		return from(v) ? -pcost : pcost;
	}
	void addflowRto(int v, int d)
	{
		pflow += from(v) ? -d : d;
	}
};
template<class Edge>
class GRAPH{
	int Vcnt, Ecnt;
	bool digraph;
	vector<vector<Edge*>> adj;
public:
	GRAPH(int V, bool digraph = false) :
		adj(V + 1), Vcnt(V + 1), Ecnt(0), digraph(digraph)
	{
		for (int i = 0; i <= V; i++)
			adj[i].assign(V + 1, 0);
	}
	GRAPH(){}
	int V() const { return Vcnt; }
	int E() const { return Ecnt; }
	bool directed() const { return digraph; }
	void insert(Edge* e)
	{
		int v = e->v();
		int w = e->w();
		if (adj[v][w] == 0)
			Ecnt++;
		adj[v][w] = e;
		if (!digraph)
			adj[w][v] = e;
	}
	void remove(Edge* e)
	{
		int v = e->v();
		int w = e->w();
		if (adf[v][w] != 0)
			Ecnt--;
		adj[v][w] = 0;
		if (!digraph)
			adj[w][v] = 0;
	}
	Edge* edge(int v, int w) const
	{
		return adj[v][w];
	}
	void read(char* filename, int& a, int& t, int& se, int& te)
	{
		int i, j, n, m, nmax, cap, cost;
		ifstream inFile;
		inFile.open(filename);
		inFile >> n >> m >> s >> se >> t >> te >> nmax;
		for (int k = 0; k < m; k++)
		{
			inFile >> i >> j >> cap >> cap >> cost;
			if (cap>0)
				insert(new EDGE(i, j, cap, cost));
		}
		insert(new EDGE(nmax + 1, 0, se, 0));
		s = nmax + 1;
		inFile.close();
	}
	void checksd(int s, int t, int& ss, int& dd)
	{
		ss = 0;
		dd = 0;
		for (int i = 0; i < Vcnt; i++)
		{
			if (adj[s][i] && adj[s][i]->from(s) && adj[s][i]->flow()>0)
				ss += adj[s][i]->flow();
			if (adj[i][t] && adj[i][t]->from(i) && adj[i][t]->flow() > 0)
				dd += adj[i][t]->flow();
		}
	}
};
template<class Edge>
class adjIterator
{
	const GRAPH<Edge>& G;
	int i, j, v;
public:
	adjIterator(const GRAPH<Edge>& G, int v) :
		G(G), v(v), i(0), j(0){}
	Edge* beg(){
		i = -1;
		j = -1;
		return nxt();
	}
	Edge* nxt(){
		for (i++; i < G.V(); i++)
		{
			if (G.edge(v, i))
				return G.edge(v, i);
		}
		for (j++; j < G.V(); j++)
		{
			if (G.edge(j, v))
				return G.edge(j, v);
		}
		return 0;
	}
	bool end() const
	{
		return (i >= G.V() && j >= G.V());
	}
};
//Augumented path algorithm
template<class Graph, class Edge> 
class MAXFLOW
{
	const Graph& G;
	int s, t, maxf;
	vector<int> wt;
	vector<Edge*> st;
	int ST(int v) const{
		return st[v]->other(v);
	}
	void augment(int s, int t)
	{
		int d = st[t]->capRto(t);
		for (int v = ST(t); v != s; v = ST(v))
		{
			if (st[v]->capRto(v) < d)
				d = st[v]->capRto(v);
		}
		st[t]->addflowRto(t, d);
		maxf += d;
		for (v = ST(t); v != s; v = ST(v))
			st[v]->addflowRto(v, d);
	}
	bool pfs(); //Priority First Search
public:
	MAXFLOW(const Graph& G, int s, int t, int& maxflow) :
		G(G), s(s), t(t), st(G.V()), wt(G.V()), maxf(0){
		while (pfs())
			augment(s, t);
		maxflow += maxf;
	}

};
template<class Graph,class Edge>
bool MAXFLOW<Graph, Edge>::pfs()
{
	PQ<int> pQ(G.V(), wt);
	for (int v = 0; v < G.V(); v++)
	{
		wt[v] = 0;
		st[v] = 0;
		pQ.insert(v);
	}
	wt[s] = M;
	pQ.change(s);
	while (!pQ.empty())
	{
		int v = pQ.deletemax();
		wt[v] = M;
		if (v == t || (v != s&&st[v] == 0))
			break;
		adjIterator<Edge> A(G, v);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			int w = e->other(v);
			int cap = e->capRto(w);
			int P = cap < wt[v] ? cap : wt[v];
			if (cap>0 && P > wt[w])
			{
				wt[w] = P;
				pQ.change(w);
				st[w]=e;
			}
		}
	}
	return st[t] != 0;
}
template<class keyType>
class PQ
{
	int d, N;
	vector<int> pq, qp;
	const vector<keyType>& a;
	void exch(int i, int j)
	{
		int t = pq[i];
		pq[i] = pq[j];
		pq[j] = t;
		qp[pq[i]] = i;
		qp[pq[j]] = j;
	}
	void fixUp(int k)
	{
		while (k > 1 && a[pq[(k + d - 2) / d]] < a[pq[k]])
		{
			exch(k, (k + d - 2) / d);
			k = (k + d - 2) / d;
		}
	}
	void fixDown(int k, int N)
	{
		int j;
		while ((j = d*(k - 1) + 2) <= N)
		{
			for (int i = j + 1; i < j + d&&i <= N; i++)
			{
				if (a[pq[j]] < a[pq[i]])
					j = i;
			}
			if (!(a[pq[k]] < a[pq[j]]))
				break;
			exch(k, j);
			k = j;
		}
	}
public:
	PQ(int N, const vector<keyType>& a, int d = 3) :
		a(a), pq(N + 1, 0), qp(N + 1, 0), N(0), d(d){}
	int empty() const { return N == 0; }
	void insert(int v) {
		pq[++N] = v;
		qp[v] = N;
		fixUp(N);
	}
	int deletemax()
	{
		exch(1, N);
		fixDown(1, N - 2);
		return pq[N--];
	}
	void change(int k)
	{
		fixUp(qp[k]);
	}
};
//---Preflow push algorithm
template<class Graph,class Edge>
void MAXFLOW<Graph,Edge>::heights()
{
	QUEUE<int> queue(G.V());
	for (int i = 0; i < G.V(); i++)
		h[i] = 0;
	queue.put(t);
	while (!queue.empty())
	{
		int v = queue.get();
		adjIterator<Edge> A(G, v);
		for (Edge* c = A.beg(); !A.end(); e = A.nxt())
		{
			int w = e->other(v);
			if (h[w] == 0 && e->residual(w))
			{
				h[w] = h[v] + 1;
				queue.put(w);
			}
		}
	}
	h[s] = G.V();
}
template<class Graph,class Edge>
class MAXFLOW{
	const Graph& G;
	int s, t;
	vector<int> h, wt, st;
	PQ<int> gQ;
public:
	MAXFLOW(Graph& G, int s, int t, int& maxflow) :
		G(G), s(s), t(t), h(G.V(), 0), wt(G.V(), 0), st(G.V(), 0), gQ(G.V(), h){
		heights();
		wtmax();
		gQ.put(s);
		st[s] = 1;
		while (!gQ.empty())
		{
			int v = gQ.get();
			st[v] = 0;
			discharge(v);
			relabel(v);
		}
		maxflow += wt[t];
	}
};
template<class Graph,class Edge>
void MAXFLOW<Graph, Edge>::wtmax()
{
	adjIterator<Edge> A(G, s);
	for (Edge* e = A.beg(); !A.end(); e = A.nxt())
	{
		if (e->from(s))
			wt[s] += e->cap();
	}
}
template<class Graph,class Edge>
void MAXFLOW<Graph,Edge>::push(Edge* e, int v, int w, int f)
{
	e->addflowRto(w, f);
	wt[v] -= f;
	wt[w] += f;
}
template<class Graph,class Edge>
void MAXFLOW<Graph, Edge>::discharge(int v)
{
	adjIterator<Edge> A(G, v);
	for (Edge* e = A.beg(); !A.end(); e = A.nxt())
	{
		int w = e->other(v);
		int cap = e->capRto(w);
		int P = cap < wt[v] ? cap : wt[v];
		if (P> && (v == s || h[v] == h[w] + 1)){
			push(e, v, w, P);
			if ((w != s) && (w != t) && (!st[w])){
				gQ.put(w);
				st[w] = 1;
			}
		}
	}
}
template<class Graph,class Edge>
void MAXFLOW<Graph, Edge>::relabel(int v)
{
	if (v != s&&v != t&&wt[v] > 0)
	{
		int hv = INT_MAX;
		adjIterator<Edge> A(G, v);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			int w = e->other(v);
			if (e->residual(v) && h[w] < hv)
				hv = h[w];
		}
		if (hv < INT_MAX)
			h[v] = hv + 1;
		gQ.put(v);
		st[v] = 1;
	}
}
// the transformation and application of MaxFlowProblem
//FEASIBLE flow problem
template<class Graph,class Edge>
class FEASIBLE
{
	const Graph& G;
public:
	FEASIBLE(const Graph& G, vector<int> sd) : G(G)
	{
		int maxflow, ss, dd, supply, demand;
		Graph G(G.V() + 2, 1);
		for (int v = 0; v < G.V(); v++)
		{
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
				F.insert(e);
		}
		int s = G.V();
		int t = G.V() + 1;
		supply = 0;
		demand = 0;
		for (int i = 0; i < G.V(); i++)
		{
			if (sd[i] >= 0)
			{
				supply += sd[i];
				F.insert(new EDGE(s, i, sd[i]));
			}
			else
			{
				demand -= sd[i];
				F.insert(new EDGE(i, t, -sd[i]));
			}
		}
		MAXFLOW<Graph, Edge>(F, s, t, maxflow);
		F.checksd(s, t, ss, dd);
		if (supply == ss)
			cout << "supply ok" << endl;
		else
			cout << "supply not enough" << endl;
		if (demand == dd)
			cout << "demand met" << endl;
		else
			cout << "demand not met" << endl;
		F.outflow();
	}
	void checksd(int s, int t, int& ss, int& dd)
	{
		ss = 0;
		dd = 0;
		for (int i = 0; i < Vcnt; i++)
		{
			if (adj[s][i] && adj[s][i]->from(s) && adj[s][i]->flow()>0)
				ss += adj[s][j]->flow();
			if (adj[i][t] && adj[i][t]->from(s) && adj[i][t]->flow() > 0)
				dd += adj[i][t]->flow();
		}
	}
};
//Binary char of the biggest matches
template<class Graph, class Edge> 
class BMATCHING
{
	const Graph& G;
public:
	BMATCHING(const Graph& G, int N1) :G(G)
	{
		int s, t, maxflow;
		Graph F(G.V() + 2, 1);
		for (int v = 0; v < G.V(); v++)
		{
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				F.insert(e);
			}
		}
		s = G.V();
		t = G.V() + 1;
		for (int i = 0; i < N1; i++)
		{
			F.insert(new EDGE(s, i, 1));
		}
		for (i = N1; i < s; i++)
		{
			F.insert(new EDGE(i, t, 1));
		}
		MAXFLOW<Graph, Edge>(F, s, t, maxflow);
		for (i = 0; i < N1; i++)
		{
			adjIterator<Edge> A(F, i);
			for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
			{
				if (e->flow() == 1 && e->from(i) && e->capRto(i) == 1)
					cout << e->v() << "->" << e->w() << endl;
			}
		}
	}
};
//----Maxflow with the lower bound constraints
class EDGE
{
	int pv, pw, pcap, pcaplow, pflow, pflag;
public:
	EDGE(int v, int w, int caplow, int cap)
		:pv(v), pw(w), pcaplow(caplow), pcap(cap), pflow(0), pflag(0){}
	int v() const { return pv; }
	int w() const { return pw; }
	int cap() const { return pcap; }
	int caplow() const { return pcaplow; }
	int flow() const { return pflow; }
	bool from(int v) const { return pv == v; }
	void sublow() { pcap -= pcaplow; }
	void addlow() { pcap += pcaplow; pflow += pcaplow; pflag = 1; }
	bool residual(int v) const{
		return (pv == v&&pcap - pflow > 0 || pw == v&&pflow > 0);
	}
	int other(int v) const
	{
		return from(v) ? pw : pv;
	}
	int capRto(int v) const
	{
		return from(v) ? pflow - pcaplow*pflag : pcap - pflow;
	}
	void addflowRto(int v, int d)
	{
		pflow += from(v) ? -d : d;
	}
	//feasible(G,s,t,sd)
	void read(char* filename, int& s, int& t, vector<int>& sd)
	{
		int i, j, n, m, caplow, cap;
		ifstream inFile;
		inFile.open(filename);
		inFile >> n >> m >> s >> t;
		for (int k = 0; k < m; k++)
		{
			inFile >> i >> j >> caplow >> cap;
			sd[j] += caplow;
			sd[i] -= caplow;
			insert(new EDGE(i, j, caplow, cap));
		}
		inFile.close();
	}
	void feasible(Graph& G, int s, int t, vector<int> sd)
	{
		int ss, dd, supply, demand, maxflow = 0;
		Graph F(G.V() + 2, 1);
		for (int v = 0; v < G.V(); v++)
		{
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				if (e->from(v))
				{
					e->sublow();
					F.insert(e);
				}
			}
		}
		F.insert(new EDGE(t, s, 0, INT_MAX));
		s = G.V();
		t = G.V() + 1;
		supply = 0;
		demand = 0;
		for (int i = 0; i < G.V(); i++)
		{
			if (sd[i] >= 0)
			{
				supply += sd[i];
				F.insert(new EDGE(s, i, 0, sd[i]));

			}
			else
			{
				deman -= sd[i];
				F.insert(new EDGE(i, t, 0, -sd[i]));
			}
			MAXFLOW<Graph, Edge>(F, s, t, maxflow);
			F.checksd(s, t, ss, dd);
			if (supply == ss)
				cout << "supply ok" << endl;
			else
				cout << "supply not enough" << endl;
			if (demand == dd)
				cout << "demand met" << endl;
			else
				cout << "demand not met" << endl;
			for (v = 0; v < G.V(); v++)
			{
				adjIterator<Edge> A(G, v);
				for (Edge* e = A.beg(); !A.end(); e = A.nxt())
				{
					if (e->from(v))
						e->addflow();
				}
			}
		}
	}
};
int main(int argc, char* argv[])
{

}