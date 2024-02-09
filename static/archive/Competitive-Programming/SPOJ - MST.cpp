#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
ll n, m;
ll p[100005], sz[100005];
pair<int, pair<int, int>> a[100005];
ll find(ll x) {
  if (p[x] == x)
    return x;
  return p[x] = find(p[x]);
}
void merge(ll x, ll y) {
  ll a = find(x), b = find(y);
  if (sz[a] > sz[b])
    swap(a, b);
  p[a] = b;
  sz[b] += sz[a];
  sz[a] = 0;
  return;
}
bool isconnected(ll x, ll y) { return find(x) == find(y); }
signed main() {
  ll weight = 0;
  for (int i = 1; i <= 100000; i++) {
    p[i] = i, sz[i] = 1;
    ;
  }
  ll x, y, k;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> x >> y >> k;
    a[i].first = k;
    a[i].second.first = x;
    a[i].second.second = y;
  }
  sort(a, a + m);
  for (int i = 0; i < m; i++) {
    if (!isconnected(a[i].second.first, a[i].second.second)) {
      merge(a[i].second.first, a[i].second.second);
      weight += a[i].first;
    }
    if (sz[find(1)] == n) {
      cout << weight << endl;
      break;
    }
  }
}