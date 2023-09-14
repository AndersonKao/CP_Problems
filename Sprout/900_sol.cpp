#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
  int sz, rev, val;
  Node *lc, *rc;
  Node(int c = 0) : val(c), sz(1), rev(0), lc(0), rc(0) {}
  void push() { 
    if (!rev) return;
    rev = 0;
    swap(lc, rc);
    if (lc) lc->rev ^= 1;
    if (rc) rc->rev ^= 1;
  }
  Node *pull() { return sz = (lc ? lc->sz : 0) + 1 + (rc ? rc->sz : 0), this; }
};

Node *merge(Node *a, Node *b) {
  if (!a || !b) return a ? a : b;
  a->push();
  b->push();
  if (rand() % (a->sz + b->sz) < a->sz) return a->rc = merge(a->rc, b), a->pull();
  return b->lc = merge(a, b->lc), b->pull();
}

void split(Node *t, Node *&a, Node *&b, int k) {
  if (!t) return a = b = nullptr, void();
  t->push();
  int lsz = t->lc ? t->lc->sz : 0;
  if (lsz >= k) return b = t, split(t->lc, a, b->lc, k), b->pull(), void();
  a = t, split(t->rc, a->rc, b, k - (lsz + 1)), a->pull();
}

int main() {
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;

  string S;
  cin >> S;

  Node *root = new Node(S[0]);
  for (int i = 1; i < N; ++i) root = merge(root, new Node(S[i]));

  while (Q--) {
    int L, R;
    cin >> L >> R;
    Node *a, *b, *c, *d;
    split(root, a, b, L - 1);
    split(b, c, d, R - L + 1);
    c->rev ^= 1;
    root = merge(a, merge(c, d));
  }

  string res; {
    for (int i = 0; i < N; ++i) {
      Node *a, *b, *c, *d;
      split(root, a, b, i);
      split(b, c, d, 1);
      res.push_back(c->val);
      root = merge(a, merge(c, d));
    }
  }
  cout << res << endl;

  return 0;
}