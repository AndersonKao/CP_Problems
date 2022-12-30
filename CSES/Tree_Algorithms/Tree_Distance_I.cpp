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
const int maxn = 200000;
vec<int> G[maxn];
int dis_a[maxn], dis_b[maxn]; // distance from a, b.
int toleaf[maxn];

int dfs_farest(int u, int pa = -1){
	int ans_leaf = u;
	for(int v: G[u]){
		if(v == pa) continue;
		int leaf = dfs_farest(v, u);
		if(toleaf[u] < toleaf[v]){
			toleaf[u] = toleaf[v];
			ans_leaf = leaf;	
		}
	}
	toleaf[u] += 1;
	return ans_leaf;
}
void dfs_from(int* dis, int u, int pa = -1, int d = 0){
	dis[u] = d;
	for(int v: G[u]){
		if(v == pa) continue;
		dfs_from(dis, v, u, d + 1);
	}
}

int main(){
	yccc;		
	int n; cin >> n;
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v), G[v].eb(u);
	}
	fill(toleaf, toleaf + n, 0);
	int a = dfs_farest(0);
	fill(toleaf, toleaf + n, 0);
	int b = dfs_farest(a);
	
	dfs_from(dis_a, a);	
	dfs_from(dis_b, b);

	for(int i = 0; i < n; i++){
		cout << max(dis_a[i], dis_b[i]) << " \n"[i == n-1];
	}


	return 0;
}

