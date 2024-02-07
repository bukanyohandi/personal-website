#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0);
  cout.tie(0);

  int R, C;
  cin >> R >> C;
  getchar();

  vector<vector<short>> island(R, vector<short>(C, -1));
  vector<string> grid(R);
  for (int i = 0; i < R; ++i) {
    getline(cin, grid[i]);
    assert((int)grid[i].length() == C);
  }

  function<void(int, int, int)> floodfill = [&](int x, int y,
                                                int island_number) {
    if (x < 0 || x >= R || y < 0 || y >= C) {
      return;
    }
    if (grid[x][y] != 'X') {
      return;
    }
    if (island[x][y] == island_number) {
      return;
    }

    island[x][y] = island_number;
    floodfill(x + 1, y, island_number);
    floodfill(x - 1, y, island_number);
    floodfill(x, y + 1, island_number);
    floodfill(x, y - 1, island_number);

    return;
  };

  int islands = 0;
  for (int x = 0; x < R; ++x) {
    for (int y = 0; y < C; ++y) {
      if (grid[x][y] == 'X' && island[x][y] == -1) {
        floodfill(x, y, islands++);
      }
    }
  }

  vector<int> dx = {-1, 0, 1, 0}, dy = {0, -1, 0, 1};
  vector<vector<int>> costs(islands, vector<int>(islands, 100));
  for (int i = 0; i < islands; ++i) {
    queue<pair<int, int>> bfs;
    vector<vector<bool>> visited(R, vector<bool>(C, false));

    for (int x = 0; x < R; ++x) {
      for (int y = 0; y < C; ++y) {
        if (island[x][y] == i) {
          bfs.push(make_pair(x * C + y, 0));
        }
      }
    }

    while (!bfs.empty()) {
      pair<int, int> bfs_front = bfs.front();
      bfs.pop();

      int x = bfs_front.first / C;
      int y = bfs_front.first % C;
      int cost = bfs_front.second;

      for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx < 0 || nx >= R || ny < 0 || ny >= C) {
          continue;
        }
        if (grid[nx][ny] == 'S' && !visited[nx][ny]) {
          bfs.push(make_pair(nx * C + ny, cost + 1));
          visited[nx][ny] = true;
        } else if (grid[nx][ny] == 'X' && island[nx][ny] != i &&
                   costs[i][island[nx][ny]] == 100) {
          costs[i][island[nx][ny]] = cost;
        }
      }
    }
  }

  vector<vector<int>> memo(1 << islands, vector<int>(islands, -1));
  function<int(int, int)> tsp = [&](int mask, int last_island) -> int {
    if (mask == (1 << islands) - 1)
      return 0;

    int &ret = memo[mask][last_island];
    if (ret != -1)
      return ret;
    ret = 37501;

    for (int i = 0; i < islands; ++i) {
      if (i == last_island)
        continue;

      if ((mask >> i) & 1)
        ret = min(ret, tsp(mask, i) + costs[last_island][i]);
      else if (costs[last_island][i] != INT_MAX)
        ret = min(ret, tsp(mask | (1 << i), i) + costs[last_island][i]);
    }

    return ret;
  };

  int ans = INT_MAX;
  for (int i = 0; i < islands; ++i) {
    ans = min(ans, tsp(1 << i, i));
  }

  cout << ans << endl;

  return 0;
}