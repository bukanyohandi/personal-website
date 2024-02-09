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

int N, P, Le, Ri, Ans, tmp;
string S;
vector<int> Pos;

int Add(char A, char B) { return min((B - A + 26) % 26, (A - B + 26) % 26); }

int main() {
  //	ios_base::sync_with_stdio(0);
  //	cin.tie(0); cout.tie(0);
  cin >> N >> P;
  P--;
  cin >> S;
  Le = 0;
  Ri = (int)S.length() - 1;
  while (Le < Ri) {
    if (S[Le] != S[Ri]) {
      Ans += Add(S[Le], S[Ri]);
      Pos.pb(Le);
    }
    Le++;
    Ri--;
  }
  if (Pos.size() == 0) {
    cout << Ans << endl;
    return 0;
  }
  if (2 * P + 1 > S.length())
    P = S.length() - P - 1;
  sort(Pos.begin(), Pos.end());
  Le = Pos[0];
  Ri = Pos[(int)Pos.size() - 1];
  Ans += Ri - Le;
  if (Le <= P && P <= Ri) {
    Ans += min(P - Le, Ri - P);
  } else if (P < Le) {
    Ans += Le - P;
  } else {
    Ans += P - Ri;
  }
  cout << Ans << endl;
  return 0;
}
