#include <bits/stdc++.h>
using namespace std;
int N, M, X, Y, pref[1005], flyin[1005], table[1005];
char tmp;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> M >> X >> Y;
  for (int i = 1; i <= N; ++i)
    for (int j = 1; j <= M; ++j) {
      cin >> tmp;
      pref[j] += (tmp == '#');
    }
  flyin[1] = table[1] = 1e9;
  for (int i = 2; i <= M; ++i) {
    pref[i] += pref[i - 1];
    flyin[i] = table[i] = 1e9;
  }
  for (int i = 1; i <= M; ++i)
    for (int j = X; j <= min(Y, i); ++j) {
      flyin[i] = min(flyin[i], table[i - j] + pref[i] - pref[i - j]);
      table[i] = min(table[i], flyin[i - j] + N * j + pref[i - j] - pref[i]);
    }
  cout << min(flyin[M], table[M]) << endl;
}