
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x << endl;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define F first
#define S second

int main() {
	yccc;
	int n;
	cin >> n;
	int cnt = 0;
	bool sol = true;
	int first = 0;
	while(n--){
		string str;
		cin >> str;
		if(str == "salty"){
			cnt = 0;
		}
		else if(str == "sweet"){
			cnt++;
		}
		if(cnt == 2){
			if(n > 0)
				sol = false;
		}
	}
	cout << (sol ? "Yes" : "No") ;

	return 0;
}
