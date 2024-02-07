#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> arr(N);
  for (auto &e : arr) {
    cin >> e;
  }

  vector<int> mines(N, -1);
  for (int i = 1; i < N - 1; ++i) {
    if (arr[i] == 3) {
      mines[i - 1] = 1;
      mines[i] = 1;
      mines[i + 1] = 1;
    }
  }

  return 0;
}