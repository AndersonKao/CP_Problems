#include <bits/stdc++.h>
using namespace std;
#define al(a) a.begin(), a.end()
#define REP(i, n) for (int i = 0; i < n; i++)
#define REP1(i, n) for (int i = 1; i <= n; i++)

template <typename T>
using vec = vector<T>;
using ll = long long;

template <typename T>
struct Fenwick{
	vector<T> BIT;
	int n;
	Fenwick(){
		BIT.clear();
		n = 0;
	}
	Fenwick(int n){
		this->n = n;
		BIT.resize(this->n, 0);
	}
	Fenwick(vec<T> & data){
		n = data.size() + 1;
		BIT.resize(n);
		REP1(i, n)
			this->modify(i, data[i]);
	}
	void Build(int n){
		this->n = n;
		BIT.resize(this->n, 0);
	}
	void Build(vec<T> & data){
		n = data.size() + 1;
		BIT.resize(n);
		REP1(i, n)
			this->modify(i, data[i]);
	}
	void modify(int i, T val){
		while(i <= n){
			BIT[i] += val;
			i += (i & (-i));
		}
	}
	void rangeModify(int l,int r, T val){
		this->modify(l, val);
		this->modify(r + 1, val);
	}
	T query(int i){
		T ans = 0;
		while (i > 0){
			ans += BIT[i];
			i -= (i & (-i));
		}
		return ans;
	}
	T rangeQuery(int l, int r){
		return query(r) - query(l - 1);
	}
};

struct Polynomial_Queries{
	vec<Fenwick<ll>> BITs;
	int n;
	// 0 "idx", 1 constant, 2 doubled "idx^2"
	// 3 doubled "idx", 4 doubled constant, 5 origin array
	Polynomial_Queries(){
		BITs.resize(6);
	}
	void Build(vec<ll> & data){
		n = data.size() + 1;
		REP(i, 5)
			BITs[i].Build(n);
		BITs[5] = Fenwick<ll>(data);
	}
	void RangeModify(int l, int r, ll val){
		BITs[0].rangeModify(l, r, val);
		BITs[1].rangeModify(l, r, (1- l) * val);
		BITs[2].rangeModify(l, r, 2);
		BITs[3].rangeModify(l, r, 1 - 2 * l);
		BITs[4].rangeModify(l, r, l * l + l);
		ll len = r - l + 1;
		ll r_l = r - l;
		BITs[1].rangeModify(r + 1, n, len * val);
		BITs[4].rangeModify(r + 1, n, len * r_l);
	}
	ll Query(int idx){
		ll ans = 0;
		ans += BITs[0].query(idx) * idx;
		ans += BITs[1].query(idx);
		ll doubled = 0;
		doubled += BITs[2].query(idx) * idx * idx;
		doubled += BITs[3].query(idx) * idx;
		doubled+= BITs[4].query(idx);
		ans += doubled >> 1;
		ans += BITs[5].query(idx);
		return ans;
	}
	ll RangeQuery(int l, int r){
		return Query(r) - Query(l - 1);
	}
};
Polynomial_Queries pq;

int main(){
	int n, q;
	cin >> n >> q;
	vec<ll> data;
	data.resize(n);
	REP(i, n)
	{
		cin >> data[i];
	}
	pq.Build(data);
	int type, l, r;
	REP(i, q)
	{
		cin >> type >> l >> r;
		if(type & 1){
			pq.RangeModify(l, r, 1);
		}
		else
		{
			cout << pq.RangeQuery(l, r) << endl;
		}
	}

	return 0;
}
