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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 200000;
const ll MOD = 1e9 + 7;
vec<int> G[maxn];
int dfn[maxn], low[maxn];
int Time = 0;
int cycleId[maxn];
int BackedgeNum = 0;
int n, m;
vec<int> newG[2*maxn+1];
int pa[31][maxn]; // pa(i, u), vertex u's 2^i ancestor.

/* Binary Search Version */
int D[maxn], L[maxn];
int tstamp = 0;
int dp[maxn];
int vertexNum;
bool downbackedge[maxn];
void dfs(int u, int pa = -1){
	dfn[u] = low[u] = ++Time;
	bool noback = true;
	for(int v:G[u]){
		if(!dfn[v]){
			dfs(v, u);
		}
		else if(v != pa && dfn[v] < dfn[u]){
			downbackedge[v] = true;
			cycleId[u] = n + (BackedgeNum++);
			noback = false;
		}
	}
	if(noback){
		cycleId[u] = u;
		for(int v: G[u]){
			if(v == pa) continue;
			if(cycleId[v] != v && downbackedge[v] == false){
				cycleId[u] = cycleId[v];
			}
		}
	}
}

void ComputeP()
{
	int lgN = __lg(n + BackedgeNum);
    for (int i = 1; i < lgN; ++i)  // i = 0 is pre-built
    {
        for (int x = 0; x < n + BackedgeNum; ++x)
        {
            pa[i][x] = (pa[i - 1][x] == -1 ? -1 : pa[i - 1][pa[i - 1][x]]);
        }
    }
}
// call this first
void DFS(int u, int fa = -1, int cur = 0){
	dp[u] = (u < n ? 0 : 1) + cur;
    D[u] = tstamp++;
	pa[0][u] = fa;
    for(int v: newG[u]){
        if( v == fa ) continue;
        DFS(v, u, dp[u]);
    }
    L[u] = tstamp++;
}
bool isPa(int u, int v){
    return D[u] <= D[v] && L[u] >= D[v];
}

int LCA(int u, int v){
    if(isPa(u,v))
        return u;
    if(isPa(v,u))
        return v;
    for (int i = 30; i >= 0; i--){
        if(pa[i][u] != -1 && !isPa(pa[i][u], v)){
            u = pa[i][u];
		}
    }
    return pa[0][u];
}

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

vector<int> applyPermutation(vector<int> sequence, vector<int> permutation) {
    vector<int> newSequence(sequence.size());
    for(int i = 0; i < sequence.size(); i++) {
        newSequence[permutation[i]] = sequence[i];
    }
    return newSequence;
}

// O(nlogk) to apply permutation b times on sequence
vector<int> permute(vector<int> sequence, vector<int> permutation, long long b) {
    while (b > 0) {
        if (b & 1) {
            sequence = applyPermutation(sequence, permutation);
        }
        permutation = applyPermutation(permutation, permutation);
        b >>= 1;
    }
    return sequence;
}
int main(){
	yccc;		
	cin >> n >> m;
	for(int i = 0 ;i < m ; i++){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v), G[v].eb(u);
	}
	dfs(0);
	/*
	for(int u = 0 ; u < n; u++){
		cout << u << ": " << cycleId[u] << (u == n-1 ? "\n" : " ");
	}*/

	int root = 0x3f3f3f3f;
	for(int u = 0; u < n; u++){
		root = min(root, cycleId[u]);
		for(int v: G[u]){
			if(cycleId[u] != cycleId[v]){
				newG[cycleId[u]].eb(cycleId[v]);
			}
		}
	}


	for(int i = 0; i <= 30; i++){
		fill(pa[i], pa[i]+n+BackedgeNum, -1);
	}
	
	DFS(root);
	ComputeP();

	int q;
	int u, v;
	cin >> q;
	while(q--){
		cin >> u >> v;
		u--, v--;
		u = cycleId[u], v = cycleId[v];
		int ca = LCA(u, v);
		int p = dp[u] + dp[v] - dp[ca]*2 + (ca >= n ? 1 : 0);
		ll res = 1, tmp = 2;	
		while(p){
			if(p & 1){
				(res *= tmp) %= MOD;
			}	
			(tmp *= tmp) %= MOD;
			p >>= 1;
		}
		cout << res << endl;
	}
	
	return 0;
}

