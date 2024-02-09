#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  string S;

  cin >> N;
  cin >> S;

  for (int k = 1; k <= N - 1; ++k) {
    int l = 0;
    for (int i = 0; i + k < N; ++i) {
      if (S[i] != S[i + k]) {
        l++;
      } else {
        break;
      }
    }
    cout << l << endl;
  }
}