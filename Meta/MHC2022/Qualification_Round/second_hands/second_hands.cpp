#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

int main(){
	int T;
	cin >> T;
	int caseN = 1;
	while(T--){
		int N, K;
		cin >> N >> K;
		int num = 0;
		vector<int> Vs(101, 0);
		for(int i = 0; i < N; i++){
			int t;
			cin >> t;
			Vs[t]++;
		}
		bool sol = true;
		for(int n: Vs){
			if(n > 2)
				sol = false;
			num += n;
		};
		if(num > 2 * K)
			sol = false;
		cout << "Case #" << caseN++ << ": " << (sol ? "YES" : "NO") << endl;
	}
		
	return 0;
}

