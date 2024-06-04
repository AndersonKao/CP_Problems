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
	long long A[105];
	long long B[105];
	for(int i = 0; i < m; i++)
	{
		cin >> A[i];
		B[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++){
			int val;
			cin >> val;
			B[j] += val;
		}
	}
	
	for(int i = 0; i < m; i++)
	{
		if (B[i] < A[i])
		{
			cout << "No";
			break;
		}
		if (i == m-1)
			cout << "Yes";
	}

	return 0;
}
