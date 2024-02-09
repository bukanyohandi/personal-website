#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
const int MAXK = 900;

int n, k;
int pref[MAXN + 1];
vector<int> v;

int cost(int l, int r) {
  int mid = (l + r) / 2;
  int ret;
  if ((r - l + 1) % 2 == 1)
    ret = (pref[r] - pref[mid]) - (pref[mid - 1] - pref[l - 1]);
  else
    ret = (pref[r] - pref[mid]) - (pref[mid] - pref[l - 1]);
  return ret;
}

int memo[MAXN + 1][MAXK + 1];
int dp(int n, int k) {
  if (n <= k)
    return 0;
  if (n == 0)
    return 0;
  if (k == 0)
    return 10000000;

  if (k > MAXK) {
    int ret = INT_MAX;
    for (int i = 1; i <= n; ++i) {
      ret = min(ret, dp(i - 1, k - 1) + cost(i, n));
    }

    return ret;
  } else {
    int &ret = memo[n][k];
    if (ret != -1)
      return ret;

    ret = INT_MAX;
    for (int i = 1; i <= n; ++i) {
      ret = min(ret, dp(i - 1, k - 1) + cost(i, n));
    }

    return ret;
  }
}

int main() {
  memset(memo, -1, sizeof(memo));

  int x;
  while (cin >> x) {
    v.push_back(x);
  }
  k = v.back();
  v.pop_back();
  n = v.size();

  sort(v.begin(), v.end());
  for (int i = 1; i <= n; ++i) {
    pref[i] = pref[i - 1] + v[i - 1];
  }
  cout << dp(n, k) << endl;
}