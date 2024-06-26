#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace __gnu_pbds;
using namespace std;

#define eb emplace_back
#define F first
#define S second
#define mp make_pair
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;
struct node {
	bool ans; // anyone don't have
    int val; // (key, val)
    int pri, sz; //  priority, size
    node *l, *r;

    node () { }
    node (int val) : val(val), pri(rand()), l(nullptr), r(nullptr), sz(1){
		ans = val ? false : true;
	} 
    void push(){
    }
    void pull(){
		sz = 1;
		ans = val ? false : true;
//		cout << "\npulling " << val << endl;
//		debug(ans);
		if(l){
//			cout << "has leftans = " << l->ans << " lsz= " << l->sz <<endl;
			sz += l->sz;
			ans = ans || l->ans;
		}
		if(r){
//			cout << "has rightans= " << r->ans << " rsz= " << r->sz <<endl;
			sz += r->sz;
			ans = ans || r->ans;
		}
//		cout << "result " << ans << endl;
    }
};

int sz(node * p){
    return p ? p->sz : 0;
}

int size(node * p){
    return p ? p->sz : 0;
}

void push(node * p){
    if(p){
        p->push();
    }
}

void pull(node * p){
	if(p) p->pull();
}

node * merge (node * a, node * b) {
    if (!a || !b)  return a ? a : b;
    if (a->pri < b->pri){
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
// split tree into size(l) = k, size(r) = size(rt) - k.
// all keys in l <= all keys in r.
void split_by_size(node * rt, node * &a, node * &b, int k){
    push(rt);
    if (!rt) 
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


void erase_by_pos(node*& rt, int pos){
    node* a, *b, *c;
	split_by_size(rt, a, b, pos-1);
	split_by_size(b, b, c, 1);
	rt = merge(a, c);
	delete b;
}

node * find_by_order(node * root, int k){
    if (k <= size(root->l))
        return find_by_order(root->l, k);
    if (k == size(root->l) + 1)
        return root;
    return find_by_order(root->l, k - size(root->l) + 1);
}
int query(node* rt){
	if(rt->ans){
		if(rt->l && rt->l->ans){
			return query(rt->l);
		}
		else if(rt->val == 0){
			return sz(rt->l) + 1;
		}
		else if(rt->r && rt->r->ans){
			return sz(rt->l) + 1 + query(rt->r);
		}
	}
	return sz(rt) + 1;
}

void heapify(node * t)
{
    if (!t) return;
    node * max = t;
    if (t->l != nullptr && t->l->pri > max->pri)
        max = t->l;
    if (t->r != nullptr && t->r->pri > max->pri)
        max = t->r;
    if (max != t) {
        swap (t->pri, max->pri);
        heapify (max);
    }
}

// Construct a treap on values {a[0], a[1], ..., a[n - 1]} in O(n)
node * build (int n) {
    if (n == 0) return nullptr;
    int mid = n / 2;
    node * t = new node (0);
    t->l = build (mid);
    t->r = build (n - mid - 1);
    heapify (t);
    pull(t);
    return t;
}
int initpos[200001];
int ans[200001];
int idx = 0;
void inorder(node* rt){
	if(rt == nullptr) return;
	inorder(rt->l);
	idx++;
	if(rt->val)
		ans[rt->val] = idx - initpos[rt->val] + 1;
	inorder(rt->r);
}
void print(node*rt){
	if(rt == nullptr) return;
	if(rt->l){
		cout << "go left\n";
		print(rt->l);
	}
	cout << "(" << rt->val << ", " << rt->ans << "," << sz(rt) << ")\n";
	if(rt->r){
		cout << "go right\n";
		print(rt->r);
	}
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
	int n, m;
	cin >> n >> m;

	node* mT = build(n);
	for(int i = 1; i <= m; i++){
		int pos; cin >> pos;
		initpos[i] = pos;
		node* L, *M, *R, *todel;
		node* nnode = new node(i);
		split_by_size(mT, L, R, pos-1);

		int fpos = query(R);
		/*
		cout << "R: \n" ;
		print(R);
		*/
////////////////		
//		debug(fpos + pos - 1);
		if(fpos + pos - 1 > n){
			split_by_size(R, R, todel, sz(R) - 1);
			ans[todel->val] = n - initpos[todel->val] + 1;
//			cout << "todel " << todel->val << endl;
			mT = merge(L, merge(nnode, R));
		}
		else{
			split_by_size(R, M, R, fpos-1); 	
			split_by_size(R, todel, R, 1);
			mT = merge(L, merge(nnode, merge(M, R)));
		}
		/*
		cout << "mT: \n";
		print(mT);
		cout << endl;*/
	}
	inorder(mT);

	for(int i = 1; i <= m; i++){
		cout << ans[i] << (i == m ? "" : " ");
	}
}
