#include <iostream>
using namespace std;

long long data[200005] = {};

int main() {
  long long i, maj = 0, mij = 0, g, ma, mi, owhhi, n;
  cin >> n;
  cin >> data[0];
  mi = data[0];
  ma = data[0];
  for (i = 1LL; i < n; i++) {
    cin >> data[i];
    ma = max(ma, data[i]);
    mi = min(mi, data[i]);
  }
  g = ma - mi;
  for (i = 0LL; i < n; i++) {
    if (data[i] == ma) {
      maj++;
    } else if (data[i] == mi) {
      mij++;
    }
  }
  if (ma == mi) {
    maj = n * (n - 1) / 2;
  } else {
    maj = maj * mij;
  }
  cout << g << " " << maj << endl;
  return 0;
}