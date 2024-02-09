#include <bits/stdc++.h>
/*
        Karya anak bangsa yang paling agung
        Author : Yohandi or... bukan..
*/

#define fs first
#define sc second
#define pb push_back
#define eb emplace_back
#define endl "\n"

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

int N, Q, C, D;
int A[222222], B[222222], Tree[888888];
map<int, bool> Cons;
map<int, int> Last;
multiset<int> Set[222222];

int fMax(int Pos) {
  if (Set[Pos].size() == 0)
    return 1000000000;
  else
    return *(Set[Pos].rbegin());
}

int Build(int Low, int High, int Pos) {
  if (Low == High) {
    if (Cons[Low]) {
      return Tree[Pos] = fMax(Low);
    } else {
      return Tree[Pos] = 1000000000;
    }
  }
  int Mid = (Low + High) / 2;
  return Tree[Pos] =
             min(Build(Low, Mid, 2 * Pos), Build(Mid + 1, High, 2 * Pos + 1));
}

void Update(int Low, int High, int Pos, int Index) {
  if (Low == High) {
    Tree[Pos] = fMax(Low);
    // cout<<"-> "<<Index<<" "<<Tree[Pos]<<endl;
    return;
  }
  int Mid = (Low + High) / 2;
  if (Index <= Mid) {
    Update(Low, Mid, 2 * Pos, Index);
  } else {
    Update(Mid + 1, High, 2 * Pos + 1, Index);
  }
  Tree[Pos] = min(Tree[2 * Pos], Tree[2 * Pos + 1]);
  // cout<<Pos<<" -> "<<2*Pos<<" "<<2*Pos+1<<endl;
  // cout<<Tree[Pos]<<" -> "<<Tree[2*Pos]<<" "<<Tree[2*Pos+1]<<endl;
  return;
}

int main() {
  cin >> N >> Q;
  for (int i = 1; i <= 800000; ++i)
    Tree[i] = 1e9;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i] >> B[i];
    Last[i] = B[i];
    Cons[B[i]] = true;
    Set[B[i]].insert(A[i]);
  }
  Build(1, 200000, 1);
  for (int i = 1; i <= Q; ++i) {
    cin >> C >> D;
    // cout<<Tree[1]<<endl;
    // cout<<Last[C]<<" - "<<C<<endl;
    // auto it=Set[Last[C]].find(A[C]);
    // if(it!=Set[Last[C]].end()) Set[Last[C]].erase(it);
    Set[Last[C]].erase(Set[Last[C]].lower_bound(A[C]));
    Set[D].insert(A[C]);
    // for(int j=1;j<=6;++j){
    //     cout<<j<<" "<<fMax(j)<<endl;
    // }
    Update(1, 200000, 1, Last[C]);
    Update(1, 200000, 1, D);
    Last[C] = D;
    cout << Tree[1] << endl;
  }
  return 0;
}
