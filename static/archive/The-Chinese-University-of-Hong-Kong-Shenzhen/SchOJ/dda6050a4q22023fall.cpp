/*
    Author: Yohandi
    Problem Title: The Maximal Magical power
    Problem Link: http://oj.cuhk.edu.cn/problem/dda6050a4q22023fall
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  const int MAX_BIT = 17;

  struct node {
    node *next[2];
  };

  node *root = new node();

  function<void(int)> insert = [&](int element) {
    node *cur = root;
    for (int bit = MAX_BIT - 1; bit >= 0; --bit) {
      int alt = (element >> bit) & 1;
      if (cur->next[alt] == NULL) {
        cur->next[alt] = new node();
      }
      cur = cur->next[alt];
    }

    return;
  };

  function<int(int)> maximize = [&](int element) {
    int ret = 0;
    node *cur = root;
    for (int bit = MAX_BIT - 1; bit >= 0; --bit) {
      int alt = ((element >> bit) & 1) ^ 1;
      if (cur->next[alt] != NULL) {
        ret += (1 << bit);
        cur = cur->next[alt];
      } else {
        cur = cur->next[alt ^ 1];
      }
    }

    return ret;
  };

  int n;
  cin >> n;

  vector<int> arr(n);
  for (auto &element : arr) {
    cin >> element;

    insert(element);
  }

  int ans = 0;
  for (auto element : arr) {
    ans = max(ans, maximize(element));
  }

  cout << ans << "\n";

  return 0;
}