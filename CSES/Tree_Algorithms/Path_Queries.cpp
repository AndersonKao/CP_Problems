// Euler tour technique
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
int t = 0;
int n,m;
const int maxn = 200001;
ll val[maxn]; //
ll seq[maxn]; // ans of u by Euler Tour Array
ll lz[maxn*4]; // lazy tag
int L[200001], R[200001]; // range of subtree of u on Euler Tour Array
vec<int> G[maxn];
void EulerTour(int u, int pa){
	L[u] = t++;
	seq[L[u]] = val[u];
	if(pa != -1){
		seq[L[u]] += seq[L[pa]];
	}
	for(int v: G[u]){
		if(v == pa) continue;
		EulerTour(v, u);
	}
	R[u] = t-1;
}

/*
void init(int L, int R, int idx){
	if(R < L) return;
	if(L == R){
		seg[idx] = seq[L];
	}
	int M = (L + R) >> 1;
	init(L, M, idx * 2);
	init(M+1, R, idx * 2 + 1);
}*/

void update(int L, int R, int idx, int l, int r, ll val){
	if(l <= L && R <= r){
		lz[idx] += val;
		return;
	}
	if(R < l || r < L){
		return;
	}
	// push lz

	lz[idx*2] += lz[idx];
	lz[idx*2+1] += lz[idx];
	lz[idx] = 0;

	int M = (L+R)>>1;
	update(L, M, idx*2, l, r, val);
	update(M+1, R, idx*2+1, l, r, val);
}

void Update(int u, ll x)
{
	ll diff = x - val[u];
	val[u] = x;
	update(0, n-1, 1, L[u], R[u], diff);
}

ll query(int L, int R,int idx, int target){
	if(L == R && L == target){
		return lz[idx];
	}

	lz[idx*2] += lz[idx];
	lz[idx*2+1] += lz[idx];
	lz[idx] = 0;

	int M = (L+R)>>1;
	if(target <= M){
		return query(L, M, idx*2, target);
	}
	else{
		return query(M+1, R, idx*2+1, target);
	}
}


ll Query(int u){
	return query(0, n-1, 1, L[u]) + seq[L[u]];
}

int main(){
	yccc;		
	cin >> n >> m;
	for(int u = 1; u <= n; u++){
		cin >> val[u];
	}
	for(int i = 0; i < n-1; i++){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
	}	

	EulerTour(1, -1);

	/*
	for(int u = 1; u <= n; u++){
		cout << u << ": " << seq[L[u]] << endl;
	}
	for(int u = 1; u <= n; u++){
		cout << u << ": " << L[u] << ", " << R[u] << endl;
	}*/
	
	//init(0, n-1, 1);

	while(m--){
		int op, u;
		cin >> op >> u;
		if(op == 1){
			ll x;
			cin >> x;
			Update(u, x);
		}
		else{
			cout << Query(u) << endl;
		}
		/*
		cout << "-----------\n";
		for(int u = 1; u <= n; u++){
			cout << u << ": " << Query(u) << endl;
		}
		cout << "-----------\n";*/
	}
	return 0;
}

