// Traffic_Lights_2.cpp
// backward, faster
#include <bits/stdc++.h>
using namespace std;
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
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
	int n, x;
	cin >> x >> n;
	vec<int> tra(n);
	REP0(i, n){
		cin >> tra[i];
	}
	vec<int> ans;
	set<int> tS(al(tra));
	tS.emplace(0), tS.emplace(x);	

	auto it = tS.begin();

	int curans = 0;
	do{
		auto pre = it;
		it++;
		curans = max(*it - *pre, curans);	
	}while(it!=tS.end());
	ans.eb(curans);
	reverse(al(tra));
	for(int v: tra){
		auto it = tS.lower_bound(v);
		auto itnxt = it; itnxt++;
		auto itpre = it; itpre--;
		int curlen = *itnxt - *itpre;
		tS.erase(it);
		curans = max(curans, curlen);
		ans.eb(curans);
	}
	reverse(al(ans));
	REP(i, 1, n){
		cout << ans[i] << " \n"[i == n];
	}

	return 0;
}

