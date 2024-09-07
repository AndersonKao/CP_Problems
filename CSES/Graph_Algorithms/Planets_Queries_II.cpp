
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

const int MAXN = 200001;

int nxt[MAXN];
bool incycle[200001];
vec<int> forest[200001];
int vis[200001];
int component[200001];
int treeid[200001];
int depth[200001];
int instack[MAXN];
int D[MAXN], L[MAXN];

vec<vec<int>> cycles;

void findcycle(int u){

	int v = u;
	stack<int> st;
	while(vis[v] == false){
		st.emplace(v);
		instack[v] = true;
		vis[v] = true;
		v = nxt[v];
	}

	if(instack[v] == true){
		int id = cycles.size();
		cycles.resize(id + 1);
		while(st.top() != v)
		{
			cycles[id].eb(st.top());
			incycle[st.top()] = true;
			instack[st.top()] = false;
			st.pop();
		}
		cycles[id].eb(st.top()); // v itself
		incycle[st.top()] = true;
		instack[st.top()] = false;
		st.pop();
	}	
	while(st.size()){ // clear stack
		instack[st.top()] = false;
		st.pop();
	}
}

int tstamp = 0;
bool isPa(int u, int v){ // is u a parent of v?
	return (D[u] <= D[v] && L[v] <= L[u]);
}

void dfs(int u, int tid, int comp, int dep){
	D[u] = tstamp++;
	treeid[u] = tid;
	component[u] = comp;
	depth[u] = dep;
	for(int v: forest[u]){
		if(incycle[v]) continue;
		dfs(v, tid, comp, dep+1);
	}
	L[u] = tstamp++;
}

int main() {
//	yccc;
	int n, q;
	cin >> n >> q;
	for(int u = 1; u <= n; u++){
		cin >> nxt[u];
		forest[nxt[u]].eb(u);
	}
	for(int u = 1; u <= n; u++){
		if(vis[u] == false){
			findcycle(u);
		}
	}
	for(int i = 0; i < cycles.size(); i++){
		int treenum = cycles[i].size();
		for(int v: cycles[i]){
			dfs(v, treenum--, i, 0);
		}
	}
	/*cout << "dep: ";
	for(int u = 1; u <= n; u++){
		cout << depth[u] << " ";
	}
	cout << endl;
	cout << "com: ";
	for(int u = 1; u <= n; u++){
		cout << component[u] << " ";
	}
	cout << endl;
	
	cout << "treeid: ";
	for(int u = 1; u <= n; u++){
		cout << treeid[u] << " ";
	}
	cout << endl;*/
	for(int i = 0; i < q; i++){
		int u, v;
		cin >> u >> v;
		int dis = -1;
		if(component[u] == component[v]){
			if(treeid[u] == treeid[v] && isPa(v, u)){
				dis = depth[u] - depth[v];
			}
			else if(incycle[v]){
				dis = depth[u];
				dis += (treeid[v] - treeid[u] + cycles[component[u]].size()) % cycles[component[u]].size();
			}
		}
		cout << dis << endl;
	}
	return 0;
}
