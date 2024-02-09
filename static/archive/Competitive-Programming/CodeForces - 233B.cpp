#include <iostream>
#include <math.h>
using namespace std;

int s(long long x) {
  int ret = 0;
  while (x > 0) {
    ret += (x % 10);
    x /= 10;
  }
  return ret;
}

int main() {
  long long n;
  long long start, end, x = -1;

  cin >> n;

  start = max(1LL, (long long)sqrt(n) - 90);
  end = (long long)sqrt(n);
  for (long long i = start; i <= end; ++i) {
    if (i * i + s(i) * i - n == 0) {
      x = i;
    }
  }

  cout << x << endl;
}