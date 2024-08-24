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

vec<int> G[200001];
bool req[200001];
bool contain[200001];
int sz[200001];
int ans = 0;
//vec<int> seq;

void dfs(int u, int pa){
	//cout << "dfs\n";
	sz[u] = 1;
	contain[u] = req[u];
	for(int v: G[u]){
		if(v == pa) continue;
		dfs(v, u);
		contain[u] = contain[u] || contain[v];
		sz[u] += sz[v];
	}
}

void solve2(int u, int pa){
	//cout << "s2\n";
	for(int v: G[u]){
		if(v == pa) continue;
		if(contain[v] == false){
			ans -= sz[v];
		}	
		else{
			solve2(v, u);
		}
	}
}
void solve(int u, int pa){
	//cout << "s\n";
	int cnt = 0;
	int go = -1;
	for(int v: G[u]){
		if(v == pa) continue;
		if(contain[v]){
			cnt++;
			go = v;
		}	
	}
	if(cnt > 1 || req[u]){
		ans = sz[u];
		solve2(u, pa);
	}
	else{
		solve(go, u);
	}

}



int main(){
	yccc;		
	int n, k;
	cin >> n >> k;
	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v); G[v].eb(u);
	}
//	req.resize(k);
	for(int i = 0; i < k; i++){
		int u;
		cin >> u;
		req[u] = true;
	}

	dfs(1, -1);
	solve(1, -1);
	cout << ans << endl;

	return 0;
}

