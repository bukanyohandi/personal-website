#include <bits/stdc++.h>
using namespace std;

const int MAXN = 131072;

int a[MAXN + 5], tree[4 * MAXN + 5];

void build(int low, int high, int pos) {
  if (low == high) {
    tree[pos] = a[low];
    return;
  }

  int level = log2(high - low + 1) - 1;
  int mid = (low + high) / 2;
  build(low, mid, 2 * pos);
  build(mid + 1, high, 2 * pos + 1);
  if (level % 2 == 0) {
    tree[pos] = tree[2 * pos] | tree[2 * pos + 1];
  } else {
    tree[pos] = tree[2 * pos] ^ tree[2 * pos + 1];
  }
}

void update(int low, int high, int pos, int p, int b) {
  if (low == high) {
    tree[pos] = b;
    return;
  }

  int level = log2(high - low + 1) - 1;
  int mid = (low + high) / 2;
  if (p <= mid) {
    update(low, mid, 2 * pos, p, b);
  } else {
    update(mid + 1, high, 2 * pos + 1, p, b);
  }

  if (level % 2 == 0) {
    tree[pos] = tree[2 * pos] | tree[2 * pos + 1];
  } else {
    tree[pos] = tree[2 * pos] ^ tree[2 * pos + 1];
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < (1 << n); ++i) {
    cin >> a[i + 1];
  }

  build(1, 1 << n, 1);
  for (int i = 0; i < m; ++i) {
    int p, b;
    cin >> p >> b;
    update(1, 1 << n, 1, p, b);
    cout << tree[1] << endl;
  }
}