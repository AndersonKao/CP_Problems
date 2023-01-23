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
const int maxn = 1000;
ll seq[maxn];
int main(){
	yccc;		
	int n; ll x;
	cin >> n >> x;
	REP(i, n){
		cin >> seq[i];
	}
	
	multiset<pair<ll, p<int>>> mS;
	REP(i, n){
		REP(j, n){
			if(i == j) continue;
			mS.emplace(pair<ll, p<int>>(seq[i] + seq[j], {i, j}));
		}
	}
	bool nosol = true;
	for(int i = 0; i < n && nosol; i++){
		for(int j = 0; j < n && nosol; j++){
			if(i == j) continue;
			if(seq[i] + seq[j] >= x){
				continue;
			}
			ll tar = x - seq[i] - seq[j];
			auto it = mS.lower_bound({tar, {-1, -1}});
			while(it != mS.end() && it->F == tar && (it->S.F == i || it->S.S == j || it->S.F == j || it->S.S == i)){
				it++;	
			}
			if (it == mS.end()) continue;
			if(it->F == tar){
				cout << i+1 << " " << j+1 << " " << it->S.F+1 << " " << it->S.S+1 << endl;	
				nosol = false;
			}
		}
	}
	if(nosol)
		cout << "IMPOSSIBLE\n";

	return 0;
}

