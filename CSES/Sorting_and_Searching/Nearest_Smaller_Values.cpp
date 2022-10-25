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
int seq[200000];
int ans[200000];
int main(){
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> seq[i];
	}	
	stack<int> st;
	for(int i = 0; i < n; i++){
		while(st.size() && seq[st.top()] >= seq[i])
			st.pop();
		if(st.empty()){
			ans[i] = 0;
		}
		else{
			ans[i] = st.top()+1;
		}
		st.emplace(i);
	}
	for(int i = 0; i < n; i++){
		cout << ans[i] << (i == n-1 ? "\n" : " ");
	}
	return 0;
}

