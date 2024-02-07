#include <bits/stdc++.h>
using namespace std;

template <class T, T (*op)(T, T)> class SparseTable {
public:
  SparseTable(vector<T> v) {
    __n = (int)v.size();

    table.push_back(v);
    for (int j = 1; (1 << j) <= __n; ++j) {
      vector<T> tmp(__n);

      for (int i = 0; (i + (1 << j) - 1) < __n; ++i) {
        tmp[i] = op(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
      }
      table.push_back(tmp);
    }
  }

  T query(int left, int right) {
    assert(0 <= left && left < right && right <= __n);

    int lg = (int)log2(right - left);
    return op(table[lg][left], table[lg][right - (1 << lg)]);
  }

private:
  int __n;
  vector<vector<T>> table;
};

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a < b ? b : a; }

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int N, K;
  cin >> N >> K;

  vector<int> arr(N);
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }

  SparseTable<int, min> min_table(arr);
  SparseTable<int, max> max_table(arr);

  for (int i = 0; i < N - K + 1; ++i) {
    if (i != 0)
      cout << " ";
    cout << min_table.query(i, i + K);
  }
  cout << endl;
  for (int i = 0; i < N - K + 1; ++i) {
    if (i != 0)
      cout << " ";
    cout << max_table.query(i, i + K);
  }

  return 0;
}