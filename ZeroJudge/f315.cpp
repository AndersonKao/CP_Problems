#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
template<typename T>
using vec = vector<T>;
using pii = pair<int, int>;
using ll = long long;
#define debug(x) cout << #x << ": " << x << endl;
vec<pair<int, int>> cnt;
auto cmp = [](const pii &a, const pii& b){
	if(a.F > b.F){
		if(a.S)
			cnt[a.F].S++;
		else
			cnt[a.F].F++;
	}
	return a.F < b.F;
};
vector<pii> seq;
int main(){
	int n;
	cin >> n;
	cnt.resize(n, pii(0,0));
	seq.resize(2*n);
	vec<bool> app(n, false);
	for(int i = 0; i < 2*n; i++){
		int val;
		cin >> val;
		val--;
		seq[i].F = val;	
		seq[i].S = app[val];
		app[val] = true;
	}
	stable_sort(seq.begin(), seq.end(), cmp);
	ll ans = 0;
	for(int i = 0; i < n ;i++){
		debug(i);
		debug(cnt[i].F);
		debug(cnt[i].S);
		ans += (cnt[i].S - cnt[i].F);
	}
	cout << ans << endl;
	return 0;
}
