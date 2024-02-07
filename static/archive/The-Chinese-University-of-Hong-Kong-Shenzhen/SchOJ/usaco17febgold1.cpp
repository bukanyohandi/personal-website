#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int N, T;
  cin >> N >> T;

  vector<vector<int>> grid(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> grid[i][j];
    }
  }

  int sz;
  vector<int> dx, dy;
  for (int delta_x = -3; delta_x <= 3; ++delta_x) {
    for (int delta_y = -3; delta_y <= 3; ++delta_y) {
      int range = abs(delta_x) + abs(delta_y);
      if (range == 1 || range == 3) {
        dx.push_back(delta_x);
        dy.push_back(delta_y);
      }
    }
  }
  sz = (int)dx.size();
  assert(sz == (int)dy.size());

  vector<long long> dist(N * N, INT_MAX);
  priority_queue<pair<long long, int>> pq;

  pq.push({0, 0});
  while (!pq.empty()) {
    pair<long long, int> pq_top = pq.top();
    pq.pop();

    long long cost = -pq_top.first;
    int u = pq_top.second;

    if (dist[u] < cost)
      continue;
    dist[u] = cost;

    int x = u / N;
    int y = u % N;

    int range = abs(x - N + 1) + abs(y - N + 1);
    if (range < 3) {
      dist[N * N - 1] =
          min(dist[N * N - 1], dist[x * N + y] + (long long)T * range);
      continue;
    }

    for (int k = 0; k < sz; ++k) {
      int nx = x + dx[k];
      int ny = y + dy[k];
      if (nx < 0 || nx >= N || ny < 0 || ny >= N)
        continue;

      long long ncost = cost + grid[nx][ny] + T * 3;
      if (dist[nx * N + ny] > ncost) {
        dist[nx * N + ny] = ncost;
        pq.push({-ncost, nx * N + ny});
      }
    }
  }

  cout << dist[N * N - 1] << endl;

  return 0;
}