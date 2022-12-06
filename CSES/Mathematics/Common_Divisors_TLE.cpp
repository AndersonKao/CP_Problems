// O(N*sqrt(N)) TLE
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
int cnt[1000001];
int main(){
	yccc;		
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		ll val;
		cin >> val;
		for(ll i = 1; i * i <= val; i++){
			if(val % i == 0){
				cnt[i]++, cnt[val/i]++;
			}
		}
	}
	for(int x = 1e6; x > 0; x--){
		if(cnt[x] >= 2){
			cout << x << endl;
			break;
		}
	}
	return 0;
}

