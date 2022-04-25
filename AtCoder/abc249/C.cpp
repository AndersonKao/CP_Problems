
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define eb emplace_back

using ll = long long;
using pii = pair<int, int>;
template<typename T>
using vec = vector<T>;
auto cmp = [](int& a, int& b){
	return a < b;
};

int n, K;

vec<string> strs;
vec<int> cnt(26, 0);
int ans = 0;
int cur = 0;
void DFS(int idx){
	if(idx >= n){
		ans = max(ans, cur);
		return;
	}
	// no select	
	DFS(idx+1);
	
	REP(i, strs[idx].length()){
		int m = strs[idx][i] - 'a';
		cnt[m]++;
		if(cnt[m] == K){
			cur++;		
		}else if(cnt[m] == K+1)
			cur--;
	}
	DFS(idx+1);
	REP(i, strs[idx].length()){
		int m = strs[idx][i] - 'a';
		cnt[m]--;
		if(cnt[m] == K){
			cur++;		
		}else if(cnt[m] == K-1)
			cur--;
	}
}


int main(){
	cin >> n >> K;
	strs.resize(n);
	REP(i, n)
		cin >> strs[i];
	DFS(0);
	cout << ans << endl;
	return 0;
}
