#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ": " << x << endl;
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
const int inf = 1000000;
int N;
vector<vector<pair<int, int>>> G;
vector<vector<vector<int>>> f;
int D;
bool valid(int& val){
	if(val > D)
		val = D;
	return val >= 0 && val <= D;
}
void fillv(vec<vec<int>> &f, int val){
	for(vector<int>& vf: f){
		fill(al(vf), val);
	}
}

void DFS(int u, int pa){
#ifdef Ddp
	cout << "proc " << u << endl;
#endif
	if (G[u].size() == 1 && u != pa) {
		for(vector<int>&vf: f[u])
			fill(al(vf), 1);
		#ifdef Ddp
		cout << u << " is leaf\n";
#endif
		return;
	}
	
	for(pii v: G[u]){
		if(v.F == pa) continue;
		DFS(v.F, u);
	}

	int v, w;
	tie(v, w) = ((G[u][0].F == pa && G[u].size() > 1) ? G[u][1] : G[u][0]);
	
	vec<vec<int>> &cf = f[u]; 
	vec<vec<int>> &rf = f[v]; 
	for(int i = 0; i <= D; i++){
		for(int j = 0; j <= D; j++){
			int ri = i - w, rj = j + w;
			if(valid(ri) && valid(rj)){
				cf[i][j] |= rf[ri][rj];
			}
			ri = i + (60 - w), rj = j - (60 - w);
			if(valid(ri) && valid(rj)){
				cf[i][j] |= rf[ri][rj];
			}
		}
	}
#ifdef Ddp
	cout << "do with " << v << endl;
	for(int i = 0; i <= min(65, D); i++){
		for(int j = 0; j <= min(65, D); j++){
			cout << f[u][i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
#endif
	int pv = v;
	for(pii& neigh : G[u]){
		int v, w;
		tie(v, w) = neigh;
		if(v == pa || v == pv)
			continue;
#ifdef Ddp
		cout << "do with " << v << endl;
#endif
		vec<vec<int>> &lf = f[v];
		vec<vec<int>> rf = cf; // treat tf as right subtree, R subtree always round down (0 -> 0);
		fillv(cf, 0);
			
		for(int i = 0; i <= D; i++){
			for(int j = 0; j <= D; j++){
				if (true)
				{
					// case 1-1  L round down, R round down, i by L, j by L
					int li = i - w, lj = j + w;
					int ri = min(D-i, i), rj = min(D-j, j);
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 1-2  L round down, R round down, i by L, j by R
					li = i - w, lj = min(D-j, j) + w;
					ri = min(D - i, i), rj = j;
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 1-3  L round down, R round down, i by R, j by L
					li = min(D-i, i) - w, lj = j + w;
					ri = i, rj = min(D-j, j);
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 1-4  L round down, R round down, i by R, j by R 
					li = min(D-i, i) - w, lj = min(D-j, j) + w;
					ri = i, rj = j;
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
				}
				if(true){
					// case 2-1  L round up, R round down, i by L, j by L
					int li = i + (60 - w), lj = j - (60 - w);
					int ri = min(D-i, i), rj = min(D-j, j);
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 2-2  L round up, R round down, i by L, j by R
					li = i + (60 - w), lj = min(D-j, j) - (60 - w);
					ri = min(D - i, i), rj = j;
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 2-3  L round up, R round down, i by R, j by L 
					li = min(D-i, i) + (60 - w), lj = j - (60 - w);
					ri = i, rj = min(D-j, j);
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
					// case 2-4  L round up, R round down, i by R, j by R 
					li = min(D-i, i) + (60 - w), lj = min(D-j, j) - (60 - w);
					ri = i, rj = j;
					if (valid(li) && valid(lj) && valid(ri) && valid(rj))
						cf[i][j] |= (lf[li][lj] && rf[ri][rj]);
				}
			}
		}
#ifdef Ddp
		for(int i = 0; i <= min(65,D); i++){
			for(int j = 0; j <= min(65,D); j++){
				cout << f[u][i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
#endif
	}
//	}
}

bool verify() {
#ifdef Dverify
	cout << "pick : " << D << endl; 
#endif
	for(int u = 0; u < N; u++){
		f[u].clear();
		f[u].resize(D + 1, vector<int>(D + 1, 0));
	}
	if(G[0].size() == 0)
		return true;
	DFS(0, 0);
#ifdef Dverify
	cout << "verify: \n";
	for(int u = 0; u < N; u++){
		cout << u << " verifying " << endl;
		for(int i = 0; i <= min(65, D); i++){
			for(int j = 0; j <= min(65,D); j++){
				cout << f[u][i][j] << " ";
			}
			cout << endl;
		}
		cout << "--------\n";
		cout << endl;
	}
#endif
	for (int i = 0; i <= D; i++){
		for (int j = 0; j <= D; j++){
			if(f[0][i][j])
				return true;
		}
	}
	return f[0][D][D];
}

int main(){
	int caseN = 1;
	while(cin >> N){
		if(N == 0)
			break;
		G.clear();
		G.resize(N);
		f.clear();
		f.resize(N);
		for(int i = 0; i < N-1; i++){
			int u, v;
			int t;
			cin >> u >> v >> t;
			t = (t % 60);
			u--, v--;
			G[u].eb(v, t);
			G[v].eb(u, t);
		}
		int L = 0, R = 200;
		while (L < R) {
			D = (L+R) >> 1;
#ifdef Dbi
			cout << "L: " << L << ", R: " << R << endl;
#endif
			if (verify()) {
				R = D;
			}
			else{
				L = D + 1;
			}
		}
#ifdef Dbi
		cout << L <<endl;
#endif
		cout << "Case " << caseN++ << ": " << R << endl;	
	}
	return 0;
}
