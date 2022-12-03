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
	int H, M;
	cin >> H >> M;
	int a = (H / 10) * 10 + M / 10;
	int b = (H % 10) * 10 + M % 10;
	if(a >= 0 && a <= 23 && b >= 0 && b <= 59){
		cout << H << " " << M << endl;
		return 0;
	}
	for(int h = H; ; h = (h == 23 ? 0 : h+1)){
		for(int m = (h == H ? M : 0); m < 60; m++){
			int a = (h / 10) * 10 + m / 10;
			int b = (h % 10) * 10 + m % 10;
			if(a >= 0 && a <= 23 && b >= 0 && b <= 59){
				cout << h << " " << m << endl;
				return 0;
			}
		}
	}
	return 0;
}

