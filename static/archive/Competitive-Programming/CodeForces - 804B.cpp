#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define MOD 1000000007
int piv, ans;
string s;
int main() {
  cin >> s;
  for (int i = s.length() - 1; i >= 0; --i) {
    if (s[i] == 'a') {
      ans = (ans + piv) % MOD;
      piv = (piv * 2) % MOD;
    } else {
      piv++;
    }
  }
  cout << ans << endl;
}
