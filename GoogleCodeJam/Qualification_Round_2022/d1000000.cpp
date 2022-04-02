#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;

vec<int> seq;
int main(){
	yccc;	
	int T;
	cin >> T;
	REP1(cnt, T){
		cout << "Case #" << cnt << ": ";
		int N;
		cin >> N;
		seq.resize(N);
		REP(i, N)
			cin >> seq[i];
		int ans = 0;
		sort(al(seq));
		REP(i, N){
//			debug(seq[i]);
			if(seq[i] > ans)
				ans++;
		}
		cout << ans << endl;
	}
}
