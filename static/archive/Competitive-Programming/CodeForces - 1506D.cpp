#include <iostream>
#include <map>
#include <queue>
using namespace std;

int testcases, n;
int a[262144];

int solve() {
  int ret = n;
  pair<int, int> p1, p2;
  map<int, int> frequency;
  priority_queue<pair<int, int>> pq;

  for (int i = 0; i < n; ++i) {
    frequency[a[i]] += 1;
  }
  for (pair<int, int> pr : frequency) {
    pq.push({pr.second, pr.first});
  }

  while (pq.size() > 1) {
    p1 = pq.top();
    pq.pop();
    p2 = pq.top();
    pq.pop();
    p1.first -= 1;
    p2.first -= 1;
    ret -= 2;
    if (p1.first > 0)
      pq.push(p1);
    if (p2.first > 0)
      pq.push(p2);
  }

  return ret;
}

int main() {
  cin >> testcases;
  for (int t = 0; t < testcases; ++t) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    cout << solve() << endl;
  }
}