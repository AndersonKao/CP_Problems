#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define al(a) a.begin(), a.end()
#define F first
#define S second
#define eb emplace_back
#define REP(i,n) for(int i = 0; i < (int)n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define debug(x) cout << " > " << #x << ": " << x << endl
#define depii(x) cout << " > " << #x << ": (" << x.first << ", " << x.second << ")" << endl
using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
const int intINF = numeric_limits<int>::max();
const ll llINF = numeric_limits<ll>::max();
const double eps = 1e-9;

int fcmp(const double &a, const double& b){
	if(fabs(a - b) < eps)
		return 0;
	return (a > b) * 2 - 1;
}

auto cmp = [](const int &a, const int &b) {
	return a < b;
};

int N;
vec<string> strs;
vec<vec<pii>> tab;
deque<int> ansSt;
vec<bool> used;
vec<vec<int>> all(26);
vec<vec<int>> bg(26);
bool sol = false;
bool begin(int i){
	int cnt = 1;
	ansSt.eb(i);
	int ch = tab[ansSt.back()].back().F;
	for(int& i : all[ch]){
		used[i] = true;
		ansSt.eb(i);
		cnt++;
	}
	while(cnt < N){
		int ch = tab[ansSt.back()].back().F;
		if(bg[ch].size() && !used[bg[ch][0]]){
			ansSt.eb(bg[ch][0]);
			int bt = tab[bg[ch][0]].back().F;
			for(int& i : all[bt]){
				used[i] = true;
				ansSt.eb(i);
				cnt++;
			}
		}else{
			int find = -1;
			REP(i, 26){
				if(bg[i].size() && !used[bg[i][0]]){
					find = i;
					break;
				}
			}	
			if(find == -1){
				
			}else{
				ansSt.eb(find);
				int bt = tab[find].back().F;
				for(int& i : all[bt]){
					used[i] = true;
					ansSt.eb(i);
					cnt++;
				}
			}
		}
	}
	return true;
}
bool valid(int idx){
	vec<bool> apr(26, false);
	int ch = strs[idx][0] - 'A';
	apr[ch] = true;
	for(int i = 1; i < (int)strs[idx].length(); i++){
		ch = strs[idx][i] - 'A';
		if(strs[idx][i] != strs[idx][i-1]){
			if(apr[ch])
				return false;
		}
		apr[ch] = true;
	}
	return true;
}
int main(){
	yccc;
	int cnt = 1;
	int T;
	cin >> T;
	while(T--){
		cin >> N;
		cout << "Case #" << cnt++ << ": ";
		while(ansSt.size())
			ansSt.pop_back();
		sol = false;
		strs.resize(N);
		tab.clear();
		tab.resize(N);
		used.resize(N);
		REP(i, 26)
			all.clear(), bg.clear();
		REP(i, N)
			cin >> strs[i];
		bool nonvalid = false;
		REP(i, N)
		{
			if (!valid(i))
			{
				nonvalid = true;
			}
		}
		if(!nonvalid){
			REP(i, N){
				char ch = strs[i][0];
				int cnt = 1;
				for (int j = 1; j < (int)strs[i].length(); j++)
				{
					if(strs[i][j] != ch){
						tab[i].emplace_back(ch - 'A', cnt);
						ch = strs[i][j];
						cnt = 1;
					}else
						cnt++;
				}
				tab[i].emplace_back(ch - 'A', cnt);
				if(tab[i].size()== 1)
					all[ch - 'A'].eb(i);
				else
					bg[tab[i][0].F].eb(i);
			}
			bool fail = false;
			REP(i, 26)
			{
				if (bg[i].size() > 1)
				{
					fail = true;
					break;
				}
			}
			if(!fail){
				REP(i, N){
					fill(al(used), false);
					if(begin(i)){
						sol = true;
						break;
					}
				}
			}
		}
		if(sol){
			while(ansSt.size()){
				cout << strs[ansSt.front()];
				ansSt.pop_front();
			}
		}else{
			cout << "IMPOSSIBLE";
		}
		cout << endl;
	}
	return 0;
}
