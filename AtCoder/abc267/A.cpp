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


int main(){
	string s;
	cin >> s;		
	int ans;
	if(s == "Monday"){
		ans = 5;
	}
	if(s == "Tuesday"){
		ans = 4;
	}
	if(s == "Wednesday"){
		ans = 3;
	}
	if(s == "Thursday"){
		ans = 2;
	}
	if(s == "Friday"){
		ans = 1;
	}
	cout << ans << enld;
	return 0;
}

