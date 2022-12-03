#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

struct Node {
	char ch;
	int pri, size;
	Node *l, *r;

	Node() {}
	Node(char ch) : ch(ch), pri(rand()) {
		l = r = nullptr;
	}
};

void pull(Node* t) {
	assert(t != 0);
	t->size = 1 + (t->l ? t->l->size : 0) + (t->r ? t->r->size : 0);
}

int size(Node* t) {
	return t ? t->size : 0;
}

void split(Node* root, Node*& a, Node*& b, int k) {
	if (!root) {
		a = b = nullptr;
		return;
	} else if (k >= size(root->l) + 1) {
		a = root;
		int nsize = k - size(root->l) - 1;

		split(root->r, a->r, b, nsize);
	} else {
		b = root;
		split(root->l, a, b->l, k);
	}

	pull(root);
}

Node* merge(Node* a, Node* b) {
	if (!a or !b) return a ? a : b;
	if (a->pri > b->pri) {
		a->r = merge(a->r, b);
		pull(a);
		return a;
	} else {
		b->l = merge(a, b->l);
		pull(b);
		return b;
	}
}

void heapify(Node* t) {
	if (!t) return;
	Node* Max = t;
	
	if (t->l != nullptr and t->l->pri > Max->pri)
		Max = t->l;
	if (t->r != nullptr and t->r->pri > Max->pri)
		Max = t->r;
	
	if (Max != t) {
		swap(t->pri, Max->pri);
		heapify(Max);
	}
}

Node* build(string str, int base, int n) {
	if (n == 0) return nullptr;

	int mid = n / 2;

	Node* t = new Node(str[base+mid]);
	t->l = build(str, base, mid);
	t->r = build(str, base+mid+1, n-mid-1);
	heapify(t);
	pull(t);

	return t;
}

void go(Node* root) {
	if (!root) return;

	if (root->l) go(root->l);
	cout << root->ch;
	if (root->r) go(root->r);

	delete root;
}

int main() {
    yccc;

	int n, m;
	cin >> n >> m;

	string str;
	cin >> str;

	Node* root = build(str, 0, str.size());
	
	while (m--) {
		int l, r;
		cin >> l >> r;

		Node *a, *b, *c;

		split(root, a, b, l-1);
		split(b, c, b, r-l+1);

		root = merge(a, merge(b, c));
	}

	go(root);
}
