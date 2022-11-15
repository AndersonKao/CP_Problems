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
const int maxn = 10000;
vec<int> G[maxn];
vec<p<int>> E;
int pa[maxn];
int dfn[maxn];
int Time = 0;
int downedge[maxn][2];
int dp[maxn][2];
int depth[maxn];
int paid[maxn];
int oddbackNum = 0;
int oddans;
void dfs(int u, int fa = -1, int d = 0){
	dfn[u] = ++Time;
	depth[u] = d;
	pa[u] = fa;
	for(int idx: G[u]){
		int v = E[idx].F ^ E[idx].S ^ u;
		if(v == fa) paid[u] = idx;
		if(!dfn[v]){
			dfs(v, u, d+1);
		}
		else if(v != fa && dfn[v] < dfn[u]){
			if((d - depth[v]) & 1){ // even cycle
				dp[u][0]++;
				downedge[v][0]++;	
			}
			else{
				if(oddbackNum == 0){
					oddans = idx;
				}
				oddbackNum++;	
				dp[u][1]++;
				downedge[v][1]++;	
			}
		}
	}
	for(int idx: G[u]){
		int v = E[idx].F ^ E[idx].S ^ u;
		if(pa[v] == u){
			dp[u][0] += dp[v][0];
			dp[u][1] += dp[v][1];
		}
	}
	dp[u][0] -= downedge[u][0];
	dp[u][1] -= downedge[u][1];
}
int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u>> v;
		u--, v--;
		G[u].eb(E.size()), G[v].eb(E.size());
		E.eb(u, v);
	}
	for(int i = 0; i < n; i++){
		if(!dfn[i]){
			dfs(i);
		}
	}
	if(oddbackNum == 0){
		cout << m << endl;
		for(int i = 1; i <= m; i++){
			cout << i << (i == m ? "\n" : " ");
		}
		return 0;
	}
	vec<int> ans;
	if(oddbackNum == 1){
		ans.eb(oddans);
	}
	for(int i = 0; i < n; i++){
		if(pa[i] != -1 && dp[i][0] == 0 && dp[i][1] == oddbackNum){
			ans.eb(paid[i]);
		}
	}
	cout << ans.size() << endl;
	sort(ans.begin(), ans.end());
	for(int idx : ans){
		cout << idx+1 << " ";
	}
	return 0;
}

