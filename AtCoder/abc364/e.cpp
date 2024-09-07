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

ll dp[2][100][10005];

int main() {
	yccc;
	int n, x, y;
	cin >> n >> x >> y;
	vec<ll> X(n), Y(n);
	for(int i = 0; i < n; i++)
		cin >> X[i] >> Y[i];

	for(int w = 0; w <= x; w++){
		for(int j = 1; j <= n; j++)
			dp[1][j][w] = INT_MAX;
		dp[1][0][w] = 0;
	}	
	int ans = 0;
	for(int i = 0; i < n; i++){
		int ix = (i & 1);
		int ip = ix ^ 1;
		for(int w = 0; w <= x; w++){
			dp[ix][0][w] = 0;
		}
		for(int j = 1; j <= i+1; j++){
			bool ifany = false;
			for(int w = 0; w <= x; w++){
				dp[ix][j][w] = INT_MAX;			
				dp[ix][j][w] = min(dp[ix][j][w], dp[ip][j][w]);
				if(w - X[i] >= 0){
				 	ll val = dp[ip][j-1][w - X[i]] + Y[i];
					if(val <= y)
						dp[ix][j][w] = min(dp[ix][j][w], val);
				}
				if(dp[ix][j][w] < INT_MAX){
					ifany = true;
				}
			}
			if(ifany){
				ans = max(ans, j);
			}
		}
		for(int j = i+2; j <= n; j++){
			for(int w = 0; w <= x; w++){
				dp[ix][j][w] = INT_MAX;
			}
		}
		//cout << "-----\n";
		/*

		for(int j = 0; j <= n; j++){
			for(int w = 0; w <= x; w++){
				cout << dp[ix][j][w] << " ";
			}
			cout << endl;
		}*/
	}
	
	cout << (ans == n ? ans : ans + 1) << endl;



	return 0;
}
