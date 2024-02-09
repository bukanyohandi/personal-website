#include <bits/stdc++.h>
using namespace std;
int T, N;
long long Arr[10001], Memo[10001];
long long DP(int Pos) {
  if (Pos >= N)
    return 0;
  long long &Ret = Memo[Pos];
  if (Ret != -1)
    return Ret;
  return Ret = max(DP(Pos + 2) + Arr[Pos], DP(Pos + 1));
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cin >> N;
    for (int i = 0; i < N; ++i)
      cin >> Arr[i];
    memset(Memo, -1, sizeof(Memo));
    cout << "Case " << t << ": " << DP(0) << endl;
  }
}