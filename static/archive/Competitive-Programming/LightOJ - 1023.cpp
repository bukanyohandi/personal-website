#include <bits/stdc++.h>
using namespace std;
int n, k;
int arr[26];
bool vis[26];
void f(int now, int len) {
  if (k == 0)
    return;
  if (len == n) {
    k--;
    for (int i = 0; i < n; ++i) {
      printf("%c", arr[i] + 'A');
    }
    printf("\n");
    return;
  }
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      vis[i] = true;
      arr[len] = i;
      f(i, len + 1);
      vis[i] = false;
    }
  }
}
int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    printf("Case %d:\n", i + 1);
    scanf("%d %d", &n, &k);
    f(0, 0);
  }
}