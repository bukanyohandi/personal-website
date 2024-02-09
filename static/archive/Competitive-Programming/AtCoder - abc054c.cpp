#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define ll long long
#define ld long double
#define EPS 0.0000000001
#define INF 1e9
#define MOD 1000000007
#define rep(i, n) for (i = 0; i < n; i++)
#define loop(i, a, n) for (i = a; i < n; i++)
#define all(in) in.begin(), in.end()
#define shosu(x) fixed << setprecision(x)

typedef vector<int> vi;
typedef pair<int, int> pii;

int main(void) {
  int n, m;
  cin >> n >> m;
  int i;
  int path[10][10] = {};
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    path[a][b]++;
    path[b][a]++;
  }

  vi v;
  rep(i, n) v.push_back(i);

  int ans = 0;
  do {
    if (v[0] != 0)
      break;
    rep(i, n - 1) if (path[v[i]][v[i + 1]] == 0) break;
    if (i == n - 1)
      ans++;
  } while (next_permutation(all(v)));

  cout << ans << endl;
}