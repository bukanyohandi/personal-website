/*
** The holy #include <bits/stdc++.h>
*/
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <iomanip>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#define endl '\n'
const double PI = 3.14159265358979323846;
using namespace std;
inline void boost(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
}
long long save,mid,le=1,ri=(long long)1e18+1,N,M,A[100005],B[100005];
bool possible(long long x){
	long long ret=0;
	for(int i=1;i<=N;++i){
		if(x/B[i]<A[i]) ret+=A[i]-x/B[i];
	}
	if(ret<=M) return true;
	return false;
}
int main(){
	boost();
	cin>>N>>M;
	for(int i=1;i<=N;++i){
		cin>>A[i];
	}
	for(int i=1;i<=N;++i){
		cin>>B[i];
	}
	while(le<=ri){
		mid=(le+ri)/2;
		if(possible(mid)){
			ri=mid-1;
			save=mid;
		} else {
			le=mid+1;
		}
	}
	cout<<save<<endl;
}