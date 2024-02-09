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
    paths.resize(n, 0);
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
    paths[source] = 1;
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
            paths[edge.first] = paths[current];
          } else if (dist[edge.first] == dist[current] + edge.second){
            paths[edge.first] += paths[current];
          }
        }
      }
    }

    return paths;
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
  vector<int> paths;
  vector<vector<pair<int, T> > > edges;
};

int main(){
    int n, m;
    cin >> n;
    
    int a, b, c;
    vector<int> u, v, w;
    while(cin >> a >> b >> c){
        u.push_back(a);
        v.push_back(b);
        w.push_back(c);
    }
    m = (int)u.size();

    Dijkstra<int> graph(n);
    for(int i = 0; i < m; ++i){
        graph.addEdge(u[i], v[i], w[i]);
        graph.addEdge(v[i], u[i], w[i]);
    }

    graph.setInfinite(INT_MAX / 2);
    graph.setZero(0);
    
    cout << graph.distance(0)[n - 1] << endl;
}