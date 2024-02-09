#include <bits/stdc++.h>
using namespace std;
int tmp, n, x, data[105], data2[105], piv1, piv2;
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> data[i];
  }
  sort(data + 1, data + 1 + n);
  tmp = n / 2;
  x = 1;
  piv1 = 1;
  piv2 = n;
  while (tmp > 0) {
    data2[piv1] = data[x];
    x++;
    data2[piv2] = data[x];
    x++;
    piv1++;
    piv2--;
    tmp--;
  }
  if (n % 2 == 1)
    data2[((n + 1) / 2)] = data[n];
  for (int i = 1; i <= n; ++i) {
    cout << data2[i];
    if (i != n)
      cout << " ";
    else
      cout << endl;
  }
}