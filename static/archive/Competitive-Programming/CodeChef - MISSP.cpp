#include <bits/stdc++.h>
using namespace std;
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    int n, ans = 0;
    scanf("%d", &n);
    for (int j = 0; j < n; ++j) {
      int x;
      scanf("%d", &x);
      ans ^= x;
    }
    printf("%d\n", ans);
  }
}