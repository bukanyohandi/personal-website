#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  int q;
  cin >> q;

  auto find_row = [&](const vector<long long> &positions, int p) {
    int left = 0;
    int right = positions.size() - 1;
    while (left < right) {
      int mid = (left + right + 1) / 2;
      if (positions[mid] <= p) {
        left = mid;
      } else {
        right = mid - 1;
      }
    }
    return left;
  };

  vector<long long> prefix(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    prefix[i + 1] = prefix[i] + a[i];
  }

  vector<long long> cumulative(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    cumulative[i + 1] = cumulative[i] + prefix[i + 1];
  }

  vector<long long> positions(n + 1, 0);
  positions[0] = 0;
  for (int i = 0; i < n; ++i) {
    int len_i = n - i;
    positions[i + 1] = positions[i] + len_i;
  }

  vector<long long> sum_i(n, 0);
  for (int i = 0; i < n; ++i) {
    sum_i[i] = cumulative[n] - cumulative[i] - (n - i) * prefix[i];
  }

  vector<long long> cum_sum_i(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    cum_sum_i[i + 1] = cum_sum_i[i] + sum_i[i];
  }

  for (int _ = 0; _ < q; ++_) {
    int li, ri;
    cin >> li >> ri;
    --li;
    --ri;

    int i_l = find_row(positions, li);
    int i_r = find_row(positions, ri);

    long long total_sum = 0;
    if (i_l == i_r) {
      int offset_l = li - positions[i_l];
      int offset_r = ri - positions[i_l];
      int j_l = i_l + offset_l;
      int j_r = i_l + offset_r;
      total_sum =
          cumulative[j_r + 1] - cumulative[j_l] - (j_r - j_l + 1) * prefix[i_l];
    } else {
      int offset_l = li - positions[i_l];
      int j_l = i_l + offset_l;
      int j_r = n - 1;
      total_sum +=
          cumulative[j_r + 1] - cumulative[j_l] - (j_r - j_l + 1) * prefix[i_l];

      if (i_l + 1 <= i_r - 1) {
        total_sum += cum_sum_i[i_r] - cum_sum_i[i_l + 1];
      }

      int offset_r = ri - positions[i_r];
      int j_l_last = i_r;
      int j_r_last = i_r + offset_r;
      total_sum += cumulative[j_r_last + 1] - cumulative[j_l_last] -
                   (j_r_last - j_l_last + 1) * prefix[i_r];
    }
    cout << total_sum << '\n';
  }

  return 0;
}