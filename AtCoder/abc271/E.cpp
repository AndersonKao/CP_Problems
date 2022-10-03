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

ll inf = 300000000000000;
template<typename T>
using vec = vector<T>;
int seq[200005];
vec<int> numid[200005];
struct edge{
	int u, v;
	ll c;
};
int main(){
	int N, M, K;		
	cin >> N >> M >> K;
	vec<ll> sdis(N+1, inf);	
	vec<edge> E(M);
	REP(i, M){
		cin >> E[i].u >> E[i].v >> E[i].c;
	}
	REP(i, K){
		cin >> seq[i];
		seq[i]--;
	}
	sdis[1] = 0;
	for(int i = 0; i < K; i++){
		int eid = seq[i];
		sdis[E[eid].v] = min(sdis[E[eid].u] + E[eid].c, sdis[E[eid].v]);
	}
	if(sdis[N] == inf){
		cout << -1 << endl;
	}
	else
	cout << sdis[N] << endl;
	return 0;
}

