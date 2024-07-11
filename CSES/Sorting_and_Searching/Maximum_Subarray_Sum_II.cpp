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

ll V[200005];
ll pre[200005];

int main() {
	yccc;
	int n, a, b;
	cin >> n >> a >> b;
	for(int i = 1; i <= n; i++){
		cin >> V[i];
		pre[i] = pre[i-1] + V[i];
	}

	multiset<ll> pset;

	for(int i = a; i <= b; i++){
		pset.emplace(pre[i]);
	}
	ll ans = LLONG_MIN;

	for(int i = 1; i + a - 1 <= n; i++)
	{
		ans = max(ans, *pset.rbegin() - pre[i-1]);
		if(i + a - 1 <= n)
		{
			pset.erase(pset.find(pre[i + a - 1]));
		}
		if(i + b <= n){
			pset.emplace(pre[i + b]);
		}
	}
	cout << ans << endl;



	return 0;
}
