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

struct node{
	ll val, ans;
	int sz;
	int rev;
	node *l, *r;
	int pri;

	node(): pri(rand()){}
	node(ll val):val(val), ans(val), sz(1), rev(0), l(nullptr), r(nullptr), pri(rand()){}
	void push(){
		if(rev){
			swap(l, r);
			if(l) l->rev ^= 1;
			if(r) r->rev ^= 1;
			rev = 0;
		}
	}
	void pull(){
		sz = 1;
		ans = val;
		if(l)
			sz += l->sz, ans += l->ans;
		if(r)
			sz += r->sz, ans += r->ans;
	}
};
int size(node* p){
	return (p ? p->sz : 0);
}
void pull(node*p){
	if(p) p->pull();
}
void push(node*p){
	if(p) p->push();
}

node* merge(node*a, node* b){
	if(!a || !b) return (a ? a : b);
	if(a->pri < b->pri){
		push(a);
		a->r = merge(a->r, b);
		pull(a);
		return a;
	}
	else{
		push(b);
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}

void split_by_size(node* rt, node* &a, node* &b, int k){
	push(rt);
	if(!rt) a = b = nullptr;	
	else if(k >= size(rt->l) + 1){
		a = rt;
		int nk = k - (size(rt->l) + 1);
		split_by_size(a->r, a->r, b, nk);
	}
	else{
		b = rt;
		split_by_size(b->l, a, b->l, k);
	}
	pull(rt);
}

void heapify(node* p){
	if(!p) return;
	node* mx = p;
	if(p->l && mx->pri > p->l->pri){
		mx = p->l;	
	}
	if(p->r && mx->pri > p->r->pri){
		mx = p->r;	
	}
	if(mx != p){
		swap(mx->pri, p->pri);
		heapify(mx);
	}
}

node* build( int* a, int n){
	if(n == 0) return nullptr;
	int m = (n >> 1);
	node* p = new node(a[m]);
	p->l = build(a, m);	
	p->r = build(a + m + 1, n - m -1);	
	heapify(p);
	pull(p);
	return p;
}
void Print(node* p){
	if(p){
		Print(p->l);
		cout << p->val << ", " << p->ans << endl;
		Print(p->r);
	}
}

int arr[200000];

int main(){
	node* rt = nullptr;
	int n, q;
	cin >> n >> q;
	REP(i, n)
		cin >> arr[i];
	rt = build(arr, n);
	while(q--){
		int op;
		int l, r;
		cin >> op >> l >> r;
		node* a, *b, *c;
		split_by_size(rt, a, b, l-1);
		split_by_size(b, b, c, r-l+1);
		if(op == 1){
			b->rev ^= 1;
		}
		else {
			cout << b->ans << endl;
		}
		rt = merge(a, merge(b, c));
	}


		
	return 0;
}

