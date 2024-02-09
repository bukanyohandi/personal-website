#include <bits/stdc++.h>
using namespace std;
int n;
int p[1001];
int find(int x) {
  if (p[x] == x)
    return x;
  return p[x] = find(p[x]);
}
vector<pair<int, int>> save;
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i)
    p[i] = i;
  for (int i = 1; i < n; ++i) {
    int a, b;
    cin >> a >> b;
    int ra = find(a), rb = find(b);
    if (ra != rb) {
      p[ra] = rb;
    } else {
      save.push_back({a, b});
    }
  }
  int cnt = 0;
  vector<pair<pair<int, int>, pair<int, int>>> ans;
  for (int i = 2; i <= n; ++i) {
    if (find(i) != find(1)) {
      p[find(i)] = find(1);
      ans.push_back({save[cnt++], {1, i}});
      // cout<<save[cnt].first<<" "<<save[cnt].second<<" "<<save[cnt].first<<"
      // "<<i<<endl;
    }
  }
  cout << ans.size() << endl;
  for (auto i : ans) {
    cout << i.first.first << " " << i.first.second << " " << i.second.first
         << " " << i.second.second << endl;
  }
}