#include <bits/stdc++.h>
using namespace std;
long long data2[105];
int main() {
  pair<long long, long long> data[105];
  long long n, m, best = 0;
  cin >> n >> m;
  for (long long i = 1LL; i <= m; ++i) {
    for (long long j = 1LL; j <= n; ++j) {
      cin >> data[j].first;
      data[j].second = j;
    }
    sort(data + 1, data + 1 + n);
    long long q = n;
    while (data[q].first == data[q - 1].first) {
      q--;
      if (q == 1)
        break;
    }
    data2[data[q].second]++;
    best = max(best, data2[data[q].second]);
  }
  for (long long i = 1LL; i <= n; ++i) {
    if (data2[i] == best) {
      cout << i << endl;
      return 0;
    }
  }
  cout << 1 << endl;
  return 0;
}