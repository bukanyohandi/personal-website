#include <bits/stdc++.h>
using namespace std;
int main() {
  int n, a, b, isi = 0, best = 0;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a >> b;
    isi -= a;
    isi += b;
    best = max(best, isi);
  }
  cout << best << endl;
}