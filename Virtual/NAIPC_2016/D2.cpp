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
const int maxn = 2500 ;
int K, n;
int pval[maxn + 2], sval[maxn + 2], pa[maxn + 2];
vec<int> G[2500+1];
const double eps = 1e-6;
double dp[maxn+1][maxn+2];
double val[maxn+1];
double tdp[maxn+2];
int sz[maxn+1];
double fcmp(double a, double b = 0.0){
	if(abs(a-b) < eps)
		return 0.0;
	return a-b;
}
void dfs(int u, int pa){
	sz[u] = 1;
	for(int v: G[u]){
		if(v == pa) continue; 
		dfs(v, u); 
		sz[u] += sz[v];
	}

	dp[u][0] = 0.0;
	dp[u][1] = 0.0;
	int prsz = 1;
	for (int v: G[u]){

		if(v == pa) continue;

		fill(tdp, tdp+sz[u]+1, -1e30);
		prsz += sz[v];
		for(int num = 2; num <= min(prsz, K); num++){
			for(int k = max(0, num - prsz + sz[v]); k <= sz[v] && k <= num-1; k++){
				tdp[num] = max(tdp[num], dp[u][num-k] + dp[v][k]); 
			}
		}

		for(int num = 2; num <= min(prsz, K); num++){
			dp[u][num] = tdp[num];
		}
	//	debug(v);
		/*
		cout << "dp: ";
		for(int num = 1; num <= sz[u]; num++){
			cout << dp[u][num] << " ";
		}
		cout << endl;
		*/
	}
	for(int num = 1; num <= min(sz[u], K); num++){
		dp[u][num] += val[u];
	}
	/*
	cout << "dp: ";
	for(int num = 1; num <= sz[u]; num++){
		cout << dp[u][num] << " ";
	}
	cout << endl;
	*/

}


int main() {
	yccc;
	cin >> K >> n;
	K+=1;
	for(int i = 1; i <= n; i++){
		cin >> sval[i] >> pval[i] >> pa[i];
		G[i].eb(pa[i]);
		G[pa[i]].eb(i);
	}
	double L = 0.0, R = 1e5;
	while(abs(R-L) > eps){
		double M = (R+L) / 2.0;

		for(int i = 0; i <= n; i++){
			for(int j = 0; j <= K+1; j++){
				dp[i][j] = -1e30;
			}
		}

		val[0] = 0.0;
		for(int i = 1; i <= n; i++){
			val[i] = pval[i] - M * sval[i];
		}

		/*
		cout << "val: ";
		for(int i = 1; i <= n; i++){
			cout << val[i] << " ";
		}
		cout << endl;
		*/

		dfs(0, -1);

		/*
		for(int u = 0; u <= n; u++){
			for(int i = 0; i <= sz[u]; i++){
				cout << u << ": " << i << " " << dp[u][i] << endl;
			}
		}
		cout << endl;

		debug(dp[0][k+1]);
		*/

		if(dp[0][K] > 0.0){
			L = M;
		}
		else{
			R = M;
		}
	}
	cout << fixed << setprecision(3) << (L+R) / 2.0 << endl;
}
