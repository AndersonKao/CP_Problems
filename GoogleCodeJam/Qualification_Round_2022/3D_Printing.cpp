#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;


int main(){
	yccc;	
	int T;
	cin >> T;
	ll limit = 1000000;
	REP1(cnt, T){	
		cout << "Case #" << cnt << ":";
		vec<ll> m(4, numeric_limits<ll>::max());
		REP(i, 3){
			REP(j, 4){
				ll cunit;
				cin >> cunit;
				m[j] = min(m[j], cunit);
			}
		}
		ll sum = accumulate(al(m), 0);
//		debug(sum);
		if(sum < limit){
			cout << " IMPOSSIBLE";
		}else{
			sum = limit;
			REP(j, 4){
				if(sum > 0){
					sum -= m[j];
					if(sum <= 0)
						m[j] += sum;
					cout << " " << m[j];
				}else{
					cout << " " << 0;
				}
			}
		}
		cout << endl;
	}
}
/*
1
999999 999998 999997 999996
999999 1 999993  999991            
999994 1 999994 3 888888
*/
