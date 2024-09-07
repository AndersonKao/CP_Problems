
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

int main() {
	yccc;
	int n;
	ll x, y;
	cin >> n >> x >> y;
	vec<pair<ll, ll>> s(n);
	for(int i = 0; i < n; i++){
		cin >> s[i].first;
	}
	for(int i = 0; i < n; i++)
		cin >> s[i].second;
	sort(al(s), greater<pair<ll, ll>>());
	int ans = n;
	ll sumx = 0;
	ll sumy = 0;
	for(int i = 0; i < n; i++)
	{
		sumx += s[i].first;
		sumy += s[i].second;
		if(sumx > x || sumy > y){
			ans = min(ans, i+1);
		}
	}
	for(int i = 0; i < n; i++)
		swap(s[i].first, s[i].second);
	sort(al(s), greater<pair<ll, ll>>());
	sumx = sumy = 0;
	for(int i = 0; i < n; i++)
	{
		sumy += s[i].first;
		sumx += s[i].second;
		if(sumx > x || sumy > y){
			ans = min(ans, i+1);
		}
	}
	cout << ans << endl;

	return 0;
}
