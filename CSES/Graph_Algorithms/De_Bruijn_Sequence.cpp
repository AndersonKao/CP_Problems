#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

vec<list<pair<int, int>>::iterator> edges;
const int maxn = (1 << 15);

list<pair<int, int>> G[maxn];

list<int> ans, res;
int deg[maxn] = {0};
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
	int n;
	cin >> n;
	if(n == 1){
		cout << "01" << endl;
		return 0;
	}
	for(int u = 0; u < (1 << n); u++){
		int v1 = ((u & ((1 << (n-1)) - 1)) << 1);
		int v2 = v1 + 1;
		G[u].eb(v1);
		G[u].eb(v2);
		G[u].emplace_front(v1, edges.size());
		edges.push_back(G[v1].begin());
		G[u].emplace_front(v2, edges.size());
		edges.push_back(G[v2].begin());
		deg[u]+=2;
	}
	for(int i = 0; i < m; i++){
		cin >> u >> v;
	}

	edgenum = m;

	dfs(0, -1, 1, ans);
	vec<bool> vis(n, false);
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

