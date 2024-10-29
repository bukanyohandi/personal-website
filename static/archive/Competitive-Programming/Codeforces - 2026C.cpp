#include <bits/stdc++.h>
using namespace std;

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    long long n;
    cin >> n;

    string s;
    cin >> s;

    long long ans = 0, last = -1;
    bool stop = false;
    vector<bool> tag(n, false);
    deque<long long> dq;
    for (long long i = n - 1; i >= 0; --i) {
      if (s[i] == '1') {
        dq.push_back(i);
      } else {
        ans += i + 1;
        tag[i] = true;

        if (!dq.empty()) {
          tag[dq.front()] = true;
          dq.pop_front();
        }
      }
    }
    vector<long long> vt;
    for (long long i = 0; i < n; ++i) {
      if (!tag[i]) {
        vt.push_back(i);
      }
    }
    // cout << "[" << ans << endl;
    // for(auto x: vt) cout << x << " "; cout << endl;
    for (int i = 0; i < (vt.size() + 1) / 2; i++) {
      ans += vt[i] + 1;
    }

    cout << ans << endl;
  }
}