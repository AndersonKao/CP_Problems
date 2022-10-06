
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
const int maxn = 200001;
vec<int> G[maxn];
const ll inf = 10000000000000LL;
ll w[maxn];
ll ans[maxn][3]; // even, odd, disa
void dfs(int u, int pa){
	if(u != pa && G[u].size() == 1){ // leaf
//		cout << u << " is leaf\n";
		ans[u][2] = 0;	
		ans[u][0] = w[u];
		return;
	}
	else if(u == pa && G[u].size() == 0){
		for(int i = 0; i < 3;i++)
			ans[u][i] = 0;
		return;
	}

	for(int v: G[u]){
		if(v == pa) continue;
		dfs(v, u);
	}
	vec<pair<ll, int>> V;	
	ll res = 0;

	for(int v: G[u]){
		if(v == pa) continue;
		V.eb(ans[v][2] - ans[v][0], v);
		res += ans[v][0];
	}
	sort(al(V), greater<pair<ll, int>>());

	int did = (G[u].size() - (u == pa ? 0 : 1)) & 1;
	ans[u][did] = res + w[u];

	for(int i = 0; i < V.size(); i++){
		int j = ((i+1) & 1) ^ did;
		res += V[i].F;
		ans[u][j] = max(ans[u][j], res + w[u]); 
	}

	V.clear();
	res = 0;
	for(int v:G[u]){
		if(v == pa) continue;
		V.eb(ans[v][2] - ans[v][1], v);
		res += ans[v][1];
	}
	sort(al(V), greater<pair<ll, int>>());

	ans[u][2] = res;
	for(int i = 0; i < V.size(); i++){
		res += V[i].F;
		ans[u][2] = max(ans[u][2], res);	
	}
}
int main(){
	int n;
	cin >> n;
//	memset(ans, -(ll)inf, sizeof(ans));
	for(int i = 1; i <= n; i++)
		fill(ans[i], ans[i]+3, -inf);
	for(int i = 2; i <= n; i++){
		int u;
		cin >> u;
		G[i].eb(u), G[u].eb(i);
	}
	for(int i = 1; i <=n; i++){
		cin >> w[i];
	}
	dfs(1, 1);
#ifdef DEBUG
	for(int i = 1; i <=n; i++){
		cout << i << ": ";
		for(int j = 0; j < 3;j++)
			cout << ans[i][j] << " ";
		cout << "\n";
	}
#endif
	
	cout << max(ans[1][1], ans[1][2]) << endl;
	return 0;
}

