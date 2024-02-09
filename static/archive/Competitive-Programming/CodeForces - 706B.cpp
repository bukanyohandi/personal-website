#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int n, q;
  int arr[100005];
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> arr[i];
  sort(arr + 1, arr + 1 + n);
  cin >> q;
  for (int i = 0; i < q; i++) {
    int l = 0, r = n, ans = 0, x;
    cin >> x;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (arr[mid] <= x) {
        ans = mid;
        l = mid + 1;
      } else
        r = mid - 1;
    }
    cout << ans << endl;
  }
}