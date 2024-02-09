#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0);
    cout.tie(0);

    vector<int> a;

    int i = 0;
    while (cin >> i) {
        a.push_back(i);
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    int step;
    cin >> step;

    int ans = 0;
    map<int, int> lst;
    for(int i = 0; i < a.size(); ++i){
        lst[a[i]] = max(lst[a[i]], lst[a[i] - step] + 1);
        ans = max(ans, lst[a[i]]);
    }

    cout << ans << "\n";
}