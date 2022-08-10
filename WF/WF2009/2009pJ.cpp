#include<bits/stdc++.h>
using namespace std;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
const int inf = 1000000;

int N;
vector<vector<pair<int, int>>> G;
vector<vector<int>> f;
int validD;
bool valid(int val){
	return val>= -validD && val <= validD;
}

void DFS(int u, int pa, int D){
	if((pa != -1 && G[u].size() == 1)|| G[u].size() == 0){
		fill(f[u].begin(), f[u].end(), 0);
		return;
	}
	
	for(pii v: G[u]){
		if(v.F == pa) continue;
			DFS(v.F, u, D);
	}
#ifdef DDFS
	cout << "proc " << u << endl;
#endif
	vector<int>& cf = f[u];
	fill(al(cf), inf);
	int v = (G[u][0].F == pa ? G[u][1].F : G[u][0].F);
	int w = (G[u][0].F == pa ? G[u][1].S : G[u][0].S);
	vector<int> &lv = f[v];
	for(int i = 0; i <= D; i++){
		// round up
		int li = i - w;
		if(li >= 0 && valid(lv[li]) && valid(lv[li] - w)){
			cf[i] = min(lv[li] - w, cf[i]);
		}
#ifdef Dli
		debug(li);
		if(li >= 0){
			if(lv[li] > D)
				cout << "li val outofrange\n";
		}
		else		
			cout << "li outofrange\n";
#endif
		// round down
			li = i + 60 - w;
		if(w != 0 && li <= D && valid(lv[li]) && valid(lv[li] + 60 - w)){ // li <= D is not need since the solution is not necessary be D
			cf[i] = min(lv[li] + (60 - w), cf[i]);
		} 
#ifdef Dli
		if(li <= D){
			if(lv[li] > D)
				cout << "li val outofrange\n";
		}
		else		
			cout << "li outofrange\n";
#endif
	}
#ifdef Ddp
	cout << "do with " << v << endl;
	for(int i = 0; i < 100; i++){
		cout << f[u][i] << " ";
	}
		cout << endl;
#endif
	int pv = v;
	vector<int> tf(cf.size());
//	if(G[u].size() > (2 + (pa == -1 ? -1 : 0))){
		for(pii& neigh : G[u]){
			int v = neigh.F, w = neigh.S;
			if(v == pa || v == pv)
				continue;
#ifdef Ddp
			cout << "do with " << v << endl;
#endif
			tf = cf; // treat tf as right subtree, R subtree always round up (0-> 0);
			fill(al(cf), inf);
			vector<int> &lf = f[v];
			for(int i =0; i <= D; i++){
				// case 1-1  L round up, R round up, i by L
				int li = i-w, ri = min(D-i, i);
				if(li >= 0 && li <= D && ri >= 0 && ri <= D && valid(lf[li]) && valid(tf[ri]) && valid(lf[li]-w) &&valid(lf[li] - w + tf[ri]))
					cf[i] = min(max(lf[li] - w, tf[ri]), cf[i]);
				// case 1-2  L round up, R round up, i by R 
				li = min(D-i, i) - w, ri = i;
				if(li >= 0 && li <= D && ri >= 0 && ri <= D && valid(lf[li]) && valid(tf[ri]) && valid(lf[li]-w) &&valid(lf[li] - w + tf[ri]))
					cf[i] = min(max(lf[li] - w, tf[ri]), cf[i]);
				// case 3-1  L round down, R round up, i by L
				li = i + 60 - w, ri = min(D-i, i);
				if(w != 0 && li >= 0 && li <= D && ri >= 0 && ri <= D && valid(lf[li]) && valid(tf[ri]) && valid(lf[li] +60 -w) &&valid(lf[li] + 60 - w + tf[ri]))
					cf[i] = min(max(lf[li] + (60 - w), tf[ri]), cf[i]);
				// case 3-2  L round down, R round up, i by R
				li = min(D-i, i) + 60 - w, ri = i;
				if(w != 0 && li >= 0 && li <= D && ri >= 0 && ri <= D && valid(lf[li]) && valid(tf[ri]) && valid(lf[li] +60 -w) &&valid(lf[li] + 60 - w + tf[ri]))
					cf[i] = min(max(lf[li] + (60 - w), tf[ri]), cf[i]);
			}
#ifdef Ddp
			for(int i = 0; i < 100; i++){
				cout << f[u][i] << " ";
			}
			cout << endl;
#endif
		}
//	}
}

bool verify(int D){
#ifdef Dverify
	cout << "pick : " << D << endl; 
#endif
	validD = D;
	for(int u = 0; u < N; u++){
		f[u].resize(6001);
		fill(al(f[u]), inf);
	}
	DFS(0, -1, D);	
#ifdef Dverify
	cout << "verify: \n";
	for(int u = 0; u < N; u++){
		cout << u << " verifying " << endl;
		for(int i = 0; i < 100; i++){
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
			t = (60 - (t % 60)) % 60;
			u--, v--;
			G[u].eb(v, t);
			G[v].eb(u, t);
		}
		int L = 0, R = 6000;
		while(L < R){
			int M = (L+R) >> 1;
#ifdef Dbi
			cout << "L: " << L << ", R: " << R << endl;
#endif
			if(verify(M)){
				R = M;
			}
			else{
					L = M + 1;
				}
		}
#ifdef Dbi
		cout << L <<endl;
#endif
		cout << "Case " << caseN++ << ": " << R << endl;	
	}
	return 0;
}
