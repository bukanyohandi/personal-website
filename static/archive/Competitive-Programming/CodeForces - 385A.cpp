#include <algorithm>
#include <stdio.h>

using namespace std;

int main() {
  int gaps, i, j, n, c;
  scanf("%d %d", &n, &c);
  int data[n];
  for (i = 0; i < n; i++) {
    scanf("%d", &data[i]);
  }
  gaps = 0;
  for (i = 0; i < n - 1; i++) {
    if (gaps < (data[i] - data[i + 1])) {
      gaps = data[i] - data[i + 1];
    }
  }
  gaps = gaps - c;
  gaps = max(gaps, 0);
  printf("%d\n", gaps);
}