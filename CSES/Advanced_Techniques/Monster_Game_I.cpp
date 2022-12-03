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
const int maxn = 200001;
const ll inf = 0x3f3f3f3f3f3f3f3f;
ll sval[maxn];
ll fval[maxn];
ll dp[maxn];

struct line{
	ll a, b;
	line(){a = b = 0;}
	line(ll a, ll b):a(a), b(b){}
	ll gety(ll x){
		return x*a + b;
	}
};
ll intersect(ll a, ll b, ll c ,ll d){
	return (d - b) / (a - c);
}

ll gety(ll x, int lid){
	return x * fval[lid] + dp[lid];
}
bool can_kill(int L1, int L2, int Lnew){
	ll x12 = intersect(fval[L1], dp[L1], fval[L2], dp[L2]);
	ll x2now = intersect(fval[L2], dp[L2], fval[Lnew], dp[Lnew]);
	return x2now < x12;
}

int main(){
	yccc;		
	int n, skill;
	cin >> n >> skill;
	fill(dp, dp+n, inf);
	for(int i = 0; i < n; i++){
		cin >> sval[i];
	}
	for(int i = 0; i < n; i++){
		cin >> fval[i];
	}
	deque<int> mS;
	for(int i = 0; i < n; i++){
		// the first one
		dp[i] = skill * sval[i];
		// transfer
		if(i > 0){
			while(mS.size() >= 2 && gety(sval[i], mS[0]) > gety(sval[i], mS[1])){
				mS.pop_front();
			}
			dp[i] = min(dp[i], gety(sval[i], mS[0])); 
			if(fval[i] == fval[mS.back()]){
				continue;
			}
			while(mS.size() >= 2 && can_kill(mS[mS.size()-2], mS[mS.size()-1], i))
				mS.pop_back();
			mS.push_back(i);
		}
		else
			mS.push_back(i);
	}
	cout << dp[n-1] << endl;
	return 0;
}

