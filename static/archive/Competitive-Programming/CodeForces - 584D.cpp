#include <cmath>
#include <iostream>
#include <vector>

bool is_prime(int n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }
  return true;
}

std::vector<int> three_prime_sum(int n) {
  std::vector<int> primes;

  // If n is already a prime number
  if (is_prime(n)) {
    primes.push_back(n);
    return primes;
  }

  if (n % 2 == 0) {
    // n is even, subtract 2 still make it even
    n -= 2;
    primes.push_back(2);
  } else {
    // n is odd, subtract 3 to make it even
    n -= 3;
    primes.push_back(3);
  }

  // Now n is even, use Goldbach's Conjecture to find two primes that sum up to
  // n
  for (int i = 2; i <= n / 2; ++i) {
    if (is_prime(i) && is_prime(n - i)) {
      primes.push_back(i);
      primes.push_back(n - i);
      break;
    }
  }

  return primes;
}

int main() {
  int n;
  std::cin >> n;

  if (n == 4) {
    std::cout << "2\n2 2\n";
    return 0;
  }

  std::vector<int> primes = three_prime_sum(n);
  std::cout << (int)primes.size() << std::endl;
  for (int prime : primes) {
    std::cout << prime << " ";
  }
  std::cout << std::endl;

  return 0;
}
