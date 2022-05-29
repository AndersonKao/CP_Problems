#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
using ll = long long;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;

#define debug(x) cout << #x << ": " << x << endl;
const int INF = 100000;
vec<vec<int>> G;
int main(){
	int N;
	int E;
	cin >> N;
	cin >> E;
	G.resize(N, vec<int>(N, INF));
	REP(i, E){
		int u, v, w;
		cin >> u >> v >> w;
		u--, v--;
		G[u][v] = w;
	}
	REP(i, N)
		G[i][i] = 0;
	vec<vec<int>> dis = G;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if(dis[i][j] == INF)
				cout << "x, ";
			else
				cout << dis[i][j]<< ", ";
		}
		cout << endl;
	}
	cout << "-------------\n\n";
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
		}
		cout << "using: ";
		for(int i = 0; i <= k; i++)
			cout << i+1 << (i == k  ? "\n" : ", ");
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++){
				if(dis[i][j] == INF)
					cout << "x, ";
				else
					cout << dis[i][j]<< ", ";
			}
			cout << endl;
		}
		cout << "-------------\n\n";
	}

		return 0;
}
