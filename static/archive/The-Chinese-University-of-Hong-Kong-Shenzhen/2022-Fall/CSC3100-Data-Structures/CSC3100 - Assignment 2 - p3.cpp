/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

const int dx[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int power3[8];
char grid[2187][2187];

void fill(int cx, int cy, int k)
{
	if (k == 1) {
		for (int n = 0; n < 8; ++n) {
			grid[cx + dx[n]][cy + dy[n]] = '#';
		}
		grid[cx][cy] = ' ';
	} else {
		for (int n = 0; n < 8; ++n) {
			fill(cx + dx[n] * power3[k - 1],
			     cy + dy[n] * power3[k - 1], k - 1);
		}
		int len = power3[k - 1];
		for (int x = cx - (len / 2); x <= cx + (len / 2); ++x) {
			for (int y = cy - (len / 2); y <= cy + (len / 2); ++y) {
				grid[x][y] = ' ';
			}
		}
	}
}

int main()
{
	power3[0] = 1;
	for (int k = 1; k <= 7; ++k) {
		power3[k] = power3[k - 1] * 3;
	}

	int k;
	cin >> k;
	fill(power3[k] / 2, power3[k] / 2, k);
	for (int x = 0; x < power3[k]; ++x) {
		for (int y = 0; y < power3[k]; ++y) {
			cout << grid[x][y];
		}
		cout << endl;
	}
}