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

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		vec<ll> gsum(n, 0);
		vec<ll> gmax(n, 0);
		vec<vec<ll>> group(n);
		REP(i, n){
			int k;
			cin >> k;			
			REP(j, k){
				ll m;
				cin >> m;
				group[i].eb(m);
				gsum[i] += m;
				gmax[i] = max(gmax[i], m);
			}
		}
		vec<int> V(n);
		iota(al(V), 0);
		auto cmp = [&](int a, int b){
			if(gsum[a] != gsum[b]){
				return gsum[a] > gsum[b];
			}
			else if(gmax[a] != gmax[b]){
				return gmax[a] > gmax[b];
			}
			else if(group[a].size() != group[b].size()){
				return group[a].size() > group[b].size();
			}
			return a < b;
		};
		sort(al(V), cmp);
		for(int id: V){
			for(int i = 0; i < group[id].size(); i++){
				cout << group[id][i] << (i == group[id].size()-1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}

