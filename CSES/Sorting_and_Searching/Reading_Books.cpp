
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
	vec<ll> V(n);
	ll sum = 0;
	ll M = 0;
   	for(int i = 0; i < n; i++){
		cin >> V[i];
		sum += V[i];
		M = max(M, V[i]);
	}
	ll sM = sum - M;
	ll ans;
	if(M >= sM){
		ans = 2*M;
	}
	else{
		ans = sum;
	}
	cout << ans << endl;
	return 0;
}
