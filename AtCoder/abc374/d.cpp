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

vec<pair<pii, pii>> lines;
double dis(pii a, pii b){
	int xdis = b.F - a.F;
	int ydis = b.S - a.S;
	return sqrt(xdis * xdis + ydis * ydis);
}
int main(){
	yccc;		
	int n, s, t;
	cin >> n >> s >> t;
	lines.resize(n);
	for(int i = 0; i < n; i++){
		cin >> lines[i].F.F >> lines[i].F.S >> lines[i].S.F >> lines[i].S.S;
	}
	sort(al(lines));
	double ans = 1e12;
	do{
		int bitmask = (1 << n);
		for(int bit = 0; bit < bitmask; bit++){
			double res = 0.0;
			pii cur(0,0);
			for(int i = 0; i < n; i++){
				if(bit & (1 << i)){
					res += dis(cur, lines[i].S) / s;
				}
				else{
					res += dis(cur, lines[i].F) / s;
				}
				res += dis(lines[i].F, lines[i].S) / t;
				if(bit & (1 << i)){
					cur = lines[i].F;
				}
				else{
					cur = lines[i].S;
				}
			}
			ans = min(ans, res);
		}
	}while(next_permutation(al(lines)));
	cout << fixed << setprecision(7) <<  ans << endl;


	return 0;
}

