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
	int n;
	cin >> n;
	vec<p<int>> E(n);
	for(int i = 0; i < n; i++){
		cin >> E[i].F >> E[i].S;
	}
	sort(al(E));
	vec<int> ans;
	for(p<int> &e : E){
		auto it = lower_bound(al(ans), e.S, greater<int>());
		if(it == ans.end()){
			ans.eb(e.S);
		}
		else{
			*it = e.S;
		}
	}
	cout << ans.size() << endl;

	return 0;
}

