// O(n^2 + q) 
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

int pre[1001][1001] = {0};

int main() {
	yccc;
	int n, q;
	cin >> n >> q;
	char ch;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			pre[i][j] = pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1];
			cin >> ch;
			if(ch == '*'){
				pre[i][j] += 1;
			}
		}
	}
	while(q--){
		int x1, x2, y1, y2;
		cin >> y1 >> x1 >> y2 >> x2;
		cout << pre[y2][x2] - pre[y1-1][x2] - pre[y2][x1-1] + pre[y1-1][x1-1]<< endl;
	}
	return 0;
}
