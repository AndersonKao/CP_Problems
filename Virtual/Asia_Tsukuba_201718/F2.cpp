#include <bits/stdc++.h>
using namespace std;

template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define eb emplace_back
#define F first
#define S second
#define al(a) a.begin(),a.end()
using ll = long long;
const ll inf = 200000000000;
using edge = pair<ll, int>;
vec<vec<edge>>G;
vec<vec<edge>>rG;
int n, m;
void dijkstra(int s, vec<vec<edge>>&G, vec<ll>& dis, vec<int>& from){
	dis.resize(G.size(), inf);	
	from.resize(G.size(), 0);	
	dis[s] = 0;
	from[s] = s;
	priority_queue<edge, vec<edge>, greater<edge>> pq;
	pq.emplace(0, s);
	while(pq.size()){
		int u;
		ll d;
		tie(d, u) = pq.top();
		pq.pop();
		if(d != dis[u]) continue;
		for(edge&e: G[u]){
			int v;
			ll w;
			tie(w, v) = e;
			if(dis[v] > dis[u] + w){
				dis[v] = dis[u]+w;
				from[v] = u;
				pq.emplace(dis[v], v);
			}
		}
	}
}
vector<tuple<int ,int, ll>> Es;
vector<p<int>> EGid;

using con = pair<int, int>;

struct tarjan{
	vector<vector<int>> G;
	vector<int> D;
	vector<int> L;
	vector<con> edgeBridge;
	vector<int> APnode;
	int timestamp;
	tarjan(int size = 1){
		init(size);
	}
	void init(int size = 1){
		timestamp = 1;
		G.clear(), D.clear(), L.clear();
		G.resize(size);
		D.resize(size, 0);
		L.resize(size, 0);
		edgeBridge.clear();
		APnode.clear();
	}
	void addedge(int u, int v){
		G[u].eb(v);
		G[v].eb(u);
	}
	void DFS(int v, int pa){
		D[v] = L[v] = timestamp++;
		int Childcount = 0;
		bool isAP = false;
		for(int w: G[v]){
			if(w == pa)
				continue;
			if(!D[w]){
				DFS(w, v);
				Childcount++;
				if(D[v] <= L[w])
					isAP = true;
				if(D[v] < L[w]){
					edgeBridge.eb(v, w);
				}
				L[v] = min(L[v], L[w]);
			}
			L[v] = min(L[v], L[w]);
		}
		if(v == pa && Childcount < 2)
			isAP = false;
		if(isAP)
			APnode.eb(v);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> n>> m;	
	G.resize(n+1);
	rG.resize(n+1);
	for(int i = 0; i< m; i++){
		int u, v, w;
		cin >> u>> v >> w;
		EGid.eb(G[u].size(), rG[v].size());
		G[u].eb(w, v);
		rG[v].eb(w, u);
		Es.eb(u, v, w);
	}
	vec<ll> Gdis, rGdis;
	vec<int> Gfrom, rGfrom;
	dijkstra(1, G, Gdis, Gfrom);
	dijkstra(2, rG, rGdis, rGfrom);

	vec<int> cnt(n+1, 0);
	for(int u = 1; u <= n; u++){
		for(edge& e: rG[u]){
			int v; ll w;
			tie(w, v) = e;	
			if(Gdis[u] == Gdis[v] + w){
				cnt[u]++;
			}
		}
	}
	tarjan inG(n+1);
	for(tuple<int, int ,ll>&e: Es){
		int u, v;
		ll w;
		tie(u, v, w) = e;
		if(Gdis[u] + rGdis[v] + w == Gdis[2]){ 
			inG.addedge(u, v);
		}
	}
	for(int u = 1; u <= n; u++){
		inG.DFS(u, u);
	}
	sort(al(inG.edgeBridge));
	/*
	for(con&e : inG.edgeBridge){
		cout << e.F << ", " << e.S << endl;
	}
	*/


	for(tuple<int, int ,ll>&e: Es){
		int mans = 0; // 1 for happy 2 for soso 3 for bad
		int u, v;
		ll w;
		tie(u, v, w) = e;

		if(Gdis[v] + w + rGdis[u] < Gdis[2]){
			mans = 1;
		}
		else {
				p<int> mp(u, v);
				auto it = lower_bound(al(inG.edgeBridge), mp);
				if(it != inG.edgeBridge.end() && it->F == mp.F && it->S == mp.S){
//					cout << "found : " << mp.F << ", " << mp.S << endl;
					mans = 3;
				}
				else
					mans = 2;
		}
		if(mans == 1){
			cout << "HAPPY";
		}
		else if(mans == 2){
			cout << "SOSO";
		}
		else
			cout << "SAD";
		cout << endl;
	}
}
