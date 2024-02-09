#include <bits/stdc++.h>
using namespace std;
int tc, n, a, b, ans1, ans2, td = 0, pw;
string s;
pair<int, int> ans[10005];
bool visited[10005];
vector<int> vc[10005];
bool connected(int x, int y) {
  for (int i = 0; i <= n; ++i) {
    visited[i] = false;
  }
  int piv, tmp;
  queue<int> bfs;
  bfs.push(x);
  visited[x] = true;
  while (!bfs.empty()) {
    piv = bfs.size();
    for (int i = 0; i < piv; ++i) {
      if (bfs.front() == y)
        return true;
      for (int j = 0; j < vc[bfs.front()].size(); ++j) {
        tmp = vc[bfs.front()][j];
        if (!visited[tmp]) {
          visited[tmp] = true;
          bfs.push(tmp);
        }
      }
      bfs.pop();
    }
  }
  return false;
}
int main() {
  cin >> tc;
  pw = tc;
  while (tc--) {
    while (cin >> s) {
      if (s == "c") {
        cin >> a >> b;
        vc[a].push_back(b);
        vc[b].push_back(a);
      } else if (s == "q") {
        cin >> a >> b;
        if (connected(a, b)) {
          ans1++;
        } else {
          ans2++;
        }
      } else {
        ans[td].first = ans1;
        ans[td].second = ans2;
        td++;
        n = stoll(s);
        ans1 = ans2 = 0;
        for (int i = 0; i < 10001; ++i) {
          vc[i].clear();
        }
      }
    }
    ans[td].first = ans1;
    ans[td].second = ans2;
    td++;
  }
  for (int i = 1; i <= pw; ++i) {
    if (i != 1)
      cout << endl;
    cout << ans[i].first << "," << ans[i].second << endl;
  }
}