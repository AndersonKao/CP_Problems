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
using vec = vector<T>;
int p[200000];
int main(){
	yccc;		
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		cin >> p[i];
	}
	sort(p, p+n);
	ll ans = 0;
	if(n & 1){
		for(int i = 0 ; i < n; i++){
			ans += abs(p[i] - p[n/2]);
		}
	}	
	else{
		int mid = (p[n/2-1] + p[n/2])/2;
		for(int i = 0 ; i < n; i++){
			ans += abs(p[i] - mid);
		}
	}
	cout << ans << endl;
	return 0;
}

