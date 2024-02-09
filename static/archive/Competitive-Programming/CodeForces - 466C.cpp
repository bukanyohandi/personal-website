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

lint N;
lint tmp, Ans;
lint A[555555];
vector<lint> Vec1, Vec2;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    A[i] += A[i - 1];
  }
  if (A[N] % 3) {
    cout << 0 << endl;
    return 0;
  }
  tmp = A[N] / 3;
  for (int i = 1; i < N; ++i) {
    if (A[i] == tmp)
      Vec1.pb(i);
    if (A[i] == tmp * 2)
      Vec2.pb(i);
  }
  for (auto i : Vec1) {
    lint le = 0, ri = (int)Vec2.size() - 1, mid, save = -1;
    while (le <= ri) {
      mid = (le + ri) / 2;
      if (Vec2[mid] > i) {
        ri = mid - 1;
        save = mid;
      } else
        le = mid + 1;
    }
    if (save != -1)
      Ans += (int)Vec2.size() - save;
  }
  cout << Ans << endl;
  return 0;
}
