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

int main(){
	yccc;		
	int n;
	cin >> n;
	ll base = 28;
	for(ll k = 1; k <= n; k++){
		if(k == 1){
			cout << 0 << "\n";
		}
		else if(k == 2){
			cout << 6 << "\n";
		}
		else if(k == 3){
			cout << 28 << "\n";
		}
		else{
			base += (2*k-1) * (k-1) * (k-1);
			base += (2*k-1) * (2*k -2) / 2;
			base -= 2 * (k - 2); // i, j -> i+2, j+1 or i-2, j+1.
			base -= 2 * (k - 3); // i, j -> i+1, j+2 or i-1, j+2.
			base -= 2 * k - 2;
			base -= 2 * k - 4;
			cout << base << endl;
		}
	}
	
	return 0;
}

