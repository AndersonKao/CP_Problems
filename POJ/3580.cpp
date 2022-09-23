#include <iostream>
#include <algorithm>
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
#define ll long long
#define nullptr 0
int seq[100000];
struct node{
	ll val, add, min_ans;
	int pri, rev, sz;
	node* l, *r;
	node(ll val): val(val), add(0), min_ans(val), pri(rand()), rev(0), sz(1), l(nullptr), r(nullptr){}
	void push(){
		if(rev){
			swap(l, r);
		}
		if(l){
			l->add += add;
			l->val += add;
			l->min_ans += add;
			if(rev) l->rev ^= 1;
		}
		if(r){
			r->add += add;
			r->val += add;
			r->min_ans += add;
			if(rev) r->rev ^= 1;
		}
		if(rev)
			rev ^= 1;
		add = 0;
	}
	void pull(){
		min_ans = val;
		sz = 1;
		if(l){
			min_ans = min(min_ans, l->min_ans);
			sz += l->sz;
		}
		if(r){
			min_ans = min(min_ans, r->min_ans);
			sz += r->sz;
		}
	}
};
void heapify(node* t){
	if(!t) return;
	node* mt = t;
	if(t->l && t->l->pri > mt->pri)
		mt = t->l;
	if(t->r && t->r->pri > mt->pri)
		mt = t->r;
	if(mt != t){
		swap(t->pri, mt->pri);
		heapify(mt);
	}
}
void Print(node* rt){
	if(rt){
		Print(rt->l);
		cout << rt->val << " ";
		Print(rt->r);
	}
}
int size(node* p){
	return (p ? p->sz : 0);
}

void push(node* p){
	if(p)
		p->push();	
}
void pull(node* p){
	if(p)
		p->pull();	
}
 

node* merge(node* a, node* b){
	if(!a || !b){
		return (a ? a : b);	
	}
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

void split_by_size(node* rt, node* & a, node* & b, int k){
	push(rt);
	if(!rt)
		a = b = nullptr;
	else if(k >= size(rt->l) + 1){
		a = rt;
		int nk = k - (size(rt->l) + 1);
		split_by_size(rt->r, a->r, b, nk);
	}
	else{
		b = rt;
		split_by_size(rt->l, a, b->l, k);
	}
	pull(rt);
}

void insert(node* & rt, node* p, int pos){
	if(!rt){
		rt = p;
	}
	else if(p->pri <= rt->pri){
		split_by_size(rt, p->l, p->r, pos);
		rt = p;
		pull(rt);
	}
	else{
		push(rt);
		if (pos <= size(rt->l))
			insert(rt->l, p, pos);
		else
			insert(rt->r, p, pos - (size(rt->l) + 1));
		pull(rt);
	}
}

/* insert after $pos$ items. */
void Insert(node* &rt, int pos, ll val){
	node* newp = new node(val);	
	node*a, *b;
//	split_by_size(rt, a, b, pos);
//	rt = merge(a, merge(newp, b));
	insert(rt, newp, pos);
}

void Delete(node* & rt, int pos){
	node* a, *b, *c;
	split_by_size(rt, a, b, pos-1);
	split_by_size(b, b, c, 1);
	rt = merge(a, c);
	delete b;
}

ll Query(node* & rt, int l, int r){
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, (r - l + 1));
	ll ans = b->min_ans; 
	rt = merge(a, merge(b, c));
	return ans;
}

void Reverse(node* & rt, int l, int r){
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, (r - l + 1));
	b->rev ^= 1;
	rt = merge(a, merge(b, c));
}

void Revolve(node* & rt, int l, int r, int T){
	int len = (r-l+1);
	T %= len;
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, len);

	node* b1, *b2;
	split_by_size(b, b1, b2, len - T);
	rt = merge(a, merge( merge(b2, b1), c) );
}

void Modify(node* & rt, int l, int r, ll val){
	node* a, *b, *c;
	split_by_size(rt, a, b, l-1);
	split_by_size(b, b, c, (r - l + 1));

	b->add += val;
	b->val += val;
	b->min_ans += val;
	rt = merge(a, merge(b, c));
}

node* build(int* a, int n){
	if(n == 0) return nullptr;
	int mid = n >> 1;
	node* t = new node(a[mid]);
	t->l = build(a, mid);
	t->r = build(a + mid + 1, n - mid - 1);
	heapify(t);
	pull(t);
	return t;
}


void clear(node* rt){
	if(rt){
		clear(rt->l);
		clear(rt->r);
		delete(rt);
	}
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;	
	node* mT = nullptr;
	REP(i, n){
		cin >> seq[i];
	}
	mT = build(seq, n);
	int m;
	cin >> m;
	/*
	REP(i, 10){
		int pos = rand() % n;
		ll val = rand() % 900417;
		cout << "Insert " << pos << ", " << val << endl;
		Insert(mT, pos, val);
		cout << "mT: ";
		Print(mT);
		cout << endl;
	}
	*/
	REP(i, m){
		string op;
		int pos, l, r, T;
		ll val;
		cin >> op;
#ifdef Dop
		debug(i);
		cout << op << endl;
#endif
		if (op == "ADD"){
			cin >> l >> r >> val;
			Modify(mT, l, r, val);
		}
		else if (op == "REVERSE"){
			cin >> l >> r;
			Reverse(mT, l, r);
		}
		else if (op == "REVOLVE"){
			cin >> l >> r >> T;
			Revolve(mT, l, r, T);
		}
		else if (op == "INSERT"){
			cin >> pos >> val;	
			Insert(mT, pos, val);
			/*
			cout << "mT: ";
			Print(mT);
			cout << endl;
			*/
		}
		else if (op == "DELETE"){
			cin >> pos;
			Delete(mT, pos);
		}
		else if (op == "MIN"){
			cin >> l >> r;
			cout << Query(mT, l, r) << "\n";
		}
	}
	clear(mT);

	return 0;
}

