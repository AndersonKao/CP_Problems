#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
int BIT[200001] = {0};

int n;
void add(int idx, int val){
	int res = idx;
	while(res <= n){
		BIT[res] += val;
		res += (res & -res);
	}
}
int query(int idx){
	int ans = 0;
	int res = idx;
	while(res > 0){
		ans += BIT[res];
		res -= (res & -res);
	}
	return ans;
}

int main(){
	cin >> n;
	vector<int> V(n);
	for(int &v :V)
		cin >> v;
	ll ans = 0;
	for(int i = n-1; i >= 0; i--){
		int v = V[i];
		ans += query(v);
		add(v, 1);
	}
	cout << ans << endl;
	

			
	return 0;
}

