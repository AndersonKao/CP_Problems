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

const int maxn = 100001;

vector<int> G[maxn];
int in[maxn], out[maxn];

// create a graph, each node have bit string of (n-1)
// De-brujin sequence corroespond to the Euler circuit (node id + next step)
vector<int> path;

void DFS(int u){
	while(G[u].empty() == false){
		int v = G[u].back();
		G[u].pop_back();
		DFS(v);
	}
	path.eb(u);
}

int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		out[u]++;
		in[v]++;
	}
	for(int node = 2; node <= n-1; node++){
		if(out[node] != in[node]){
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	}
	if(out[1] - in[1] > 1 || out[1] < in[1] || in[n] - out[n] > 1 || in[n] < out[n]){
		cout << "IMPOSSIBLE\n";
		return 0;
	}	

	DFS(1);
	reverse(al(path));
	if(path.back() != n || path.size() != m + 1){
		cout << "IMPOSSIBLE\n";
		return 0;
	}
	for(int node: path){
		cout << node << " ";
	}

	return 0;
}

