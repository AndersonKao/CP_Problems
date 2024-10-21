#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const ll MOD = 998244353LL;

void solve(int ct){
	string str;
	cin >> str;
	int K;
	cin >> K;
	K--;
	int idx = 0;
	ll base = 1;
	int lidx = str.length()-1;
	if(str.length() == 1){
		str[lidx] = '9' - K;
	}
	else{
		if(str[lidx] == '?'){
			if(str[lidx-1] == '?'){
				base = 15;
				int tK = K % base;
				if(tK < 6){
					str[lidx-1] = '2';
					str[lidx] = '6' - tK;
				}
				else{
					str[lidx-1] = '1';
					str[lidx] = '9' - (tK - 6);
				}
			}
			else{
				if(str[lidx-1] == '2'){
					base = 6;
					str[lidx] = '6' - (K % base);
				}
				else{
					base = 9;
					str[lidx] = '9' - (K % base);
				}
			}
		}
	}
	K = K / base;
	for(int i = str.length()-2; i >= 0; i--){
		if(str[i] != '?') continue;
		if(str[i+1] <= '6'){
			if(K & 1){
				str[i] = '1';		
			}
			else{
				str[i] = '2';
			}
			K >>= 1;
		}
		else{
			str[i] = '1';
		}
	}
	vec<ll> dp(str.length(), 0);
	dp[0] = 1;
	for(int i = 1; i < str.length(); i++){
		if(str[i] == '0'){
			if(i == 1){
				dp[i] = 1;
			}
			else{
				dp[i] = dp[i-2];
			}
		}
		else{
			dp[i] = dp[i-1];
			if(str[i-1] == '1'){
				if(i == 1){
					dp[i] += 1;
				}
				else{
					dp[i] += dp[i-2];
				}
			}
			else if(str[i-1] == '2'){
				if(str[i] <= '6'){
					if(i == 1){
						dp[i] += 1;
					}
					else{
						dp[i] += dp[i-2];	
					}
				}
			}
			dp[i] %= MOD;
		}
	}

	cout << "Case #" << ct << ": ";
	cout << str << " ";
	cout << dp[str.length()-1] << endl;
}

int main(){
	yccc;		
	int t;
	cin >> t;
	for(int ct = 1; ct <= t; ct++){
		solve(ct);
	}
	return 0;
}

