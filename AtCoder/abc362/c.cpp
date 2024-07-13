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
	vec<int> L(n), R(n);
	vec<ll> ans(n);
	ll sum = 0;
	for(int i = 0; i < n; i++){
		cin >> L[i] >> R[i];
		ans[i] = L[i];
		sum += L[i];
	}
	//cout << sum << endl;
	if(sum > 0){
		cout << "No" << endl;
		return 0;
	}
	for(int i = 0; i < n; i++){
		
		if(sum < 0){
			if(R[i] - L[i] >= -sum){
				ans[i] = L[i] + (-sum);
				sum = 0;
			}
			else{
				sum += (R[i] - L[i]);
				ans[i] = R[i];
			}
		}
		//cout << sum << ", " << ans[i] << endl;
	}
	if(sum < 0){
		cout << "No" << endl;
		return 0;
	}
	cout << "Yes" << endl;
	for(int i = 0; i < n; i++){
		cout << ans[i] << (i == n-1 ? '\n' : ' ');
	}

	

	return 0;
}
