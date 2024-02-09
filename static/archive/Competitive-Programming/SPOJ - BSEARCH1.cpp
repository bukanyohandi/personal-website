#include <bits/stdc++.h>
using namespace std;
int N, Q, X, Idx;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> Q;
  vector<int> Vec(N);
  for (auto &i : Vec)
    cin >> i;
  for (int i = 1; i <= Q; i++) {
    cin >> X;
    Idx = lower_bound(Vec.begin(), Vec.end(), X) - Vec.begin();
    if (Vec[Idx] != X) {
      cout << -1 << endl;
    } else {
      cout << Idx << endl;
    }
  }
}