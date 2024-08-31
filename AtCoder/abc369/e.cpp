
#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
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

struct edge{
	int u, v;
	ll w;
	edge(){u = v = w = 0;}
	edge(int u, int v, ll l):u(u), v(v), w(l){}
};

vec<edge> edges;
const ll inf = 0x3f3f3f3f3f3f3f3fLL;

ll G[450][450];

int main(){
	yccc;		
	int n, m;
	cin >> n >> m;
	for(int u = 1; u <= n; u++){
		for(int v = 1; v <= n; v++){
			G[u][v] = inf;
		}
		G[u][u] = 0;
	}
	for(int i = 0; i < m; i++){
		int u, v; ll l;
		cin >> u >> v >> l;
		edges.eb(u, v, l);
		G[u][v] = G[v][u] = min(G[u][v], l);
	}

	for(int k = 1; k <= n; k++){
		for(int u = 1; u <= n; u++){
			for(int v = 1; v <= n; v++){
				if(v == u) continue;
				G[u][v] = min(G[u][v], G[u][k] + G[k][v]);
			}
		}
	}
	/*
	for(int u = 1; u <= n; u++){
		cout << u << ": ";
		for(int v = 1; v <= n; v++){
			cout << G[u][v] << " ";
		}
		cout << endl;
	}*/

	int q;
	cin >> q;
	while(q--){
		int k;
		cin >> k;
		vec<int> B(k);
		for(int i = 0; i < k; i++){
			cin >> B[i];	
			B[i]--;
		}
		sort(al(B));
		ll ans = inf;
		do{
			for(int bts = 0; bts < (1 << k); bts++){
				ll cur = 0;
				ll u = 1;
				for(int i = 0; i < k; i++){
					if((1 << i) & bts){
						cur += G[u][edges[B[i]].v];
						cur += edges[B[i]].w;
						u = edges[B[i]].u;
					}
					else{
						cur += G[u][edges[B[i]].u];
						cur += edges[B[i]].w;
						u = edges[B[i]].v;
					}
				}	
				cur += G[u][n];
				ans = min(ans, cur);
			}
		}while(next_permutation(al(B)));
		cout << ans << endl;	
	}
	return 0;
}

