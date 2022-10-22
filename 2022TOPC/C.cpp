
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0);
#define endl '\n'
#define eb emplace_back
#define F first
#define S second
#define al(a) a.begin(),a.end()

int main() {
	yccc;

	int h, m;
	cin >> h >> m;

	cout << (h-9) * 60 + m << endl;
	
}
