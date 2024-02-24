/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

int n, prev;
int a[100005];
int tree[400005];

long long ans;

void build()
{
	memset(tree, 0, sizeof(tree));
}

void update(int low, int high, int pos, int x)
{
	if (low == high) {
		tree[pos]++;
		return;
	}
	int mid = (low + high) / 2;
	if (x <= mid) {
		update(low, mid, pos * 2, x);
	} else {
		update(mid + 1, high, pos * 2 + 1, x);
	}
	tree[pos] = tree[pos * 2] + tree[pos * 2 + 1];
}

int query(int low, int high, int pos, int ql, int qr)
{
	if (ql <= low && high <= qr) {
		return tree[pos];
	} else if (ql > high || qr < low) {
		return 0;
	} else {
		int mid = (low + high) / 2;
		return query(low, mid, pos * 2, ql, qr) +
		       query(mid + 1, high, pos * 2 + 1, ql, qr);
	}
}

void update(int x)
{
	return update(1, n, 1, x);
}

int query(int ql, int qr)
{
	return query(1, n, 1, ql, qr);
}

int main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	build();
	for (int i = 1; i <= n; ++i) {
		ans += query(a[i], n); // increase ans by sum of freq[a[i]..n]
		update(a[i]); // increase freq[a[i]] by 1
	}

	cout << ans << endl;
}