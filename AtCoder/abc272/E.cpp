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

int main(){
	int N, M;
	cin >> N >> M;
	vec<int> V(N+1);
	REP1(i, N)
		cin >> V[i];
	vec<int> st(N+1), ed(N+1);
	REP1(v, N){
		if(V[v] >= 0){
			if(V[v] > N){
				st[v] = N+1;
				ed[v] = N+1;
			}
			else{
				st[v] = 0;
				ed[v] = (N - V[v]) / v + 1;
			}
		}
		else{
			st[v] = (-V[v] / v) + (-V[v] % v == 0 ? 0 : 1);	
			ed[v] = (N - V[v]) / v + 1;
		}
	}
	vec<vec<int>> Rid(M+1); // round [i] need to concern 
	REP1(i, N){
//		cout << st[i] << " " << ed[i] << endl;
		for(int r = st[i]; r <= min(ed[i], M); r++){
			Rid[r].eb(i);
		}
	}
	REP1(round, M){
		vec<int> mV;
//		debug(round);
		for(int id: Rid[round]){
//			cout << id << ", ";
			mV.eb(V[id] + id * round);
		}
//		cout << endl;
		sort(al(mV));
		mV.resize(unique(al(mV))- mV.begin());
		/*
		cout << "mV: ";
		for(int v: mV){
			cout << v << ", ";
		}
		cout << endl;
		*/
		int ans = 0;
		auto it = mV.begin();
		while(it != mV.end() && ans == *it){
			ans++;
			it++;
		}
		cout << ans << endl;
	}
	return 0;
}

