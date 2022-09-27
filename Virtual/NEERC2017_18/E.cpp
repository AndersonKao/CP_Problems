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
int n;
bool hasmul[1000001];
int valnum[1000001] = {0};
int main(){
#ifndef Kao
	freopen("equal.in", "r", stdin);
	freopen("equal.out", "w", stdout);
#endif
	cin >> n;
	vec<int> arr(n);	
	vec<int> ans(n+1);
	REP(i, n){
		cin >> arr[i];
		valnum[arr[i]]++;
	}
	vec<int> numset = arr;
	sort(al(numset));
	numset.resize(distance(numset.begin(), unique(al(numset))));
	int ntypes = ans[0] = numset.size();
	for(int v: numset){
		for(int i = 2; i * i <= v; i++){
			if(v % i == 0){
				hasmul[i] = hasmul[v/i] = true;
			}
		}
		if(v != 1)
			hasmul[1] = true;
	}
	vec<int> mV[2];	
	for(int v: numset){
		mV[0].eb(valnum[v]);
		if(hasmul[v]){
			mV[1].eb(valnum[v]);
		}
	}
	sort(al(mV[0])), sort(al(mV[1]));
	int l = 0;
	int cnt = 0;
	for(int k: mV[0]){ // to LCM
		for(int i = l+1; i < l + k; i++){
			ans[i] = ntypes - cnt;
		}
		if(l == 0)
			ans[l+k] = ntypes;
		else{
			cnt++;
			ans[l+k] = ntypes-cnt;
		}
		l = l + k;
	}
	l = 0;
	cnt = 0;
	int ksum = 0;
	for(int k: mV[1]){ // to some a_j
		for(int i = l+1; i < l + k; i++){
			ans[i] = min(ans[i], ntypes - cnt);
		}
		cnt++;
		ans[l+k] = min(ans[l+k], ntypes - cnt);
		l = l + k;
		ksum += k;	
	}
	cout << ans[0];
	for(int i = 1; i <= n; i++){
		if(i <= ksum)
			cout << " " << ans[i];
		else
			cout << " " << min(ans[i], ans[ksum]); 
			// for case: 最後一組數字恰好是所有數字的LCM
			// ex. 7 2 2 1 1 1 1 1
			// ex. 8 30 30 30 6 6 6 5 5 
	}
	cout << "\n";
	return 0;
}

