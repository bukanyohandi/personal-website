#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  string S;
  vector<string> V;

  cin >> N;

  for (int i = 0; i < N; ++i) {
    cin >> S;
    V.push_back(S);
  }

  reverse(V.begin(), V.end());

  for (int i = 0; i < N; ++i) {
    cout << V[i] << endl;
  }
}