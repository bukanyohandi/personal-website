#include <bits/stdc++.h>
using namespace std;

int compute(int x) {
  if (x == 1)
    return 0;
  return x % 2 == 0 ? compute(x / 2) + 1 : compute(3 * x + 1) + 1;
}

int main() {
  int x, y, k;
  cin >> x >> y >> k;

  vector<pair<int, int>> vec;
  for (int i = x; i <= y; ++i) {
    vec.push_back({compute(i), i});
  }
  sort(vec.begin(), vec.end());
  cout << vec[k - 1].second << endl;
}