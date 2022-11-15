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
vec<int> G[maxn];
int dfn[maxn] = {0};
int low[maxn];
int Time = 0;
vec<p<int>> ans;
int bridgenum= 0;
void dfs(int u, int pa = -1){
	low[u] = dfn[u] = ++Time;
	for(int v: G[u]){
		if(dfn[v] == 0){
			ans.eb(u, v);
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if(dfn[u] < low[v]){
				bridgenum++;
			}	
		}
		else if(v != pa && dfn[v] < dfn[u]){
			ans.eb(u, v);
			low[u] = min(low[u], dfn[v]);
		}
	}
}
int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v), G[v].eb(u);
	}
	dfs(0);
//	cout << bridgenum << endl;
	for(int u = 0; u < n; u++){
		if(dfn[u] == 0 || bridgenum){
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	for(p<int> e: ans){
		cout << e.F+1 << " " << e.S+1 << endl;
	}

	return 0;
}

