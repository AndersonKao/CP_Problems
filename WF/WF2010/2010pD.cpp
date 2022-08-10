#include <bits/stdc++.h>
#define eb emplace_back
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define mp make_pair
#define debug(x) cout << #x << ": " << x << endl;
using namespace std;
using pii = pair<int ,int>;
vector<pii> Vs;
vector<vector<int>>G;
pii DFS(int u, int pa){
//	debug(u);
	vector<pii> need;
	for(int v: G[u]){
		if(v ==pa)
			continue;
		need.eb(DFS(v, u));
	}
	sort(al(need), [](pii&a, pii&b){
		return (a.F - a.S) > (b.F - b.S);
	});

	int A = Vs[u].F, B = Vs[u].S;
	for(pii& e: need){
//		cout << "doing :" << e.F << ", " << e.S << endl;
		A = max(A, B + e.F);
		B += e.S;
	}
	return mp(A, B);
}
int main(){
	int n;
	int caseN = 1;
	while(cin >> n){
		if(n == 0)
			break;
		G.clear();
		G.resize(n);
		Vs.clear();
		for(int i = 0; i < n; i++){
			int a, m,g;
			cin >> a >> m >> g;
			Vs.eb(max(a, m+g), m+g);
		}
		for(int i = 0; i < n-1; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			G[u].eb(v);
			G[v].eb(u);
		}
		int ans = numeric_limits<int>::max();
		for(int u = 0; u < n; u++){
			ans = min(ans, DFS(u, -1).F);
		}
		cout << "Case " << caseN++ << ": " << ans << endl;
	}
	return 0;
}
