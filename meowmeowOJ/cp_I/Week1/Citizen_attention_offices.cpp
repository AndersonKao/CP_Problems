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
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
vec<vec<ll>> mat(5, vec<ll>(5));
int arr[5];
ll min_ans = numeric_limits<ll>::max();
int ans_arr[5];
void recur(int pos, int idx){
	if(idx == 5){
		ll cur = 0;
		REP(r, 5){
			REP(c, 5){
				ll res = numeric_limits<ll>::max();
				REP(i, 5){
					res = min(res, (ll)abs(r-arr[i]/5) + abs(c-arr[i]%5)); 
				}
				cur += res * mat[r][c];
			}
		}
		if(cur < min_ans){
			min_ans = cur;
			REP(i, 5){
				ans_arr[i] = arr[i];
			}
		}
		return;
	}
	if(pos == 25)
		return;
	arr[idx] = pos;
	recur(pos+1, idx+1);
	recur(pos+1, idx);
}

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		REP(i, 5)
			fill(al(mat[i]), 0);	
		REP(i, n){
			int r,c;
			cin >> r >> c; 
			cin >> mat[r][c];
		}
		min_ans = numeric_limits<ll>::max();
		recur(0, 0);
		REP(i, 5){
			cout << ans_arr[i] << (i == 4 ? "\n" : " ");
		}
	}
		
	return 0;
}

