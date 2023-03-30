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
	set<int> tS; // traffic position
	multiset<int> mS; // passage len set
	int x; cin >> x;
	mS.emplace(x);
	tS.emplace(0), tS.emplace(x);
	int n; cin >> n;
	REP0(i, n){
		int v; cin >> v;
		auto itnxt = tS.lower_bound(v);
		auto itpre = itnxt; itpre--;
		mS.erase(mS.lower_bound(*itnxt - *itpre));
		mS.emplace(*itnxt - v);	
		mS.emplace(v - *itpre);	
		tS.emplace_hint(itnxt, v);
		cout << *mS.rbegin() << " \n"[i == n-1];
	}
	
	return 0;
}

