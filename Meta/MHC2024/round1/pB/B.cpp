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
const int maxn = 10000000;
vec<bool> is_prime(maxn+1, true);
void SieveErato(){
    int n = maxn; // becase of ll
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }
}
int ans[maxn+1];

int main(){
	yccc;		
	SieveErato();
	ans[0] = 0;
	ans[1] = 0;
	ans[2] = 0;
	ans[3] = 0;
	ans[4] = 0;
	ans[5] = 2;
	for(int i = 6; i <= maxn; i++){
		if(is_prime[i] && is_prime[i - 2]){
			ans[i] = ans[i-1] + 1;	
		}
		else{
			ans[i] = ans[i-1];	
		}
	}
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
		int n;
		cin >> n;
		

		cout << "Case #" << i + 1 << ": ";
		cout << ans[n] << endl;
	}

	return 0;
}

