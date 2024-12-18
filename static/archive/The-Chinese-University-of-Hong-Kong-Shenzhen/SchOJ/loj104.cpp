#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <class T> class OrderStatisticsTree {
private:
  typedef tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag,
               tree_order_statistics_node_update>
      OSTree;
  OSTree ost;
  int timestamp = 0;

public:
  OrderStatisticsTree() {}

  void insertVal(T val) { ost.insert({val, timestamp++}); }

  void deleteVal(T val) {
    auto it = ost.lower_bound({val, 0});
    if (it != ost.end() && it->first == val) {
      ost.erase(it);
    }
  }

  int queryRank(T val) { return ost.order_of_key({val, 0}); }

  T queryNumber(int rank) {
    auto it = ost.find_by_order(rank);
    if (it != ost.end()) {
      return it->first;
    }
    throw std::out_of_range("Rank is out of bounds");
  }

  T predecessor(T val) {
    auto it = ost.lower_bound({val, 0});
    if (it == ost.begin()) {
      throw std::out_of_range("No predecessor exists");
    }
    --it;
    return it->first;
  }

  T successor(T val) {
    auto it = ost.upper_bound({val, INT_MAX});
    if (it == ost.end()) {
      throw std::out_of_range("No successor exists");
    }
    return it->first;
  }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  OrderStatisticsTree<int> ost; // Use the Order Statistics Tree

  for (int i = 0; i < n; ++i) {
    int op, x;
    cin >> op >> x;

    if (op == 1) {
      ost.insertVal(x);
    } else if (op == 2) {
      ost.deleteVal(x);
    } else if (op == 3) {
      cout << ost.queryRank(x) + 1 << "\n";
    } else if (op == 4) {
      cout << ost.queryNumber(x - 1) << "\n";
    } else if (op == 5) {
      try {
        cout << ost.predecessor(x) << "\n";
      } catch (const std::out_of_range &) {
        cout << "No predecessor\n";
      }
    } else {
      try {
        cout << ost.successor(x) << "\n";
      } catch (const std::out_of_range &) {
        cout << "No successor\n";
      }
    }
  }

  return 0;
}
