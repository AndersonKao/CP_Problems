#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;

vec<vec<int>> G;
vec<int> val;
//vec<int> mval; // max val for that vertex;
ll sum;

void dfs(int now){
	for(int& u: G[now]){
		dfs(u);
	}	
	if(now == 0){
		for(int &u:G[now])
			sum += val[u];
		return;
	}
	int pick = -1;
	int pickval = numeric_limits<int>::max();
	for(int &u:G[now]){
		if(val[u] < pickval){
			pick = u;
			pickval = val[u];
		}	
	}
	if(pick != -1){
		val[now] = max(val[now], val[pick]);
		for(int &u:G[now]){
			if(u != pick)
				sum += val[u];
		}
	}
}

int main(){
//	yccc;	
	int T;
	cin >> T;
	REP1(cnt, T){
		int N;
		cin >> N;
		// ---init---
		G.clear();
		G.resize(N+1);
		
		val.resize(N+1);
		// ---init end---
		REP1(i, N){
			cin >> val[i];
//			mval[i] = val[i];
		}
		REP1(i, N){
			int u;
			cin >> u;
			G[u].eb(i);	
		}
		sum = 0;
		dfs(0);
		cout << "Case #" << cnt << ": " << sum << endl;
	}
}
