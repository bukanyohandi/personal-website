#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  vector<int> arr(n);
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  vector<int> odd, even;
  for (int i = 0; i < n; i++) {
    if (arr[i] % 2 == 0) {
      even.push_back(arr[i]);
    } else {
      odd.push_back(arr[i]);
    }
  }
  sort(odd.begin(), odd.end());
  sort(even.begin(), even.end());

  int oddIndex = 0, evenIndex = 0;
  for (int i = 0; i < n; ++i) {
    if (arr[i] % 2 == 0) {
      arr[i] = even[evenIndex++];
    } else {
      arr[i] = odd[oddIndex++];
    }
  }

  bool ans = true;
  for (int i = 0; i + 1 < n; ++i) {
    if (arr[i] > arr[i + 1]) {
      ans = false;
    }
  }

  cout << (ans ? "YES" : "NO") << endl;

  return 0;
}