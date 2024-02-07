#include <bits/stdc++.h>
using namespace std;

pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b) {
  return {a.first + b.first, a.second + b.second};
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string pattern = "bessie";
  int k = (int)pattern.size();

  string s;
  getline(cin, s);

  int n = (int)s.size();
  vector<int> cost(n);
  for (int i = 0; i < n; ++i) {
    cin >> cost[i];
  }

  vector<vector<pair<int, int>>> memo(n, vector<pair<int, int>>(k));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < k; ++j)
      memo[i][j] = {-1, -1};

  function<pair<int, int>(int, int)> dp =
      [&](int s_pos, int pattern_pos) -> pair<int, int> {
    if (s_pos == n)
      return {0, 0};

    pair<int, int> &ret = memo[s_pos][pattern_pos];
    if (ret != make_pair(-1, -1))
      return ret;

    bool equal = s[s_pos] == pattern[pattern_pos];

    ret = dp(s_pos + 1, 0);
    ret = max(ret, dp(s_pos + 1, pattern_pos) + make_pair(0, -cost[s_pos]));
    if (equal) {
      ret = max(ret, dp(s_pos + 1, (pattern_pos + 1) % k) +
                         make_pair((int)pattern_pos == k - 1, 0));
    }

    return ret;
  };

  auto result = dp(0, 0);
  cout << result.first << endl << -result.second << endl;

  return 0;
}