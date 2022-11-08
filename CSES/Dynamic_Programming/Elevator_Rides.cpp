// AC
// maintain: 1. minimum rides [S] 2. minimum weight of last ride [S]
// S is a set of people.
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

int n;
int w[maxn];
p<int> dp[(1<<maxn)];

inline int lowbit(int x){
	return x & (~x + 1);
}

int main(){
	yccc;		
	int x;
	cin >> n >> x;
	for(int i = 0; i < n; i++){
		cin >> w[i];
	}
	dp[0].F = 1, dp[0].S = 0;
	for(int mask = 1; mask < (1 << n); mask++){
		dp[mask].F = dp[mask].S = inf;
		for(int i = 0; i < n; i++){
			if((1 << i) & mask){
				int submask = mask - (1 << i);
				if(dp[submask].S + w[i] <= x){
					if(dp[submask].F < dp[mask].F){
						dp[mask].F = dp[submask].F;
						dp[mask].S = dp[submask].S + w[i];
					}
					else if(dp[submask].F == dp[mask].F){
						dp[mask].S = min(dp[mask].S, dp[submask].S + w[i]);
					}
				}
				else{
					if(dp[submask].F + 1 < dp[mask].F){
						dp[mask].F = dp[submask].F + 1;
						dp[mask].S = w[i];
					}
					else if(dp[submask].F + 1 == dp[mask].F){
						dp[mask].S = min(dp[mask].S, w[i]);
					}
				}
			}
		}
//		cout << bitset<5>(mask) << ", " << dp[mask].F << ", " << dp[mask].S << endl;
	}
	cout << dp[(1 << n)-1].F << endl;

	return 0;
}

