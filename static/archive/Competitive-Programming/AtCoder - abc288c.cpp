#include <bits/stdc++.h>
using namespace std;

int N, M;
int P[200005];

int find(int x) {
  if (P[x] == x)
    return x;
  return P[x] = find(P[x]);
}

int main() {
  cin >> N >> M;
  for (int i = 1; i <= N; ++i) {
    P[i] = i;
  }

  int ans = 0;
  for (int i = 0; i < M; ++i) {
    int A, B;
    cin >> A >> B;
    if (find(A) == find(B)) {
      ans++;
    } else {
      P[find(A)] = find(B);
    }
  }

  cout << ans << endl;
}