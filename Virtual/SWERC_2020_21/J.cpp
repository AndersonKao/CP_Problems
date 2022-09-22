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

struct segT{
	int n;
	vector<int> seq;
	void Build(vector<int> &arr){
		this->n = arr.size();
		seq.resize(n, 0);	
		build(0, n-1, 0, arr);
	}
	void build(int l, int r, int idx, vector<int>& arr){
		int m = (l+r) >> 1;
		build(l, m, LC(idx), arr);
		build(m+1, r, RC(idx), arr);
	}

}

int main(){
	int n;

		
	return 0;
}

