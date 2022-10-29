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
const ll inf = 0x3f3f3f3f3f3f3f3f;
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		vec<int> V(n);
		for(int &e : V)
			cin >> e;
		vec<ll> P(n+1, 0);
		for(int i = 1; i <= n; i++){
			P[i] = V[i-1] + P[i-1];
//			cout << P[i] << (i == n ? '\n' : ' ');
		}
		P[0] = inf;
		stack<int> mS;
		stack<ll> MinS;
		int ans = 0;
		for(int i = 1; i <= n; i++){
			int Mmin = i;
			while(mS.size() && P[mS.top()] <= P[i]){
				if(P[MinS.top()] <= P[Mmin])
					Mmin = MinS.top();
//				cout << "pop: " << mS.top() << ", " << MinS.top() << endl;
				mS.pop();
				MinS.pop();
			}

			ans = max(i - Mmin, ans);

			if(mS.empty() && P[Mmin] >= 0){
				ans = max(ans, i);
			}
			/*
			debug(i);
			debug(Mmin);
			if(mS.size()){
				debug(mS.top());
				debug(MinS.top());
			}
			*/

			MinS.emplace((P[i] < P[Mmin]) ? i : Mmin);
			mS.emplace(i);
		}
		cout << ans << endl;
	}

	return 0;
}

