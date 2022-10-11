#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
ll seq[200000];
int main(){
	int n;
	cin >> n;
	REP(i, n)
		cin >> seq[i];
	ll modd[2] = {-1, -1}, meven[2] = {-1, -1};
	REP(i, n){
		if(seq[i] & 1){
			if(seq[i] >= modd[0]){
				modd[1] = modd[0];
				modd[0] = seq[i];
			}
			else if(seq[i] > modd[1]){
				modd[1] = seq[i];
			}
		}
		else{
			if(seq[i] >= meven[0]){
				meven[1] = meven[0];
				meven[0] = seq[i];
			}
			else if(seq[i] > meven[1]){
				meven[1] = seq[i];
			}
		}
	}
	ll ans = -1;
	if(modd[0] != -1 && modd[1] != -1){
		ans = max(ans, modd[0] + modd[1]);
	}
	if(meven[0] != -1 && meven[1] != -1){
		ans = max(ans, meven[0] + meven[1]);
	}
	cout << ans << endl;
	return 0;
}

