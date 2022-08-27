#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
template <typename T>
using vec = vector<T>;
const int inf = 1000000;

int N;
vector<vector<pair<int, int>>> G;
vector<vector<int>> f;
int D;
bool validposi(int val){
	return val >= 0 && val <= D;
}
bool valid(int val){
	return val <= D;
}

void DFS(int u, int pa){
#ifdef DDFS
	cout << "proc " << u << endl;
#endif
	if(pa != u && G[u].size() == 1){
		fill(f[u].begin(), f[u].end(), 0);
#ifdef DDFS
		cout << u << " done.\n";
#endif
		return;
	}
	
	for(pii v: G[u]){
		if(v.F == pa) continue;
			DFS(v.F, u);
	}
	int v, w;
	tie(v, w) = (G[u][0].F == pa && G[u].size() > 1 ? G[u][1] : G[u][0]);

	vector<int>& cf = f[u];
	vector<int>& rf = f[v];

	for(int i = 0; i <= D; i++){
		// round up
		if(i > 0)
			cf[i] = min(cf[i], cf[i - 1]);
		for (int round = 0; round < 2; round++)
		{
			if(round)// round up 
				w -= 60;
			int ri = i - w;
			if(validposi(ri) && valid(rf[ri] - w)){
				cf[i] = min(max(0,rf[ri] - w), cf[i]);
			}
		}
		w += 60;
#ifdef Ddp
		if(cf[i] > D)
			cout << "li val outofrange\n";
#endif
	}
	int pv = v;
	for(pii& neigh : G[u]){
		int v, w;
		tie(v, w) = neigh;
		if(v == pa || v == pv)
			continue;
#ifdef Ddp
		cout << "do with " << v << endl;
#endif
		vector<int> &lf = f[v];
		vec<int> rf = cf; // treat tf as right subtree, R subtree always round up (0-> 0);
		fill(al(cf), inf);
		for(int i =0; i <= D; i++){
			if(i > 0)
				cf[i] = min(cf[i], cf[i - 1]);
			for (int round = 0; round < 2; round++){
				if(round)
					w -= 60;
				// case 1-1  L round up, R round up, i by L
				int li = i - w, ri = min(D - i, i);
				if(validposi(li) && valid(lf[li]-w) && valid(lf[li] - w + rf[ri]))
					cf[i] = min(max({lf[li] - w, rf[ri], 0}), cf[i]);
				// case 1-2  L round up, R round up, i by R 
				li = min(D-i, i) - w, ri = i;
				if(validposi(li) && valid(lf[li]-w) && valid(lf[li] - w + rf[ri]))
					cf[i] = min(max({lf[li] - w, rf[ri], 0}), cf[i]);
			}
			w += 60;
		}
	}
#ifdef Ddp
	cout << "table " << u << ": ";
	for (int i = 0; i < min(100, D); i++)
	{
		cout << f[u][i] << " ";
	}
		cout << endl;
#endif
#ifdef DDFS
	cout << u << " done.\n";
#endif
}

bool verify(){
#ifdef Dverify
	cout << "pick : " << D << endl; 
#endif
	for(int u = 0; u < N; u++){
		f[u].resize(D+1);
		fill(al(f[u]), inf);
	}
	if(G[0].size() == 0)
		return true;
	DFS(0, 0);
#ifdef Dverify
	cout << "verify: \n";
	for(int u = 0; u < N; u++){
		cout << u << " verifying " << endl;
		for(int i = 0; i < min(100, D); i++){
			cout << f[u][i] << " ";
		}
		cout << endl;
	}
#endif
	for(int k = 0; k <= D; k++)
		if(valid(f[0][k]))
			return true;
	return false;
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
			t = t % 60;
			u--, v--;
			G[u].eb(v, t);
			G[v].eb(u, t);
		}
		int L = 0, R = 6000;
		while(L < R){
			D = (L+R) >> 1;
#ifdef Dbi
			cout << "L: " << L << ", R: " << R << endl;
#endif
			if(verify()){
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
