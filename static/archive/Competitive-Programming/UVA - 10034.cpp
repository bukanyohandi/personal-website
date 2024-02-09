#include <bits/stdc++.h>
using namespace std;
int tc, n, piv = 1;
double a, b;
bool visited[105];
pair<double, double> data[105];
double jarak(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
void solve() {
  double cost = 0, tmp;
  int tmp2;
  priority_queue<pair<double, int>, vector<pair<double, int>>,
                 greater<pair<double, int>>>
      pq;
  for (int i = 2; i <= n; ++i) {
    pq.push(make_pair(
        jarak(data[1].first, data[1].second, data[i].first, data[i].second),
        i));
  }
  visited[1] = true;
  while (!pq.empty()) {
    tmp = pq.top().first;
    tmp2 = pq.top().second;
    pq.pop();
    if (!visited[tmp2]) {
      visited[tmp2] = true;
      cost += tmp;
      for (int i = 1; i <= n; ++i) {
        if (i == tmp2)
          continue;
        pq.push(make_pair(jarak(data[tmp2].first, data[tmp2].second,
                                data[i].first, data[i].second),
                          i));
      }
    }
  }
  cout << fixed << setprecision(2) << cost << endl;
}
int main() {
  cin >> tc;
  while (tc--) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      visited[i] = false;
      cin >> data[i].first >> data[i].second;
    }
    if (piv != 1) {
      cout << endl;
    } else {
      piv++;
    }
    solve();
  }
}