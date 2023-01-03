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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;

int main(){
	yccc;		
	int n, k;
	cin >> n >> k;
	vec<p<int>> E;
	REP(i, n){
		int s, t;
		cin >> s >> t;
		E.eb(s, t);
	}
	multiset<int> mS;
	REP(i, k){
		mS.emplace(0);
	}
	sort(al(E), [](p<int> &a, p<int> &b){
			return a.S < b.S;
			});
	int ans = 0;
	for(auto e: E){
		auto it = mS.upper_bound(e.F);
		if(it == mS.begin()){
			continue;
		}
		it--;
		mS.erase(it);
		mS.emplace(e.S);
		ans++;
	}
	cout << ans << endl;	
	return 0;
}

