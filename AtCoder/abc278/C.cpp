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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
struct event{
	int T, A, B;
};
event events[200000];
set<int> mS[400000];
int main(){
	yccc;		
	int n, q;
	cin >> n >> q;
	vec<int> players;
	for(int i = 0; i < q; i++){
		cin >> events[i].T >> events[i].A >> events[i].B;
		players.eb(events[i].A);
		players.eb(events[i].B);
	}

	sort(players.begin(), players.end());
	players.resize(unique(al(players)) - players.begin());

	for(int i = 0; i < q; i++){
		events[i].A = lower_bound(al(players), events[i].A) - players.begin();
		events[i].B = lower_bound(al(players), events[i].B) - players.begin();
	}

	for(int i = 0; i < q; i++){
		int t = events[i].T;
		int a = events[i].A;
		int b = events[i].B;
		if(t == 1){
			mS[a].emplace(b);
		}
		else if(t == 2){
			mS[a].erase(b);
		}
		else {
			if(mS[a].count(b) && mS[b].count(a)){
				cout << "Yes\n";
			}
			else{
				cout << "No\n";

			}
		}
	}

	return 0;
}

