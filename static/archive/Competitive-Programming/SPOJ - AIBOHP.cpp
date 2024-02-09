#include <bits/stdc++.h>
using namespace std;
int N, memo[6201][6201];
string S;
int longest(int le, int ri) {
  if (le > ri)
    return 0;
  int &ret = memo[le][ri];
  if (ret != -1)
    return ret;
  if (S[le] == S[ri])
    return ret = (le != ri) + 1 + longest(le + 1, ri - 1);
  return ret = max(longest(le + 1, ri), longest(le, ri - 1));
}
int main() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> S;
    memset(memo, -1, sizeof(memo));
    cout << S.length() - longest(0, S.length() - 1) << '\n';
  }
}