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
int seq[100002];
int Left[100001];
int main(){
	int n;
	while(cin >> n){
		memset(seq, 0, sizeof(seq));
		for(int i = 1; i <= n; i++)
			cin >> seq[i];	
		stack<int> st;
		st.emplace(0);
		ll ans = 0;
		for(int i = 1; i <= n+1; i++){
			while(st.size() && seq[st.top()] >= seq[i]){
				ans = max(ans, (i - Left[st.top()] - 1LL) * 1LL * seq[st.top()]);
				st.pop();
			}
			if(st.size())
				Left[i] = st.top();
			else
				Left[i] = i;
			st.emplace(i);
		}
		cout << ans << endl;
	}
	return 0;
}

