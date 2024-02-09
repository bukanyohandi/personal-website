#include <bits/stdc++.h>
#define ll long long
#define endl '\n'
using namespace std;
ll tc, N, M, save, tmp, X, piv1, piv2;
queue<ll> que;
vector<ll> vec;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> tc;
  for (int t = 1; t <= tc; ++t) {
    while (que.size())
      que.pop();
    vec.clear();
    save = -1;
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
      X = 0;
      for (int j = 1; j <= N; ++j)
        cin >> tmp, X = (X << 1) + tmp;
      vec.push_back(X);
    }
    ll piv[1 << 16] = {};
    que.push((1 << N) - 1);
    piv[(1 << N) - 1] = 1;
    while (que.size() && !piv[0]) {
      piv1 = que.front();
      que.pop();
      for (int i = 0; i < M; ++i) {
        piv2 = piv1 ^ vec[i];
        if (!piv[piv2])
          piv[piv2] = piv[piv1] + 1, que.push(piv2);
      }
    }
    cout << "Case " << t << ": ";
    if (piv[0])
      cout << piv[0] - 1 << endl;
    else
      cout << "IMPOSSIBLE\n";
  }
}