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

struct node{
	ll sum;
	ll sum2;
	ll tag, tag2;
	ll l, r; // store[lb, rb] data; 
	bool changed;
	node* ln, *rn;
	node(int _l, int _r): l(_l), r(_r){
		sum = sum2 = tag = tag2 = 0;
		changed = false;
		ln = rn = nullptr;
	}
};
int n;

ll sum(node* np){
	ll res = 0;
	if(np->changed){
		res = np->tag2 * (np->r - np->l + 1);
	}
	else{
		res = np->sum;
	}
	res += np->tag * (np->r - np->l + 1);
	return res;
}

ll sum2(node* np){
	ll res = 0;
	if ( np->changed ){
		res = np->tag2 * (np->r + np->l) * (np->r - np->l + 1) / 2;
	}
	else{
		res = np->sum2;
	}
	res += np->tag * (np->r + np->l) * (np->r - np->l + 1) / 2;
	return res;
}

void push(node* np){
	if(!np) return;

	if(np->changed){
		np->ln->changed = np->rn->changed = true;
		np->ln->tag2 = np->rn->tag2 = np->tag2;
		np->ln->tag = np->rn->tag = 0;
	}	

	np->changed = false;
	np->ln->tag += np->tag;
	np->rn->tag += np->tag;
	np->tag = 0;
}

void pull(node* np){
	if(!np) return;

	np->sum = sum(np->ln) + sum(np->rn);
	np->sum2 = sum2(np->ln) + sum2(np->rn);
}

void Build(node* np, vec<int> & arr){
	if(np->l == np->r){
		np->sum = arr[np->l];
		np->sum2 = arr[np->l] * np->l;
		return;
	}
	int m = (np->l + np->r) >> 1;
	np->ln = new node(np->l, m);
	np->rn = new node(m+1, np->r);
	Build(np->ln, arr);
	Build(np->rn, arr);
	pull(np);
}

void add(node* np, int l, int r, ll x){
	if(l <= np->l && np->r <= r){
		np->tag += x;
		return;
	}
	if(np->r < l || np->l > r)
		return;
	push(np);
	add(np->ln, l, r, x);
	add(np->rn, l, r, x);
	pull(np);
}

void setto(node* np, int l, int r, ll x){
	if(l <= np->l && np->r <= r){
		np->tag2 = x;
		np->tag = 0;
		np->changed = true;
		return;
	}
	if(np->r < l || np->l > r)
		return;
	push(np);
	setto(np->ln, l, r, x);
	setto(np->rn, l, r, x);
	pull(np);
}

p<ll> query(node* np, int l ,int r){
	if(l <= np->l && np->r <= r){
		return mp(sum(np), sum2(np));
	}
	if(np->r < l || np->l > r)
		return mp(0, 0);
	push(np);
	p<ll> lres = query(np->ln, l, r);
	p<ll> rres = query(np->rn, l, r);
	pull(np);
	return mp(lres.F + rres.F, lres.S + rres.S);
}

int main(){
	yccc;
	int n, q;
	cin >> n >> q;	
	vec<int> arr(n+1);
	for(int i = 1; i <= n; i++)
		cin >> arr[i];
	node* mT = new node(1, n);
	Build(mT, arr);
	for(int i = 0; i < q; i++){
		int op, l, r, x;
		cin >> op >> l >> r;	
		if ( op == 1 ){
			cin >> x;
			add(mT, l, r, x);
		}
		else if ( op == 2 ){
			cin >> x;
			setto(mT, l, r, x);
		}
		else if ( op == 3 ){
			p<ll> res = query(mT, l, r);
			if(res.F == 0){
				if(res.S == 0){
					cout << "Yes\n";
				}
				else{
					cout << "No\n";
				}
			}
			else{
				if(res.S % res.F == 0){
					ll k = res.S / res.F;
					if(l <= k && k <= r){
						cout << "Yes\n";
					}
					else{
						cout << "No\n";
					}
				}
				else{
					cout << "No\n";
				}
			}
		}
	}
	return 0;
}

