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
	if(n % 4 == 0){
		cout << "YES\n";
		cout << n / 2 << endl;
		for(int i = 1; i <= n/2; i+=2){
			cout << i << " " << n + 1 - i << " ";	
		}
		cout << endl;
		cout << n / 2 << endl;
		for(int i = 2; i <= n/2; i+=2){
			cout << i << " " << (n + 1 - i) << " ";	
		}
		cout << endl;
	}
	else if(n % 4 == 3){
		cout << "YES\n";
		cout << n / 2 + 1 << endl << "1 2 ";
		for(int i = 4; i <= (n-3)/2 + 3; i+=2){
			cout << i << " " << 3 + (n + 1 - i) << " ";	
		}
		cout << endl;
		cout << n / 2 << endl << "3 ";
		for(int i = 5; i <= (n-3)/2 + 3; i+=2){
			cout << i << " " << 3 + (n + 1 - i) << " ";	
		}
		cout << endl;
	}
	else{
		cout << "NO\n";
	}
	return 0;

}

