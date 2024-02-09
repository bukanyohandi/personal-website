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

int T;
lint N, A, Sum, Ans, Freq;
lint Pref[44444];
map<lint, lint> Count;
string S;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    cin >> A;
    cin >> S;
    N = S.length();
    for (int i = 1; i <= N; ++i) {
      Pref[i] = Pref[i - 1];
      Pref[i] += (int)S[i - 1] - '0';
    }
    if (A == 0) {
      for (int i = 1; i <= N; ++i) {
        for (int j = i; j <= N; ++j) {
          if (Pref[j] - Pref[i - 1] == 0)
            Freq++;
        }
      }
      cout << Freq * (N * (N + 1) - Freq) << endl;
      return 0;
    }
    for (int i = 1; i <= N; ++i) {
      for (int j = i; j <= N; ++j) {
        Sum = Pref[j] - Pref[i - 1];
        Count[Sum]++;
      }
    }
    for (int i = 1; i <= N; ++i) {
      for (int j = i; j <= N; ++j) {
        Sum = Pref[j] - Pref[i - 1];
        if (Sum == 0)
          continue;
        if (A % Sum == 0) {
          Ans += Count[A / Sum];
        }
      }
    }
    cout << Ans << endl;
  }
  return 0;
}
