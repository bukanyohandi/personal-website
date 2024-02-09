#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> v;

const int MOD = 1e8 + 7;

int memo[100000][4];
int dp(int pos, int state) {
  if (pos == n)
    return state == 0;

  int &ret = memo[pos][state];
  if (ret != -1)
    return ret;

  ret = dp(pos + 1, state);
  if (v[pos] == state) {
    ret += dp(pos + 1, state);
  } else if (v[pos] == state - 1) {
    ret += dp(pos + 1, state - 1);
  }
  ret %= MOD;

  return ret;
}

signed main() {
  memset(memo, -1, sizeof(memo));

  int x;
  while (cin >> x) {
    v.push_back(x);
  }

  n = (int)v.size();
  cout << dp(0, 3) << endl;
}