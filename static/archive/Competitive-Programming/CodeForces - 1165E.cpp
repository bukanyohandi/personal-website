/*
** The holy #include <bits/stdc++.h>
*/
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <time.h>
#include <vector>

#define endl '\n'
#define MOD 998244353
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
long long N, ans = 0, B[200005];
pair<long long, long long> A[200005];
int main() {
  //	boost();
  //	srand(time(NULL));
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i].first;
    A[i].first = (A[i].first * i) * (N - i + 1);
    A[i].second = i;
  }
  for (int i = 1; i <= N; ++i) {
    cin >> B[i];
  }
  sort(A + 1, A + 1 + N);
  sort(B + 1, B + 1 + N);
  for (int i = 1; i <= N; ++i) {
    ans = (ans % MOD + ((A[i].first % MOD) * B[N - i + 1]) % MOD) % MOD;
  }
  cout << ans % MOD << endl;
}