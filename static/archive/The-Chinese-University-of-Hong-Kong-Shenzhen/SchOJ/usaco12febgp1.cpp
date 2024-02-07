#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  long long m;
  cin >> n >> k >> m;

  struct cow {
    int price;
    int discounted_price;
  };
  vector<cow> cows(n);
  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < n; ++i) {
    cin >> cows[i].price >> cows[i].discounted_price;
    pq.push({cows[i].discounted_price - cows[i].price, i});
  }
  sort(cows.begin(), cows.end(),
       [&](cow p, cow q) { return p.discounted_price < q.discounted_price; });

  vector<bool> consider;
  for (int i = 0; i < k; ++i) {
  }
  for (int i = k;)

    cout << cowsBought << endl;
}
