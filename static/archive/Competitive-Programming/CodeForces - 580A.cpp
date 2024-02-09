#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, prev = 0, now = 0, best = 0, piv = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> now;
    if (prev <= now) {
      piv++;
    } else {
      best = max(best, piv);
      piv = 1;
    }
    prev = now;
  }
  best = max(best, piv);
  cout << best << endl;
}