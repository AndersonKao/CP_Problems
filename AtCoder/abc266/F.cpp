#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
struct dsj{
	vector<int> boss;
	dsj(int n){
		boss.resize(n);
		for(int i = 0; i < n; i++){
			boss[i] = i;
		}
	}
	int get(int u){
		if(boss[u] == u)
			return u;
		return boss[u] = get(boss[u]);
	}
	bool same(int v, int u){
		return get(u) == get(v);
	}
	void merge(int u, int v){
		int pu = get(u), pv = get(v);
		boss[pu] = pv;
	}
};

vector<vector<int>> G;
vector<bool> vis;
int N;
vector<int> incyc;
stack<int> mS;
bool found = false;
void DFS(int u, int pa){
	//debug(u);
	vis[u] = true;
	mS.push(u);
	for(int v: G[u]){
		if(v == pa)
			continue;
		if(vis[v] == false){
			DFS(v, u);
		}
		else if(found == false){
//			cout << "cycle on "  << v << endl;
			stack<int> rv;
			while(mS.top() != v){
				incyc[mS.top()] = true;
//				cout << mS.top() << endl;
				rv.push(mS.top());
				mS.pop();
			}
			incyc[mS.top()] = true;
//				cout << mS.top() << endl;
			while(rv.size()){
				mS.push(rv.top());
				rv.pop();
			}
			found = true;
		}
	}
	mS.pop();
}
vector<int> belong;
void DFS2(int u, int be){
	vis[u] = true;
	belong[u] = be;
	for(int v: G[u]){
		if(vis[v] || incyc[v]){
			continue;
		}
		DFS2(v, be);
	}
}

int main(){
	cin >> N;
	G.resize(N);
	vis.resize(N, false);
	incyc.resize(N, false);
	for(int i = 0; i < N; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
		G[v].eb(u);
	}
	bool hole = true;
	for(int u = 0; u < N; u++){
		if(G[u].size() == 1){
			DFS(u, -1);
			hole = false;
			break;
		}
	}
	fill(al(vis), false);
	belong.resize(N);
	for(int i = 0; i < N; i++){
		if(incyc[i]){
//			cout << i +1<< " ";
			DFS2(i, i);			
		}
	}
	/*
	cout << endl;
	for(int i = 0; i < N; i++){
		cout << i+1 << ": " << belong[i]+1 << "  ";
	}
	cout << endl;
	*/
	int Q;
	cin >> Q;
	for(int i = 0; i < Q; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		if(hole){
			cout << "No\n";
		}
		else{
			if(belong[u] == belong[v]){
				cout << "Yes\n";
			}
			else
				cout << "No\n";
		}
	}
	return 0;
}
