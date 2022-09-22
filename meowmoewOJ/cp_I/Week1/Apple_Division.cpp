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
int n;
ll a[20];
ll ans = numeric_limits<ll>::max();
ll sum = 0;
void recur(int i, ll cur){
	if(i == n){
		ans = min(ans, abs(cur - (sum - cur)));
		return;
	}
	recur(i+1, cur);
	recur(i+1, cur + a[i]);
}
int main(){
	cin >> n;
	REP(i, n){
		cin >> a[i];	
		sum += a[i];
	}
	recur(0, 0);
	cout << ans << endl;
	return 0;
}

