#include <bits/stdc++.h>
using namespace std;
int N, K, vis[5][55], R;
vector<pair<int, pair<int, int>>> Ans;
void gerak(int a, int b, int c, int d) {
  Ans.push_back({vis[a][b], {c, d}});
  vis[c][d] = vis[a][b];
  vis[a][b] = 0;
}
bool cek() {
  bool ret = false;
  R = 0;
  for (int i = 1; i <= N; ++i) {
    if (vis[2][i]) {
      R++;
      if (vis[2][i] == vis[1][i]) {
        gerak(2, i, 1, i);
        ret = true;
      }
    }
    if (vis[3][i]) {
      R++;
      if (vis[3][i] == vis[4][i]) {
        gerak(3, i, 4, i);
        ret = true;
      }
    }
  }
  return ret;
}
int main() {
  cin >> N >> K;
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= N; ++j)
      cin >> vis[i][j];
  if (K == N * 2 && !cek()) {
    cout << -1 << endl;
    return 0;
  }
  for (int i = N; i > 1; --i) {
    if (!vis[2][i] && vis[2][i - 1])
      gerak(2, i - 1, 2, i);
    if (!vis[3][i] && vis[3][i - 1])
      gerak(3, i - 1, 3, i);
  }
  if (vis[2][1] && !vis[3][1])
    gerak(2, 1, 3, 1);
  while (true) {
    cek();
    if (!R)
      break;
    for (int i = 2; i <= N; ++i)
      if (vis[2][i])
        gerak(2, i, 2, i - 1);
    if (vis[3][N])
      gerak(3, N, 2, N);
    for (int i = N - 1; i > 0; --i) {
      if (vis[3][i])
        gerak(3, i, 3, i + 1);
    }
    if (vis[2][1]) {
      if (vis[2][1] == vis[1][1])
        gerak(2, 1, 1, 1);
      else
        gerak(2, 1, 3, 1);
    }
  }
  cout << Ans.size() << endl;
  for (auto i : Ans) {
    cout << i.first << " " << i.second.first << " " << i.second.second << endl;
  }
}