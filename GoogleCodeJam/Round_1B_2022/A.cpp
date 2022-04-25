#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F frist
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < (int)n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;


deque<int> seq;

int n;
int main(){
	yccc;	

	int T;
	cin >> T;	
	int cnt= 1;
	while(T--){
		cin >> n;
		REP(i, n){
			int data;
			cin >> data;
			seq.emplace_back(data);
		}
		int m = 0;
		int ans = 0;
		while(seq.size()){
			if(seq.front() <= seq.back()){
				if(seq.front() >= m)
					ans++;
				m = max(m, seq.front());
				seq.pop_front();	
			}else{
				if(seq.back() >= m)
					ans++;
				m = max(m, seq.back());
				seq.pop_back();	
			}
		}
		cout << "Case #" << cnt++ << ": "  << ans << endl;
	}

}
