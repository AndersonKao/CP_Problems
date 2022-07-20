#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
using ll = long long;
#define eb emplace_back
#define F first
#define S second
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")\n";
#define REP(i, n) for(int i = 0; i < (int)n; i++)
int N;
struct Node{
	Node* l, *r;
	Node* pa;
	int val;
	int id = 0;
	Node(){
		l = r = pa = nullptr;
		val =0;
	}	
	Node(int x){
		l = r = pa = nullptr;
		val = x;
	}	
};
void delTree(Node* root){
	if(root->l)
		delTree(root->l);
	if(root->r)
		delTree(root->r);	
	delete root;
}
void inorderTree(Node* rt, int h){
	if(rt->l){
		inorderTree(rt->l, h+1);
	}
	cout << rt->id << " ";
	if(rt->r){
		inorderTree(rt->r, h + 1);	
	}
}
void preorderTree(Node* rt, int h){
	cout << rt->id << " ";
	if(rt->l){
		preorderTree(rt->l, h+1);
	}
	if(rt->r){
		preorderTree(rt->r, h + 1);	
	}
}
Node* findRightMost(Node*rt){
	if(rt->r)
		return findRightMost(rt->r);
	return rt;
}
int cnt = 0;
void build(Node* rt, string& str, int idx){
	if(idx == str.length())
		return;
	if(str[idx] == '0'){
		if(rt->l == nullptr){
			rt->l = new Node();
			rt->l->pa = rt;	
			rt->l->id = cnt++;
		}
		build(rt->l, str, idx+1);
	}
	else{
		if(rt->r == nullptr){
			rt->r = new Node();
			rt->r->pa = rt;	
			rt->r->id = cnt++;
		}
		build(rt->r, str, idx+1);
	}
}
vector<int> hmax(50), hmin(50);
vector<pair<Node*, int>> BFS(Node* rt){
	queue<pair<Node*, int>> q;	
	q.emplace(rt, 0);
	vector<pair<Node*, int>> V;
	while(q.empty() == false){
		V.push_back(q.front());
		Node* res = q.front().F;
		int h = q.front().S;
		q.pop();
		if(res->l){
			q.emplace(res->l, h+1);
		}
		if(res->r){
			q.emplace(res->r, h+1);
		}
	}
	return V;
}
int ans = 0;
void solve(vector<pair<Node*, int>>& V, int idx){
	if(idx == V.size()){
		ans++;
#ifdef Dans
		cout << "assignment: ";
		for(int i = 0; i < V.size(); i++){
			cout << V[i].first->id << " = " << V[i].first->val << ", ";
		}
		cout << endl;
#endif
		return ;
	}	
	Node*rt = V[idx].F;
	int h = V[idx].S;
	int curval = rt->val;
	int limit = curval / 2;
#ifdef Dpre
	cout << "id " << rt->id << " given " << rt->val << endl;
	debug(hmax[h]);	
	debug(hmin[h]);	
#endif
/*
	if(curval < hmax[h] || ((h > 0) && curval > hmin[h-1])){
//		cout << "invalid\n";
		return;
	}
*/
	if(rt->l != nullptr && rt->r != nullptr){
#ifdef Dpre
		cout << "go for " << rt->id << endl;
		debug(hmax[h+1]);	
		debug(hmin[h+1]);	
#endif
		
		int ri = min(limit, hmin[h]);
		for(int i = max(1, hmax[h+1]); i <= ri; i++){
			int Lval = i;
			int Rval = curval - i;
			if(Lval > Rval){
				break;
			}
			if(Rval > hmin[h]){
#ifdef Dcut
				cout << "Rval error\n";
#endif
				continue;
			}
			if(rt->l->l != nullptr && rt->l->r != nullptr && Lval == 1){
#ifdef Dcut
				cout << "Leaf error\n";
#endif
				continue;
			}
			if(rt->r->l != nullptr && rt->r->r != nullptr && Rval == 1){
#ifdef Dcut
				cout << "Leaf error\n";
#endif
				continue;
			}
			int ori_hmax = hmax[h+1];
			int ori_hmin = hmin[h+1];
			hmax[h+1] = max(hmax[h+1], max(Lval, Rval));
			hmin[h+1] = min(hmin[h+1], min(Lval, Rval));
			rt->l->val = Lval;
			rt->r->val = Rval;
			solve(V, idx+1);
			hmax[h+1] = ori_hmax;
			hmin[h+1] = ori_hmin;
		}
	}
	else {
		solve(V, idx+1);
	}
}
int main(){
	int caseN = 1;
	while(cin >> N){
		if(N == 0)
			break;
		ans = cnt = 0;
		fill(hmax.begin(), hmax.end(), 0);
		fill(hmin.begin(), hmin.end(), numeric_limits<int>::max());
		Node* root = new Node(100);
		root->id = cnt++;
		hmax[0] = hmin[0] = 100;
		REP(i, N){
			string str;
			cin >> str;
			build(root, str, 0);
		}
/*
		inorderTree(root, 0);
		cout << endl;	
		preorderTree(root, 0);
		cout << endl;	
*/
		//Node* rightMost	= findRightMost(root);
		vector<pair<Node*, int>> V = BFS(root);			
		solve(V, 0);	
		cout << "Case " << caseN++ << ": " << ans << endl;
		delTree(root);
	}	
	return 0;
}
