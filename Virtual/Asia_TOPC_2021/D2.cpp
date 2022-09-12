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
double rate[301];
double fg[301];
bool count[301] = {false};
int main(){
	int n;
	cin >> n;
	if(n == 2){
		cout << 1 << endl;
		return 0;
	}
	cout << fixed << setprecision(8);
	cout << ((1/2.0) * (1- 1.0/(n-1)) + 1.0 / (n-1) )<< endl; 
	return 0;
}

