// consider first 0...i-1 elements
// let res be the smallest number that can't be represent by them.
// i.e., 0...i-1 can represents [0, res)
// two cases.
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
const int maxn = 200000;
int seq[maxn];
int main(){
	yccc;		
	int n;
	cin >> n;
	REP(i, n){
		cin >> seq[i];
	}
	sort(seq, seq+n);
	ll res = 1;
	REP(i, n){
		if(seq[i] <= res){
			res += seq[i];
		}
		else{
			break;
		}
	}
	cout << res;
	return 0;
}

