#include <bits/stdc++.h>
#define ll long long
using namespace std;
string S;
ll memo[5000];
ll dp(int pos) {
  if (pos == S.length())
    return 1;
  ll &ret = memo[pos];
  if (ret != -1)
    return ret;
  if (S[pos] == '0')
    return ret = 0;
  ret = dp(pos + 1);
  if ((pos < S.length() - 1) &&
      ((S[pos] == '1') || (S[pos] == '2' && S[pos + 1] <= '6')))
    ret += dp(pos + 2);
  return ret;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  while (cin >> S) {
    if (S == "0")
      return 0;
    memset(memo, -1, sizeof(memo));
    cout << dp(0) << '\n';
  }
}