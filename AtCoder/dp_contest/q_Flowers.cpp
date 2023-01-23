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
const int maxn = 2000000;
struct BIT{
	vec<ll> seq;
	int N;
	BIT(int N){
		seq.resize(N+1);
		this->N = N;
	}

	ll query(int i){
		ll ans = 0;
		while( i > 0 ){
			ans = max(ans, seq[i]);
			i -= (i & (~i + 1));
		}
		return ans;
	}
	void modify(int i, ll val){
		while(i <= N){
			seq[i] = max(seq[i], val);
			i += (i & (~i + 1));
		}	
	}

};

int main(){
	yccc;		
	int N;
	cin >> N;
	vec<p<int>> V(N);
	REP(i, N){
		cin >> V[i].F;
	}

	REP(i, N){
		cin >> V[i].S;
	}

	BIT mT(N);

	for(p<int> &e : V){
		ll mx = mT.query(e.F - 1);

		mT.modify(e.F, mx + e.S);
	}

	cout << mT.query(N) << endl;
	return 0;
}

