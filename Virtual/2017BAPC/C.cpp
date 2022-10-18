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
ll gcd(ll a, ll b){
	if(b == 0)
		return a;
	return gcd(b, a%b);
}
int main(){
	int n;	
	cin >> n;
	vec<ll> V(n);
	for(ll &e: V)
		cin >> e;
	vec<vec<ll>> gcds(2);
	set<ll> gcdall;
	int round = 0;
	for(int i = 0; i < n; i++){
		gcds[round].clear();
		gcds[round].eb(V[i]);
		if(i != 0) {
			for(const ll& val: gcds[round^1]){
				gcds[round].eb(gcd(val, V[i]));
				gcdall.emplace(val);
			}
			sort(al(gcds[round]));
			gcds[round].resize(unique(al(gcds[round])) - gcds[round].begin());
		}
		round ^= 1;
	}
	for(const ll &val: gcds[round^1]){
		gcdall.emplace(val);
	}
	cout << gcdall.size() << endl;
	
	return 0;
}

