
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

long long prod[200005]; // productivity

int main() {
	yccc;
	int n;long long t; // #machines, target
	cin >> n >> t;
	for(int i = 0; i < n; i++){
		cin >> prod[i];
	}
	long long L = 1, R = (t / n + 1) * 1000000000LL;

	while(L < R){
		ll M = (L+R)/2;
		long long cur = 0;
		for(int i = 0; i < n; i++){
			cur += (M / prod[i]);
		}
		if(cur >= t){
			R = M;
		}
		else{
			L = M + 1;
		}
	}
	//cout << L << ", " << M  << endl;
	cout << L  << endl;

	return 0;
}
