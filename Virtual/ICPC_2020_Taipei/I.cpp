
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;
#define debug(x) cout << #x << ": " << x << endl;
#define endl '\n'
#define yccc ios_base::sync_with_stdio(false);
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()


struct tarjan{
	struct edge{
		int u, v;
		bool is_b;
		edge(int u, int v, int ib = false):u(u), v(v), is_b(ib){};
	};
	vec<vec<int>> G;
	vec<edge> E;
	vec<vec<int>> fG;	
	vec<int> D;
	vec<int> L;
	vec<int> c;
   	vec<bool> isAP;
	int timestamp;
	stack<int> st;
	vec<vec<int>> bcc;
	int NodeNum;
	tarjan(int size = 1){
		init(size);
	}

	void init(int size = 1){
		timestamp = 1;
		bcc.clear();
		E.clear();
		fG.clear();
		fG.assign(size, vec<int>(size, 0));
		G.assign(size, vec<int>());
		D.assign(size, 0);
		L.assign(size, 0);
		isAP.assign(size, false);
		c.assign(size, 0);

		NodeNum = size;

		while(st.size())
			st.pop();
	}
	void addedge(int u, int v){
		fG[u][v] = fG[v][u] = true;
		G[u].eb(E.size());
		E.eb(u, v);	
		G[v].eb(E.size());
		E.eb(v, u);
	}
	void DFS(int u, int pa){
		D[u] = L[u] = timestamp++;
		int Childcount = 0;
//		debug(u+1);
		st.emplace(u);
		for(int i: G[u]){
			int v = E[i].v;
			if( v == pa )
				continue;
			if( !D[v] ){
				DFS(v, u);
//				if(D[u] <= L[v]){
				Childcount++;
				if(L[v] >= D[u]){
					isAP[u] = true;
//					cout << "find AP " << u+1 << endl;
					bcc.push_back({});
					int x;
					do{
						x = st.top(), st.pop();
//						cout << "goin ? " << x+1 << endl;
						bcc.back().eb(x);
					}while(x != v);
					bcc.back().eb(u);
//					st.emplace(u);
				}
				if(L[v] > D[u]){
					E[i].is_b = true, E[i^1].is_b = true;
				}
				L[u] = min(L[u], L[v]);
			}
			L[u] = min(L[u], D[v]);
		}
		if(u == pa && Childcount < 2)
			isAP[u] = false;
	}
	void dfs2(int u, int bccid){
		c[u] = bccid;
		for(int eid:G[u]){
			if(c[E[eid].v] || E[eid].is_b) continue;
			dfs2(E[eid].v, bccid);
		}
	}

	int count(){
		int ans = 1;
		/*
		int bccid = 0;
		for(int i = 0; i < NodeNum; i++){
			if(c[i] == 0){
				dfs2(i, ++bccid);
			}
		}
		vec<int> sz(bccid+1, 0);
		for(int i = 0; i < E.size(); i++){
			if(c[E[i].u] == c[E[i].v]){
				sz[c[E[i].u]]++;
			}
		}

		for(int i = 1; i <= bccid; i++){
			ans = max(ans, sz[i]/2);
		}
		debug(ans);
		*/

		ans = 1;

		for(int i = 0; i < bcc.size(); i++){
			int res = 0;
			for(int j = 0; j < bcc[i].size(); j++){
				for(int k = j+1; k < bcc[i].size(); k++){
					if(fG[bcc[i][j]][bcc[i][k]]){
						res++;
					}
				}
			}
//			cout << res << endl;
			ans = max(ans, res);
		}
//		debug(ans);
		return ans;	
	}
};

int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	return gcd(b, a % b);
}

int main() {
	yccc;
	int t;
	cin >> t;
	tarjan mG;
	while(t--){
		int n, m;
		cin >> n >> m;
		mG.init(n);
		for(int i = 0; i < m; i++){
			int u, v;
			cin >> u >> v;
			u--, v--;
			mG.addedge(u, v);
		}

		mG.DFS(0, 0);

//		mG.run();			

		int p = mG.bcc.size();
		int q = mG.count();

		int APcnt = 0;
		/*
		for(int u = 0; u < n; u++){
			cout << u +1 << ": " << mG.c[u] << endl;
		}
		for(int i = 0; i < mG.bcc.size(); i++){
			cout << "scc " << i << "'s : ";
			for(int u: mG.bcc[i]){
				cout << u+1 << " ";
			}
			cout << endl;
		}
		*/
		for(int u = 0; u < n; u++){
			if(mG.isAP[u])
				APcnt++;
		}
		int Bcnt = 0;
		for(int i = 0; i < 2*m; i++){
			if(mG.E[i].is_b)
				Bcnt++;
		}
		Bcnt /= 2;

		//p += Bcnt;

		int g = gcd(p, q);
		p = p / g;
		q = q / g;

		cout << APcnt << " " << Bcnt << " ";

		cout << p << " " << q <<  endl;
	}
}
