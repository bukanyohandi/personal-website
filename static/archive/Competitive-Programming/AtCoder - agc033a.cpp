#include <bits/stdc++.h>
using namespace std;
int R, C, Time = -1, Piv, tmpx, tmpy;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
char grid[1005][1005];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> R >> C;
  queue<pair<int, int>> bfs;
  for (int i = 0; i <= R + 1; ++i) {
    for (int j = 0; j <= C + 1; ++j) {
      if (i == 0 || i == R + 1 || j == 0 || j == C + 1) {
        grid[i][j] = 'X';
        continue;
      }
      cin >> grid[i][j];
      if (grid[i][j] == '#')
        bfs.push({i, j});
    }
  }
  while (!bfs.empty()) {
    Piv = bfs.size();
    for (int i = 0; i < Piv; ++i) {
      tmpx = bfs.front().first;
      tmpy = bfs.front().second;
      bfs.pop();
      for (int j = 0; j < 4; ++j) {
        if (grid[tmpx + dx[j]][tmpy + dy[j]] == '.') {
          grid[tmpx + dx[j]][tmpy + dy[j]] = '#';
          bfs.push({tmpx + dx[j], tmpy + dy[j]});
        }
      }
    }
    Time++;
  }
  cout << Time << endl;
}