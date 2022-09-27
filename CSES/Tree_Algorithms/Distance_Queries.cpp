// binary serach LCA
#include <bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define F first
#define S second
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
 
vec<vec<int>> G;
vec<pii> GT;
vec<vec<int>> dp;
vec<int> depth;
int stp=0;
 
bool isPA(int u, int v){
    return (GT[u].F <= GT[v].F && GT[u].S >= GT[v].S);
}
 
void DFS(int u, int p, int d){
    GT[u].F = stp++; 
    depth[u] = d;
    //cout << "visiting: " << u + 1 << endl;
    for(int &v: G[u]){
        if(v == p)
            continue;
        dp[v][0] = u;
        DFS(v, u, d+1);
    }
    GT[u].S = stp++; 
}
int LCA(int u, int v){
    if(depth[u] > depth[v])
        swap(u, v);
    if(isPA(u, v))
        return u;
    int tmp = u;
    for(int i = 31; i >= 0; i--){
        int k = dp[tmp][i];
//        cout << k + 1  << endl;
        if(k == -1)
            continue;
        if(!isPA(k, v)){
            tmp = k; 
        }
    }
    return dp[tmp][0];
}
 
int main(){
    int n, q;
    cin >> n >> q;
    G.resize(n);
    GT.resize(n);
    depth.resize(n);
    dp.resize(n, vec<int>(32, -1));
    REP(i, n-1){
        int u, v; 
        cin >> u >> v;
        u--, v--;
        G[u].eb(v);
        G[v].eb(u);
    }
    DFS(0, -1, 0);
    for(int i = 1; i < 32; i++){
        for(int j = 0; j < n; j++){
            dp[j][i] = (dp[j][i-1] == -1 ? -1 : dp[dp[j][i-1]][i-1]);
        }
    }
    REP(i, q){
        int u, v;
        cin >> u >> v;
        u--, v--;
        int k = LCA(u, v);
        //cout << "LCA: " << k + 1 << endl;
        //cout << "d: " << depth[u] << ", " << depth[v] << ", " << depth[k] << endl;
        cout << depth[u] + depth[v] - 2 * depth[k] << endl; 
    }
 
    return 0;
}
/*
14 99
1 2
1 3
3 4
3 5
2 6
2 7
6 8
4 11
4 10
9 4
10 13
13 14
10 12 
*/
