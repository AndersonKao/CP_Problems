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
const int maxn = 100000;
const ll mod = 1000000007; 
ll dp[maxn+1][2];
vec<int> G[maxn+1];
void dfs(int u, int pa = -1){
	dp[u][0] = dp[u][1] = 1;

	for(int v: G[u]){
		if(v == pa) continue;
		dfs(v, u);
		(dp[u][0] *= (dp[v][0] + dp[v][1]) % mod) %= mod;
		(dp[u][1] *= dp[v][0]) %= mod;
	}
}
int main(){
	yccc;		
	int N; cin >> N;
	REP(i, N-1){
		int u, v;
		cin >> u >> v;
		G[u].eb(v), G[v].eb(u);
	}
	dfs(1);
	cout << (dp[1][0] + dp[1][1]) % mod << endl;
	return 0;
}

