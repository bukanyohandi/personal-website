#include <bits/stdc++.h>
using namespace std;

int main(){
    int tc, n;
    int x[200000 + 5];
    int xxor[200000 + 5];

    cin >> tc;
    for(int t = 0; t < tc; ++t){
        cin >> n;
        xxor[0] = 0;
        for(int i = 1; i <= n; ++i){
            cin >> x[i];
            xxor[i] = xxor[i - 1] ^ x[i];
        }
        if(xxor[n] == 0){
            cout << "second" << endl;
        } else {
            cout << "first" << endl;
        }
    }
}