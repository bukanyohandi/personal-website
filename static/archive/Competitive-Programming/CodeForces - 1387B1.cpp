#include <bits/stdc++.h>
using namespace std;
int N, A, B, Log;
int Tag[100005], P[100005], Pos[100005], Depth[100005];
int Par[100005][21];
vector<int> Ans;
vector<int> Edge[100005], inDepth[100005];
void DFS(int Now, int Par) {
  P[Now] = Par;
  Depth[Now] = Depth[Par] + 1;
  inDepth[Depth[Now]].push_back(Now);
  for (auto i : Edge[Now]) {
    if (i != Par) {
      DFS(i, Now);
    }
  }
  return;
}
void Build() {
  P[1] = 1;
  memset(Par, -1, sizeof(Par));
  for (int i = 1; i <= N; ++i)
    Par[i][0] = P[i];
  for (int j = 1; j <= Log; ++j) {
    for (int i = 1; i <= N; ++i) {
      if (Par[i][j - 1] != -1 && Par[Par[i][j - 1]][j - 1] != -1) {
        Par[i][j] = Par[Par[i][j - 1]][j - 1];
      }
    }
  }
  return;
}
int Ancestor(int U, int Diff) {
  for (int j = Log; j >= 0; --j) {
    if (Diff & (1 << j)) {
      U = Par[U][j];
    }
  }
  return U;
}
int LCA(int U, int V) {
  if (Depth[U] < Depth[V])
    swap(U, V);
  U = Ancestor(U, Depth[U] - Depth[V]);
  if (U == V)
    return U;
  for (int j = Log; j >= 0; --j) {
    if (Par[U][j] != Par[V][j]) {
      U = Par[U][j];
      V = Par[V][j];
    }
  }
  return P[U];
}
int Dis(int U, int V) { return Depth[U] + Depth[V] - 2 * Depth[LCA(U, V)]; }
int Cost() {
  int Ret = 0;
  for (int i = 0; i < Ans.size(); ++i) {
    if (Ans[i] == i + 1) {
      return -1;
    }
  }
  for (int i = 0; i < Ans.size(); ++i) {
    Pos[Ans[i]] = i;
  }
  for (int i = 1; i <= N; ++i) {
    if (Ans[i - 1] != i) {
      Ret += Dis(Ans[i - 1], i);
      swap(Pos[Ans[i - 1]], Pos[i]);
    }
  }
  return Ret;
}
int main() {
  cin >> N;
  Log = log2(N);
  for (int i = 1; i <= N; ++i)
    Tag[i] = i;
  for (int i = 1; i <= N - 1; ++i) {
    cin >> A >> B;
    Edge[A].push_back(B);
    Edge[B].push_back(A);
  }
  DFS(1, 0);
  Build();
  for (int i = N; i >= 2; --i) {
    for (auto j : inDepth[i]) {
      if (Tag[j] == j) {
        swap(Tag[j], Tag[P[j]]);
      }
    }
  }
  if (Tag[1] == 1)
    swap(Tag[1], Tag[inDepth[2][0]]);
  for (int i = 1; i <= N; ++i)
    Ans.push_back(Tag[i]);
  cout << Cost() << endl;
  for (auto i : Ans)
    cout << i << " ";
  cout << endl;
}