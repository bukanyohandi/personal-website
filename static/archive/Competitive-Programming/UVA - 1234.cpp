#include <bits/stdc++.h>
#define fs first
#define sc second
using namespace std;
int pay, tc, N, M, X, Y, Z, P[10005], S[10005], W[1005], tmpx, tmpy;
vector<pair<int, pair<int, int>>> vec;
pair<int, pair<int, int>> data[100005];
int par(int x) { return P[x] == x ? x : P[x] = par(P[x]); }
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  while (tc--) {
    cin >> N >> M;
    pay = 0;
    vec.clear();
    for (int i = 1; i <= M; ++i) {
      cin >> X >> Y >> Z;
      pay += Z;
      vec.push_back({Z, {X, Y}});
    }
    for (int i = 1; i <= N; ++i)
      P[i] = i, S[i] = 1;
    memset(W, 0, sizeof(W));
    for (int i = 0; i < M; ++i)
      W[vec[i].fs]++;
    for (int i = 999; i >= 0; --i)
      W[i] += W[i + 1];
    for (int i = 0; i < M; ++i)
      data[--W[vec[i].fs]] = vec[i];
    for (int i = 0; i < M; ++i) {
      tmpx = par(data[i].sc.fs);
      tmpy = par(data[i].sc.sc);
      if (tmpx == tmpy)
        continue;
      if (S[tmpx] > S[tmpy])
        S[tmpx] += S[tmpy], P[tmpy] = tmpx;
      else
        S[tmpy] += S[tmpx], P[tmpx] = tmpy;
      pay -= data[i].fs;
    }
    cout << pay << endl;
  }
  cin >> tc;
  return 0;
}