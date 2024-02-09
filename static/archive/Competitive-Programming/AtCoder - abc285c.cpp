#include <bits/stdc++.h>
using namespace std;

int main() {
  string S;
  cin >> S;

  long long ans = 0;
  for (int i = 0; i < (int)S.length(); ++i) {
    ans = (ans * 26) + (S[i] - 'A' + 1);
  }

  cout << ans << endl;
}