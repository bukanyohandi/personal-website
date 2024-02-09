#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define all(a) a.begin(), a.end()

// Ordered Set, Ordered Multiset
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define o_set                                                                  \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
       tree_order_statistics_node_update>
#define o_multiset                                                             \
  tree<int, null_type, less<int>, rb_tree_tag,                                 \
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

lint Power(lint A, lint B) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1);
  return tmp * tmp * (B & 1 ? A : 1);
}

lint Power(lint A, lint B, lint C) {
  if (!B)
    return 1LL;
  lint tmp = Power(A, B >> 1, C);
  return tmp * tmp % C * (B & 1 ? A : 1) % C;
}

int N, M;
string Ans;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N >> M;
  if ((N > M + 1) || (M > 2 * (N + 1))) {
    puts("-1");
    return 0;
  }
  if (N == M + 1) {
    Ans = "0";
    for (int i = 1; i <= M; ++i)
      Ans += "10";
    cout << Ans << endl;
    return 0;
  }
  if ((M == 2 * (N + 1)) || (M + 1 == 2 * (N + 1))) {
    Ans = "1";
    if (M % 2 == 0)
      Ans += '1';
    for (int i = 1; i <= N; ++i)
      Ans += "011";
    cout << Ans << endl;
    return 0;
  }
  for (int i = 1; i <= N; ++i) {
    if (i <= M - N)
      Ans += '1';
    Ans += "10";
  }
  cout << Ans << endl;
  return 0;
}
