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
struct dsj{
	vec<int> pa;	
	dsj(int N){
		pa.resize(N+1);
		iota(al(pa), 0);
	}
	int root(int u){
		return pa[u] == u ? u : (pa[u] = root(pa[u]));
	}
	void merge(int u, int v){
		pa[root(v)] = root(u);
	}
};
int main(){
	yccc;		
	int N, K, L;
	cin >> N >> K >> L;
	dsj road(N), rail(N);
	REP(i, K){
		int u, v;
		cin >> u >> v;
		road.merge(u, v);
	}
	REP(i, L){
		int u, v;
		cin >> u >> v;
		rail.merge(u, v);
	}
	map<p<int>, int> ans;
	REP1(u, N){
		ans[{road.root(u), rail.root(u)}]++;
	}
	REP1(u, N){
		cout << ans[{road.root(u), rail.root(u)}] << " \n"[u == N];
	}
	return 0;
}

