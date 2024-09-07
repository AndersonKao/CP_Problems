// persistent segment tree
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

const int maxn = 200001;
ll arr[maxn];

struct node{
	int L, R;
	node* lc, *rc;
	ll sum;
	node(int L, int R, node*lc = nullptr, node *rc = nullptr, ll sum = 0):L(L), R(R), lc(lc), rc(rc), sum(sum){

	}
};

int n, q;
vec<node *> trees;
node* build(int L, int R){
	if(R < L)
		return nullptr;
	node* cur = new node(L, R);
	if(L == R){
		cur->sum = arr[L];	
	}
	else{
		int M = (L+R)>>1;
		cur->lc = build(L, M);
		cur->rc = build(M+1, R);
		cur->sum = cur->lc->sum + cur->rc->sum;
	}
	return cur;
}
void dfs(node* cur){
	if(cur == nullptr)
		return;
	cout << cur->L << ", " << cur->R << ", " << cur->sum << endl;
	dfs(cur->lc);
	dfs(cur->rc);
}

void modify(node* cur, int a, ll x){
	if(cur->L == cur->R && cur->L == a){
		cur->sum = x;
		return;
	}

	int M = (cur->L + cur->R) >> 1;
	if(a <= M){
		node* lchild = new node(cur->lc->L, cur->lc->R, cur->lc->lc, cur->lc->rc);
		cur->lc = lchild;
		modify(cur->lc, a, x);
	}
	else{
		node* rchild = new node(cur->rc->L, cur->rc->R, cur->rc->lc, cur->rc->rc);
		cur->rc = rchild;
		modify(cur->rc, a, x);
	}
	cur->sum = cur->lc->sum + cur->rc->sum;
}

ll query(node* cur, int a, int b){
	if(cur == nullptr) return 0;
	if(cur->R < a || b < cur->L){
		return 0;
	}
	if(a <= cur->L && cur->R <= b){
		return cur->sum;
	}
	return query(cur->lc, a, b) + query(cur->rc, a, b);
}

int main(){
//	yccc;		
	cin >> n >> q;
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	trees.eb(build(0, n-1));

	//dfs(trees[0]);
	while(q--){
		int op, k;
		cin >> op >> k;
		k--;
		if(op == 1){
			int a; ll x;
			cin >> a >> x;
			a--;
			modify(trees[k], a, x);	
		}
		if(op == 2){
			int a, b;
			cin >> a >> b;
			a--; b--;
			cout << query(trees[k], a, b) << endl;
		}
		if(op == 3){
			node* nnode = new node(0, n-1, trees[k]->lc, trees[k]->rc, trees[k]->sum);
			trees.eb(nnode);
		}
	}


	return 0;
}

