#include <iostream>
using namespace std;

long long n, l, r;
long long ans, size;

int log2(long long n) {
  int ret = 0;
  while (n > 0) {
    ret += 1;
    n /= 2;
  }
  return ret - 1;
}

bool isOne(long long n, long long le, long long ri, long long pos) {
  if (le > ri)
    return false;
  long long mid = (le + ri) / 2;
  if (pos < mid) {
    return isOne(n / 2, le, mid - 1, pos);
  } else if (pos == mid) {
    return (n % 2 == 1);
  } else {
    return isOne(n / 2, mid + 1, ri, pos);
  }
}

int main() {
  cin >> n >> l >> r;

  size = ((long long)1 << (log2(n) + 1)) - 1;
  for (long long i = l; i < r + 1; ++i) {
    if (isOne(n, 1, size, i)) {
      ans += 1;
    }
  }

  cout << ans << endl;
}