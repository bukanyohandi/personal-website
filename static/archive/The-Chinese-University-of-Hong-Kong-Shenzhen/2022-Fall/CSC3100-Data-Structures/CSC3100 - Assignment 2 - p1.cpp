/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

string representation(int n)
{
	string ret = "";

	if (n == 0 || n == 2) {
		ret.push_back((char)('0' + n));
	} else {
		for (int i = 29; i >= 0; --i) {
			if (n & (1 << i)) {
				if (ret != "")
					ret += "+";
				if (i == 1) {
					ret += "2";
				} else {
					ret += "2(" + representation(i) + ")";
				}
			}
		}
	}

	return ret;
}

int main()
{
	int n;
	cin >> n;

	cout << representation(n) << endl;
}