#include <bits/stdc++.h>
using namespace std;
int N, K, Arr[100000];
priority_queue<int> PQ;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> N >> K;
  for (int i = 0; i < N; ++i) {
    cin >> Arr[i];
    PQ.push((K > 1 ? 1 : -1) * Arr[i]);
  }
  K == 2 ? cout << max(Arr[0], Arr[N - 1])
         : cout << ((K > 1) ? 1 : -1) * PQ.top() << '\n';
}