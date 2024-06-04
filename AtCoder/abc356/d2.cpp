
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

const long long MOD = 998244353;

long long N, M;
ll ans = 0;

int main() {
	yccc;

	cin >> N >> M; 
	ll div = 2;
	ll t = 1;

	for(int i = 0; (1LL << i) <= M && (1LL << i) <= N; i++)
	{
//		cout << i << "-th\n" << div << ", " << t << endl;
		if (((1LL << i) & M) == 0){
			div *= 2;
			t *= 2;	
			continue;
		}
		ans += ((N+1) / div) * t;
//		cout << "add " << ((N+1) / div) * t << endl;
		ans %= MOD;

		ans += max(0LL, ((N+1) % div) - (div/2LL));
//		cout << "add " << max(0LL, ((N+1) % div) - (div/2LL)) << endl;
		ans %= MOD;

		div *= 2;
		t *= 2;	

	}
	cout << ans << endl;

	return 0;
}
