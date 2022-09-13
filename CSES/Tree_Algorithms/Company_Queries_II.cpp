// AC 2022-03-29 14:39:22
// WA
// forgot to handle if u and v in `isPa` are the same vertices case.
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < n; i++)
#define F first
#define S second
#define eb emplace_back
using pii = pair<int, int>;
template<typename T>
using vec = vector<T>;
vec<vec<int>> pa;
vec<vec<int>> G;
vec<pii> IO;
bool isPa(int u, int v){
	return (IO[u].F <= IO[v].F && IO[u].S >= IO[v].S);
}
 
int LCA(int u, int v){
	if(isPa(u, v))
		return u;
	if(isPa(v, u))
		return v;
	int tmp = u;	
	for(int i = 30; i >= 0; i--){
		if(pa[i][tmp] != -1 && !isPa(pa[i][tmp], v))
			tmp = pa[i][tmp];
	}
	return pa[0][tmp];
}
int tstamp;
void DFS(int u){
	IO[u].F = tstamp++;
	for(int &v: G[u]){
		DFS(v);
	}
	IO[u].S = tstamp++;
}
 
int main(){
	int n, q;
	cin >> n >> q;
	pa.resize(31, vector<int>(n, -1));	
	G.resize(n);
	IO.resize(n);
	int u, v;
	REP(i, n-1){
		cin >> v;
		v--;	
		pa[0][i+1] = v;
		G[v].eb(i+1);
	}
	tstamp = 0;
	DFS(0);
	for(int i = 1; i < 31; i++){
		for(int j = 0; j < n; j++){
			pa[i][j] = (pa[i-1][j] == -1 ? -1 : pa[i-1][pa[i-1][j]]);
		}	
	}
	REP(i, q){
		cin >> u >> v;
		u--, v--;
		cout << LCA(u, v) + 1 << endl;
	}
 
	return 0;
}
