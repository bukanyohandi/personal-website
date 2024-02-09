#include <bits/stdc++.h>
using namespace std;
int N[70005], prefix[1000005], a, b;
bool ada[1000005];
int NOD(int x) {
  int ans = 1, piv;
  if (x % 2 == 0) {
    piv = 0;
    while (x % 2 == 0 && x > 0) {
      x /= 2;
      piv++;
    }
    ans *= (piv + 1);
  }
  for (int i = 3; i * i <= x; ++i) {
    if (x % i == 0) {
      piv = 0;
      while (x % i == 0 && x > 0) {
        x /= i;
        piv++;
      }
      ans *= (piv + 1);
    }
  }
  if (x > 1)
    return ans * 2;
  return ans;
}
int main() {
  int n, piv = 1;
  cin >> n;
  N[0] = 1;
  ada[1] = true;
  for (int i = 1; i <= 65000; ++i) {
    N[i] = N[i - 1] + NOD(N[i - 1]);
    ada[N[i]] = true;
  }
  for (int i = 1; i <= 1000000; ++i) {
    prefix[i] = prefix[i - 1];
    if (ada[i])
      prefix[i]++;
  }
  while (n--) {
    cin >> a >> b;
    cout << "Case " << piv << ": " << prefix[b] - prefix[a - 1] << endl;
    piv++;
  }
}