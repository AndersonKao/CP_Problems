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
ll val[200000];
ll sum[200000];
vector<vector<int>> G;
pii diaV(0, 0);
int diaLen = 0;
pii DFS_dia(int u, int pa){
	int di1 = 1, di2 = 1;
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
	/*
	debug(u + 1);
	debug(di1v + 1);
	debug(di1);
	debug(di2v + 1);
	debug(di2);
	*/
	return make_pair(di1 + 1, di1v);
}
vector<vector<pii>> mQ;
vector<int> mANS;
int st[200000];
int sti;
void DFS(int u, int pa, int depth){
	for(pii& v: mQ[u]){
		if(mANS[v.S] != -1)continue;
		if(v.F <= depth){
			mANS[v.S] = st[sti - v.F]+1;
		}
	}
	st[sti++] = u;
	for(int v: G[u]){
		if(v == pa)continue;
		DFS(v, u, depth+1);
	}
	sti--;
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
	cin >> q;
	mQ.resize(n);
	mANS.resize(q, -1);
	REP(i, q){
		int u, len;
		cin >> u >> len;
		u--;
		mQ[u].eb(len, i);
	}

	DFS_dia(0, -1);
	sti = 0;
	DFS(diaV.F, -1, 0);
	sti = 0;
	DFS(diaV.S, -1, 0);
	for(int i = 0; i < q; i++){
		cout << mANS[i] << endl;
	}
	return 0;
}

