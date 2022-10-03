
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
int target, n;
vec<p<int>> aSt;
bool sol = false;
void DFS(int idx, vec<p<int>> &V, int cur){
	if(cur == target){
		sol = true;
		vec<int> ans;
		for(p<int>& e: aSt){
			for(int i = 0; i< e.S; i++){
				ans.eb(e.F);
			}
		}
		cout << ans[0];
		for(int i = 1; i < ans.size(); i++){
			cout << "+" << ans[i];
		}
		cout << "\n";
	}
	if(idx == V.size() || cur >= target){
		return;
	}
	for(int m = V[idx].S; m >= 0; m--){
		aSt.eb(V[idx].F, m);
		DFS(idx+1, V, cur + V[idx].F * m);
		aSt.pop_back();
	}
}
int main(){
	while(cin >> target >> n){
		if(n == 0){
			break;
		}
//		cout << "target: " << target << " n: " << n << "\n";
		vec<p<int>> V;		
		REP(i, n){
			int v;
			cin >> v;
			V.eb(v, i);
		}
		auto cmp = [](p<int>& a, p<int>&b){
			return a.F == b.F;	
		};
		V.resize(distance(V.begin(), unique(al(V), cmp)));
		V.eb(-1, n); 
		for(int i = 0; i < V.size()-1; i++){
			V[i].S = V[i+1].S - V[i].S;	
		}
		V.pop_back();
		aSt.clear();
		sol = false;
		cout << "Sums of " << target << ":\n";
		DFS(0, V, 0);
		if(sol == false){
			cout << "NONE\n";
		}
	}
	return 0;
}

