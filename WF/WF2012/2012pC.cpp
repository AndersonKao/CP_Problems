// new time complexity (n^3 + nCr + 2^n*n*n)
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(v) for(int a: v) cout << a << " "; cout << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
template<typename T>
using p = pair<T,T>;
const ll disINF = 1000000000000LL;
template<typename T>
using vec = vector<T>;
int n, m;
int h;
ll ANS;
int Aset[20], Bset[20];
bool computed[(1<<20)];
int Aid, Bid;
vec<vec<int>> bitpat;
ll G[20][20];
int Atarget;
ll counter = 0;
//vector<vector<ll>> dpA, dpB;
ll dpA[(1 << 20)][20];
ll dpB[(1 << 20)][20];

void go_dp(ll dp[][20]){
	// finish i set (bit-pattern), ending at A[i] hotel.
	for(int i = 0; i < (1 << n); i++){
		fill(dp[i], dp[i] + n, disINF);
	}
	if(dp == dpA){
		dp[1][0] = 0;
	}
	else{
		dp[1 << (n-1)][n-1] = 0;
	}
//	cout << "godp\n";
	int sz = (1 << n);
	for(int mask = 2; mask < sz; mask++){
		for(int i : bitpat[mask]){
			int submask = mask ^ (1 << i);
			for(int j: bitpat[submask]){
				dp[mask][i] = min(dp[mask][i], dp[submask][j] + G[i][j]);
			}
		}
	}
}

void solve(){
//	Bset.clear();
	int Asetmask = 0;
	for(int i = 1; i < Aid; i++){
		Asetmask |= (1 << Aset[i]);
	}
	if(computed[Asetmask]){
		return;
	}
	int ita = Aid-1;
	Bid = 0;
	int Bsetmask = 0;
	for(int i = n-1; i >= 0; i--){
		if(ita >= 0 && i == Aset[ita]){
			ita--;
			continue;
		}
		Bset[Bid++] = i;
		if(i < n-1)
			Bsetmask |= (1 << i);
	}	
//	cnter++;
	computed[Asetmask] = computed[Bsetmask] = true;
//	cout << "doit " << bitset<64>(Asetmask) << " and " << bitset<64>(Bsetmask) << endl;
#ifdef Dset
	cout << "Aset: ";
	for(int u: Aset){
		cout << u <<", " ;
	}
	cout << endl;
	cout << "Bset: ";
	for(int u: Bset){
		cout << u <<", " ;
	}
	cout << endl;
	return;
#endif
	
	int Amask = Asetmask ^ 1;
	int Bmask = Bsetmask ^ (1 << (n-1));
	ll curans = 0, toadd = disINF;
	for(int u = 0; u < Aid; u++){
		for(int v = 0; v < Bid; v++){
			toadd = min(dpA[Amask][Aset[u]] + G[Aset[u]][Bset[v]] + dpB[Bmask][Bset[v]], toadd);
		}
	}
	curans += toadd;
	swap(Aset[0], Bset[0]);
	toadd = disINF;
	Amask = Asetmask ^ (1 << (n-1));
	Bmask = Bsetmask ^ 1;
	for(int u = 0; u < Aid; u++){
		for(int v = 0; v < Bid; v++){
			toadd = min(dpB[Amask][Aset[u]] + G[Aset[u]][Bset[v]] + dpA[Bmask][Bset[v]], toadd);
		}
	}
	curans += toadd;
	ANS = min(ANS, curans);
	swap(Aset[0], Bset[0]);
}
//vector<vector<vector<int>>> allset;
void enumA(int curd, int curgen){
	if(Aid == Atarget){
//		allset[curgen].eb(Aset);
		solve();
//		enumcnt++;
		return;
	}
	if(curd == curgen-1)
		return;
	if(((curgen - 1) - curd + Aid) < Atarget)
		return;
	enumA(curd+1, curgen);
	Aset[Aid++] = curd;
	enumA(curd+1, curgen);
	Aid--;
}
void genallset(){
	bitpat.resize(1 << 20);
	for(int i = 1; i < (1 << 20); i++){
		int len = __lg(i) + 1;
		for(int k = 0; k < len; k++){
			if(i & (1 << k)){
				bitpat[i].eb(k);
			}
		}
	}
}

int main(){
	genallset();
	int casen=1;
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	while(cin >> n >> m){
		Atarget = (n-2)/2 + 1; // add one for headquarters
		ANS = disINF;
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
						G[u][v] = min(G[u][v], G[u][k] + G[k][v]);
				}
			}
		}
		fill(computed, computed+(1<<n), false);
		go_dp(dpA);
		go_dp(dpB);
		Aid = Bid = 0;
		Aset[Aid++] = 0;
		enumA(1, n);
		cout << "Case " << casen++ << ": " << ANS << endl;
	}
	return 0;
}

