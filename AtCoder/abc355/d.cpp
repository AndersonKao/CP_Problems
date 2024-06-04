
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
	int n;
	cin >> n;
	vec<int> Ls, Rs;
	vec<p<int>> arr;
	for(int i = 0; i < n; i++)
	{
		int l, r;
		cin >> l >> r;
		arr.eb(l, r);
		Ls.eb(l);
		Rs.eb(r);
	}
	sort(al(Ls));
	sort(al(Rs));
	long long ans = 0;

	for(int i = 0; i < n; i++)
	{
		int l = arr[i].first, r = arr[i].second;
		long long outside = 0;
		outside += Ls.end() - upper_bound(al(Ls), r);
		outside += lower_bound(al(Rs), l) - Rs.begin();
		ans += (n - 1) - outside;
//		cout << Ls.end() - upper_bound(al(Ls), r) << ", ";
//		cout<< lower_bound(al(Rs), l) - Rs.begin() << endl;
	}
	ans /= 2;
	cout << ans << endl;

}
