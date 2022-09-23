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
vec<int> G[200000];
int val[200000];
ll seq[200001] = {0};
int n, m;	
ll query(int idx){
	ll ans = 0;
	while(idx > 0){
		ans += seq[idx];
		idx -= idx & (-idx);
	}
	return ans;
}
void modify(int idx, ll val){
	while(idx <= n){
		seq[idx] += val;
		idx += idx & (-idx);
	}
}

int t = 1;
int l[200000], r[200000]; // [l, r].

void DFS(int u, int pa){
	l[u] = t;	
	for(int v:G[u]){
		if(v == pa) continue;
		DFS(v, u);
	}
	r[u] = t;
	t++;
}

int main(){
	cin >> n >> m;
	REP(i, n){
		cin >> val[i];
	}
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v), G[v].eb(u);
	}
	DFS(0, 0);
	REP(u, n){
		modify(r[u], val[u]);
	}
	REP(i, m){
		int op, u, x;
		cin >> op >> u;
		u--;
		if(op == 1){
			cin >> x;
			modify(r[u], x - val[u]);
			val[u] = x;
		}
		else{
			cout << query(r[u]) - query(l[u] - 1) << endl;
		}
	}
		
	return 0;
}

