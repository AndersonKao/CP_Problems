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

vector<int> G[200000];
vector<int> color;
int tour[200000];
int lend[200000];
int ans[200000];
int stamp = 0;
void DFS(int u, int pa){
	lend[u] = stamp;
	for(int v:G[u]){
		if (v == pa) continue;
		DFS(v, u);
	}
	tour[stamp] = u;
	stamp++;
}
struct BIT{
	int n;
	vector<int> seq;
	BIT(){}
	BIT(int n){
		this->n = n;
		seq.resize(n+1, 0);
	}
	void update(int idx, int val){
		idx++;
		while(idx <= n){
			seq[idx] += val;
			idx += (idx) & (-idx);
		}
	}
	int query(int idx){
		idx++;
		int ans = 0;
		while(idx > 0){
			ans += seq[idx];
			idx -= (idx) & (-idx);
		}
		return ans;
	}
};
int main(){
	int n;
	cin >> n;		
	color.resize(n);
	REP(i, n){
		cin >> color[i];	
		color[i]--;
	}
	vector<int> colorset(color);
	sort(al(colorset));
	colorset.resize(distance(colorset.begin(), unique(al(colorset))));
	REP(i, n){
		color[i] = distance(colorset.begin(), lower_bound(al(colorset), color[i]));
	}
	REP(i, n-1){
		int u, v;
		cin >> u >> v;
		u--, v--;
		G[u].eb(v);
		G[v].eb(u);
	}
	DFS(0, -1);
	BIT mT(n);
	vector<int> rightmost(colorset.size(), -1);

	for(int i = 0; i < n; i++){
		int u = tour[i];
		if(rightmost[color[u]] != -1){
			mT.update(rightmost[color[u]], -1);
		}
		mT.update(i, 1);
		ans[u] = (mT.query(i) - mT.query(lend[u]-1));	
		rightmost[color[u]] = i;
	}
	for(int i = 0; i < n; i++)
		cout << ans[i] << " ";
	return 0;
}

