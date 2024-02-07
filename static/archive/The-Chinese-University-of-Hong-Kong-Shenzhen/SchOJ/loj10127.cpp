#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int m, p;
  cin >> m >> p;

  vector<int> tree(4 * m, 0);
  function<int(int, int, int, int, int)> query = [&](int low, int high, int pos,
                                                     int ql, int qr) {
    if (ql <= low && high <= qr)
      return tree[pos];
    if (low > qr || ql > high)
      return 0;
    int mid = (low + high) >> 1;
    return max(query(low, mid, 2 * pos + 1, ql, qr),
               query(mid + 1, high, 2 * pos + 2, ql, qr));
  };
  function<void(int, int, int, int, int)> update =
      [&](int low, int high, int pos, int x, int val) {
        if (low == high) {
          tree[pos] = val;
          return;
        }
        int mid = (low + high) >> 1;
        if (x <= mid) {
          update(low, mid, 2 * pos + 1, x, val);
        } else {
          update(mid + 1, high, 2 * pos + 2, x, val);
        }
        tree[pos] = max(tree[2 * pos + 1], tree[2 * pos + 2]);
        return;
      };

  int a = 0;
  int cnt = 0;
  for (int i = 0; i < m; ++i) {
    char op;
    int x;
    cin >> op >> x;

    if (op == 'A') {
      update(0, m - 1, 0, cnt++, (x + a) % p);
    } else {
      a = query(0, m - 1, 0, max(0, cnt - x), m - 1);
      cout << a << "\n";
    }
  }

  return 0;
}