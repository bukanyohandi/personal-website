#include <bits/stdc++.h>
using namespace std;

map<pair<int, int>, int> done;

int main() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int k;
    cin >> k;
    vector<int> v;
    for (int j = 0; j < k; ++j) {
      int x;
      cin >> x;
      v.push_back(x);
      //   cin >> v[i];
    }
    // cout << v[0] << " " << v[1] << endl;
    for (int j = 0; j < k; ++j) {
      for (int jj = j + 1; jj < k; ++jj) {
        done[make_pair(v[j], v[jj])] = true;
        // cout << v[j] << ", " << v[jj] << endl;
        // cout << "test" << endl;
      }
    }
    // cout << "done for " << i << endl;
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = i + 1; j <= N; ++j) {
      //   cout << "check for " << i << " " << j << endl;
      if (done[make_pair(i, j)] == false) {
        cout << "No" << endl;
        // cout << i << " " << j << endl;
        return 0;
      }
    }
  }

  cout << "Yes" << endl;
}