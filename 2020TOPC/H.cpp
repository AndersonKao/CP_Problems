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
const ll inf = 1e9;
const ll mod = 1000000007;
int main(){
	int n;
	cin >> n;
	vec<ll> vals(n);
	for(ll &e : vals){
		cin >> e;
	}
	ll posmax = -inf, posmin = inf, negmax = inf, negmin = -inf;
	ll pmaxv = -1, pminv = -1, nmaxv = -1, nminv = -1;
	bool allneg = true, allpos = true;
	for(int i = 0; i < n ;i++){
		ll e = vals[i];
		if(e >= 0){
			allneg = false;
			if(posmax < e){
				posmax = e;
				pmaxv = i;
			}
			if(posmin > e){
				posmin = e;
				pminv = i;
			}
		}
		else{
			allpos = false;
			if(negmax > e){
				negmax = e;
				nmaxv = i;
			}
			if(negmin < e){
				negmin = e;
				nminv = i;
			}
		}
	}
	ll minans = 0, maxans = 0; 	
	if(allpos){
		for(int i = 0; i < n; i++){
			if(i == pmaxv) continue;
			maxans += posmax * vals[i];
			maxans %= mod;
		}
		for(int i = 0; i < n; i++){
			if(i == pminv) continue;
			minans += posmin * vals[i];
			minans %= mod;
		}
	}
	else if(allneg){
		for(int i = 0; i < n; i++){
			if(i == nmaxv) continue;
			maxans += negmax * vals[i];
			maxans %= mod;
		}
		for(int i = 0; i < n; i++){
			if(i == nminv) continue;
			minans += negmin * vals[i];
			minans %= mod;
		}
	}
	else{
		for(int i = 0; i < n; i++){
			if(vals[i] >= 0){
				minans += negmax * vals[i];  
				minans = ((minans % mod) + mod) % mod;
				if(i != pmaxv){
					maxans += posmax * vals[i];
					maxans = ((maxans % mod) + mod) % mod;
				}
			}
			else{
				minans += posmax * vals[i];  
				minans %= mod;
				if(i != nmaxv){
					maxans += negmax * vals[i];
					maxans = ((maxans % mod) + mod) % mod;
				}
			}
		}
		minans -= negmax * posmax;
		minans = ((minans % mod) + mod) % mod;
		maxans += negmin * posmin;
		maxans = ((maxans % mod) + mod) % mod;
	}
	minans = ((minans % mod) + mod) % mod;
	maxans = ((maxans % mod) + mod) % mod;
	cout << minans << " " << maxans << endl;
		
	return 0;
}

