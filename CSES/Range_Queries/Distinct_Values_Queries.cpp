// AC
// USE BIT and lPos, need review
// WA
// idiot, read the problem and check int I/O again!
#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define REP(i,n) for(int i = 0; i < n; i++)
#define eb emplace_back
#define al(a) a.begin(), a.end()
using ll = long long;
using pii = pair<int, int>;
using piii = tuple<int, int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;

vec<int> data;
vec<int> value;
vec<piii> queries;
vec<int> ANS;
vec<int> lPos; // lastest distinct value position.
vector<int> BIT; // If a pos has the lastest distinct value, it's 1, otherwise, 0.

int qry(int i){
	int idx = i;
	int ans = 0;
	while(idx >= 1){
		ans += BIT[idx];	
		idx -= idx & (-idx);
	}
	return ans;
}
void upt(int i, int val){
	int idx = i;
	while(idx < BIT.size()){
		BIT[idx] += val;	
		idx += idx & (-idx);
	}
}

bool cmp(piii&a, piii&b){
	if(get<1>(a) == get<1>(b))
		return get<0>(a) < get<0>(b);
	return get<1>(a) < get<1>(b);
}
int main(){
	int n, q;
	cin >> n >> q;
	data.resize(n);
	BIT.resize(n+1);
	ANS.resize(q);
	REP(i, n){
		cin >> data[i];	
		value.eb(data[i]);
	}	
	sort(al(value));
	value.resize(distance(value.begin(), unique(al(value))));
	lPos.resize(value.size(), -1);
	REP(i, n){
		data[i] = distance(value.begin(), lower_bound(al(value), data[i]));
	}	
	int a, b;
	REP(i, q){
		cin >> a >> b;
		a--, b--;
		queries.eb(a, b, i);
	}	
	sort(al(queries), cmp);
/*
	REP(i, queries.size())
		cout << get<0>(queries[i]) << ", " << 	get<1>(queries[i]) << endl;
	cout << endl;
*/
	size_t qid = 0;
	REP(i, n){
		int now = data[i];
		if(lPos[now] != -1) upt(lPos[now] + 1, -1);
		lPos[now] = i;
		upt(i + 1, 1);
		for(; qid < queries.size(); qid++) {
			int l = get<0>(queries[qid]), r = get<1>(queries[qid]), aid =get<2>(queries[qid]);
			if(r != i)
				break;
			ANS[aid] = qry(r + 1) - qry(l);
		}
	}
	for(auto &ans: ANS){
		cout << ans << "\n";
	}
	
	return 0;
}
