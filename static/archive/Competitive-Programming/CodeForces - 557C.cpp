#include <bits/stdc++.h>

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

int T, N, K, Q;
int L[111111], D[111111], Cost[111111], pay[222];
pair<int, int> P[111111];

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> N;
    int Ans = INT_MAX;
    for (int i = 1; i <= N; ++i)
      cin >> L[i], P[i].fs = L[i];
    for (int i = 1; i <= N; ++i)
      cin >> D[i], P[i].sc = D[i];
    sort(P + 1, P + N + 1);
    for (int i = 1; i <= N; ++i)
      Cost[i] = P[i].sc;
    for (int i = N; i >= 1; --i) {
      Cost[i] += Cost[i + 1];
    }
    // for(int i=1;i<=N;++i){
    // 	cout<<Cost[i]<<" ";
    // }
    // cout<<endl;
    bool New = 1;
    int piv = 0, pat = 0, lat;
    for (int i = 1; i <= N; ++i) {
      if (New) {
        piv = i;
        New = 0;
      }
      if (P[i].fs == P[i + 1].fs && i <= N - 1) {
        pat += 1;
        continue;
      }
      // cout<<pat<<endl;
      pat++;
      int t = i + 1 - 2 * pat;
      pat = 0;
      if (t < 0)
        t = 0;
      lat = 0;
      int piv2 = 0;
      for (int j = 1; j <= 200; ++j) {
        lat += pay[j];
        // cout<<lat<<endl;
        if (lat <= t)
          piv2 += pay[j] * j;
        else {
          lat -= pay[j];
          piv2 += j * (t - lat);
          break;
        }
      }
      Ans = min(Ans, Cost[i + 1] + piv2);
      // cout<<Ans<<endl;
      for (int j = piv; j <= i; ++j)
        pay[P[j].sc]++;
      New = 1;
    }
    cout << Ans << endl;
  }
  return 0;
}
