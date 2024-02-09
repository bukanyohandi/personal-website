#include <bits/stdc++.h>
using namespace std;

int N, M;
int grid[405][405];
vector<pair<int, int>> possible_moves;

bool inrange(int x, int y) { return 1 <= x && x <= N && 1 <= y && y <= N; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> N >> M;
  for (int x = 0; x <= 1000; ++x) {
    for (int y = 0; y <= 1000; ++y) {
      if (x * x + y * y == M) {
        possible_moves.push_back(make_pair(x, y));
      }
    }
  }
  // for(int i = 0; i < possible_moves.size(); ++i){
  //     cout << possible_moves[i].first << " " << possible_moves[i].second <<
  //     endl;
  // }
  memset(grid, -1, sizeof(grid));
  queue<pair<int, int>> bfs;
  bfs.push(make_pair(1, 1));
  int len = 0;
  while (!bfs.empty()) {
    int sz = (int)bfs.size();
    for (int i = 0; i < sz; ++i) {
      int cx = bfs.front().first;
      int cy = bfs.front().second;
      bfs.pop();
      grid[cx][cy] = len;
      for (int j = 0; j < (int)possible_moves.size(); ++j) {
        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            if (abs(dx) + abs(dy) == 2 &&
                inrange(cx + dx * possible_moves[j].first,
                        cy + dy * possible_moves[j].second) &&
                grid[cx + dx * possible_moves[j].first]
                    [cy + dy * possible_moves[j].second] == -1) {
              bfs.push(make_pair(cx + dx * possible_moves[j].first,
                                 cy + dy * possible_moves[j].second));
            }
          }
        }
      }
    }
    len++;
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      if (j != 1) {
        cout << " ";
      }
      cout << grid[i][j];
    }
    cout << endl;
  }
}