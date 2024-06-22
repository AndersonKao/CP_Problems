
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

int deg[200005];

int main() {
	yccc;
	int n;
	cin >>n ;
	vector<ll> arr;
	priority_queue<pair<ll, int>> pq;
	for(int i = 0; i < n; i++){
		ll val;
		cin >> val;
		arr.eb(val);
	}
	ll ans = 0;
	sort(al(arr));
	
	pq.emplace(arr[0], 0);
	for(int i = 1; i < n; i++)
	{
		ll val; int id;
		tie(val, id) = pq.top();

		pq.pop();
		
		ans += val; 
		ans += arr[i];
		deg[id]++;

		pq.emplace((2*deg[id]+1) * arr[id], id);

		deg[i]++;

		pq.emplace((2*deg[id] + 1) * arr[i], i);
	}
	cout << ans << endl;
	return 0;
}
