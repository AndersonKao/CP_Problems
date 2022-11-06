#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;
#define debug(x) cout << #x << ": " << x << endl;
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)
#define endl '\n'
#define F first
#define S second
#define eb emplace_back
const int maxn = 2501 ; // vertex label 0~(origin n)
int K, n;
int pval[maxn], sval[maxn], pa[maxn];
vec<int> G[maxn];
const double eps = 1e-6;
double dp[maxn+1][maxn];
// Define V(i) = Post[i]
// define P(i) = V(i) - sz(V(i))
// consider forest contains subtrees root on {V(i), V(P(i)), V(P(P(i)))...}
double val[maxn+1];
double tdp[maxn+2];
int sz[maxn+1];
int D[maxn+1];
//int Post[maxn+1];
int tstamp;
double fcmp(double a, double b = 0.0){
	if(abs(a-b) < eps)
		return 0.0;
	return a-b;
}
int dfs(int u, int pa){
	int sz = 1;
	for(int v: G[u]){
		if(v == pa) continue; 
		sz += dfs(v, u); 
	}

	// Post[++tstamp] = u;
	
	D[u] = ++tstamp;
	int i = tstamp; 

	dp[i][0] = 0.0;

	for(int num = 1; num <= tstamp; num++){
		// don't take i-th vertex in postorder
		dp[i][num] = max(dp[i][num], dp[i - sz][num]);
		// take i-th vertex in postorder
		dp[i][num] = max(dp[i][num], dp[i-1][num-1] + val[u]);
	}

	return sz;	
}


int main() {
	yccc;
	cin >> K >> n;
	n+=1;
	K+=1;
	for(int i = 1; i <= n-1; i++){
		cin >> sval[i] >> pval[i] >> pa[i];
		G[i].eb(pa[i]);
		G[pa[i]].eb(i);
	}

	double L = 0.0, R = 1e5;
	while(abs(R-L) > eps){
		double M = (R+L) / 2.0;
		for(int i = 0; i <= n; i++){
			for(int j = 0; j <= K; j++){
				dp[i][j] = -1e30;
			}
		}
		dp[0][0] = 0.0;

		val[0] = 0.0;
		for(int i = 1; i < n; i++){
			val[i] = pval[i] - M * sval[i];
		}

		tstamp = 0;
		dfs(0, -1);

		if(dp[tstamp][K] > 0.0){
			L = M;
		}
		else{
			R = M;
		}
	}
	cout << fixed << setprecision(3) << (L+R) / 2.0 << endl;
}
