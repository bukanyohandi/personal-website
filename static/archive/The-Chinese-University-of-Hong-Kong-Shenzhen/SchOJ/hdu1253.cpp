#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int N, M, K, t;
  cin >> N >> M >> K >> t;

  vector<vector<vector<int>>> grid(N, vector<vector<int>>(M, vector<int>(K)));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      for (int k = 0; k < K; ++k) {
        cin >> grid[i][j][k];
      }
    }
  }

  if (grid[0][0][0] == 1) {
    cout << -1 << endl;
    return 0;
  }

  struct cell {
    int x, y, z;
  };
  queue<cell> bfs;
  bfs.push({N - 1, M - 1, K - 1});
  grid[N - 1][M - 1][K - 1] = 1;
  int ans = 0;
  bool found = false;
  while (!bfs.empty()) {
    int sz = bfs.size();
    for (int i = 0; i < sz; ++i) {
      cell cur = bfs.front();
      bfs.pop();

      if (cur.x == 0 && cur.y == 0 && cur.z == 0) {
        found = true;
        break;
      }

      for (int dx = -1; dx <= 1; ++dx) {
        if (cur.x + dx < 0 || cur.x + dx >= N)
          continue;
        if (grid[cur.x + dx][cur.y][cur.z] == 0) {
          bfs.push({cur.x + dx, cur.y, cur.z});
          grid[cur.x + dx][cur.y][cur.z] = 1;
        }
      }

      for (int dy = -1; dy <= 1; ++dy) {
        if (cur.y + dy < 0 || cur.y + dy >= M)
          continue;
        if (grid[cur.x][cur.y + dy][cur.z] == 0) {
          bfs.push({cur.x, cur.y + dy, cur.z});
          grid[cur.x][cur.y + dy][cur.z] = 1;
        }
      }

      for (int dz = -1; dz <= 1; ++dz) {
        if (cur.z + dz < 0 || cur.z + dz >= K)
          continue;
        if (grid[cur.x][cur.y][cur.z + dz] == 0) {
          bfs.push({cur.x, cur.y, cur.z + dz});
          grid[cur.x][cur.y][cur.z + dz] = 1;
        }
      }
    }
    if (found)
      break;
    ans++;
  }

  if (ans > t)
    ans = -1;
  if (grid[0][0][0] == 0)
    ans = -1;

  cout << ans << endl;
  return 0;
}