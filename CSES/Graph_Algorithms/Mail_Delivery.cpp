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

vec<list<pair<int, int>>::iterator> edges;

list<pair<int, int>> G[100001];

list<int> ans, res;
int deg[100001] = {0};
int edgenum;

void dfs(int u, int pa, int st, list<int> &arr){
	if(pa != -1 && u == st){
//		arr.eb(u);
		return;
	}
	if(G[u].size() == 0)
		return;
	int v = (*G[u].begin()).first;
	int edge_id = (*G[u].begin()).second;
	//debug(v);
//	debug(edges[edge_id]->first);
	arr.eb(v);
	deg[u]--;
	deg[v]--;
	edgenum--;
	G[u].pop_front();
	G[v].erase(edges[edge_id]);
	dfs(v, u, st, arr);
}

int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	int u, v;
	for(int i = 0; i < m; i++){
		cin >> u >> v;
		G[u].emplace_front(v, edges.size());
		G[v].emplace_front(u, edges.size()+1);
		edges.push_back(G[v].begin());
		edges.push_back(G[u].begin());
		deg[u]++;
		deg[v]++;
	}

	for(int u = 1; u <= n; u++){
		if(deg[u] & 1){
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}

	edgenum = m;

	dfs(1, -1, 1, ans);
	/*
	for(int u: ans){
		cout << u << " ";
	}
	cout << endl;
	*/

	for(auto it = ans.begin(); it != ans.end(); it++){
		if(deg[*it] > 0){
			res.clear();
			dfs(*it, -1, *it, res);
			auto start = it;
			it++;
			ans.splice(it, res);
			while(it != start){
				it--;
			}
		}
	}
	if(ans.size() != m){
		cout << "IMPOSSIBLE\n";
		return 0;
	}

	cout << 1;
	for(int u: ans){
		cout << " " << u;
	}
	return 0;
}

