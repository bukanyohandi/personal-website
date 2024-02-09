#include <bits/stdc++.h>
using namespace std;
int prefix[105];
int main() {
  int tc, a, b;
  cin >> tc;
  for (int i = 1; i <= 100; ++i) {
    prefix[i] = prefix[i - 1];
    if (i % 2 == 1)
      prefix[i] += i;
  }
  for (int z = 1; z <= tc; ++z) {
    cin >> a >> b;
    cout << "Case " << z << ": " << prefix[b] - prefix[a - 1] << endl;
  }
}