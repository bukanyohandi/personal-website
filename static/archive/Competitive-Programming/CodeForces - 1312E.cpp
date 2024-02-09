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

int T, N, LC, RC;
int A[555], DP[555];
int Memo[555][555];

int Check(int Le, int Ri) {
  if (Le == Ri)
    return A[Le];
  if (Memo[Le][Ri] != -1)
    return Memo[Le][Ri];
  Memo[Le][Ri] = 0;
  // int &Ret=Memo[Le][Ri];
  // if(Ret!=-1) return Ret;
  // if(Le==1&&Ri==4) cout<<"[ "<<Le<<" , "<<Ri<<" ]\n";
  for (int i = Le + 1; i <= Ri; ++i) {
    // LC=Check(Le,i-1);
    // RC=Check(i,Ri);
    // if(Le==1&&Ri==4){
    //     cout<<Le<<" "<<i-1<<" : "<<Check(Le,i-1)<<endl;
    //     cout<<i<<" "<<Ri<<" : "<<RC<<endl;
    // }
    if ((Check(Le, i - 1) != 0) && (Check(Le, i - 1) == Check(i, Ri))) {
      // if(Le==1&&Ri==4) cout<<"MASUK : ["<<Le<<" , "<<i-1<<"] ["<<i<<" ,
      // "<<Ri<<"]\n";
      Memo[Le][Ri] = Check(Le, i - 1) + 1;
    }
  }
  return Memo[Le][Ri];
  // if(Le==1&&Ri==4) cout<<"[ "<<Le<<" , "<<Ri<<" ]\n";
  // return Ret;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  T = 1;
  //	cin>>T;
  rep(t, 1, T) {
    memset(Memo, -1, sizeof(Memo));
    cin >> N;
    for (int i = 1; i <= N; ++i)
      cin >> A[i];
    for (int i = 1; i <= N; ++i) {
      for (int j = i; j <= N; ++j) {
        Check(i, j);
      }
    }
    for (int i = 1; i <= N; ++i)
      DP[i] = i;
    // Check(1,N);
    for (int i = 1; i <= N; ++i) {
      for (int j = i; j <= N; ++j) {
        if (Check(i, j) > 0) {
          DP[j] = min(DP[j], DP[i - 1] + 1);
        }
      }
    }
    // for(int i=1;i<=N;++i){
    //     cout<<i<<" -> DP = "<<DP[i]<<endl;
    // }
    cout << DP[N] << "\n";
  }
  return 0;
}
