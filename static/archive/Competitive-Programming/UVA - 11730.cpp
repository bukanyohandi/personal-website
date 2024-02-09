#include <bits/stdc++.h>
using namespace std;
int n, m, kentud = 1;
bool bukanprima[10005], visited[10005];
void solve() {
  int piv, ans = 0;
  queue<int> ice;
  ice.push(n);
  visited[n] = true;
  while (!ice.empty()) {
    if (ice.front() > m) {
      ice.pop();
      continue;
    }
    piv = ice.size();
    for (int i = 0; i < piv; ++i) {
      if (ice.front() == m) {
        cout << "Case " << kentud << ": " << ans << endl;
        kentud++;
        return;
      }
      for (int j = 2; j < ice.front(); ++j) {
        if (!bukanprima[j] && !visited[ice.front() + j] &&
            ice.front() % j == 0) {
          ice.push(ice.front() + j);
          visited[ice.front() + j] = true;
        }
      }
      ice.pop();
    }
    ans++;
  }
  cout << "Case " << kentud << ": " << -1 << endl;
  kentud++;
  return;
}
int main() {
  for (int i = 2; i <= 1000; ++i) {
    if (!bukanprima[i]) {
      for (int j = 2 * i; j <= 1000; j += i) {
        bukanprima[j] = true;
      }
    }
  }
  while (cin >> n >> m) {
    for (int i = 1; i <= 1000; ++i)
      visited[i] = false;
    if (n == 0 && m == 0)
      return 0;
    solve();
  }
}