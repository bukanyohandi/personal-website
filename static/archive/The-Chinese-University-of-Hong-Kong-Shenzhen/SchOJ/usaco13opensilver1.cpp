#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0);
  cout.tie(0);

  int N, M;
  cin >> N >> M;
  getchar();

  int Cx = -1, Cy = -1, Dx = -1, Dy = -1;
  vector<string> grid(N);
  for (int i = 0; i < N; ++i) {
    getline(cin, grid[i]);
    assert((int)grid[i].length() == M);

    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == 'C') {
        Cx = i;
        Cy = j;
      } else if (grid[i][j] == 'D') {
        Dx = i;
        Dy = j;
      }
    }
  }

  assert(Cx != -1);
  assert(Cy != -1);
  assert(Dx != -1);
  assert(Dy != -1);

  struct position {
    int x, y;
    bool direction;
  };

  function<int(position)> hash = [&](position value) {
    return (value.x * M + value.y) * 2 + value.direction;
  };
  function<position(int)> inv_hash = [&](int hash_value) {
    position ret;
    ret.x = (hash_value / 2) / M;
    ret.y = (hash_value / 2) % M;
    ret.direction = hash_value % 2;
    return ret;
  };

  int dx[] = {1, -1};
  function<position(position)> fall = [&](position current) {
    int x = current.x;
    int y = current.y;
    bool direction = current.direction;

    if (x == Dx && y == Dy)
      return current;

    position ret;
    ret.x = -1;
    ret.y = y;
    ret.direction = direction;

    if (x == 0 && direction == 1)
      return ret;
    if (x == N - 1 && direction == 0)
      return ret;

    ret.x = x;
    if (grid[x + dx[(int)direction]][y] == '#')
      return ret;

    ret.x += dx[(int)direction];
    return fall(ret);
  };

  queue<int> bfs;
  vector<int> dist(N * M * 2, INT_MAX);

  position C;
  C.x = Cx;
  C.y = Cy;
  C.direction = false;
  C = fall(C);

  if (C.x != -1) {
    bfs.push(hash(C));
    dist[hash(C)] = 0;
  }
  while (!bfs.empty()) {
    int bfs_front = bfs.front();
    bfs.pop();

    position current;

    current = inv_hash(bfs_front);
    if (current.y - 1 >= 0 && grid[current.x][current.y - 1] != '#') {
      current.y -= 1;
      current = fall(current);
      if (current.x != -1 && dist[hash(current)] == INT_MAX) {
        dist[hash(current)] = dist[bfs_front];
        bfs.push(hash(current));
      }
    }

    current = inv_hash(bfs_front);
    if (current.y + 1 < M && grid[current.x][current.y + 1] != '#') {
      current.y += 1;
      current = fall(current);
      if (current.x != -1 && dist[hash(current)] == INT_MAX) {
        dist[hash(current)] = dist[bfs_front];
        bfs.push(hash(current));
      }
    }

    current = inv_hash(bfs_front);
    current.direction ^= true;
    current = fall(current);
    if (current.x != -1 && dist[hash(current)] == INT_MAX) {
      dist[hash(current)] = dist[bfs_front] + 1;
      bfs.push(hash(current));
    }
  }

  position D1, D2;
  D1.x = Dx;
  D1.y = Dy;
  D1.direction = false;
  D2.x = Dx;
  D2.y = Dy;
  D2.direction = true;

  int ans = min(dist[hash(D1)], dist[hash(D2)]);
  if (ans == INT_MAX)
    ans = -1;
  cout << ans << endl;

  return 0;
}