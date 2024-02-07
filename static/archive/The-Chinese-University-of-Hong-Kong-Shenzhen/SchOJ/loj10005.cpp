#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  priority_queue<int> pq_max, pq_min;
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;

    pq_max.push(x);
    pq_min.push(-x);
  }

  int dump;
  cin >> dump;

  while ((int)pq_max.size() > 1) {
    int x, y;

    x = pq_max.top();
    pq_max.pop();
    y = pq_max.top();
    pq_max.pop();

    pq_max.push(x * y + 1);

    x = -pq_min.top();
    pq_min.pop();
    y = -pq_min.top();
    pq_min.pop();

    pq_min.push(-(x * y + 1));
  }

  cout << -(pq_max.top() + pq_min.top()) << endl;

  return 0;
}