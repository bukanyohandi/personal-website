#include <bits/stdc++.h>
using namespace std;

vector<string> grid(9);

bool check(int hash) {
  int r = hash / 9;
  int c = hash % 9;
  return grid[r][c] == '#';
}

int dist(int a, int b) {
  int r1 = a / 9;
  int c1 = a % 9;
  int r2 = b / 9;
  int c2 = b % 9;

  return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

bool is_square(int aa, int bb, int cc, int dd) {
  int a, b, c, d;
  a = aa;
  b = bb;
  c = cc;
  d = dd;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
  a = aa;
  b = bb;
  c = dd;
  d = cc;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
  a = aa;
  b = cc;
  c = bb;
  d = dd;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
  a = aa;
  b = cc;
  c = dd;
  d = bb;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
  a = aa;
  b = dd;
  c = bb;
  d = cc;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
  a = aa;
  b = dd;
  c = cc;
  d = bb;
  if (dist(a, b) == dist(b, c) && dist(b, c) == dist(c, d) &&
      dist(c, d) == dist(d, a))
    return true;
}

int main() {
  for (int i = 0; i < 9; ++i) {
    cin >> grid[i];
  }

  int ans = 0;

  for (int a = 0; a < 81; ++a) {
    for (int b = a + 1; b < 81; ++b) {
      for (int c = b + 1; c < 81; ++c) {
        for (int d = c + 1; d < 81; ++d) {
          if (!check(a) || !check(b) || !check(c) || !check(d))
            continue;

          if (is_square(a, b, c, d) || is_square(b, a, c, d) ||
              is_square(c, a, b, d) || is_square(d, a, b, c))
            ans += 1;
        }
      }
    }
  }

  cout << ans << endl;
}