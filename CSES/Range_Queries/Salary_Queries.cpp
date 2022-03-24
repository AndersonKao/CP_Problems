// AC 
// 2022-03-22 10:10:46
// selfWA
// do not accidentally discretize "index".
// selfRE
// For how many times you do write an 'int n' in your segment Tree 'Build' Function idiot.

#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define REP(i, n) for(int i = 0; i < n; i++)
#define al(a) a.begin(), a.end()
#define eb emplace_back

using ll = long long;
using pii = pair<int, int>;
using que = tuple<char, int, int>;
template<typename T> using vec = vector<T>;
vector<int> data;
vector<que> queries;
vector<int> value;

inline int LC(int idx){
	return idx * 2 + 1;
}
inline int RC(int idx){
	return idx * 2 + 2;
}
vec<int> cnt;

template<typename T>
struct segT{
	vec<T> seq;
	int n;
	
	void Build(vec<T>& data){
		n = data.size();
		seq.resize(4*n, 0);	
		build(0, n - 1, 0, data);
	}
	void build(int l, int r, int idx, vec<T>& data){
		if(l == r){
			seq[idx] = data[l];
			return;
		}
		int M = (l + r) >> 1;
		build(l, M, LC(idx), data);
		build(M+1, r, RC(idx), data);
		seq[idx] = seq[LC(idx)] + seq[RC(idx)];
	}
	int Query(int l, int r){
		return query(l, r, 0, n - 1, 0); 
	}
	int query(int l, int r, int L, int R, int idx){
		if(l <= L && r >= R){
			
			return seq[idx];
		}
		if(l > R || r < L)
			return 0;
		int M = (L + R) >> 1;
		return query(l, r, L, M, LC(idx)) + query(l, r, M+1, R, RC(idx)) ; 
	}
	void Modify(int pos, int add){
		modify(pos, 0, n-1, 0, add);
	}
	void modify(int pos, int L, int R, int idx, int add){
		if(L == pos && R == pos){
			seq[idx] += add;
			return ;
		}
		int M = (L + R) >> 1;
		if(pos <= M)
			modify(pos, L, M, LC(idx), add);	
		else if(pos > M)
			modify(pos, M+1, R, RC(idx), add);
		seq[idx] = seq[LC(idx)] + seq[RC(idx)];
	}
};
segT<int> mT;
int main(){
	int n, q;
	cin >> n >> q;
	data.resize(n);
	queries.resize(q);
	REP(i, n){
		cin >> data[i];
		value.eb(--data[i]);
	}
	REP(i, q){
		cin >> get<0>(queries[i]) >> get<1>(queries[i])>> get<2>(queries[i]);
		value.eb(--get<1>(queries[i])); 
		value.eb(--get<2>(queries[i]));
	}
	sort(al(value));
	value.resize(distance(value.begin(), unique(al(value))));
	cnt.resize(value.size(), 0);
	REP(i, n){
		data[i] = distance(value.begin(), lower_bound(al(value), data[i]));
		cnt[data[i]]++;
	}
		
	REP(i, q){
		if(get<0>(queries[i]) == '?')
			get<1>(queries[i]) = distance(value.begin(), lower_bound(al(value), get<1>(queries[i]))); 
	    get<2>(queries[i]) = distance(value.begin(), lower_bound(al(value), get<2>(queries[i]))); 
	}
	mT.Build(cnt);
	REP(i, q){
		if(get<0>(queries[i]) == '!'){
			mT.Modify(data[get<1>(queries[i])], -1);
			data[get<1>(queries[i])] = get<2>(queries[i]);			
			mT.Modify(data[get<1>(queries[i])], 1);
		}
		else if(get<0>(queries[i]) == '?'){
			cout  << mT.Query(get<1>(queries[i]), get<2>(queries[i])) << endl;
		}
	}


	return 0;
}
