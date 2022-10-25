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

int main(){
	int n;	
	cin >> n;
	vec<pair<ll, int>> V(n);
	vec<ll> D(n);
	REP(i, n){
		cin >> V[i].F >> D[i];	
		V[i].S = i;
	}
	sort(al(V));
	ll ans = 0;
	ll cur = 0;
	for(auto&e: V){
		cur += e.F;
		ans += (D[e.S] - cur);
	}
	cout << ans << endl;
	return 0;
}

