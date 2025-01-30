#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
// Idea: there is no back edge on BFS tree
vector<vector<int>> G;
vector<int> timestamp;
vector<bool> vis;
vector<pair<int, int>> E;
int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	G.resize(n+1);
	timestamp.resize(n+1, 0);
	vis.resize(n+1, false);
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
		E.eb(u, v);
	}
	// BFS
	int t = 0;
	for(int u = 1; u <= n; u++){
		if(vis[u]) continue;
		queue<int> myGo;
		myGo.emplace(u);
		vis[u] = true;
		while(myGo.empty() == false){
			int u = myGo.front();
			myGo.pop();
			for(int v: G[u]){
				if(vis[v] == false){
					timestamp[v] = ++t;					
					vis[v] = true;
					myGo.emplace(v);
				}
			}
		}
	}
	for(pair<int, int>& e: E){
		if(timestamp[e.first] <= timestamp[e.second]){
			cout << e.first << " " << e.second << endl;
		}
		else{
			cout << e.second << " " << e.first << endl;
		}
	}
	return 0;
}

