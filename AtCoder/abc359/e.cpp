
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

ll h[200005];
ll ans[200005];

int main() {
	yccc;
	int n;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		cin >> h[i];
	}
	stack<pair<ll, int>> st;

	ans[1] = h[1];
	st.emplace(h[1], 1);

	for(int i = 2; i <= n; i++){
		//cout << i << ":\n";
		ans[i] = ans[i-1];

		ll sum = i-1;

		ans[i] += h[i];
		while(st.size() && st.top().first < h[i]){
			//cout << st.top().first << ", " << st.top(). second << endl;;
			//cout << (h[i] - st.top().first) * st.top().second << endl;
			ans[i] += (h[i] - st.top().first) * st.top().second;
			sum -= st.top().second;
			st.pop();
		}
		if(st.size())
		{
			st.emplace(h[i], i - sum);
		}
		else{
			st.emplace(h[i], i);
		}
	}

	for(int i = 1; i <= n; i++)
	{
		cout << ans[i] + 1 << " ";
	}
	cout << endl;

	return 0;
}
