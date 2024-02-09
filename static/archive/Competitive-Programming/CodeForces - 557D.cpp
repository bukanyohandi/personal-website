#include <bits/stdc++.h>
using namespace std;
int N, M, Count1, Count2;
int Visited[100001];
bool Found = 0;
long long Ans;
vector<int> Edge[100001];
void Solve(int Now, int Stat) {
  if (Visited[Now] != -1)
    return;
  Visited[Now] = Stat;
  if (Stat == 1)
    Count2++;
  else
    Count1++;
  for (auto i : Edge[Now])
    Solve(i, 1 - Stat);
}
void DFS(int Now, int Par) {
  if (Found)
    return;
  Visited[Now] = Visited[Par] + 1;
  for (auto i : Edge[Now]) {
    if (i == Par)
      continue;
    if (Visited[i]) {
      if ((Visited[Now] - Visited[i]) % 2 == 0) {
        Found = 1;
      }
    } else {
      DFS(i, Now);
    }
  }
  return;
}
int main() {
  cin >> N >> M;
  if (M == 0) {
    Ans = (long long)N * (N - 1) * (N - 2) / 3 / 2 / 1;
    cout << 3 << " " << Ans << endl;
    return 0;
  }
  for (int i = 1; i <= M; ++i) {
    int A, B;
    cin >> A >> B;
    Edge[A].push_back(B);
    Edge[B].push_back(A);
  }
  bool Ok = 1;
  for (int i = 1; i <= N && Ok; ++i) {
    if (Edge[i].size() >= 2)
      Ok = 0;
  }
  if (Ok) {
    Ans = (long long)N * M;
    cout << 2 << " " << Ans - 2 * M << endl;
    return 0;
  }
  DFS(1, 0);
  if (Found) {
    cout << 0 << " " << 1 << endl;
    return 0;
  }
  memset(Visited, -1, sizeof(Visited));
  for (int i = 1; i <= N; ++i) {
    if (Visited[i] == -1) {
      Count1 = Count2 = 0;
      Solve(i, 0);
      Ans += (long long)Count1 * (Count1 - 1) / 2 / 1;
      Ans += (long long)Count2 * (Count2 - 1) / 2 / 1;
    }
  }
  cout << 1 << " " << Ans << endl;
}