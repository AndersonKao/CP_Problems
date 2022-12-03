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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 100000;
using edge = pair<int, int>;
vec<edge> G[maxn];
int dis[maxn];
const int inf = 0x3f3f3f3f;
void addedge(int u, int v, int w){
	G[u].eb(w, v);	
}
int main(){
	yccc;		
	int K;
	cin >> K;
	for(int u = 1; u < K; u++){
		addedge(u, (u+1 == K ? 0 : u+1), 1);
		addedge(u, 10*u % K, 0);
	}
	fill(dis, dis + K, inf);
	priority_queue<edge, vec<edge>, greater<edge>> pq;
	pq.emplace(dis[1] = 0, 1);
	while(pq.size()){
		int u, curd;
		tie(curd, u) = pq.top();
		pq.pop();
		if(curd != dis[u])
			continue;
		for(edge& e: G[u]){
			int v, w; tie(w, v) = e;
			if(dis[u] + w < dis[v]){
				pq.emplace(dis[v] = dis[u] + w, v);
			}
		}
	}
	cout << dis[0] + 1 <<endl;;

	return 0;
}

