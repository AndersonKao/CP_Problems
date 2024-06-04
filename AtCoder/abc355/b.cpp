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
	int n, m;
	cin >> n >> m;
	vec<p<int>> arr;
	for(int i = 0; i < n; i++){
		int val;
		cin >> val;
		arr.eb(val, 1);
	}

	for(int i = 0; i < m; i++){
		int val;
		cin >> val;
		arr.eb(val, 2);
	}
	sort(al(arr));

	bool sol = false;
	for(int i = 0; i < n + m - 1; i++)
	{
		if(arr[i].second == 1 && arr[i+1].second == 1)
			sol = true;
	}
	cout << (sol ? "Yes" : "No") << endl;
}
