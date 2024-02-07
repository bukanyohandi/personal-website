#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  set<int> st;
  vector<pair<int, int>> arr(n);
  for (auto &p : arr) {
    cin >> p.first >> p.second;
    st.insert(p.second);
  }
  sort(arr.begin(), arr.end());

  int le = 0;
  int ri = 0;
  int ans = INT_MAX;
  int cnt = (int)st.size();
  map<int, int> freq;
  while (ri < n) {
    while (ri < n && cnt > 0) {
      if (freq[arr[ri].second] == 0) {
        cnt--;
      }
      freq[arr[ri].second]++;
      ri++;
    }
    while (le < ri && cnt == 0) {
      ans = min(ans, arr[ri - 1].first - arr[le].first);
      freq[arr[le].second]--;
      if (freq[arr[le].second] == 0) {
        cnt++;
      }
      le++;
    }
  }
  cout << ans << endl;

  return 0;
}