#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
const long long MOD = 1000000007;
using namespace std;
int N;
int A[300003], DynP[300003], Tree[1200012];
long long Ans;
long long Total[300003], Cara[300003];
map<int, long long> Jumlah[300003];
deque<pair<int, int>> Hitung[300003];
vector<pair<int, int>> Order;
inline int Query(int Low, int High, int Pos, int Le, int Ri) {
  if (Le <= Low && High <= Ri)
    return Tree[Pos];
  if (Le > High || Low > Ri)
    return 0;
  int Mid = (Low + High) / 2;
  return max(Query(Low, Mid, 2 * Pos, Le, Ri),
             Query(Mid + 1, High, 2 * Pos + 1, Le, Ri));
}
inline void Update(int Low, int High, int Pos, int Idx, int Val) {
  if (Low == High) {
    Tree[Pos] = Val;
    return;
  }
  int Mid = (Low + High) / 2;
  if (Idx <= Mid) {
    Update(Low, Mid, 2 * Pos, Idx, Val);
  } else {
    Update(Mid + 1, High, 2 * Pos + 1, Idx, Val);
  }
  Tree[Pos] = max(Tree[2 * Pos], Tree[2 * Pos + 1]);
  return;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    Order.push_back({A[i], -i});
  }
  sort(Order.begin(), Order.end());
  for (int i = 0; i < Order.size(); ++i) {
    DynP[-Order[i].second] = Query(1, N, 1, 1, -Order[i].second - 1) + 1;
    Update(1, N, 1, -Order[i].second, DynP[-Order[i].second]);
  }
  Cara[0] = 1;
  for (int i = 1; i <= N; ++i) {
    while (!Hitung[DynP[i] - 1].empty() &&
           A[i] <= Hitung[DynP[i] - 1].back().first) {
      Total[DynP[i] - 1] -= Cara[Hitung[DynP[i] - 1].back().second];
      Total[DynP[i] - 1] += MOD;
      Total[DynP[i] - 1] %= MOD;
      Hitung[DynP[i] - 1].pop_back();
    }
    Hitung[DynP[i]].push_front({A[i], i});
    Cara[i] = DynP[i] == 1 ? 1 : Total[DynP[i] - 1];
    Cara[i] -= Jumlah[DynP[i]][A[i]];
    Cara[i] += MOD;
    Cara[i] %= MOD;
    Total[DynP[i]] += Cara[i];
    Total[DynP[i]] %= MOD;
    Jumlah[DynP[i]][A[i]] += Cara[i];
    Jumlah[DynP[i]][A[i]] %= MOD;
  }
  cout << Total[Query(1, N, 1, 1, N)] % MOD << endl;
}