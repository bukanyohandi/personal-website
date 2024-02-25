#include <bits/stdc++.h>
using namespace std;

struct ship {
  int x, y, n;
};

bool cmp(ship p, ship q) { return p.y < q.y; }

int main() {
  int n;
  cin >> n;

  vector<ship> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].x >> v[i].y >> v[i].n;
  }
  sort(v.begin(), v.end(), cmp);

  vector<int> opened(10000 + 1, 0);
  for (int i = 0; i < n; ++i) {
    int available = 0;
    for (int j = v[i].x; j <= v[i].y; ++j) {
      available += opened[j];
    }
    if (available >= v[i].n)
      continue;
    int needed = v[i].n - available;
    for (int j = v[i].y; j >= v[i].x; --j) {
      if (opened[j] == 1 || needed == 0)
        continue;
      opened[j] = 1;
      needed--;
    }
  }

  int ans = 0;
  for (int i = 1; i <= 10000; ++i) {
    ans += opened[i];
  }

  cout << ans << endl;
}