/*
    Author: Yohandi
    Date: 03/06/2022
    This is a demo for using the "fenwick_tree.hpp" header class.
    Problem link: https://www.spoj.com/problems/YODANESS/en/
*/

#include <assert.h>

#include <iostream>
#include <map>
#include <vector>
using namespace std;

template <class T> class FenwickTree {
public:
  FenwickTree() { __n = 0; }
  FenwickTree(int n) {
    assert(n >= 0);

    __n = n;
    BIT.resize(__n);
  }

  void add(int index, T val) {
    assert(0 <= index && index < __n);
    assert(zeroIsSet == true);

    for (++index; index <= __n; index += index & -index) {
      BIT[index - 1] += val;
    }

    return;
  }

  void clear() {
    fill(BIT.begin(), BIT.end(), zero);

    return;
  }

  T getZero() { return zero; }

  void resize(int n) {
    assert(n >= 0);

    __n = n;
    BIT.resize(n, zero);

    return;
  }

  void setZero(T val) {
    zero = val;
    zeroIsSet = true;

    return;
  }

  int size() { return __n; }

  T sum(int left, int right) {
    assert(0 <= left && left < right && right <= __n);
    assert(zeroIsSet == true);

    return sum(right) - sum(left);
  }

private:
  bool zeroIsSet;
  int __n;
  T zero;
  vector<T> BIT;

  T sum(int right) {
    T ret = zero;
    for (int index = right; index > 0; index -= index & -index) {
      ret += BIT[index - 1];
    }

    return ret;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string str[30000];
  map<string, int> pos;
  FenwickTree<int> tree(30000);

  tree.setZero(0);

  int tc, n, ans;
  cin >> tc;

  for (int t = 0; t < tc; ++t) {
    tree.clear();

    cin >> n;
    for (int i = 0; i < n; ++i) {
      cin >> str[i];
    }
    for (int i = 0; i < n; ++i) {
      string tmp;

      cin >> tmp;
      pos[tmp] = i;
    }

    ans = n * (n - 1) / 2;
    for (int i = 0; i < n; ++i) {
      ans -= tree.sum(0, pos[str[i]] + 1);
      tree.add(pos[str[i]], 1);
    }

    cout << ans << endl;
  }
}