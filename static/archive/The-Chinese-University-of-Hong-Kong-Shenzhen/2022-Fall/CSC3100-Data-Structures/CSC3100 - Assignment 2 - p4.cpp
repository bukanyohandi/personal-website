/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

int n, S;
long long sum[500];
deque<int> dq[500];

void upd()
{
	for (int i = 0; i < S; ++i) {
		while ((int)dq[i].size() > S) {
			int val = dq[i].back();
			dq[i + 1].push_front(val);
			dq[i].pop_back();
			sum[i + 1] += val;
			sum[i] -= val;
		}
	}
	for (int i = 0; i < S; ++i) {
		while ((int)dq[i].size() < S && (int)dq[i + 1].size() > 0) {
			int val = dq[i + 1].front();
			dq[i].push_back(dq[i + 1].front());
			dq[i + 1].pop_front();
			sum[i] += val;
			sum[i + 1] -= val;
		}
	}

	return;
}

void ins(int pos, int val)
{
	int dq_pos = pos / S;

	stack<int> tmp;
	for (int i = 0; i < pos - (dq_pos * S); ++i) {
		tmp.push(dq[dq_pos].front());
		dq[dq_pos].pop_front();
	}
	dq[dq_pos].push_front(val);
	while (!tmp.empty()) {
		dq[dq_pos].push_front(tmp.top());
		tmp.pop();
	}

	sum[dq_pos] += val;

	upd();

	return;
}

void del(int pos)
{
	pos--;

	int dq_pos = pos / S;
	int val = 0;

	stack<int> tmp;
	for (int i = 0; i < pos - (dq_pos * S); ++i) {
		tmp.push(dq[dq_pos].front());
		dq[dq_pos].pop_front();
	}
	val = dq[dq_pos].front();
	dq[dq_pos].pop_front();
	while (!tmp.empty()) {
		dq[dq_pos].push_front(tmp.top());
		tmp.pop();
	}

	sum[dq_pos] -= val;

	upd();

	return;
}

long long calc(int r)
{
	if (r == 0)
		return 0;
	r--;

	int dq_pos = r / S;
	long long ret = 0;
	stack<int> tmp;

	for (int i = 0; i < dq_pos; ++i) {
		ret += sum[i];
	}

	for (int i = 0; i < r - (dq_pos * S) + 1; ++i) {
		tmp.push(dq[dq_pos].front());
		ret += tmp.top();
		dq[dq_pos].pop_front();
	}
	while (!tmp.empty()) {
		dq[dq_pos].push_front(tmp.top());
		tmp.pop();
	}

	return ret;
}

long long calc(int l, int r)
{
	return calc(r) - calc(l - 1);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	S = ceil(sqrt(n));

	for (int i = 0; i < n; ++i) {
		int op;
		cin >> op;
		if (op == 1) {
			int pos, val;
			cin >> pos >> val;
			ins(pos, val);
		} else if (op == 2) {
			int pos;
			cin >> pos;
			del(pos);
		} else if (op == 3) {
			int l, r;
			cin >> l >> r;
			cout << calc(l, r) << endl;
		}
	}
}