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
ll A, B, C, D, M, S, T;
ll dis(ll d, ll t){
	if(t <= M/C){
		return t*B;
	}
	ll tB = min(t-d, (M+d*D) / C);
	ll tA = (t-d) - tB;	
	return tA * A + tB*B;
}
ll arrive(ll t){
	ll mdis = 0;
	for(ll d = 0; d <= t; d++){
		mdis = max(mdis, dis(d, t));
	}
	return mdis;
}
int main(){
	cin >> A >> B >> C >> D >> M >> S >> T;
	ll l = 0, r = T;
	ll mdis;
	if((mdis = arrive(T)) < S){
		cout << "No\n" << mdis << endl;
		return 0;
	}
	while(l < r){
		ll m = (l+r) >> 1;
		if(arrive(m) >= S){
			r = m;
		}
		else{
			l = m+1;
		}
	}
	cout << "Yes\n" << l << endl;
	return 0;
}

