#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  struct node {
    int nina = 0, emilija = 0;
    node *index[26];
  };

  node *root = new node();

  function<void(string, something)> fill = [&](string song, something) {
    return;
  };

  int n, m;
  cin >> n;
  vector<string> nina_songs(n);
  for (int i = 0; i < n; ++i) {
    cin >> nina_songs[i];
  }
  cin >> m;
  vector<string> emilija_songs(m);
  for (int i = 0; i < m; ++i) {
    cin >> emilija_songs[i];
  }
}