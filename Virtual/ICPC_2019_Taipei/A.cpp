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
#define endl "\n"
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
const int width = 6;
int type[11]; // 1 for - 2 for | 
int di[4][2] = {
	{0, -1},
	{-1, 0},
	{0 , 1},
	{1, 0}
};
int n = 0;
int cnt1 = 0;
bool Validit(const string & cur){
	int idx = 3 * width - 1;	
	for(int i = 0; i < cnt1; i++)
		if(cur[idx-i] != 'b')
			return false;
	return true;
}
inline bool getcid(int i, int idx, int mtype, int& cid){
	int col = i % width, row = i / width;
	if(type[idx] == 1){
		if(mtype == 0){
			if(col == 0)
				return false;
			cid = (col - 1) + row * width;
		}		
		else{
			if(col == width - 1)
				return false;
			cid = (col + 1) + row * width;
		}
	}
	else{
		if(mtype == 0){
			if(row == 0)
				return false;
			cid = (row - 1) * width + col;	
		}
		else{
			if(row == width-1)
				return false;
			cid = (row + 1) * width + col;	
		}
	}
	return true;
}
bool move(const string& cur, string& next, int idx, int mtype){
	next = cur;
	for(int i = 0; i < width * width; i++){
		if(cur[i] - 'a' == idx){
			int cid;
			if( !getcid(i, idx, mtype, cid) )
				return false;
			int val = (cur[cid] - 'a');
			if(val != 0 && val != idx)
				return false;
			next[i] = 'a';
		}
	}
	for(int i = 0; i < width * width; i++){
		if(cur[i] - 'a' == idx){
			int cid = -1;
			getcid(i, idx, mtype, cid);
			next[cid] = cur[i];
		}
	}
	return true;
}

void printit(const string& cur){
	for(int i = 0; i < width * width; i++){
		cout << cur[i];
		if(i % width == width - 1)
			cout << endl;
	}
	cout << "-----------\n";
}

int main(){
	yccc;		
	string init = ""; 
	bool badinput = false;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < width; j++){
			int x;
			cin >> x;
			init += char('a' + x);
			n = max(n, x);
			if(x == 1 && i != 2)
				badinput = true;
			if(x == 1)
				cnt1++;
		}
	}
	if(badinput){
		cout << "-1\n";
		return 0;
	}
	for(int i = 0; i < width; i++){
		for(int j = 0; j < width; j++){
			int idx = (init[i*width + j] - 'a');
			int id = i * width + j;
			if( type[idx] == 0 ){
				for(int did = 0; did < 4; did++){
					int ni = i + di[did][0], nj = j + di[did][1];
					if (ni >= 0 && ni < width && nj >= 0 && nj < width){
						int uid = ni*width + nj;
						if(init[uid] == init[id]){
							type[idx] = 1 + (did&1);
							break;
						}
					}
				}
			}
		}
	}
	/*
	for(int i = 1; i <= n; i++){
		cout << i << ": " << type[i] << endl;
	}
	*/

	queue<string> mQ[2];
	unordered_set<string> vis;
	bool sol = false;
	int step = 0;
	vis.emplace(init);
	mQ[0].emplace(init);
	string next, cur;
	if( Validit(init) ){
		sol = true;
	}
	while(!sol && step+1 <= 10 - cnt1 && mQ[0].size()){
		step++;
//		cout << "step: " << step << endl;
		while(mQ[0].size() && !sol){
			cur = mQ[0].front(); mQ[0].pop();
			/*
			cout << "front: \n";
			printit(cur);*/
			for(int idx = 1; idx <= n && !sol; idx++){
				for(int mtype  = 0; mtype <= 1 && !sol; mtype++){
					if ( move(cur, next, idx, mtype) ){
//						cout << "gen " << next << endl;
						if( vis.find(next) == vis.end() ){ 
							sol = Validit(next);

							vis.emplace(next);
							mQ[1].emplace(next);
						}
					}
				}
			}
		}
		swap(mQ[0], mQ[1]);
	}
	if(sol){
		cout << step + cnt1 << "\n";
	}
	else{
		cout << "-1\n";
	}


	return 0;
}

