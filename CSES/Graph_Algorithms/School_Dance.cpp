// AC 2022-10-21 08:35:31 UTC+3
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 500;
// time complexity: O(EV), V times DFS
// G[i]記錄了左半邊可以配到右邊的那些點
/* bipartite graph be like..
0\ /-0
1-X--1
2/ \/2
3  /\3
4 /  4
5/   5
.    .
.    .
*/
// match[i] 記錄了右半邊配對到左半邊的哪個點
vec<int> G[maxn];
int match[maxn]; // A <=B
bool used[maxn];
bool dfs(int v)
{
    for(int e:G[v])
    {
        if( used[e] ) continue;
        used[e] = true;
        if( match[e] == -1 || dfs( match[e] ) )
        {
            match[e] = v;
            return true;               
        }
    }
    return false;
}
int konig(int n) // num of vertices of left side
{
    memset(match,-1,sizeof(match));

    int ans=0;
    
    for(int i=0;i<n;++i)
    {
        memset(used, 0, sizeof(used));
        if( dfs(i) )
            ans++;
    }

    return ans;
}
void addedge(int u, int v){ // left side, right side
    G[u].eb(v);
}
int main(){

	int n, m, k;
	cin >> n >> m >> k;
	for(int i = 0; i < k; i++){
		int u, v;
		cin >> u >> v;
		addedge(u-1, v-1);
	}
	cout << konig(n) << endl;
	for(int u = 0; u < m; u++){
		if(match[u]== -1) continue;
		cout << match[u]+1 << " " << u+1 << endl;
	}
	return 0;
}

