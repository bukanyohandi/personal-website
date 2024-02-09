#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> v(N);
  int ans = 0;
  for (int i = 0; i < N; ++i) {
    cin >> v[i];
    ans += v[i];
  }
  cout << ans << endl;
}