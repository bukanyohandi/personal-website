#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define N 1000000;
using namespace std;
int data[500100];
ll swaps;
void merge(int p, int q, int r) {
  int len1 = q - p + 1, len2 = r - q;
  vector<int> left, right;
  for (int i = 0; i < len1; i++)
    left.pb(data[p + i]);
  for (int i = 0; i < len2; i++)
    right.pb(data[q + i + 1]);
  left.pb(999999999 + 10);
  right.pb(999999999 + 10);
  size_t x = 0;
  size_t y = 0;
  for (int k = p; k <= r; k++) {
    if (left[x] <= right[y])
      data[k] = left[x++];
    else {
      data[k] = right[y++];
      swaps += len1 - x;
    }
  }
}
void merge_sort(int p, int r) {
  if (p < r) {
    int q = (int)floor((p + r) / 2.0);
    merge_sort(p, q);
    merge_sort(q + 1, r);
    merge(p, q, r);
  }
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  while (scanf("%d", &n) && n) {
    swaps = 0;
    for (int i = 0; i < n; i++)
      scanf("%d", &data[i]);
    merge_sort(0, n - 1);
    cout << swaps << endl;
  }
  return 0;
}