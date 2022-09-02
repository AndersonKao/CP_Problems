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
const ll disINF = 1000000000LL;
int n, m;
int h;
vector<int>Aset, Bset;
ll G[20][20];
int Atarget;
void solve(){
	cout << "Aset: ";
	for(int u: Aset){
		cout << u <<", " ;
	}
	cout << endl;
	
}
void enumA(int curd){
	if((Aset.size() - 1) == Atarget){
		solve();
	}
	if(curd == n-1){
		return;
	}
	if(((n - 2) - curd + 1)+ (Aset.size()-1) < Atarget){
		return;
	}
	Aset.eb(curd);
	enumA(curd+1);
	Aset.pop_back();
	enumA(curd+1);
}

int main(){
	int casen=1;
	while(cin >> n >> m){
		cout << "Case " << casen++ << ":\n";
		h = n-2;
		Atarget = h/2;
		REP(i, n){
			REP(j, n){
				if(i == j)
					G[i][j] = 0;
				else
					G[i][j] = disINF;
			}
		}
		for(int i = 0; i < m; i++){
			int u,v,t;
			cin >> u >> v >> t;
			G[u][v] = (G[v][u] = t);
		}
		// floyd-Warshall
		for(int k = 0; k < n; k++){
			for(int u = 0; u < n; u++){
				for(int v = 0; v < n; v++){
					if(G[u][v] > G[u][k] + G[k][v]){
						G[u][v] = G[u][k] + G[k][v];
					}
				}
			}
		}
		Aset.eb(0);
		enumA(1);
	}
		
	return 0;
}

