#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> mV;
int N;
inline int ni(int i){
	return (i + 1 == N ? 0 : i + 1);
}
inline int pi(int i){
	return (i - 1 == -1 ? N-1 : i - 1);
}
int main(){
	cin >> N;
	mV.resize(N);
	int mi = 0;
	ll total = 0, ave = 0;
	for(int i = 0 ; i< N; i++){
		cin >> mV[i];
		total += mV[i];
		if(mV[i] > mV[mi]){
			mi = i;
		}
	}
	ave = total / N;
	// clockwise
	int cur = mi;
	ll onhand = 0;
	ll cost = 0;
//	vector<ll> ori = mV;
	bool sol = true;
	for(int i = 0; i < N; i++){
		if(mV[cur] > ave){
			onhand += (mV[cur] - ave);
		}
		else if(mV[cur] < ave){
			onhand -= (ave - mV[cur]);
		}
		if(onhand < 0){
			sol = false;
			break;
		}
		cur = ni(cur);
		cost += onhand;
	}
	ll ans = numeric_limits<ll>::max();
	if(sol){
		ans = min(ans, cost);
	}
	sol = true;
	onhand = cost = 0;
	cur = mi;
	for(int i = 0; i < N; i++){
		if(mV[cur] > ave){
			onhand += (mV[cur] - ave);
		}
		else if(mV[cur] < ave){
			onhand -= (ave - mV[cur]);
		}
		if(onhand < 0){
			sol = false;
			break;
		}
		cur = pi(cur);
		cost += onhand;
	}
	if(sol){
		ans = min(ans, cost);
	}
	cout << ans << endl;
	return 0;
}
