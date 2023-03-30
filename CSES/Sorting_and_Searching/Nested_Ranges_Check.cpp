#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < n; i++)
#define REPa(i, a, b) for(int i = a; i <= b; i++)
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

struct seg{
	int l, r, id;
	bool operator<(seg b){
		if(l == b.l){
			return r > b.r;
		}
		return l <= b.l;
	}
};
const int maxn = 200000;
bool contains[maxn], contained[maxn];
int main(){
	yccc;		
	int n; cin >> n;
	vector<seg> seq(n);
	REP(i, n){
		cin >> seq[i].l >> seq[i].r;
		seq[i].id = i;
	}
	sort(al(seq));
	int maxR = 0;
	REP(i, n){
		if(seq[i].r <= maxR){
			contained[seq[i].id] = true;	
		}	
		maxR = max(maxR, seq[i].r);
	}
	int minR = INT_MAX;
	for(int i = n-1; i >= 0; i--){
		if(seq[i].r >= minR){
			contains[seq[i].id] = true;
		}
		minR = min(minR, seq[i].r);
	}
	REP(i, n){
		cout << contains[i] << " \n"[i == n-1];
	}
	REP(i, n){
		cout << contained[i] << " \n"[i == n-1];
	}
	
	return 0;
}

