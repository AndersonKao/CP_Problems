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

using pli = pair<ll, int>;
const ll inf = 300000000000000;
vector<vector<int>> G;
pii diaV(0, 0);
int diaLen = 0;
pii DFS_dia(int u, int pa){
	int di1 = 0, di2 = 0;
	int di1v = u, di2v = u;
	for(int v: G[u]){
		if(v == pa)
			continue;
		int leaf, cur;
		tie(cur, leaf) = DFS_dia(v, u);
		
		if(cur >= di1){
			di2 = di1;
			di1 = cur;
			di2v = di1v;
			di1v = leaf;
		}
		else if(cur > di2){
			di2 = cur;
			di2v = leaf;
		}
	}
	if(di1 + di2 > diaLen){
		diaLen = di1 + di2;
		diaV = pii(di1v, di2v);
	}
	return make_pair(di1 + 1, di1v);
}
int main(){
	int n;
	cin >> n;
	int q;
	G.resize(n);
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
		G[v].eb(u);
	}
	DFS_dia(0, -1);
	cout << diaLen << endl;
	return 0;
}
