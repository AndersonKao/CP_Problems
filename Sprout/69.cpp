
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
const ll inf = 100000005;
int main(){
	int T;
	cin >> T;
	while(T--){
		int n, k;
		cin >> n >> k;
		vec<p<ll>> myhorse(n);
		vec<ll> compete(n);
		for(p<ll>&e : myhorse){
			cin >> e.F >> e.S;
		}
		for(ll &e : compete){
			cin >> e;
		}
		sort(al(compete));
		ll l = 0, r = inf;
		while(l < r){
			ll m = l + ((r - l) >> 1);
			vec<ll> trained; 
			for(p<ll>&e : myhorse){
				trained.eb(e.F + m * e.S);
			}
			sort(al(trained));
			int num = 0;
			int it = 0, itc = 0;
			while(it != n && itc != n){
				if(compete[itc] < trained[it]){
					num++;
					it++, itc++;
				}
				else{
					it++;
				}
			}
			if(num >= k){
				r = m;
			}
			else{
				l = m + 1;
			}
		}
		if(l == inf){
			cout << -1 << endl;
		}
		else{
			cout << l <<endl;
		}

	}
	return 0;
}

