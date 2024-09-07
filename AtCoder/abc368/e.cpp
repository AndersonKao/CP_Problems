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

const int maxn = 200001;
int n, m;
ll X;
ll ans[maxn];
set<pair<ll, int>> Ts[maxn];
vec<int> G[maxn];
int indeg[maxn];
struct train{
	int A, B;
	ll S, T;
};


int main(){
	yccc;		
	cin >> n >> m >> ans[0];
	vec<train> trains(m);
	for(int i = 0; i < m; i++){
		cin >> trains[i].A;	
		cin >> trains[i].B;	
		cin >> trains[i].S;	
		cin >> trains[i].T;	
		Ts[trains[i].A].emplace(trains[i].S, i);
		endV.eb(trains[i].T, i);
	}
	sort(al(endV));

	for(int i = 0; i < m; i++){
		pair<ll, int> tosearch(trains[i].T, -1);
		auto it = Ts[trains[i].B].lower_bound(tosearch);
		
		while(it !=	Ts[trains[i].B].end()){
			G[i].eb(it->second);
			indeg[it->second]++;
			it++;
		}
	}

	queue<int> topo;
//	vec<int> topo;

	for(int i = 0; i < m; i++){
		if(indeg[i] == 0){
			topo.emplace(i);
		}
		/*
		cout << i << ": ";
		for(int v: G[i]){
			cout << v << " ";
		}
		cout << endl;
		*/
//		debug(indeg[i]);
	}
	while(topo.size()){
		int u = topo.front();
		topo.pop();
//		debug(u);
		for(int v: G[u]){
			if(trains[v].S + ans[v] < trains[u].T + ans[u]){
				ans[v] = trains[u].T + ans[u] - trains[v].S;
			}
			indeg[v]--;
			if(indeg[v] == 0){
				topo.emplace(v);
			}
		}
	}

	for(int i = 1; i < m; i++){
		cout << ans[i] << " ";
	}
	return 0;
}

