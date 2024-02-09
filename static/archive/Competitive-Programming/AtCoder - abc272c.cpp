#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> odd, even;
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    if (x % 2 == 1) {
      odd.push_back(x);
    } else {
      even.push_back(x);
    }
  }
  int ans = -1;
  if ((int)odd.size() >= 2) {
    sort(odd.begin(), odd.end());
    int sum = odd.back();
    odd.pop_back();
    sum += odd.back();
    ans = max(ans, sum);
  }
  if ((int)even.size() >= 2) {
    sort(even.begin(), even.end());
    int sum = even.back();
    even.pop_back();
    sum += even.back();
    ans = max(ans, sum);
  }
  cout << ans << endl;
}