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
int seq[2000000];
int ans[2000000];
int n, k;
int dis(int j, int i){
	if(i > j)
		return i-j;
	else
		return  n - (j - i);
}
int main(){
	cin >> n >> k;	
	for(int i = 0; i < n; i++){
		cin >> seq[i];
	}
	deque<int> dq;
	for(int i = n - k + 1; i < n; i++){
		while(dq.size() && seq[dq.back()] <= seq[i])
			dq.pop_back();
		dq.eb(i);
	}
	/*
	cout << "init:";
	for(int v: dq){
		cout << " " << v;
	}
	cout << endl;
	*/
	for(int i = 0; i < n; i++){
		while(dq.size() && dis(dq.front(), i) >= k){
			dq.pop_front();
		}
		while(dq.size() && seq[dq.back()] <= seq[i])
			dq.pop_back();
		/*
		cout << i << ":";
		for(int v: dq){
			cout << " " << v;
		}
		cout << endl;
		*/
		dq.eb(i);
		ans[((i - k + 1) + n) % n] = seq[dq.front()];
	}

	for(int i = 0; i < n; i++){
		cout << ans[i] << (i == n-1 ? "\n" : " ");
	}
	return 0;
}

