#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int offset = 0;
int n, m, k;
const ll MOD = 998244353LL;

inline int shift(int idx){
	return idx + offset > n ? (idx + offset - n) : (idx + offset);
}

int main(){
	yccc;		
	cin >> n >> m >> k;
	vec<pair<int, int>> edges(m);
	vec<ll> dp(n+1, 0);

	for(int i = 0; i < m; i++){
		cin >> edges[i].first >> edges[i].second;
	}
	dp[1] = 1;

	for(int i = 0; i < k; i++){
		vec<ll> res;			   
		for(pii& p: edges){
			int u = shift(p.first);
			res.eb(dp[u]);
		}
		offset--;
		if(offset < 0)
			offset += n;
		for(int i = 0; i < m; i++){
			int v = shift(edges[i].second);
			dp[v] += res[i];
			dp[v] %= MOD;
		}
	}
	ll ans = 0;
	for(int u = 1; u <= n; u++){
		ans += dp[u];
		ans %= MOD;	
	}
	cout << ans << endl;
	return 0;
}

