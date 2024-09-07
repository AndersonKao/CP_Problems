
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

const int maxlen = 200000000;
int main() {
	yccc;
	int n, q;
	cin >> n >> q;
	vec<int> a(n);
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	sort(al(a));
	while(q--){
		int b, k;
		cin >> b >> k;
		int found;
		int L = 0, R = maxlen;
		do{
			int curlen = (R+L)/2;
			auto itR = upper_bound(al(a), b+curlen);
			auto itL = lower_bound(al(a), b-curlen);
			int cnt = itR - itL;
			int nxtlen;
			if(cnt > k){
				R = curlen;
			}
			else if(cnt < k){
				L = curlen;
			}
			else if(cnt == k)
				break;
		}while(R - L > 10);
		
		int curlen = (R+L)/2;
		//debug(L); debug(R);
		if(R - L <= 10){
			for(curlen = L; curlen <= R; curlen++){
				auto itR = upper_bound(al(a), b+curlen);
				auto itL = lower_bound(al(a), b-curlen);
				int cnt = itR - itL;
				if(cnt >= k){
					break;
				}
			}
		}
		//debug(curlen);
		auto itR = upper_bound(al(a), b+curlen) - 1;
		auto itL = lower_bound(al(a), b-curlen);
		//debug(*itL);
		//debug(*itR);
		//debug(itR - itL);
		int ans = (*itR - b) > (b - *itL) ? (*itR) : (*itL);
		cout << abs(ans - b) << endl;
	}
	return 0;
}
