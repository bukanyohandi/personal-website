#include <bits/stdc++.h>
using namespace std;

int main(){
    string s;
    int freq[10];
    memset(freq, 0, sizeof(freq));

    cin >> s;
    for(auto c: s){
        freq[c - '0']++;
    }

    int tmp = 0;
    vector<int> num;
    for(int i = 9; i >= 0; --i){
        if(i == 0 && num.size() == 0) break;
        while(freq[i] >= 2){
            freq[i] -= 2;
            num.push_back(i);
        }
        if(tmp == 0 && freq[i] > 0){
            tmp = i;
        }
    }
    
    if((int)num.size() == 0){
        cout << tmp << endl;
    } else {
        for(int i = 0; i < num.size(); ++i){
            cout << num[i];
        }
        if(tmp != -1) cout << tmp;
        for(int i = (int)num.size() - 1; i >= 0; --i){
            cout << num[i];
        }
        cout << endl;
    }
}