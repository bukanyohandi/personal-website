#include <bits/stdc++.h>
using namespace std;

int main() {
  int tc;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    int n;
    cin >> n;

    vector<long long> v(n);
    for (auto &e : v) {
      cin >> e;
    }

    if (n == 1) {
      cout << 1 << endl;
      continue;
    }

    long long k = 1e18;
    if (n % 2 == 1) {
      for (int i = 0; i < n; ++i) {
        vector<long long> arr;
        arr.clear();
        for (int j = 0; j < n; ++j) {
          if (j != i) {
            arr.push_back(v[j]);
          }
        }
        long long mx = -1;
        for (int j = 0; j < n - 1; j += 2) {
          long long tmp = arr[j + 1] - arr[j];
          mx = max(mx, tmp);
        }
        k = min(k, mx);
      }
    } else {
      // for(int i = 0; i < n - 1; ++i){
      long long mx = -1;
      for (int j = 0; j < n; j += 2) {
        long long tmp = v[j + 1] - v[j];
        // if(j == i){
        //     tmp = (v[j + 1] - v[j] + 1) / 2;
        // }
        mx = max(mx, tmp);
      }
      k = min(k, mx);
      // }
    }

    cout << k << endl;
  }
}