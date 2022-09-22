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
vector<int> G[100000];
bool pred[100000] = {false};
set<int> reach[100000];

void annotate(int u, int r){
	if(reach[u].size() >= 2) return ;
	reach[u].emplace(r);
	for(int v: G[u]){
		if(reach[v].count(r) || reach[v].size() >= 2) continue;
		annotate(v, r);
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	int st;
	cin >> st;
	REP(i, m){
		int u, v;
		cin >> u >> v;
		if(v != st)
			G[v].eb(u);
		else{
			pred[u] = true;
		}
	}
	for(int u = 0; u < n; u++){
		if(u == st || pred[u] == false) continue;
		annotate(u, u);
	}
	vector<int> V;
	for(int u = 0; u < n; u++){
		if(pred[u] == true && reach[u].size() == 1){
			V.eb(u);
		}
	}
	cout << V.size() << endl;
	for(int v: V)
		cout << v << endl;
	return 0;
}

