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
vec<vec<ll>> G;
const ll mod = 1000000007;
vec<vec<ll>> mul(const vec<vec<ll>>& A,const vec<vec<ll>> & B){
	vec<vec<ll>> C(A.size(), vec<ll>(B[0].size(), 0));
	if(A[0].size() != B.size())
		return C;
	for(int i = 0; i < C.size(); i++){
		for(int j = 0; j < C[i].size(); j++){
			for(int k = 0; k < A[0].size(); k++){
				(C[i][j] += A[i][k] * B[k][j] % mod) %= mod;
			}
		}
	}

	return C;
}
vec<vec<ll>> binpow(vec<vec<ll>> &G, int k){
	vec<vec<ll>> res = G;
	vec<vec<ll>> ans(G.size(), vec<ll>(G.size(), 0));
	for(int i = 0; i < ans.size(); i++){
		ans[i][i] = 1;
	}
	while(k > 0){
		if(k & 1){
			ans = mul(ans, res);	
		}
		res = mul(res, res);
		k >>= 1;
	}
	return ans;
}
int main(){
	yccc;		
	int n, m, k;
	cin >> n >> m >> k;
	G.resize(n, vec<ll>(n, 0));
	REP(i, m){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u][v]++;
//	   	G[v][u]++;
	}
	vec<vec<ll>> F = binpow(G, k);
	cout << F[0][n-1];
	return 0;
}

