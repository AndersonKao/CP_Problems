#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using vec = vector<T>;
const int INF = 2000000;
const int MAXN = 1000000;
int n, q;
vec<int> G[MAXN + 1];
int ansV[MAXN + 1];
void DFS(int u, int pa){
	ansV[u] = (pa == -1 ? u : min(u, ansV[pa]));
	for(int v:G[u]){
		if(v == pa) continue;
		DFS(v, u);
	}
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	cin >> n >> q;
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		G[u].eb(v);
		G[v].eb(u);
	}
	int op, u;	
	cin >> op >> u;
	int last = 0;
	u = ((u + last) % n + 1);
	DFS(u, -1);
	int k = u;
	REP(i, q-1){
		cin >> op >> u;
		u = ((u + last) % n + 1);
		if(op == 1){
			k = min(k, ansV[u]);
		}
		else{
			last = min(k, ansV[u]);
			cout << last << "\n";
		}
	}
	return 0;
}

