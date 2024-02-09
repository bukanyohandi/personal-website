#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define ll long long
#define pii pair<int, int>
#define pid pair<int, double>
#define pll pair<ll, ll>
#define pdd pair<double, double>
#define uint unsigned int
#define rep(i, x, n) for (ll i = x; i <= n; ++i)
#define pqd priority_queue<int>
#define pqi priority_queue<int, vector<int>, greater<int>>

const ll INF = 2e9 + 5;
const int RINF = -1e9 - 9;
const int MX = 1e4 + 9;
const int mod = 1e9 + 7;
const double EPS = 1e-9;
int n, m, q, s, u, v, c, node, cost[MX];
vector<pii> edges[MX];
priority_queue<pii> pq;
bool dn = 1;
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  while (1) {
    cin >> n >> m >> q >> s;
    if (!(n + m + q + s))
      break;
    if (dn)
      dn = 0;
    else
      cout << '\n';
    rep(i, 0, n - 1) {
      cost[i] = INF;
      edges[i].clear();
    }
    rep(i, 1, m) {
      cin >> u >> v >> c;
      edges[u].pb({v, c});
    }
    cost[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
      int nw = pq.top().se, c = (-pq.top().fi);
      pq.pop();
      if (c > cost[nw])
        continue;
      for (auto nxt : edges[nw]) {
        if (cost[nxt.fi] > cost[nw] + nxt.se) {
          cost[nxt.fi] = cost[nw] + nxt.se;
          pq.push({-cost[nxt.fi], nxt.fi});
        }
      }
    }
    while (!pq.empty())
      pq.pop();
    while (q--) {
      cin >> node;
      if (cost[node] == INF)
        cout << "Impossible" << '\n';
      else
        cout << cost[node] << '\n';
    }
  }
  return 0;
}