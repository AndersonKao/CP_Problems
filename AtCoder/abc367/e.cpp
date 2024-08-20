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

int G[200001][100];
int label[200001];

int main(){
//	yccc;		
	int n;
	ll k;
	cin >> n >> k;
	for(int u = 1; u <= n; u++){
		int v;
		cin >> G[u][0];
	}
	for(int u = 1; u <= n; u++){
		cin >> label[u];
	}
	for(int t = 1; t < 100; t++){
		for(int u = 1; u <= n; u++){
//			debug(G[u][t-1]);
			G[u][t] = G[G[u][t-1]][t-1];
		}
	}

	for(int u = 1; u <= n; u++){
		int v = u;
		for(ll i = 0; (1LL << i) <= k; i++){
			if((1LL << i) & k){
//				debug(G[v][i]);
				v = G[v][i];
			}
		}
		cout << label[v] << " ";
	}
	return 0;
}

