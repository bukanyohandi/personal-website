#include <bits/stdc++.h>
#define NIL -1
using namespace std;

int N, M;
int Cost[111111];
long long Ans1, Ans2 = 1;

class Graph {
  int V;
  list<int> *adj;
  void SCCUtil(int u, int disc[], int low[], stack<int> *st,
               bool stackMember[]);

public:
  Graph(int V);
  void addEdge(int v, int w);
  void SCC();
};

Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) { adj[v].push_back(w); }

void Graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
                    bool stackMember[]) {
  static int time = 0;
  disc[u] = low[u] = ++time;
  st->push(u);
  stackMember[u] = true;
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;
    if (disc[v] == -1) {
      SCCUtil(v, disc, low, st, stackMember);
      low[u] = min(low[u], low[v]);
    } else if (stackMember[v] == true)
      low[u] = min(low[u], disc[v]);
  }
  int w = 0;
  int Min = 1000000001, Freq = 0;
  if (low[u] == disc[u]) {
    while (st->top() != u) {
      w = (int)st->top();
      if (Cost[w] < Min) {
        Min = Cost[w];
        Freq = 1;
      } else if (Cost[w] == Min)
        Freq++;
      stackMember[w] = false;
      st->pop();
    }
    w = (int)st->top();
    if (Cost[w] < Min) {
      Min = Cost[w];
      Freq = 1;
    } else if (Cost[w] == Min)
      Freq++;
    stackMember[w] = false;
    st->pop();
  }
  if (Min == 1000000001)
    return;
  // cout<<"->"<<Min<<endl;
  Ans1 += Min;
  Ans2 *= Freq;
  Ans2 %= 1000000007;
}

void Graph::SCC() {
  int *disc = new int[V];
  int *low = new int[V];
  bool *stackMember = new bool[V];
  stack<int> *st = new stack<int>();

  for (int i = 0; i < V; i++) {
    disc[i] = NIL;
    low[i] = NIL;
    stackMember[i] = false;
  }
  for (int i = 0; i < V; i++)
    if (disc[i] == NIL)
      SCCUtil(i, disc, low, st, stackMember);
}

int main() {
  int N, M;
  cin >> N;
  for (int i = 1; i <= N; ++i)
    cin >> Cost[i];
  cin >> M;
  Graph g1(N + 1);
  for (int i = 1; i <= M; ++i) {
    int U, V;
    cin >> U >> V;
    g1.addEdge(U, V);
  }
  g1.SCC();
  cout << Ans1 << " " << Ans2 << endl;
  return 0;
}