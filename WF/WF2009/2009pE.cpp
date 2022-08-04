// WA
// detect type method wrong, be care of not type reachable element should also be not type
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll disINF = 5000000000;
#define eb emplace_back
#define debug(x) cout << #x << ": " << x << endl;
struct edge{
	int u, v;
	ll cost;	
	ll add = 0;
	edge(){}
	edge(int u, int v, ll c):u(u), v(v), cost(c){}
	int getv(int u){
		return this->u == u ? this->v : this->u;
	}
	void print(){
		cout << u << ", " << v << ", " << cost << endl;
	}
};
vector<edge> Es;
vector<bool> vis;
void DFS(vector<vector<int>> &G, int u, vector<int>& topo){
	vis[u] = true;
	for(int i: G[u]){
		int v = Es[i].getv(u);
		if(vis[v] == false)
			DFS(G, v, topo);	
	}
	topo.eb(u);
}
vector<int> getTopo(vector<vector<int>> &G, int u, vector<ll>& dis, vector<bool>& type){
	vis.resize(G.size());
	fill(vis.begin(), vis.end(), false);
	vector<int> topo;
	DFS(G, u, topo);	
	reverse(topo.begin(), topo.end());
	dis.resize(G.size());
	fill(dis.begin(), dis.end(), disINF);
	dis[u] = 0;
	type[u] = true;
	for(int& u: topo){
		for(int ei: G[u]){
			int v = Es[ei].getv(u);
			ll cost = Es[ei].cost;
			if(dis[v] == disINF){
				dis[v] = dis[u] + cost;
				type[v] = true;
			}
			else if(dis[v] != dis[u] + cost){
				if(dis[v]	> dis[u] + cost)
					dis[v] = dis[u] + cost;
				type[v] = false;
			}
			if(type[u] == false)
				type[v] = false;
		}	
	}
	return topo;	
}
int main(){
	int N, R;
	int caseN = 1;
	while(cin >> N >> R){
		if(N == 0 && R == 0)
			break;
		Es.clear();
		vector<vector<int>> G(N);
		vector<vector<int>> reG(N);
		for(int i = 0; i < R; i++){
			int u, v;
			ll c;
			cin >> u >> v >> c;
			u--, v--;
			G[u].eb(Es.size());
			reG[v].eb(Es.size());
			Es.eb(u, v, c);
		}
#ifdef DEs
		int ei = 0;
		for(edge&e : Es){
			cout << ei++ << ": ";
			e.print();
		}
#endif
		vector<ll> disS(N, disINF);
		vector<ll> disT(N, disINF);
		vector<bool> typeA(N, false), typeB(N,false);
		vector<int> topo = getTopo(G, 0, disS, typeA);
		vector<int> retopo = getTopo(reG, N-1, disT, typeB);
#ifdef Dtopo
		cout << "topo:\n";
		for(int u: topo){
			cout << u << " ";
		}
		cout << endl;
		cout << "retopo:\n";
		for(int u: retopo){
			cout << u << " ";
		}
		cout << endl;
		cout << "typeA: ";
		for(int u = 0; u< N; u++)
			if(typeA[u]) cout << u << " ";
		cout << endl;
		cout << "typeB: ";
		for(int u = 0; u< N; u++)
			if(typeB[u]) cout << u << " ";
		cout << endl;
#endif
		if(typeA[N-1]){
			cout << "Case " << caseN++ << ": ";	
			cout << "0 " << disS[N-1] << endl;
			continue;
		}
		bool sol = true;
		for(int u = 0; u < N; u++){
			if(typeA[u] == false && typeB[u] == false)
				sol = false;
		}
		if(sol == false){
			cout << "Case " << caseN++ << ": No solution\n";
			continue;
		}
		vector<ll> ldisS(N, 0);		// longest distance from S;
		for(int u: topo){
			for(int i : G[u]){
				int v = Es[i].getv(u);
				ll c = Es[i].cost;
				if(ldisS[v] < ldisS[u] + c){
					ldisS[v] = ldisS[u] + c;
				}
			}	
		}	
		vector<int> adjE;
		ll ubdis= ldisS[N-1]; // upper bound distance, adjust all to this one
		for(int i = 0; i < Es.size(); i++){
			if(typeA[Es[i].u] && typeB[Es[i].u] == false && typeB[Es[i].v]){
				// type A -> type (A)B
				Es[i].add = ubdis - ldisS[Es[i].u] - Es[i].cost - disT[Es[i].v];
				if(Es[i].add != 0)
					adjE.eb(i);
			}
		}

		cout << "Case " << caseN++ << ": " << adjE.size() << " " << ldisS[N-1] << endl;

		for(int i: adjE){
			cout << i + 1 << " " << Es[i].add << endl;
		}
	}
		
	return 0;
}
