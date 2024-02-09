/*
    Author: Yohandi
    Problem Title: Military Squad Management
    Problem Link: http://oj.cuhk.edu.cn/problem/dda6050a4q32023fall
*/

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
  DisjointSet(int size)
      : parent(size + 1), size(size + 1, 1), offset(size + 1, 0) {
    for (int i = 0; i <= size; ++i) {
      parent[i] = i;
    }
  }

  function<int(int)> find = [&](int i) {
    if (i != parent[i]) {
      int old_parent = parent[i];
      parent[i] = find(parent[i]);
      offset[i] += offset[old_parent];
    }

    return parent[i];
  };

  function<void(int, int)> union_set = [&](int i, int j) {
    int root_i = find(i);
    int root_j = find(j);
    if (root_i != root_j) {
      parent[root_j] = root_i;
      offset[root_j] = size[root_i];
      size[root_i] += size[root_j];
    }

    return;
  };

  function<int(int, int)> count_between = [&](int i, int j) {
    if (find(i) == find(j)) {
      return abs(offset[i] - offset[j]) - 1;
    }

    return -1;
  };

private:
  vector<int> parent, size, offset;
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int T;
  cin >> T;

  DisjointSet disjoint_set(30000);
  for (int t = 0; t < T; ++t) {
    string operation;
    int i, j;

    cin >> operation >> i >> j;

    if (operation == "M") {
      disjoint_set.union_set(i, j);
    } else if (operation == "C") {
      cout << disjoint_set.count_between(i, j) << "\n";
    }
  }

  return 0;
}