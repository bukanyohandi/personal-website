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
#define MAX 100001

#define all(a) a.begin(), a.end()
#define lb(a, x) (lower_bound(all(a), x) - a.begin())
#define ub(a, x) (upper_bound(all(a), x) - a.begin())

#define rep(a, x, y) for (int a = (int)x; a <= (int)y; ++a)
#define repd(a, x, y, d) for (int a = (int)x; a <= (int)y; a += d)
#define res(a, x, y) for (int a = (int)x; a >= (int)y; --a)
#define resd(a, x, y, d) for (int a = (int)x; a >= (int)y; a -= d)

using namespace std;

int Ans[MAX], C[MAX], Arr[MAX];
vector<int> Edge[MAX];
vector<int> Queries[MAX];
// vector<pair<int,int>> Queries[111111];
map<int, int> Map1[MAX], Map2[MAX];

void DFS(int Now, int Par) {
  Map1[Now][C[Now]]++;
  Map2[Now][1]++;
  for (auto i : Edge[Now]) {
    if (i == Par)
      continue;
    DFS(i, Now);
  }
  for (auto i : Edge[Now]) {
    if (i == Par)
      continue;
    if (Map1[Now].size() < Map1[i].size()) {
      Map1[Now].swap(Map1[i]);
      Map2[Now].swap(Map2[i]);
      // swap(Map1[Now],Map1[i]);
      // swap(Map2[Now],Map2[i]);
    }
  }
  for (auto i : Edge[Now]) {
    if (i == Par)
      continue;
    for (auto j : Map1[i]) {
      int X = Map1[Now][j.first];
      Map1[Now][j.first] += j.second;
      for (int k = 1; k <= j.second; ++k)
        Map2[Now][X + k]++;
      // for(int k=1;k<=j.second;++k) Map2[Now][X+k]++;
      // X+=j.second;
    }
  }
  for (auto i : Queries[Now])
    Ans[i] = Map2[Now][Arr[i]];
  return;
}

int main() {
  // ios_base::sync_with_stdio(0);
  // cin.tie(0); cout.tie(0);
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; ++i)
    cin >> C[i];
  for (int i = 1; i <= N - 1; ++i) {
    int A, B;
    cin >> A >> B;
    Edge[A].push_back(B);
    Edge[B].push_back(A);
  }
  for (int i = 1; i <= Q; ++i) {
    int A;
    cin >> A >> Arr[i];
    Queries[A].push_back(i);
    // Queries[A].push_back({i,B});
  }
  DFS(1, -1);
  for (int i = 1; i <= Q; ++i)
    cout << Ans[i] << endl;
  return 0;
}