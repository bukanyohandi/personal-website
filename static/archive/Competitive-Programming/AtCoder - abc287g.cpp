#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define int long long

struct item {
  int kind, score, quota;
};

int N, S;
int block_size;
vector<int> location;

int sum[500], sum_quota[500];
deque<item> dq[500];

vector<item> vectorize(deque<item> &dq) {
  stack<item> st;
  vector<item> ret;

  while (!dq.empty()) {
    ret.push_back(dq.front());
    st.push(dq.front());
    dq.pop_front();
  }

  while (!st.empty()) {
    dq.push_front(st.top());
    st.pop();
  }

  return ret;
}

deque<item> dequerize(vector<item> &v) {
  deque<item> dq;
  for (int i = 0; i < (int)v.size(); ++i) {
    dq.push_back(v[i]);
  }
  return dq;
}

item remove(deque<item> &dq, int kind) {
  item ret;
  stack<item> st;

  for (int i = 0; i < (int)dq.size(); ++i) {
    if (dq.front().kind == kind) {
      ret = dq.front();
      dq.pop_front();
      continue;
    }
    st.push(dq.front());
    dq.pop_front();
  }

  while (!st.empty()) {
    dq.push_front(st.top());
    st.pop();
  }

  return ret;
}

void remerge() {
  for (int i = 0; i + 1 < S; ++i) {
    while ((int)dq[i].size() < block_size && (int)dq[i + 1].size() > 0) {
      dq[i].push_back(dq[i + 1].front());
      dq[i + 1].pop_front();

      sum[i] += dq[i].back().score * dq[i].back().quota;
      sum[i + 1] -= dq[i].back().score * dq[i].back().quota;

      sum_quota[i] += dq[i].back().quota;
      sum_quota[i + 1] -= dq[i].back().quota;

      location[dq[i].back().kind] = i;
    }
  }
  for (int i = 0; i + 1 < S; ++i) {
    while ((int)dq[i].size() > block_size) {
      dq[i + 1].push_front(dq[i].back());
      dq[i].pop_back();

      sum[i + 1] += dq[i + 1].front().score * dq[i + 1].front().quota;
      sum[i] -= dq[i + 1].front().score * dq[i + 1].front().quota;

      sum_quota[i + 1] += dq[i + 1].front().quota;
      sum_quota[i] -= dq[i + 1].front().quota;

      location[dq[i + 1].front().kind] = i + 1;
    }
  }

  return;
}

void print(int pos) {
  //   cerr << "printing " << dq[pos].size() << endl;
  //   vector<item> v = vectorize(dq[pos]);
  //   for (int i = 0; i < (int)v.size(); ++i) {
  //     cerr << "type " << v[i].kind << ": (" << v[i].score << ", " <<
  //     v[i].quota
  //          << ")" << endl;
  //   }

  return;
}

void set_score(int x, int y) {
  item cur;

  if (location[x] == -1) {
    cur.kind = x;
    cur.score = y;
    cur.quota = 0;
  } else {
    cur = remove(dq[location[x]], x);
    sum[location[x]] -= cur.score * cur.quota;
    sum_quota[location[x]] -= cur.quota;
    cur.score = y;

    remerge();
  }

  for (int i = 0; i < S; ++i) {
    if (dq[i].size() == block_size && dq[i].back().score > cur.score)
      continue;

    stack<item> st;
    while (!dq[i].empty() && dq[i].back().score < cur.score) {
      st.push(dq[i].back());
      dq[i].pop_back();
    }

    dq[i].push_back(cur);
    location[x] = i;
    sum[location[x]] += cur.score * cur.quota;
    sum_quota[location[x]] += cur.quota;

    while (!st.empty()) {
      dq[i].push_back(st.top());
      st.pop();
    }

    remerge();

    return;
  }

  return;
}

void set_quota(int x, int y) {
  if (location[x] == -1) {
    return;
  }

  vector<item> v = vectorize(dq[location[x]]);
  for (int i = 0; i < (int)v.size(); ++i) {
    if (v[i].kind == x) {
      sum[location[x]] += v[i].score * (y - v[i].quota);
      sum_quota[location[x]] += y - v[i].quota;

      v[i].quota = y;

      dq[location[x]] = dequerize(v);

      remerge();

      return;
    }
  }

  return;
}

int max_score(int cards) {
  int ans = 0, pos = 0;
  while (cards != 0 && cards >= sum_quota[pos]) {
    ans += sum[pos];
    cards -= sum_quota[pos];
    pos++;
  }

  vector<item> v = vectorize(dq[pos]);
  for (int i = 0; i < (int)v.size(); ++i) {
    if (cards == 0)
      break;

    int take = min(cards, v[i].quota);
    ans += v[i].score * take;
    cards -= take;
  }

  if (cards != 0)
    return -1;
  return ans;
}

signed main() {
  int Q;
  vector<int> a, b;

  cin >> N;
  S = (int)sqrt(N) + 1;
  block_size = (N + S - 1) / S;
  a.resize(N);
  b.resize(N);
  location.resize(N, -1);

  for (int i = 0; i < N; ++i) {
    cin >> a[i] >> b[i];
  }
  for (int i = 0; i < N; ++i) {
    set_score(i, a[i]);
  }
  for (int i = 0; i < N; ++i) {
    set_quota(i, b[i]);
  }

  print(0);
  print(1);

  cin >> Q;
  for (int i = 0; i < Q; ++i) {
    int op, x, y;
    cin >> op;
    if (op == 1) {
      cin >> x >> y;
      set_score(x - 1, y);
    } else if (op == 2) {
      cin >> x >> y;
      set_quota(x - 1, y);
    } else if (op == 3) {
      cin >> x;
      cout << max_score(x) << endl;
    }
  }

  return 0;
}