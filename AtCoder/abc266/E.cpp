#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const double eps = 1e-6;
int main(){
	int N = 0;	
	cin >> N;
	double ans = 0.0;
	double res = 1.0;
	for(int i = 1; i <= N-1; i++){
		ans += res;
		res *= (5.0/6.0);
	}
	ans += 3.5 * res; 
	cout << ans << endl;
	
	return 0;
}

