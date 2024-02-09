#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
  if (n <= 1) {
    return false;
  }
  if (n <= 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }
  int limit = static_cast<int>(std::sqrt(n));
  for (int i = 5; i <= limit; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  int n;
  cin >> n;

  if (isPrime(n)) {
    cout << 1 << endl;
  } else if (n % 2 == 0 || isPrime(n - 2)) {
    cout << 2 << endl;
  } else {
    cout << 3 << endl;
  }
}