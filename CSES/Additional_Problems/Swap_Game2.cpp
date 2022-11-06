// target for meowmeowOJ
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

const ll Prime = 0xdefaced;

struct VectorHash {
    size_t operator()(const std::vector<int>& v) const {
        std::hash<int> hasher;
        size_t seed = 0;
        for (const int& i : v) {
            seed ^= hasher(i) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        return seed;
    }
};

const int di[4][2] = {
	{0, 1},
	{1, 0},
	{0, -1},
	{-1, 0}
};

bool valid(int val){
	int res = val;
	for ( int i = 9; i >= 1; i--){
		if(res % 10 != i)
			return false;
		res /= 10;
	}
	return true;
}
int power[9];

int move(int val, int r, int c, int ri, int ci){
	int idx = 8 - (r * 3 + c), ridx = 8 - (ri * 3 + ci);
	int lval = (val / power[idx]) % 10;
	int rval = (val / power[ridx]) % 10;
	return val - lval * power[idx] - rval * power[ridx] + lval * power[ridx] + rval * power[idx];
}
int main(){
	yccc;		
	power[0] = 1;	
	for(int i = 1; i < 9; i++)
		power[i] = power[i-1] * 10;
	int init = 0;
	REP(i, 9){
		int input;
		cin >> input;
		init *= 10;
		init += input;
	}
	if(valid(init)){
		cout << 0 << endl;
		return 0;
	}

	queue<int> mQ[2];
	mQ[0].emplace(init);
	unordered_set<int> mS;
	mS.emplace(init);
	bool found = false;

	int step = 0;
	while(found == false && mQ[0].size()){
		step++;
//		cout << "step: " << step << "       --------------\n";
		while(found == false && mQ[0].size()){
			
			int cur = mQ[0].front();
//			cout << "grep: " << cur << endl;
			mQ[0].pop();
			REP(i, 3){
				REP(j, 3){
					for(int d = 0; d < 4; d++){
						int si = i + di[d][0], sj = j + di[d][1];
						if(si < 0 || si >= 3 || sj < 0 || sj >= 3)
							continue;
						int cop = move(cur, i, j, si, sj);
						if(mS.find(cop) == mS.end()){
							if(valid(cop)){
								found = true;
								break;
							}
							mS.emplace(cop);
							mQ[1].emplace(cop);
						}
					}
					if(found)
						break;
				}
				if(found)
					break;
			}
		}

		swap(mQ[0], mQ[1]);
	}
	cout << step << endl;
	return 0;

}

