#include <bits/stdc++.h>
using namespace std;

const int MAXL = 100;
const int MAXW = 100;
const int MAXH = 100;

char grid[MAXL][MAXW][MAXH];
bool visited[MAXL][MAXW][MAXH];

struct point {
  int x, y, z;
};

int l, w, h;

bool inRange(point p) {
  return p.x >= 0 && p.y >= 0 && p.z >= 0 && p.x < l && p.y < w && p.z < h;
}

char toChar(point p) { return grid[p.x][p.y][p.z]; }

bool isVisited(point p) { return visited[p.x][p.y][p.z]; }

void toggle(point p) { visited[p.x][p.y][p.z] ^= true; }

point toPoint(int x, int y, int z) {
  point tmp;

  tmp.x = x;
  tmp.y = y;
  tmp.z = z;

  return tmp;
}

bool comparePoints(point p, point q) {
  return p.x == q.x && p.y == q.y && p.z == q.z;
}

int main() {
  while (cin >> l >> w >> h) {
    if (l == 0 && w == 0 && h == 0)
      continue;

    point S;
    point E;

    for (int k = 0; k < h; ++k) {
      for (int i = 0; i < l; ++i) {
        for (int j = 0; j < w; ++j) {
          cin >> grid[i][j][k];
          visited[i][j][k] = false;

          if (grid[i][j][k] == 'S') {
            S = toPoint(i, j, k);
          }
          if (grid[i][j][k] == 'E') {
            E = toPoint(i, j, k);
          }
        }
      }
    }

    int ans = -1;
    int steps = 0;

    queue<point> bfs;

    bfs.push(S);
    toggle(S);
    while (!bfs.empty()) {
      int sz = (int)bfs.size();

      for (int i = 0; i < sz; ++i) {
        point u = bfs.front();
        bfs.pop();

        // cerr << u.x << " " << u.y << " " << u.z << endl;

        if (comparePoints(u, E)) {
          ans = steps;
          //   cerr << "E is found after " << steps << " steps" << endl;
          break;
        }

        for (int dx = -1; dx <= 1; ++dx) {
          for (int dy = -1; dy <= 1; ++dy) {
            if (abs(dx) + abs(dy) != 1)
              continue;

            point v;
            v.x = u.x + dx;
            v.y = u.y + dy;
            v.z = u.z;

            // cerr << "Try " << v.x << " " << v.y << " " << v.z << endl;

            if (inRange(v) && isVisited(v) == false && toChar(v) != '#') {
              bfs.push(v);
              toggle(v);

              //   cerr << "Proceed" << endl;
            }
          }
        }

        for (int dz = -1; dz <= 1; ++dz) {
          if (toChar(u) != '-')
            continue;
          if (abs(dz) != 1)
            continue;

          point v;
          v.x = u.x;
          v.y = u.y;
          v.z = u.z + dz;

          if (inRange(v) && isVisited(v) == false && toChar(v) == '-') {
            bfs.push(v);
            toggle(v);
          }
        }
      }

      steps++;
    }

    cout << ans << endl;
  }
}