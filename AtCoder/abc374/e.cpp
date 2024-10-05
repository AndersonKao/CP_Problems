
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
struct ma{
	ll A, B, P, Q;
};
ma mac[100];
int n;
ll X;

ll ceil(ll a, ll b){
	if(a % b == 0){
		return a / b;
	}
	return a / b + 1;
}
ll gcd(ll a, ll b){
	if(b % a == 0){
		return a;
	}
	if(a % b == 0){
		return b;
	}
	if(a < b){
		swap(a, b);
	}
	return gcd(b, a % b);
}
const ll mcnt = 10000000LL;
bool possible(ll W){
	if(W == 0)
		return true;
	//debug(W);
	ll curX = X;
	for(int i = 0; i < n; i++){
		ll budget = LLONG_MAX;
		ll g =  mac[i].A * mac[i].B / gcd(mac[i].A, mac[i].B);
		if(curX >= mac[i].P){
			ll cnt1 = (W / g);
			ll cnt1_1 = 0, cnt1_2 = 0;
			ll budget1 = cnt1 * (g / mac[i].A)* mac[i].P;
			if(W % g != 0){
				cnt1_1 = ceil(W % g, mac[i].A);
				cnt1_2 = ceil(W % g, mac[i].B);
			}
			budget = min(budget, budget1 + min(cnt1_1 * mac[i].P, cnt1_2 * mac[i].Q));
		}
		if(curX >= mac[i].Q){
			ll cnt1 = W / g;
			ll cnt1_1 = 0, cnt1_2 = 0;
			ll budget1 = cnt1 * mac[i].Q *(g/mac[i].B);
			if(W % g != 0){
				cnt1_1 = ceil(W % g, mac[i].A);
				cnt1_2 = ceil(W % g, mac[i].B);
			}
			budget = min(budget, budget1 + min(cnt1_1 * mac[i].P, cnt1_2 * mac[i].Q));
		}
		/*
		debug(budget1);
		debug(cnt1_1);
		debug(cnt1_2);
		debug(cnt2);
		debug(budget2);
		debug(cnt2_1);
		debug(cnt2_2);
		debug(budget);
		*/
		if(curX < budget){
			return false;
		}
		curX -= budget;
	}
	return true;
}

int main(){
	yccc;		
	cin >> n >> X;
	for(int i = 0; i < n; i++){
		cin >> mac[i].A >> mac[i].P >> mac[i].B >> mac[i].Q;
	}
	ll L = 0, R = 10000000000LL;
	while(L + 100 <= R){
		ll M = (R+L)/2;
		if(possible(M)){
			L = M;
		}
		else{
			R = M-1;
		}
	}
	for(ll ans = R; ans >= L; ans--){
		if(possible(ans) == true){
			cout << ans << endl;
			break;
		}
	}
	return 0;
}

