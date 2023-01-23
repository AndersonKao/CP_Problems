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
const int maxn = 100;
const int maxk = 1000;
ll s[maxn][maxk], b[maxn][maxk];
ll G[maxn][maxn];
ll G2[maxn][maxn];
ll Profit[maxn][maxn];
const ll inf = (LLONG_MAX-2)/2;

void floyd(ll adj[maxn][maxn]){
	REP(k, maxn){
		REP(u, maxn){
			REP(v, maxn){
				adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
			}
		}
	}
}
void init(ll adj[maxn][maxn], ll val = inf){
	REP(u, maxn){
		fill(adj[u], adj[u]+maxn, val);
	}
}

int main(){
	yccc;		
	int n, m, K;
	cin >> n >> m >> K;
	REP(i, n){
		REP(j, K){
			cin >> b[i][j] >> s[i][j];
		}
	}

	init(G);
	REP(i, m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		cin >> G[u][v];
	}

	floyd(G);

	REP(u, n){
		REP(v, n){
			REP(k, K){
				if(b[u][k] == -1 || s[v][k] == -1) continue;
				Profit[u][v] = max(Profit[u][v], s[v][k] - b[u][k]); 
			}
		}
	}
	ll l = 1, r = 1e9;
	while(l <= r){
		ll m = (l+r)/2;
		init(G2);
		REP(u, n){
			REP(v, n){
				G2[u][v] = m * min(G[u][v], inf / m) - Profit[u][v];
			}
		}
		floyd(G2);
		bool nonneg_cycle = false;
		REP(u, n){
			if(G2[u][u] <= 0) nonneg_cycle = true;
		}
		if(nonneg_cycle == true){
			l = m + 1;
		}
		else{
			r = m - 1;
		}
	}
	cout << r << endl;

	return 0;
}

