#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;

#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
int n;
vec<vec<int>> G;
int selected[100001];
int dp[100001];
int sz[100001];
int pa[100001];
int Tnum = 0;
vec<vec<int>> Ts;

void DFS(int u, int pa, int rt){
	sz[u] = 1;
	dp[u] = 0;
	for(int v:G[u]){
		DFS(v, u, rt);
		sz[u] += sz[v];
		dp[u] += dp[v];
	}
	if(pa != u && !selected[pa] && !selected[u]){
		dp[u] += 1;
		selected[pa] = selected[u] = true;
	}
	else if(!selected[u]){
		Ts[rt].eb(u);
	}
	
}
struct tdata{
	int u;
	int whitenum;
	tdata(){}
	tdata(int a, int b):u(a), whitenum(b){}
};

int main() {		
#ifndef Kao 
	freopen("hidden.in", "r", stdin);
	freopen("hidden.out", "w", stdout);
#endif
	cin >> n;
	G.resize(n+1);
	Ts.resize(n+1);
	for(int i = 2; i <= n; i++){
		cin >> pa[i];
		G[pa[i]].eb(i);
	}
	G[0].eb(1);
	Tnum = 0;
	for(int u: G[0]){
		DFS(u, u, u);
		Tnum++;
	}
	auto cmp = [](tdata&a, tdata&b){
		if(selected[a.u] != selected[b.u]){
			return selected[a.u] < selected[b.u];
		}
		return a.whitenum < b.whitenum;
	};
	priority_queue<tdata, vec<tdata>, decltype(cmp)> pq(cmp);
	for(int u: G[0]){
		if(u == 1) continue;
		pq.emplace(u, sz[u] - dp[u] * 2);
	}
	tdata mt(1, sz[1] - dp[1] * 2);
	while(pq.size()){
		tdata top = pq.top();	
		pq.pop();
//		cout << top.u << " " << top.whitenum << endl;
		if(selected[top.u] || Ts[1].size() == 0){
			pa[top.u] = 1;
			mt.whitenum += top.whitenum;
			for(int v: Ts[top.u])
				Ts[1].eb(v);
		}
		else{
			pa[top.u] = Ts[1].back();	
			Ts[1].pop_back();
			mt.whitenum += top.whitenum - 2;
			selected[top.u] = selected[pa[top.u]] = true;
			for(int v: Ts[top.u]){
				if(v == top.u) continue;
					Ts[1].eb(v);
			}
		}
//		cout << mt.u << ", " << mt.whitenum << endl;
	}

	// debug

	cout << (n - mt.whitenum) / 2<< endl;
	for(int u = 2; u <= n; u++){
		cout << pa[u] << (u == n ? "\n": " ");
	}

	return 0;
}
