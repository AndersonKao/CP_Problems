// failed O(3^n) won't pass
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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

int n;
ll w[maxn];
ll subsum[(1 << maxn)];
int dp[(1<<maxn)];

inline int lowbit(int x){
	return x & (~x + 1);
}
int main(){
	yccc;		
	ll x;
	cin >> n >> x;
	for(int i = 0; i < n; i++){
		cin >> w[i];
	}
	sort(w, w+n);
	for(int i = 0; i < n; i++)
		subsum[(1 << i)] = w[i];
	for(int mask = 0; mask < (1 << n); mask++){
		int lo = lowbit(mask); 
		if(mask == lo) continue;
		subsum[mask] = subsum[mask - lo] + subsum[lo];
	}
	dp[0] = 0;
	for(int mask = 1; mask < (1 << n); mask++){
		if(subsum[mask] <= x){
			dp[mask] = 1;
			continue;
		}	
		dp[mask] = inf;
//		for(int res = mask; res; res = (res - 1) & mask){
		for(int res = lowbit(mask); res < mask; res += lowbit((~res) & mask)){
			if(subsum[res] > x) break;
			dp[mask] = min(dp[mask], dp[mask - res] + 1);
		}
		cout << bitset<5>(mask) << ": " << dp[mask] << endl;
	}
	cout << dp[(1 << n) - 1];


	return 0;
}

