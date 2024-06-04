
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

int originPop = 0;

long long getcount(int k)
{
	cout << "k = " << k << endl;
	long long ans = 0;
	int Pop = 0;
	for(int i = 0; i < k; i++)
	{
		if ( ((1LL << i) & M) > 0)
			Pop++;
	}
	cout << "Pop = " << Pop << endl;
	for(int i = 0; i < Pop; i++)
	{
		ans += (1 << (k-1));
		ans %= MOD;
	}
	cout << "tmp = " << ans << endl;
	return ans;
}

long long getibit(ll N, int i)
{
	return (N >> (i));
}

int main() {
	yccc;

	cin >> N >> M; 
	for(int i = 0; (1LL << i) <= M; i++)
	{
		if (getbit(N, i) == getbit(M, i))
			originPop++;
	}

	cout << "originPop: " << originPop << endl;
	if(originPop == 0)
	{
		cout << 0 << endl;
		return 0;
	}

	long long ans = originPop;
	
	for(int i = 1; (1LL << i) <= N; i++)
	{
		if ( ((1LL << i) & N) == 0)
			continue;
		ans += getcount(i);
		ans %= MOD;
		
	}
	cout << ans << endl;

	return 0;
}
