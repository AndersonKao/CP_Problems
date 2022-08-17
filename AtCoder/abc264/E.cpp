#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(x) x.begin(), x.end()
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << x.first << ", " << x.second << endl;
using ll = long long;
using pii = pair<int, int>;
#define MAX_N 200005;
#define enp pair<int, int> // edge-weight, node-index
#define con pair<int, int> // connection
template<typename T>
using vec = vector<T>;
#define eb emplace_back
struct disJ{
	vec<int> pa;
	vec<int> sz;
	void init(int n){
		pa.resize(n);
		sz.resize(n, 1);
		REP(i, n){
			pa[i] = i;
		}
	}
	int getpa(int u){
		if(pa[u] == u)
			return u;
		return getpa(pa[u]);
	}
	void join(int u, int v){
		int pv = getpa(v);
		int pu = getpa(u);
		if(same(pu, pv))
			return;
		if(sz[pv] < sz[pu]){
			pa[pv] = pu;
			sz[pu] += sz[pv];
		}
		else{
			pa[pu] = pv;
			sz[pv] += sz[pu];
		}
	}
	bool same(int u, int v){
		return getpa(u) == getpa(v);
	}
};

int N, M, E;
vector<pii> Es;
//vector<bool> vis;
vector<bool> elecd;
vector<bool> ava;
//vector<vector<int>> G;
/*
void DFScc(int u, int pa){
	//debug(u);
	vis[u] = true;
	elecd[u] = (elecd[u] || elecd[pa]);
	for(int ei : G[u]){
		if(ava[ei] == false)
			continue;
		int v = (Es[ei].F == u ? Es[ei].S : Es[ei].F);
		if(vis[v] == false){
			DFScc(v, u);		
		}
		elecd[u] = (elecd[u] || elecd[v]);
	}
}
*/

int main(){
	cin >> N >> M >> E;	
	elecd.resize(N+M, false);
	disJ mJ;
	mJ.init(N+M);
	ava.resize(E, true);
	REP(i, E){
		int u, v;
		cin >> u >> v;
		u--, v--;
		Es.eb(u, v);
	}	
	int Q;
	cin >> Q;
	vector<int> Qs(Q);
	REP(i, Q){
		cin >> Qs[i];
		Qs[i]--;
		ava[Qs[i]] = false;
	}
	for(int i = N; i < N+M; i++){	
		elecd[i] = true;
	}
	REP(i, E){
		if(ava[i]){
			int pL = mJ.getpa(Es[i].F), pR = mJ.getpa(Es[i].S);
			mJ.join(Es[i].F, Es[i].S);
			if(elecd[pL] || elecd[pR]	)
				elecd[pL] = elecd[pR] = true;
		}
	}
	int ans = 0;
	/*
	for(int i = 0; i < N+M; i++){
		if(vis[i] == false)
			DFScc(i,i);
	}
	*/
	vector<int> ANS;
	for(int i = 0; i < N+M; i++){	
		if(elecd[mJ.getpa(i)]){
			ans++;
		}
	}
	ANS.eb(ans);
	for(int i = Q-1; i >= 0; i--){
		pii&e = Es[Qs[i]];
		int pL = mJ.getpa(e.F), pR = mJ.getpa(e.S);
		if(mJ.same(pL, pR) == false){
			if(elecd[pL] && elecd[pR] == false){
				ans += mJ.sz[pR];
				elecd[pL] = elecd[pR] = true;
			}
			if(elecd[pR] && elecd[pL] == false){
				ans += mJ.sz[pL];
				elecd[pL] = elecd[pR] = true;
			}
			mJ.join(pL, pR);
		}
		/*
		for(int i = 0; i < N+M; i++){	
			cout << mJ.cities[i] << " ";
		}
		cout << endl;
		*/
		ANS.eb(ans);
	}
	for(int i =  Q-1; i >= 0; i--)
		cout << ANS[i] - M << endl;
	return 0;
}

