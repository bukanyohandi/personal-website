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

int T, N;
set<int> Set, Set1;
map<int, int> Map;

inline void Solve(int Case) {
  cin >> N;
  vector<int> A(N), B(N), New;
  rep(i, 0, N - 1) {
    cin >> A[i];
    Set1.insert(A[i]);
  }
  if (Set1.size() == 1 && N != 1) {
    puts("1");
    cout << A[0] << endl;
    return;
  }
  sort(all(A));
  if (N == 2 && (A[1] - A[0]) % 2 == 0) {
    puts("3");
    cout << A[0] - (A[1] - A[0]) << " " << A[0] + (A[1] - A[0]) / 2 << " "
         << A[1] + (A[1] - A[0]) << endl;
    return;
  }
  Set.clear();
  adjacent_difference(A.begin(), A.end(), B.begin());
  rep(i, 1, (int)B.size() - 1) {
    Set.insert(B[i]);
    Map[B[i]] += 1;
  }
  for (auto i : Set) {
    if (New.size() == 2)
      break;
    New.pb(i);
  }
  if (Set.size() == 0) {
    puts("-1");
  } else if (Set.size() == 1) {
    puts("2");
    cout << A[0] - *Set.begin() << " " << A[N - 1] + *Set.begin() << endl;
  } else if (Set.size() == 2 && ((*Set.begin()) * 2 == New[1]) &&
             (Map[New[1]] == 1)) {
    puts("1");
    rep(i, 1, N - 1) {
      if (A[i] - A[i - 1] == New[1])
        cout << A[i] - *Set.begin() << endl;
    }
  } else {
    puts("0");
  }
  return;
}

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) Solve(t);
  return 0;
}
