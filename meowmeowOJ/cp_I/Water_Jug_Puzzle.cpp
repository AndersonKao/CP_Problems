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
int Jug[5];

bool foundit(vec<int>& V, int q){
	for(int v: V)
		if(v == q) return true;
	return false;
}

int main(){
	yccc;		
	int n;
	int Q;
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> Jug[i];
	cin >> Q;
	if(Q == 0){
		cout << 0 << endl;
		return 0;
	}

	set<vec<int>> mS;
	queue<vec<int>> mQ[2];

	mS.emplace(vec<int>(n, 0));
	mQ[0].emplace(vec<int>(n, 0));

	int round = 0;
	bool found = false;
	while(found == false && mQ[0].size()){
		round++;
//		debug(round);
		while(mQ[0].size()){
			vec<int> cur = mQ[0].front();
			mQ[0].pop();
			/*
			cout << "grep  v = ";
			for(int val: cur){
				cout << val << " ";
			}
			cout << endl;
			*/
			for(int i = 0; i < n; i++){
				if( cur[i] != Jug[i] ){
					vec<int> next = cur;
					next[i] = Jug[i];
					if(mS.find(next) == mS.end()){
						if(found = foundit(next, Q)){
							break;
						}
						mS.emplace(next);
						mQ[1].emplace(next);
					}
				}
				if( cur[i] != 0 ) {
					vec<int> next = cur;
					next[i] = 0;
					if(mS.find(next) == mS.end()){
						if(found = foundit(next, Q)){
							break;
						}
						mS.emplace(next);
						mQ[1].emplace(next);
					}
				}
			}
			if(found) break;
			for(int i = 0; i < n; i++){
				if(cur[i] == 0) continue;
				for(int j = 0; j < n; j++){
					if( i == j || cur[j] == Jug[j] ) continue;
					vec<int> next = cur;
					next[j] = min(Jug[j], next[j] + cur[i]);
					next[i] -= next[j] - cur[j];
					if(mS.find(next) == mS.end()){
						if(found = foundit(next, Q)){
							break;
						}
						mS.emplace(next);
						mQ[1].emplace(next);
					}
				}
				if(found) break;
			}
			if(found) break;
		}
		if(found == false) 
			swap(mQ[0], mQ[1]);
	}
	if(found) 
		cout << round << endl;	
	else
		cout << -1 << endl;
	return 0;
}

