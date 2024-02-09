#include <bits/stdc++.h>
using namespace std;

int main() {
  int r, c;
  cin >> r >> c;

  vector<vector<char>> b(r, vector<char>(c));
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      cin >> b[i][j];
    }
  }
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if (b[i][j] == '.' || b[i][j] == '#')
        continue;

      int p = b[i][j] - '0';
      for (int k = 0; k < r; ++k) {
        for (int l = 0; l < c; ++l) {
          if (abs(i - k) + abs(j - l) <= p && b[k][l] == '#') {
            b[k][l] = '.';
          }
        }
      }
      b[i][j] = '.';
    }
  }

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      cout << b[i][j];
    }
    cout << endl;
  }
}