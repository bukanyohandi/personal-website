#include <bits/stdc++.h>
using namespace std;
int main() {
  string S, T;
  cin >> S >> T;
  for (int i = 0; i < S.length(); ++i) {
    if (S[i] != T[i]) {
      cout << "No\n";
      return 0;
    }
  }
  cout << "Yes\n";
}