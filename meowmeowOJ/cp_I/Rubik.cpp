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
const int w = 8;

vec<pair<int, int>> ops[3]= {
{
	{ w*2 + 6, w*1 + 3 },
	{ w*3 + 6, w*0 + 3 },
	{ w*0 + 3, w*2 + 3 },
	{ w*1 + 3, w*3 + 3 },
	{ w*2 + 3, w*4 + 3 },
	{ w*3 + 3, w*5 + 3 },
	{ w*4 + 3, w*3 + 6 },
	{ w*5 + 3, w*2 + 6 },
	{ w*2 + 4, w*3 + 4 },
	{ w*3 + 4, w*3 + 5 },
	{ w*3 + 5, w*2 + 5 },
	{ w*2 + 5, w*2 + 4 }
},
{
	{ w*2 + 0, w*2 + 2 },
	{ w*2 + 1, w*2 + 3 },
	{ w*2 + 2, w*2 + 4 },
	{ w*2 + 3, w*2 + 5 },
	{ w*2 + 4, w*2 + 6 },
	{ w*2 + 5, w*2 + 7 },
	{ w*2 + 6, w*2 + 0 },
	{ w*2 + 7, w*2 + 1 },

	{ w*0 + 2, w*1 + 2 },
	{ w*1 + 2, w*1 + 3 },
	{ w*1 + 3, w*0 + 3 },
	{ w*0 + 3, w*0 + 2 }
},
{
	{ w*1 + 2, w*3 + 1 },
	{ w*1 + 3, w*2 + 1 },
	{ w*2 + 1, w*4 + 2},
	{ w*3 + 1, w*4 + 3},
	{ w*4 + 2, w*3 + 4},
	{ w*4 + 3, w*2 + 4},
	{ w*2 + 4, w*1 + 2},
	{ w*3 + 4, w*1 + 3},

	{ w*2 + 2, w*3 + 2 },
	{ w*3 + 2, w*3 + 3 },
	{ w*3 + 3, w*2 + 3 },
	{ w*2 + 3, w*2 + 2 }
}
};
bool validit(string & str){
	bool test = true;
	for(int base = 0; base < 6; base +=2){
		for(int i = base; i <= base+1; i++){
			for(int j = 2; j <= 3; j++){
				if(str[w*i + j] != str[w*base + 2])
					test = false;
			}	
		}
	}
	for(int base = 0; base < 8; base +=2){
		for(int i = 2; i <= 3; i++){
			for(int j = base; j <= base+1; j++){
				if(str[w*i + j] != str[w*2 + base])
					test = false;
			}	
		}
	}
	return test;
}
vector<char> ans;
unordered_set<string> mS;
string cur, nxt;
int limit;
bool dfs(int d){
	//cout << cur << endl;
	if(validit(cur)){
		return true;	
	}
	if(d == limit)
		return false;

	ans.eb('X');
	nxt = cur;
	for(p<int>&e : ops[0]){
		cur[e.S] = nxt[e.F];
	}
	if(mS.find(cur) == mS.end()){
		mS.emplace(cur);
		if(dfs(d+1))
			return true;
	}
	nxt = cur;
	for(p<int>&e : ops[0]){
		cur[e.F] = nxt[e.S];
	}
	ans.pop_back();

	ans.eb('Y');
	nxt = cur;
	for(p<int>&e : ops[1]){
		cur[e.S] = nxt[e.F];
	}
	if(mS.find(cur) == mS.end()){
		mS.emplace(cur);
		if(dfs(d+1))
			return true;
	}
	nxt = cur;
	for(p<int>&e : ops[1]){
		cur[e.F] = nxt[e.S];
	}
	ans.pop_back();

	ans.eb('Z');
	nxt = cur;
	for(p<int>&e : ops[2]){
		cur[e.S] = nxt[e.F];
	}
	if(mS.find(cur) == mS.end()){
		mS.emplace(cur);
		if(dfs(d+1))
			return true;
	}
	nxt = cur;
	for(p<int>&e : ops[2]){
		cur[e.F] = nxt[e.S];
	}
	ans.pop_back();

	return false;
}	

int main(){
	yccc;		
	bool valid = true;
	while(valid){
		string str = "";
		for(int i = 0; i < 6; i++){
			string tmp;
			cin >> tmp;
			str.append(tmp);
		}
//		cout << str << endl;
		valid = false;
		for(int i = 0; i < str.length(); i++){
			if(str[i] != '.')
				valid = true;
		}
		if(valid == false) break;
		if(validit(str)){
			cout << endl;
			continue;
		}
		cur = str;
		for(int d = 1; ; ++d){
			limit = d;
			ans.clear();
			mS.clear();
			mS.emplace(cur);
			if(dfs(0)){
				for(char ch: ans)
					cout << ch;
				cout << endl;
				break;
			}
		}
	}

	return 0;
}

