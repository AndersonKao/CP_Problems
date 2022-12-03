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
int n, m;
const int maxn = 200000;
vec<int> G[maxn];
struct edge{
	int u, v;
	edge(int u, int v):u(u), v(v){}
};
vec<edge> E;
int iscover[maxn];
int visited[maxn];
int edgeID;
bool dfs_cyc(int u, int pa = -1){
	visited[u] = true;
	for(int eid: G[u]){
		int v = E[eid].v ^ E[eid].u ^ u;
		if(v == pa) continue;
		if(visited[v]){
			edgeID = eid;
			return true;
		}
		if(dfs_cyc(v, u)){
			return true;
		}
	}
	return false;
}
int coverN = 0;
void dfs(int u, int pa = -1){
	for(int eid: G[u]){
		if(eid == edgeID) continue;
		int v = E[eid].v ^ E[eid].u ^ u;
		if(v == pa) continue;
		dfs(v, u);	
		if(iscover[u] == 0 && iscover[v] == 0){
			iscover[u] = true;
			coverN++;
		}
	}
}

int main(){
	yccc;		
	cin >> n >> m;
	for(int i = 0; i < n+m; i++){
		int u, v;
		cin >> u >>v;
		G[u].eb(E.size()), G[v].eb(E.size());
		E.eb(u, v);
	}
	dfs_cyc(0);
	int ans = n+m;
	int u0 = E[edgeID].u;
	// case 1
	fill(iscover, iscover+n+m, 0);
	coverN = G[u0].size();
	for(int eid: G[u0]){
		int v = E[eid].u ^ E[eid].v ^ u0;
		iscover[v] = true;
	}	
	dfs(0);
	ans = min(ans, coverN);

	// case 2
	fill(iscover, iscover+n+m, 0);
	coverN = 1;
	iscover[u0] = true;
	dfs(0);
	ans = min(ans, coverN);

	cout << ans << endl;
	return 0;
}

