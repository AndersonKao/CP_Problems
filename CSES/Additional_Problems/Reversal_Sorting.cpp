#include <bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>;
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, treeorder_statistics_node_update>;
*/
#define REP0(i, n) for (int i = 0; i < n; i++)
#define REP(i, a, b) for(int i = a; i <= b; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define ln '\n'
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;
 
template<typename T>
using vec = vector<T>;
 
struct node {
    int val; // (key, val)
    int ans; // minans
    int pri;int sz; //  priority, size
    node *l;node *r;
    int rev; // lazy tag
 
    node () { }
    node (int val) : val(val), ans(val), pri(rand()), sz(1), l(nullptr), r(nullptr), rev(0) {
	} 
    void push(){
        if(rev){
            swap(l, r);
            if(l) l->rev ^= 1;
            if(r) r->rev ^= 1;
            rev ^= 1;
        }
    }
    void pull(){
        ans = val;
		sz = 1;
		if(l){
			ans = min(ans, l->ans);
			sz += l->sz;
		}
		if(r){
			ans = min(ans, r->ans);
			sz += r->sz;
		}
    }
};
 
node * root = nullptr;
 
 
void print2(node *u){
	if(u->rev){
		if(u->r){
			print2(u->r);
		}
		cout << u->val << " ";
		if(u->l){
			print2(u->l);
		}
		return;
	}
	if(u->l){
		print2(u->l);
	}
	cout << u->val << " ";
	if(u->r){
		print2(u->r);
	}
}
 
void print(node* u){
	print2(u);
	cout << endl;
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
    p->pull();
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
    if (!rt){
        a = b = nullptr;
		return;
	}
    push(rt);
    if(k >= size(rt->l) + 1){
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
 
int traverse(node* u, int val){
//	debug(u->val);
	push(u);
	int ls = (u->l ? u->l->sz : 0) + 1;
	if(u->val == val){
		return ls;
	}
	else if(u->l && u->l->ans == val){
		return traverse(u->l, val);	
	}
	else if(u->r && u->r->ans == val){
		return ls + traverse(u->r, val);
	}
	return -1;
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
node * build (int * val, int n) {
    if (n == 0) return nullptr;
    int mid = n / 2;
    node * t = new node(val[mid]);
//	cout << "create node " << mid << ", " << key[mid] << ", " << val[mid] << endl;
    t->l = build (val, mid);
    t->r = build (val + mid + 1, n - mid - 1);
    heapify (t);
    pull(t);
    return t;
}
 
int arr[200000];
 
int main(){
	yccc;		
	srand(time(NULL));
	int n;
	cin >> n;
	for(int i = 0; i < n; i++){
		int val;
		cin >> val;
		root = merge(root, new node(val));
		//cout << arr[i] << " ";
	}
	//cout << endl;
//	root = build(arr, n);
	//print(root);
	int cnt = 0;
	vec<pair<int, int>> ans;
	node *a, *b, *c;
	for(int val = 1; val <= n; val++){
		split_by_size(root, a, b, val - 1);
		int order = traverse(b, val);
		if(order > 1){
			split_by_size(b, b, c, order);
			b->rev ^= 1;
			b = merge(b, c);
			cnt++;	
			ans.eb(val, val + order - 1);
		}
		root = merge(a, b);
	}
	cout << cnt << endl;
	for(auto &p: ans){
		cout << p.first << " " << p.second << endl;
	}
 
	return 0;
}

