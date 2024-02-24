/*
    Author: Yohandi - 120040025
*/

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k, val;
    vector<int> a;
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;

    cin >> n >> k;
    for(int i = 0; i < 2 * k; ++i){
        cin >> val;
        a.push_back(val);
    }

    sort(a.begin(), a.end());
    for(int i = 0; i < 2 * k; ++i){
        if(i < k){
            low.push(a[i]);
        } else {
            high.push(a[i]);
        }
    }

    for(int i = 0; i < n; ++i){
        int op;
        cin >> op;
        if(op == 1){
            int w;
            cin >> w;

            if(low.size() > high.size()){
                high.push(w);
            } else {
                low.push(w);
            }

            while(high.top() < low.top()){
                int a = high.top();
                int b = low.top();
                high.pop();
                low.pop();
                high.push(b);
                low.push(a);
            }
        } else if(op == 2){
            vector<int> tmp, result(2 * k);
            for(int j = 0; j < k; ++j){
                result[k - j - 1] = low.top();
                tmp.push_back(low.top());
                low.pop();
            }

            for(int j = 0; j < k; ++j){
                low.push(tmp[j]);
            }

            tmp.clear();

            for(int j = 0; j < k; ++j){
                result[k + j] = high.top();
                tmp.push_back(high.top());
                high.pop();
            }

            for(int j = 0; j < k; ++j){
                high.push(tmp[j]);
            }

            tmp.clear();

            for(int j = 0; j < 2 * k; ++j){
                if(j != 0) cout << " ";
                cout << result[j];
            }
            cout << endl;
        } else if(op == 3){
            int p;
            cin >> p;

            vector<int> tmp;
            if(p <= k){
                for(int j = 0; j < k - p; ++j){
                    tmp.push_back(low.top());
                    low.pop();
                }
                low.pop();
                for(int j = 0; j < k - p; ++j){
                    low.push(tmp[j]);
                }
            } else {
                for(int j = 0; j < p - k - 1; ++j){
                    tmp.push_back(high.top());
                    high.pop();
                }
                high.pop();
                for(int j = 0; j < p - k - 1; ++j){
                    high.push(tmp[j]);
                }
            }

            tmp.clear();

            while(low.size() > high.size()){
                high.push(low.top());
                low.pop();
            }
            while(high.size() > low.size()){
                low.push(high.top());
                high.pop();
            }

            while(high.top() < low.top()){
                int a = high.top();
                int b = low.top();
                high.pop();
                low.pop();
                high.push(b);
                low.push(a);
            }
        }
    }    
}