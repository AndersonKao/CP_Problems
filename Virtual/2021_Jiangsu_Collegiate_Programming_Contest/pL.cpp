#include <bits/stdc++.h>
using namespace std;

template<typename T> using vec = vector<T>;
#define lb lower_bound
#define al(x) x.begin(), x.end()
#define ll long long
#define endl '\n'
#define eb emplace_back
#define F first
#define S second
const ll MOD = 998244353LL;
vec<vec<int>> G;
vector<int> curval;
vector<ll> possi;
#define debug(x) cout << #x << ": " << x << endl;
bool myFind(vector<int>& V, int val){
	vector<int>::iterator it = lb(al(V), val);
	if(it == V.end() || *it != val){
		return false;
	}
	return true;
}
void DFS(int u){
//	debug(u);
	for(int v: G[u]){
		DFS(v);
	}
	possi[u] = 1;
	if(G[u].size() == 0)
		return;
	ll cnt = (curval[u] == 0 ? 1 : 0);
	for(int v: G[u]){
		possi[u] *= possi[v];
		possi[u] %= MOD;
		if(curval[v] == 0){
			cnt++;
		}
	}
#ifdef Dcurval
	cout << "curval : ";
	for(int v: G[u]){
		cout << v << ": " << curval[v] << ", ";
	}
	cout << endl;
#endif
	for(int i = 1; i<=cnt; i++){
		possi[u] *= (long long)i;
		possi[u] %= MOD;
	}
	if(curval[u] != 0){
		if(myFind(G[u], curval[u])){
			curval[u] = 0;
		}
	}
	for(int v: G[u]){
		if(curval[v] != 0){
			if(myFind(G[u], curval[v]) == false){
				if(curval[u] == 0){
					curval[u] = curval[v];	
				}	
				else{
					possi[u] = 0;
				}
			}
		}
	}
	/*
	if(u == 1 && curval[u] > 1){
		possi[u] = 0;
	}
	*/
}

int main() {	
	int T;
	cin >> T;
	while(T--){
		int N;
		cin >> N;
		G.clear();
		G.resize(N+1);
		curval.clear();
		curval.resize(N+1, 0);
		possi.clear();
		possi.resize(N+1, 0);
//		vector<int> deg(N+1, 0);
//		vector<int> pa(N+1, 0);
		for(int i = 2; i <= N; i++){
			int u;
			cin >> u;
//			pa[i] = u;
			G[u].eb(i);
//			deg[u]++;
		}	
		queue<int> mQ;
		for(int i = 1; i <= N; i++){
			sort(al(G[i]));
			cin >> curval[i];
//			if(deg[i] == 0)
//				mQ.push(i);
		}
//		cout << "good input\n";
		DFS(1);	
		/*
		while(mQ.size()){
			int u = mQ.front();
			mQ.pop();
			DFS(u);
			int v = pa[u];
			deg[v]--;
			if(deg[v] == 0)
				mQ.push(v);
		}
		*/
		/*
		cout << "possi: ";
		for(int i = 1; i <= N; i++){
			cout << possi[i] << (i == N ? "\n" : " ");
		}
		*/
		cout << possi[1] << endl;
	}

	return 0;
}
