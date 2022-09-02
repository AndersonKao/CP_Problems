#include <bits/stdc++.h>
using namespace std;
using ll = long long;
priority_queue<ll, vector<ll>, greater<ll>> mQ;

int main(){
	int N;
	cin >> N;
	if(N == 1){
		int d;
		cin >> d;
		cout << "N\n";
		return 0;
	}
	for(int i = 0; i < N; i++){
		int d;
		cin >> d;
		mQ.emplace(d);
	}
	vector<ll> mV;
	while(mQ.size()){
		ll v = mQ.top();
		mQ.pop();
		if(mQ.size() == 0){
			mV.emplace_back(v);
			break;
		}
		if(mQ.top() == v){
			mQ.pop();
			mQ.emplace(v+1);
		}
		else{
			mV.emplace_back(v);
		}
	}
	if(mV.size() > 2)
		cout << "N\n";
	else
		cout << "Y\n";
	return 0;
}
