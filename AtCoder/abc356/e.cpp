
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

int n;
ll arr[200005];
ll uarr[200005];
ll cnt[3000005];
ll pcnt[3000005]; // prefix
const ll maxmal = 3000000;


int main() {
	yccc;
	cin >> n;
	ll maxnum = 0;
	for(int i = 0; i < n; i++)
	{
		cin >> arr[i];
		cnt[arr[i]]++;
		maxnum = max(maxnum, arr[i]);
	}

	sort(arr, arr + n);

	int m = 0;
	uarr[m] = arr[0];
	m++;
	for(int i = 1; i < n; i++)
	{
		if (arr[i] != arr[i - 1])
		{
			uarr[m] = arr[i];
			m++;
		}
	}

	for(int i = 1; i <= maxmal; i++)
	{
//		cout << i << ": " << cnt[i] << endl;
		pcnt[i] = cnt[i] + pcnt[i - 1];
	}

	ll ans = 0;

	for(int i = 0; i < m; i++)
	{
//		cout << "processing " << uarr[i] << endl;
		ll val = (cnt[uarr[i]] * (cnt[uarr[i]] - 1)) / 2;
		ans += val;	
//			cout << "1. ans += " << val << endl;
		ll val1 = pcnt[uarr[i] * 2 - 1] - pcnt[uarr[i]];
		ans += val1 * cnt[uarr[i]];
		//cout << "3. ans += " << val1 << endl;

		for(ll k = 2; k <= (maxnum / uarr[i]); k++)
		{
			ll num = (pcnt[(k + 1) * uarr[i] - 1] - pcnt[k * uarr[i] - 1]);
//			cout << "there are #" << num << " with val " << k << endl;
			ll val = k * num * cnt[uarr[i]];
			ans += val;
//			cout << "2. ans += " << val << endl;
		}
	}

	cout << ans << endl;
	return 0;
}
