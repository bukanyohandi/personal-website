#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int ans = 0;
  map<int, int> cnt;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    cnt[x]++;
    if (cnt[x] % 2 == 0) {
      ans++;
    }
  }

  cout << ans << endl;
}