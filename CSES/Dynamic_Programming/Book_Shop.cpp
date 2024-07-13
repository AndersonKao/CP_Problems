
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

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

int h[1000];
int s[1000];
int dp[1000][100001];

int main() {
	yccc;
	int n, x;
	cin >> n >> x;
	for(int i = 0; i < n; i++){
		cin >> h[i];
	}
	for(int i = 0; i < n; i++){
		cin >> s[i];
	}
	for(int p = h[0]; p <= x; p++){
		dp[0][p] = s[0];
	}
	for(int i = 1; i < n; i++){
		for(int p = 0; p <= x; p++){
			dp[i][p] = dp[i-1][p];
			if(p >= h[i])
				dp[i][p] = max(dp[i][p], dp[i-1][p - h[i]] + s[i]);
		}
	}
	/*
	for(int i = 0; i < n; i++)
		for(int p = 0; p <= x; p++)
			cout << dp[i][p] << (p == x ? '\n' : ' ');
	*/
	cout << dp[n-1][x] << endl;

	return 0;
}
