#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  struct node {
    node *index[2];
  };

  node *root = new node();

  function<void(int)> fill = [&](int x) {
    node *cur = root;
    for (int bit = 30; bit >= 0; --bit) {
      if (cur->index[(x >> bit) & 1] == NULL)
        cur->index[(x >> bit) & 1] = new node();
      cur = cur->index[(x >> bit) & 1];
    }
  };

  function<int(int)> query = [&](int x) {
    int ret = 0;
    node *cur = root;
    for (int bit = 30; bit >= 0; --bit) {
      if (cur->index[1 - ((x >> bit) & 1)] != NULL) {
        ret += (1 << bit);
        cur = cur->index[1 - ((x >> bit) & 1)];
      } else {
        cur = cur->index[(x >> bit) & 1];
      }
    }
    return ret;
  };

  int n;
  cin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
    fill(arr[i]);
  }

  int ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max(ans, query(arr[i]));
  }

  cout << ans << endl;

  return 0;
}
