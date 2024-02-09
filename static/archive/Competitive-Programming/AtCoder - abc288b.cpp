#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  cin >> N >> K;

  vector<string> S(N);
  for (int i = 0; i < N; ++i) {
    cin >> S[i];
  }
  while ((int)S.size() > K) {
    S.pop_back();
  }
  sort(S.begin(), S.end());

  for (int i = 0; i < K; ++i) {
    cout << S[i] << endl;
  }
}