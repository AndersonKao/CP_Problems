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
	char ch;
	int sz;
	int pri;
	node *l, *r;
	node(char ch): ch(ch), sz(1), pri(rand()), l(nullptr), r(nullptr){}
	void pull(){
		sz = 1;
		if(l) sz += l->sz;
		if(r) sz += r->sz;
	}
};
int size(node*p){
	return (p ? p->sz : 0);
}
void pull(node *p ){
	if(p) p->pull();
}
node* merge(node*a, node*b){
	if(!a || !b) return (a ? a : b);	
	if(a->pri < b->pri){
		a->r = merge(a->r, b);
		pull(a);
		return a;
	}
	else {
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}

void split_by_size(node* rt, node*&a, node* &b, int k){
	if(!rt) a = b = nullptr;
	else if(k >= size(rt->l) + 1){
		a = rt;
		split_by_size(a->r, a->r, b, k - (size(rt->l) + 1));
		pull(a);
	}
	else{
		b = rt;
		split_by_size(b->l, a, b->l, k);
		pull(b);
	}
}
void heapify(node*p){
	if(!p) return;
	node *mx = p;
	if(p->l && mx->pri > p->l->pri)
		mx = p->l;
	if(p->r && mx->pri > p->r->pri)
		mx = p->r;
	if(mx != p){
		swap(mx->pri, p->pri);
		heapify(mx);
	}
}
node* build(char* str, int n){
	if(n == 0) return nullptr;
	int m = (n >> 1);
	node* p = new node(str[m]);
	p->l = build(str, m);
	p->r = build(str + m + 1, n - m - 1);
	pull(p);
	return p;
}
void Print(node*p){
	if(p){
		Print(p->l);
		cout << p->ch;
		Print(p->r);
	}
}
char str[200000];
int main(){
	int n, m;
	cin >> n >> m;
	scanf("%s", str);
	node* rt = build(str, n);
	REP(i, m){
		int l, r;
		scanf("%d %d", &l, &r);
		node*a, *b, *c;
		split_by_size(rt, a, b, l-1);
		split_by_size(b, b, c, r-l+1);
		rt = merge(a, merge(c, b));
	}
	Print(rt);
	printf("\n");	
	return 0;
}

