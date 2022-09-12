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
int n;
vec<vec<tuple<int, int ,int>>> G;
ll finalans = 0;
struct edge{
	ll ans_inc, ans_dec ;
	int w;
	edge(){
		ans_inc = ans_dec = 1;
	}
};
vector<edge> E;

void DFS(int u, int pa, int paei){
//	cout << "visiting " << u << endl;
	for(int i = 0 ; i < G[u].size() ;i++){
		int v, w, ei;
		tie(w, v, ei) = G[u][i];
		if(v == pa)
			continue;
		DFS(v, u, ei);
	}

	if(paei != -1){
		int pw = E[paei].w;
		for(int i = 0; i < G[u].size(); i++){
			int v, w, ei;
			tie(w, v, ei) = G[u][i];
			if(v == pa)
				continue;
			if(w < pw){
				E[paei].ans_inc += E[ei].ans_inc;	
			}
			else if(w > pw){
				E[paei].ans_dec += E[ei].ans_dec;	
			}
		}
		/*
		printf("metadata for %d\n", u);
		debug(E[paei].ans_inc);
		debug(E[paei].ans_dec);
		debug(E[paei].w);
		*/
	}
//	cout << "generating " << u << "ans\n";
	ll cur_inc = 0;
	ll accu_inc = 0;
//	cout << "inc:\n";
	for(int i = 0; i < G[u].size(); i++){
		int v, w, ei;
		tie(w, v, ei) = G[u][i];
		if(v == pa)
			continue;

		if(i > 0){
			int pv, pw, pei;
			tie(pw, pv, pei) = G[u][i-1];
			if (pv == pa){
				if(i > 1)
					tie(pw, pv, pei) = G[u][i-2];
				else pw = 0;
			}
			if(w != pw){
				cur_inc += accu_inc;
				accu_inc = 0;
			}
		}
		/*
		printf("doing %d root %d\n", u, v);
		debug(cur_inc);
		debug(E[ei].ans_dec);
		*/
		finalans += E[ei].ans_dec * cur_inc;
		accu_inc += E[ei].ans_inc;
		finalans += E[ei].ans_inc;
//		debug(finalans);
	}
//	cout << "dec:\n";
	ll cur_dec = 0;
	ll accu_dec = 0;
	for(int i = G[u].size()-1; i >= 0; i--){
		int v, w, ei;
		tie(w, v, ei) = G[u][i];
		if(v == pa)
			continue;
		/*
		if(i+1 < G[u].size() && w != get<0>(G[u][i+1])){
			cur_dec += accu_dec;
			accu_dec = 0;
		}
		//printf("doing %d root %d\n", u, v);
		//debug(cur_dec);
		//debug(E[ei].ans_inc);
		//finalans += E[ei].ans_inc * cur_dec;
		//accu_dec += E[ei].ans_dec;
		//debug(finalans);
		*/
		finalans += E[ei].ans_dec;
	}
/*
	cout << "done " << u << endl;
	debug(finalans);
	*/
}

int main(){
	cin >> n;
	G.resize(n);
	E.resize(n-1);	
	REP(i, n-1){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		G[u].eb(w, v, i);
		G[v].eb(w, u, i);
		E[i].w = w;
	}
	REP(u, n){
		sort(al(G[u]));
	}
	DFS(0, -1, -1);
	cout << finalans << endl;;
	return 0;
}

