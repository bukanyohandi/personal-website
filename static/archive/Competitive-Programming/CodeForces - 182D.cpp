#include <bits/stdc++.h>

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define MOD 100000000

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
int Ans;
string A, B;
set<string> Set;

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> A >> B;
  for (int k = 1; k <= A.length(); ++k) {
    if (A.length() % k != 0)
      continue;
    bool Found = 0;
    for (int i = 0; i < k && !Found; ++i) {
      for (int j = i + k; j < A.length() && !Found; j += k)
        if (A[j] != A[i])
          Found = 1;
    }
    if (!Found)
      Set.insert(A.substr(0, k));
  }
  for (int k = 1; k <= B.length(); ++k) {
    if (B.length() % k != 0)
      continue;
    bool Found = 0;
    for (int i = 0; i < k && !Found; ++i) {
      for (int j = i + k; j < B.length() && !Found; j += k)
        if (B[j] != B[i])
          Found = 1;
    }
    if (!Found) {
      int tmp = Set.size();
      Set.insert(B.substr(0, k));
      if (tmp == Set.size())
        Ans++;
    }
  }
  cout << Ans << endl;
  return 0;
}
