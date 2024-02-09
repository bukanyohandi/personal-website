#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back

#define all(a) a.begin(), a.end()
#define lb(a, x) (lower_bound(all(a), x) - a.begin())
#define ub(a, x) (upper_bound(all(a), x) - a.begin())

#define rep(a, x, y) for (int a = (int)x; a <= (int)y; ++a)
#define repd(a, x, y, d) for (int a = (int)x; a <= (int)y; a += d)
#define res(a, x, y) for (int a = (int)x; a >= (int)y; --a)
#define resd(a, x, y, d) for (int a = (int)x; a >= (int)y; a -= d)

// Ordered Set, Ordered Multiset
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define o_set                                                                  \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
       tree_order_statistics_node_update>
#define o_multiset                                                             \
  tree<int, null_type, less_equal<int>, rb_tree_tag,                           \
       tree_order_statistics_node_update>
using namespace __gnu_pbds;
// .order_of_key(x) -> Number of elements less than x
// * .find_by_order(k) -> Kth smallest element (0-based)
// .erase(x) -> Remove all elements equal to x

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
using lint = long long;

mt19937 rng(time(NULL));

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int T, N, M, A, B, W;
int P[111111];
lint Dis[111111];
vector<pair<int, int>> Edg[111111];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>
    Pq;
vector<int> Ans;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
      cin >> A >> B >> W;
      Edg[A].push_back({B, W});
      Edg[B].push_back({A, W});
    }
    for (int i = 1; i <= N; ++i)
      P[i] = i;
    for (int i = 2; i <= N; ++i)
      Dis[i] = 1e12;
    Pq.push({0, 1});
    while (!Pq.empty()) {
      pair<int, int> tmp = Pq.top();
      Pq.pop();
      if (tmp.first > Dis[tmp.second])
        continue;
      for (auto i : Edg[tmp.second]) {
        if (Dis[i.first] <= Dis[tmp.second] + i.second)
          continue;
        P[i.first] = tmp.second;
        Dis[i.first] = (lint)Dis[tmp.second] + i.second;
        Pq.push({Dis[i.first], i.first});
      }
    }
    if (Dis[N] == 1e12) {
      cout << "-1" << endl;
    } else {
      do {
        Ans.push_back(N);
        N = P[N];
      } while (N != 1);
      cout << 1;
      while ((bool)Ans.size()) {
        cout << " ";
        cout << Ans.back();
        Ans.pop_back();
      }
      cout << endl;
    }
  }
  return 0;
}
