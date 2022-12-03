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
ll val[200000];
int mark[200000];
int main(){
	yccc;		
	int n;
	cin >> n ;
	REP(i, n){
		cin >> val[i];
	}
	int q;
	cin >> q;
	int allset = -1;
	fill(mark, mark + n, -1);
	ll allval;
	REP(i, q){
		int t; cin >> t;
		int x;
		int idx;
		if( t == 1){
			cin >> x;
			allset = i;
			allval = x;
		}
		else if( t == 2){
			cin >> idx >> x;
			idx--;
			if(mark[idx] < allset){
				val[idx] = allval;	
				mark[idx] = allset;
			}
			val[idx] += x;
		}
		else {
			cin >> idx;
			idx--;
			if(mark[idx] < allset){
				val[idx] = allval;	
				mark[idx] = allset;
			}
			cout << val[idx] << endl;
		}
	}
	return 0;
}

