#include <bits/stdc++.h>
using namespace std;

map<long long, long long> memo;

long long f(long long N) {
  if (N == 0)
    return 1;

  long long &ret = memo[N];
  if (ret != 0)
    return ret;

  return ret = f(N / 2) + f(N / 3);
}

int main() {
  long long N;
  cin >> N;

  cout << f(N) << endl;
}