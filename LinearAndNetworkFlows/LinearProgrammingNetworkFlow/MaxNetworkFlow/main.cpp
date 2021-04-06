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
};//Page 267
template<class Graph,class Edge> 
class LOWER
{// the MINFLOW problem with the lower bound constraint
	const Graph& G;
public:
	LOWER(Graph& G, int s, int t, vector<int> sd) : G(G)
	{
		int maxflow = 0;
		feasible(G, s, t, sd);
		adjIterator<Edge> A(G, s);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			if (e->from(s))
				maxflow += e->flow();
		}
		MAXFLOW<Graph, Edge>(G, s, t, maxflow);
		cout << endl << "Maxflow =" << maxflow << endl << endl;
		G.outflow();
	}
};
//How to define the flow cost
template<class Graph,class Edge>
static int cost(Graph& G)
{
	int x = 0;
	for (int v = 0; v < G.V(); v++)
	{
		adjIterator<Edge> A(G, v);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			if (e->from(v) && e->costRto(e->w()) < INT_MAX)
				x += e->flow()*e->costRto(e - w());
		}
	}
	return x;
}
//Circle Elimination Algorithm  //neglect cycle
int costRto(int v)
{
	return from(v) ? -pcost : pcost;
}
template<classs Graph,class Edge> 
class MINCOST
{
	Graph& G;
	int s, t;
	vector<int> wt;
	vector<Edge*> st;
public:
	MINCOST(Graph& G, int s, int t) :
		G(G), s(s), t(t), st(G.V()), wt(G.V())
	{
		int flow = 0;
		MAXFLOW<Graph, Edge>(G, s, t, flow);
		for (int x = negcyc(); x != -1; x = negcyc())
			augment(x, x);
	}
	int negcyc()
	{
		for (int i = 0; i < G.V(); i++)
		{
			int neg = negcyc(i);
			if (neg >= 0)
				return neg;
		}
		return -1;
	}
	int negcyc(int ss)
	{
		st.assign(G.V(),0);
		wt.assign(G.V(), INT_MAX);
		QUEUE<int> Q(2 * G.V());
		int N = 0;
		wt[ss] = 0.0 ;
		Q.put(ss);
		Q.put(G.V());
		while (!Q.empty())
		{
			int v;
			while ((v = Q.get()) == G.V())
			{
				if (N++ > G.V())
					return -1;
				Q.put(G.V());
			}
			adjIterator<Edge> A(G.v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				int w = e->other(v);
				if (e->capRto(w) == 0)
					continue;
				double P = wt[v] + e->wt(w);
				if (P < wt[w])
				{
					wt[w] = P;
					//begin to search for the negative cycle
					for (int node_test = v; (st[node_test] != 0 && node_test != ss); node_test = ST(node_test))
					{
						if (ST(node_test) == w)
						{
							st[w] = e; return w;
						}
					}
					st[w] = e; Q.put(w);
				}
			}
		}
		return -1;
	}
	int ST(int v) const{
		if (st[v] == 0)
		{
			cout << "error!" << endl; return 0;
		}
		else{
			return st[v]->other(v);
		}
	}
	void augment(int s, int t)
	{
		int d = st[t]->capRto(t);
		for (int v = ST(t); v != s; v = ST(v))
		{
			if (st[v]->capRto(v) < d)
				d = st[v]->capRto(v);
			st[t]->addflowRto(t, d);
			for (v = ST(t); v != s; v = ST(v))
				st[v]->addflowRto(v, d);
		}
	}
};
//MINIMAL COST PATH Algorithm
template<class Graph,class Edge>
class MINCOST{
	Graph& G;
	int s, t, flow;
	vector<int> wt;
	vector<Edge*> st;
public:
	MINCOST(Graph& G, int s, int t, int se) :
		G(G), s(s), t(t), flow(se), st(G.V()), wt(G.V())
	{
		while (shortest())
			augment(s, t);
	}
	bool shortest()
	{
		st.assign(G.V(), 0);
		wt.assign(G.V(), INT_MAX);
		QUEUE<int>Q(2 * G.V());
		int N = 0;
		if (flow <= 0)
			return false;
		wt[s] = 0.0;
		Q.put(s); Q.put(G.V());
		while (!Q.empty())
		{
			int v;
			while ((v = Q.get()) == G.V())
			{
				if (N++ > G.V())
					return (wt[t] < INT_MAX);
				Q.put(G.V());
			}
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				int w = e->other(v);
				if (e->capRto(w) == 0)
					continute;
				int P = wt[v] + e->wt(w);
				if (P < wt[w])
				{
					wt[w] = P;
					st[w] = e;
					Q.put(w);
				}
			}
		}
		return (wt[t] < INT_MAX);
	}
	int ST(int v) const
	{
		if (st[v] == 0)
		{
			cout << "error!" << endl;
			return 0;
		}
		else
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
		if (d>flow)
			d = flow;
		st[t]->addflowRto(t, d);
		for (v = ST(t); v != s; v = ST(v))
			st[v]->addflowRto(v, d);
		flow -= d;
	}
};
//networkSimplex algorithm
template<class Graph,class Edge>
class MINCOST{
	const Graph& G;
	int s, t, valid;
	vector<Edge*> st;
	vector<int> mark, phi;
public:
	MINCOST(Graph& G, int s, int t, int se) :
		G(G), s(s), t(t), st(G.V()), mark(G.V(), -1), phi(G.V())
	{
		int m, c;
		upbound(m, c);
		m = m*G.V();
		c = c*G.V();
		Edge* z = new EDGE(s, t, se, c);
		G.insert(z);
		z->addflowRto(t, se);
		dfsR(z, t);
		for (valid = 1;; valid++)
		{
			phi[t] = z->costRto(s);
			mark[t] = valid;
			for (int v = 0; v < G.V(); v++)
			{
				if (v != t)
					phi[v] = phiR(v);
			}
			Edge* x = besteligible();
			int rcost = costR(x, x->v());
			if (full(x) && rcost <= 0 || empty(x) && rcost >= 0)
				break;
			update(augment(x), x);
		}
		G.remove(z);
		delete z;
	}
	void upbound(int& cap, int& cost)
	{
		cap = 0; cost = 0;
		for (int i = 0; i < G.V(); i++)
		{
			for (int j = 0; j < G.V(); j++)
			{
				if (G.edge(v, w) && cap < G.edge(v, w)->cap())
					cap = G.edge(v, w)->cap();
				if (G.edge(v, w) && cost < G.edge(v, w)->cost())
					cost = G.edge(v, w)->cost();
			}
		}
	}
	void dfsR(Edge* e, int w)
	{
		int v = e->other(w);
		st[v] = e;
		mark[v] = 1;
		mark[w] = 1;
		dfs(v);
		dfs(w);
		mark.assign(G.V(), -1;
	}
	void dfs(int v)
	{
		adjIterator<Edge> A(G, v);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			int w = e->other(v);
			if (mark[w] == -1)
			{
				st[w] = e;
				mark[w] = 1;
				dfs(w);
			}
		}
	}
	int ST(int v) const
	{
		if (st[v] == 0) return 0;
		else
			return st[v]->other(v);
	}
	int phiR(int v)
	{
		if (mark[v] == valid)
			return phi[v];
		phi[v] = phiR(ST(v)) - st[v]->costRto(v);
		mark[v] = valid;
		return phi[v];
	}
	int costR(Edge* e, int v)
	{
		int R = e->cost() + phi[e->w()] - phi[e->v()];
		return e->from(v) ? R : -R;
	}
	Edge* besteligible()
	{
		Edge* x = 0;
		for (int v = 0, min = INT_MAX; v < G.V(); v++)
		{
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				if (e->capRto(e->other(v))>0)
				{
					if (e->capRto(v) == 0)
					{
						if (costR(e, v) < min)
						{
							x = e;
							min = costR(e, v);
						}
					}
				}
			}
		}
		return x;
	}
	Edge* augment(Edge* x)
	{
		int v = full(x) ? x->w():x->v();
		int w = x->other(v);
		int r = lca(v, w);
		int d = x->capRto(w);
		for (int u = w; u != r; u = ST(u))
		{
			if (st[u]->capRto(ST(u)) < d)
				d = st[u]->capRto(ST(u));
		}
		for (u = v; u != r; u = ST(u))
		{
			if (st[u]->capRto(u) < d)
				d = st[u]->capRto(u);
		}
		x->addflowRto(w, d);
		Edge* e = x;
		for (u = w; u != r; u = ST(u))
		{
			st[u]->addflowRto(ST(u), d);
			if (st[u]->capRto(ST(u)) == 0)
				e = st[u];
		}
		for (u = v; u != r; u = ST(u))
		{
			st[u]->addflowRto(u, d);
			if (st[u]->capRto(u) == 0)
				e = st[u];
	}
		return e;
	}
	bool full(Edge* x)
	{
		return (x - .capRto(x->w()) == 0);
	}
	bool empty(Edge* x)
	{
		return (x->capRto(x->v()) == 0);
	}
	int lca(int v, int w)
	{
		mark[v] = ++valid;
		mark[w] = valid;
		while (v != w)
		{
			if (v != t)
				v = ST(v);
			if (v != t&&mark[v] == valid)
				return v;
			makr[v] = valid;
			if (w != t)
				w = ST(w);
			if (w != t&&mark[w] = -valid)
				return w;
			mark[w] = valid;
		}
		return v;
	}
	bool onpath(int a, int b, int c)
	{
		for (int i = a; i != c; i = ST(i))
		{
			if (i == b)
				return true;
		}
		return false;
	}
	void reverse(int u, int x)
	{
		Edge* e = st[u];
		for (int i = ST(u); e->other(i) != x; i = e->other(i))
		{
			Edge* y = st[i];
			st[i] = e;
			e = y;
		}
	}
	void update(Edge* w, Edge* y)
	{
		if (w == y)
			return;
		int u = y->w(), v = y->v(), x = w->w();
		if (x == t || st[x] != w)
			x = w->v();
		int r = lca(u, v);
		if (onpath(u, x, r))
		{
			reverse(u, x);
			st[u] = y;
			return;
		}
		if (onpath(v, x, r))
		{
			reverse(v, x);
			st[v] = y;
			return;
		}
	}
};
//Minimal cost flow's transformation and application
//Minimal cost flow with the lower bound constraint
template<class Graph,class Edge> 
class LOWER
{
	const Graph& G;
public:
	LOWER(Graph& G, int s, int t, int se, int te, vector<int> sd) : G(G)
	{
		int maxflow = 0;
		feasible(G, s, t, sd);
		adjIterator<Edge> A(G, s);
		for (Edge* e = A.beg(); !A.end(); e = A.nxt())
		{
			if (e->from(s))
				maxflow += e->flow();
		}
		MINCOST<GRAPH<EDGE>, EDGE>(G, s, t, se);
		G.outflow();
	}
};
//Minimal cost and minimal flow with the lower bound constraint
template<class Graph,class Edge> 
class LOWER
{
	const Graph& G;
public:
	LOWER(Graph& G, int s, int t, int se, int te, vector<int> sd) :G(G)
	{
		int maxflow = 0;
		feasible(G, s, t, sd);
		adjIterator<Edge> A(G, s);
		for (Edge* e = A.beg; !A.end(); e = A.nxt())
		{
			if (e->from(s))
				maxflow -= e->flow();
		}
		MINCOST<GRAPH<EDGE>, EDGE>(G, t, s, se);
		G.outflow();
	}
};
//Minimal weight binary match(Assignment) problem
template<class Graph,class Edge>
class ASSIGNEMNT
{
	const Graph& G;
public:
	ASSIGNMENT(const Graph& G, int N1) :G(G)
	{
		int s, t, sum = 0;
		Graph G(G.V() + 2, 1);
		for (int v = 0; v < G.V(); v++)
		{
			adjIterator<Edge> A(G, v);
			for (Edge* e = A.beg(); !A.end(); e = A.nxt())
			{
				F.insert(e);
			}
		}
	}
	s = G.v();
	t = G.V() + 1;
	for (int i = 0; i < N1; i++)
		F.insert(new EDGE(s, i, 1, 0));
	for (i = N1; i < s; i++)
		F.insert(new EDGE(i, t, 1, 0));
	MINCOST<Graph, Edge>(F, s, t, N1);
	for (i = 0; i < N1; i++)
	{
		adjIterator<Edge> A(F, i);
		for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
		{
			if (e->flow() == 1 && e->from(i))
			{
				cout << e->v() << "->" << e->w() << endl;
			}
		}
	}
};
class ConsecLP
{//special linear programming problem
	int ncon; //constraint number
	int nvar;
	int** a, s, t, supply;
public:
	ConsecLP(char* filename)
	{
		read(filename);
		GRAPH<EDGE> G(ncon + 3, 1);
		constructG(G);
		MINCOST<GRAPH<EDGE>, EDGE>(G, s, t, supply);
		cout << "Mincost=" << cost << GRAPH<EDGE>, EDGE > (G) << endl;
		G.outx();
	}
	void constructG(GRAPH<EDGE>& G)
	{
		int i, j, p, q, maxc = 0;
		a[ncon + 1][0] = 0;
		for (i = ncon + 1; i > 1; i--)
			a[i][0] -= a[i - 1][0];
		for (i = 1; i < ncon; i++)
		{
			if (a[i][0]>maxc)
				maxc += a[i][0];
		}
		for (j = 1; j <= nvar; j++)
		{
			p = 0; q = 0;
			for (i = 1; i < ncon; i++)
			{
				if ((p == 0) && (a[i][j] == 1))
					p = i;
				if ((p>0) && (q == 0) && (a[i][j] == 0))
					q = i;
			}
			if (q == 0)
				q = ncon + 1;
			EDGE* e = G.edge(p - 1, q - 1);
			if (e == 0 || e != 0 && e->cost() > a[0][j])
				G.insert(new EDGE(p - 1, q - 1, maxc, a[0][j], j));
		}
		for (i = 1; i <= ncon;i++)
			G.insert(new EDGE(i, i - 1, maxc, 0, 0));
		s = ncon + 1; t = ncon + 2; supply = 0;
		for (i = 1; i <= ncon; i++)
		{
			if (a[i][0] >= 0)
			{
				supply += a[i][0];
				G.insert(new EDGE(s, i - 1, a[i][0], 0, 0));
			}
			else
			{
				G.insert(new EDGE(i - 1, t, -a[i][0], 0, 0));
			}
		}
	}
};
//Minimum Escape Problem
class ESCAPE
{
	int n, mm, nn, f, s, t, *st;
	int btype(int i, int j)
	{
		int b = 0; //indicator
		if ((i == 1) || (i == mm || (j == 1) || j == nn))
			b++;
		if (start(v, w))
			b += 2;
		return b;
	}
	int num(int i, int j)
	{
		if ((i >= 1) && (i <= mm) && (j >= 1) && (j <= nn))
			return ((i - 1)*nn + j) * 2;
		else
			return -1;
	}
	int start(int i, int j)
	{
		return st[(i - 1)*nn + j];
	}
	void constructG(GRAPH<EDGE>& G)
	{
		int u[5], v[5];
		for (int i = 1; i <= mm; i++)
		{
			for (int j = 1; j <= nn; j++)
			{
				int k = num(v, w);
				int b = btype(v, w);
				u[1] = num(i - 1, j); u[2] = num(i, j - 1);
				u[3] = num(i + 1, j); u[4] = num(i, j + 1);
				v[1] = btype(i - 1, j); v[2] = btype(i, j - 1);
				v[3] = btype(i + 1, j); v[4] = btype(i, j + 1);
				G.insert(new EDGE(k, k + 1, 1, 0));
				if (b > 1)
					G.insert(new EDGE(s, k, 1, 0));
				else
				{
					for (int x = 1; x < 5; x++)
					{
						if ((u[x]>0) && ((v[x] == 0) || (v[x] == 2)))
							G.insert(new EDGE(u[x] + 1, k, 1, 1));
					}
				}
				if ((b == 1) || (b == 3))
					G.insert(new EDGE(k + 1, t, 1, 0));
			}
		}
	}
	void read(char* filename)
	{
		int i, j;
		ifstream inFile;
		inFile.open(filename);
		inFile >> mm >> nn >> f;
		n = mm*nn * 2 + 2;
		st = new int[mm*nn + 1];
		for (i = 0; i <= mm*nn; i++)
			st[i] = 0;
		s = 0;
		t = 1;
		for (int k = 0; k < f; k++)
		{
			inFile >> i >> j;
			st[(i - 1)*nn + j] = 1;
		}
		inFile.close();
	}
	void trans(int i, int& u, int& v)
	{
		int k = i / 2;
		u = k / nn;
		v = k%nn;
		if (v == 0)
			v = nn;
		else
			u++;
	}
	void output(GRAPH<EDGE>& G)
	{
		int u1, v1, u2, v2, sum = 0;
		adjIterator<EDGE> A(G, s);
		for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
		{
			if (e->from(s) && e->flow() > 0)
				sum++;
		}
		if (sum < f)
		{
			cout << "No solution" << endl;
			return;
		}
		cout << "successful!" << endl;
		sum = 0;
		for (int i = 2; i < n; i++)
		{
			adjIterator<EDGE> A(G, i);
			for (EDGE* e = A.beg(); !A.end(); e = A.nxt())
			{
				if (e->from(i) && e->flow()>0 && e->cost() > 0)
				{
					trans(i, u1, v1);
					trans(e->w(), u2, v2);
					cout << "(" << u1 << "," << v1 << ")-->(" << u2 << "," << v2 << ")" << endl;
					sum++;
				}
			}
		}
		cout << "Mincost=" << sum << endl;
	}
	public:
		ESCAPE(char* filename)
		{
			read(filename);
			GRAPH<EDGE> G(n, 1);
			constructG(G);
			MINCOST<GRAPH<EDGE>, EDGE>(G, s, t, f);
			output(G);
		}

};
int main(int argc, char* argv[])
{

}