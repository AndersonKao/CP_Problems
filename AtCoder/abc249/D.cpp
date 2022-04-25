
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define eb emplace_back
#define pr(X) cout << #X << ": " << X << endl 

using ll = long long;
using pii = pair<int, int>;
template<typename T>
using vec = vector<T>;

int N;
int maxi = 0;
vec<int> seq;
vec<pii> seq2;
vec<int> ext;
/*
auto cmp = [](const pii& a, const pii&b){
	if(a.F * (ll)b.F <= maxi)
		return true
	return false;
//	return a.F < b.F;
};
*/

int main(){
	cin >> N;
	seq.resize(N);

	REP(i, N){
		cin >> seq[i];
		maxi = max(maxi, seq[i]);
	}
	ext.resize(maxi + 1, 0);
	sort(al(seq));
	int cnt = 1;
	REP(i, N){
		ext[seq[i]]++;
		if(i > 0){
			if(seq[i] != seq[i-1]){
				seq2.eb(seq[i-1], cnt);
				cnt = 1;
			}
			else cnt++;
		}
	}
	seq2.eb(seq[N-1], cnt);
	ll ans = 0;
	REP(i, seq2.size()){
		for(int j = i + 1; j < seq2.size(); j++){
			ll val = (ll)seq2[i].F * seq2[j].F;
			if(val > maxi)
				break;
			if(ext[val]){
				if(val != seq2[j].F)
					ans += ext[val] * (ll)seq2[i].S * seq2[j].S * 2;
			}
		}		
	}
	for(int i = 0; i < seq2.size(); i++){
		ll val = (ll)seq2[i].F * seq2[i].F;
		if(val > maxi || !ext[val])
			continue;
		if(val == seq2[i].F){
			ll t = seq2[i].S;
				ans += t * t * t ;
		}else{
			ll t = seq2[i].S;
				ans += t * t * ext[val];
		}
	}
	if(seq2[0].F == 1){
		for(int i = 1;i < seq2.size(); i++){
			ll t = seq2[i].S;
			ans += seq2[0].S * t * t*2;
		}
	}
	cout << ans << endl;
		
	return 0;
}
