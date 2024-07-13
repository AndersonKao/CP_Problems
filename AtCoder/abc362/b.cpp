
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

int main() {
	yccc;
	int pt[3][2];
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 2; j++)
			cin >> pt[i][j];
	int dis[3];

	for(int i = 0; i < 3; i++){
		int j = (i + 1) %3;
		int a = (pt[i][0] - pt[j][0]), b =  (pt[i][1] - pt[j][1]);
		dis[i] = a * a + b * b;
	}

	bool ans = false;
	for(int i = 0; i < 3; i++){
		int j = (i + 1) %3;
		int k = (i + 2) %3;
		if(dis[i] == dis[j] + dis[k]){
			ans = true;
		}
	}
	cout << (ans ? "Yes" : "No");

	return 0;
}
