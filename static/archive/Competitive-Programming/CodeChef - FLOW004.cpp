#include <stdio.h>
int main() {
  int tc;
  scanf("%d", &tc);
  for (int t = 1; t <= tc; ++t) {
    int n, ans = 0;
    scanf("%d", &n);
    ans = n % 10;
    while (n > 9) {
      n /= 10;
    }
    printf("%d\n", ans + n);
  }
}