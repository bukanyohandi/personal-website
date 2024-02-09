#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  vector<string> S, T;

  cin >> N >> M;
  S.resize(N);
  T.resize(M);

  for (int i = 0; i < N; ++i) {
    cin >> S[i];
  }

  map<string, bool> tag;
  for (int i = 0; i < M; ++i) {
    cin >> T[i];
    tag[T[i]] = true;
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (tag[S[i].substr(3, 3)]) {
      ans++;
    }
  }

  cout << ans << endl;
}