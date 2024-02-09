#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, ans = 0;
  string S;

  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> S;
    if (S == "For") {
      ans++;
    }
  }

  if (ans >= (N + 1) / 2) {
    cout << "Yes" << endl;
  } else {
    cout << "No" << endl;
  }
}