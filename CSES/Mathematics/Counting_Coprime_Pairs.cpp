// fact 1
// number <= 1e6 won't have more than 7 prime factor.
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << ", ";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxv = 1000000;
const int maxn = 100000;
vec<ll> lp(maxv+1, 0);
vec<ll> primes;
ll vals[maxn] = {0};
ll cnts[maxv+1] = {0};
ll muls[maxv+1] = {0}; // number of multiples occurs.
void build(){
	for(int i = 2; i <= maxv; i++){
		if(lp[i] == 0){
			lp[i] = i;
			primes.eb(i);
		}
		for(ll p : primes){
			if(i * p > maxv) break;
			lp[i*p] = p;
			if(lp[i] == p)
				break;
		}
	}
}
vec<ll> factorization(ll x){
	
	vec<ll> ans;
	if(x == 1)
		ans.eb(1);
	while(x != 1){
		ll div = lp[x];
		while(x % div == 0)
			x /= div;
		ans.eb(div);
	}
	return ans;
}
int main(){
	yccc;		
	build();
	ll n; cin >> n;
	for(int i = 0; i < n; i++){
		cin >> vals[i];
		cnts[vals[i]]++;
	}
	for(int div = maxv; div > 1; div--){
		for(int j = div; j <= maxv; j += div){
			muls[div] += cnts[j];
		}
	}
	ll ans = n * (n-1);
	for(int j = 0; j < n; j++){
		vec<ll> fact = factorization(vals[j]);
		/*
		debug(vals[j]);
		devec(fact);
		cout << "\n";*/
		int bound = (1 << fact.size());
		ll ncpNum = 0; // not coprime number
		for(int mask = 1; mask < bound; mask++){
			ll val = 1;
			int flag = -1;
			for(size_t i = 0; i < fact.size(); i++){
				if((1 << i) & mask){
					flag *= -1;
					val *= fact[i];	
				}
			}
			ncpNum += flag * muls[val];
		}
//		debug(ncpNum);
		if(vals[j] == 1){
			ncpNum = 1; 
		}
		ans -= (ncpNum-1);
	}
	cout << ans / 2 << endl;
	


	return 0;
}

