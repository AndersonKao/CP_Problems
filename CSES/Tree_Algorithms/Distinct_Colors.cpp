// Small to Large Merging
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
int n;
vector<int> G[200000];
int color[200000];
int ans[200000];
void DFS(int u, int pa, set<int>& mys){
	mys.emplace(color[u]);	
	for(int v:G[u]){
		if (v == pa) continue;
		set<int> sub;
		DFS(v, u, sub);
		if(mys.size() < sub.size()){
			swap(mys, sub);
		}
		for(int val: sub){
			mys.emplace(val);
		}
	}
	ans[u] = mys.size();
}

int main(){
	cin >> n;	
	REP(i, n)
		cin >> color[i];
	REP(i, n-1){
		int a, b;
		cin >> a >> b;
		a--, b--;
		G[a].eb(b), G[b].eb(a);
	}
	set<int> mys;
	DFS(0, 0, mys);
	REP(i, n)
		cout << ans[i] << " ";

	return 0;
}

