/*
    Author: Yohandi - 120040025
*/

// Dijkstra Template: https://github.com/bukanyohandi/Algorithm-Class-Header

#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <bits/stdc++.h>
using namespace std;

template <class T>
class Dijkstra {
 public:
  Dijkstra() {
    __n = 0;
    infIsSet = false;
    zeroIsSet = false;
  }
  Dijkstra(int n) {
    assert(n >= 0);

    __n = n;
    infIsSet = false;
    zeroIsSet = false;
    edges.resize(n);
  }

  void addEdge(int u, int v, T w) {
    assert(0 <= u && u < __n);
    assert(0 <= v && v < __n);

    edges[u].push_back({v, w});

    return;
  }

  vector<T> distance(int source) {
    assert(infIsSet == true);
    assert(zeroIsSet == true);
    assert(0 <= source && source < __n);

    int current;
    T cost;
    vector<T> dist(__n, inf);
    priority_queue<pair<T, int>, vector<pair<T, int> >, greater<pair<T, int> > > costs;

    dist[source] = zero;
    costs.push({zero, source});
    while (!costs.empty()) {
      cost = costs.top().first;
      current = costs.top().second;
      costs.pop();

      if (cost <= dist[current]) {
        for (pair<T, int> edge : edges[current]) {
          if (dist[edge.first] > dist[current] + edge.second) {
            dist[edge.first] = dist[current] + edge.second;
            costs.push({dist[edge.first], edge.first});
          }
        }
      }
    }

    return dist;
  }

  T getInfinite() {
    return inf;
  }

  T getZero() {
    return zero;
  }

  void resize(int n) {
    assert(n >= 0);

    __n = n;
    edges.resize(n);

    return;
  }

  void setInfinite(T val) {
    inf = val;
    infIsSet = true;

    return;
  }

  void setZero(T val) {
    zero = val;
    zeroIsSet = true;

    return;
  }

  int size() {
    return __n;
  }

 private:
  bool infIsSet, zeroIsSet;
  int __n;
  T zero, inf;
  vector<vector<pair<int, T> > > edges;
};

#endif  // DIJKSTRA_HPP

int P[200000];
int find(int node){
  if(P[node] == node) return node;
  return P[node] = find(P[node]);
}

int u[200000], v[200000], w[200000];
vector<pair<int, int>> edges[100000];
map<pair<int, int>, int> path;

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n, m, K;
  cin >> n >> m >> K;

  Dijkstra<int> graph(2 * n);

  for(int i = 0; i < m; ++i){
    cin >> u[i] >> v[i] >> w[i];
    u[i] -= 1;
    v[i] -= 1;
    if(K != 0 && w[i] % K == 0){
      edges[u[i]].push_back({v[i], w[i]});
      edges[v[i]].push_back({u[i], w[i]});
    }

    graph.addEdge(u[i], v[i], w[i]);
    graph.addEdge(v[i], u[i], w[i]);

    path[{u[i], v[i]}] = w[i];
    path[{v[i], u[i]}] = w[i];
  }

  queue<pair<pair<int, int>, int>> BFS;
  for(int i = 0; i < m; ++i){
    BFS.push({{u[i], v[i]}, w[i]});
    BFS.push({{v[i], u[i]}, w[i]});
  }
  while(!BFS.empty()){
    int last = BFS.front().first.first;
    int current = BFS.front().first.second;
    int cost = BFS.front().second;
    BFS.pop();

    for(pair<int, int> edge: edges[current]){
      if(edge.second == K * cost && (path[{last, edge.first}] == 0 || path[{last,edge.first}] > edge.second)){
        BFS.push({{last, edge.first}, edge.second});
        graph.addEdge(last, edge.first, edge.second);
        path[{last, edge.first}] = edge.second;
      }
    }
  }
  
  graph.setInfinite(1e9);
  graph.setZero(0);
  vector<int> ans = graph.distance(0);

  for(int i = 0; i < n; ++i){
    if(i != 0) cout << " ";

    if (ans[i] == graph.getInfinite()) {
      cout << -1;
    } else {
      cout << ans[i];
    }
  }
  cout << endl;
}