#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;
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
	vector<ll> ori = mV;
	int ok = 0;
	vector<bool> counted(N, false);
	while(ok < N){
#ifdef DEBUG
		debug(cur);
		debug(cost);
		debug(onhand);
#endif
		if(mV[cur] > ave){
			mV[cur] = ave;
			onhand += (mV[cur] - ave);
			ok++;
			counted[cur] = true;
#ifdef DEBUG
			cout << "ok on " << cur << endl;
#endif
		}
		else if(mV[cur] < ave){
			if(onhand >= (ave - mV[cur])){
				onhand -= (ave - mV[cur]);
				ok++;
				mV[cur] = ave;
				counted[cur] = true;
#ifdef DEBUG
				cout << "ok on " << cur << endl;
	#endif
			}
			else{
				mV[cur] += onhand;
				onhand = 0;
			}
		}
		else {
			if(counted[cur] == false){
				counted[cur] = true;
				ok++;
			}
		}
		cost += onhand;
		cur = ni(cur);
	}
	ll ans = numeric_limits<ll>::max();
		ans = min(ans, cost);
#ifdef DEBUG
	debug(ans);
	cout << "-----\n";
#endif
	onhand = cost = 0;
	cur = mi;
	mV = ori, ok = 0;
	fill(counted.begin(), counted.end(), false);
	while(ok < N){
#ifdef DEBUG
		debug(cur);
		debug(cost);
		debug(onhand);
#endif
		if(mV[cur] > ave){
			mV[cur] = ave;
			onhand += (mV[cur] - ave);
			ok++;
			counted[cur] = true;
#ifdef DEBUG
			cout << "ok on " << cur << endl;
#endif
		}
		else if(mV[cur] < ave){
			if(onhand >= (ave - mV[cur])){
				onhand -= (ave - mV[cur]);
				ok++;
				mV[cur] = ave;
				counted[cur] = true;
#ifdef DEBUG
				cout << "ok on " << cur << endl;
	#endif
			}
			else{
				mV[cur] += onhand;
				onhand = 0;
			}
		}
		else {
			if(counted[cur] == false){
				counted[cur] = true;
				ok++;
			}
		}
		cost += onhand;
		cur = pi(cur);
	}
	ans = min(ans, cost);
	cout << ans << endl;
	return 0;
}
