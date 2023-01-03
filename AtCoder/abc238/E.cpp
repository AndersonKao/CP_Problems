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
vec<int> G[200001];
bool vis[200001] = {false};

void dfs(int u){
	vis[u] = true;
	for(int v: G[u]){
		if(vis[v]) continue;
		dfs(v);
	}
}

int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	REP(i, m){
		int u, v;
		cin >> u >> v;
		u--;
		G[u].eb(v), G[v].eb(u);
	}
	dfs(0);
	cout << (vis[n] ? "Yes" : "No") << endl;

	return 0;
}

