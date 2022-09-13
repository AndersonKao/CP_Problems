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
int D[200000];
void DFS(int u, int d){
	D[u] = d;
	for(int &v: G[u]){
		DFS(v, d+1);
	}
}
 
 int LCA(int u, int v)
{
    if (D[u] > D[v])
        swap(u, v);
    int s = D[v] - D[u];
    for (int i = 0; i < 31; ++i) // adjust to same depth
        if (s & (1 << i))
            v = pa[i][v];

    if (u == v)
        return v;
    // because they are at same depth
    // jump up if they are different
    // think about that if P[u][i] == P[v][i]
    // then that point must be the ancestor of LCA or LCA itself
    // by this, we will stop at LCA's child
    for (int i = 30; i >= 0; --i)
        if (pa[i][u] != pa[i][v])
        {
            u = pa[i][u];
            v = pa[i][v];
        }
    return pa[0][u];
}
int main(){
	int n, q;
	cin >> n >> q;
	pa.resize(31, vector<int>(n, -1));	
	G.resize(n);
	int u, v;
	REP(i, n-1){
		cin >> v;
		v--;	
		pa[0][i+1] = v;
		G[v].eb(i+1);
	}
	DFS(0, 0);
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
