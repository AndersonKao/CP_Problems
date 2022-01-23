#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fr(i,j,k) for(int i=j;i<k;i++)
#define f(n) fr(i,0,n)
#define f1(n) fr(i,1,n+1)
#define pb push_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
const int mod = 998244353;
const int maxn = 200005;
int v[maxn];
struct s
{
    int tg;   // lazytag
    ll l, r; // 區間左右界
    long long ans; // 區間內的交替子陣列數量
    int li, ri; // 延伸至左右的交替陣列長度
    int ls, rs; // 最左右的值(1 or 0)
}node[maxn << 2];
void push(int x) {
    if (!node[x].tg) {
        return;
    }
    node[x].tg = 0;
    node[x<<1].tg ^= 1;
    node[x<<1].ls ^= 1;
    node[x<<1].rs ^= 1;
    node[x<<1|1].tg ^= 1;
    node[x<<1|1].ls ^= 1;
    node[x<<1|1].rs ^= 1;
}
s pull(s l, s r) {
    s p;
    p.l = l.l;
    p.r = r.r;
    p.ls = l.ls;
    p.rs = r.rs;
    p.tg = 0;
    if (l.rs == r.ls) {
        p.li = l.li;
        p.ri = r.ri;
        p.ans = l.ans + r.ans;
        return p;
    }
    p.ans = l.ans + r.ans + l.ri * r.li;
    p.li = (l.li == (l.r - l.l + 1) ? l.li + r.li : l.li);
    p.ri = (r.ri == (r.r - r.l + 1) ? r.ri + l.ri : r.ri);
    return p;
}
void build(int x, int l, int r) {
    if (l == r) {
        cin >> v[l];
        node[x] = {1, 1, 1, l, l, v[l], v[l], 0};
        return;
    }
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
    node[x] = pull(node[x<<1], node[x<<1|1]);
}
s query(int x,int l,int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        return node[x];
    }
    int mid = (l + r) >> 1;
    push(x);
    if (ql > mid) {
        return query(x << 1 | 1, mid + 1, r, ql, qr);
    }
    else if (qr <= mid) {
        return query(x << 1, l, mid, ql, qr);
    }
    else {
        return pull(query(x<<1, l, mid, ql, qr), query(x<<1|1, mid + 1, r, ql, qr));
    }
}
void update(int x,int l, int r, int ql, int qr) {
    if (ql <= l && qr >= r) {
        node[x].tg ^= 1;
        node[x].ls ^= 1;
        node[x].rs ^= 1;
        return;
    }
    int mid = (l + r) >> 1;
    push(x);
    if (ql <= mid) {
        update(x << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        update(x << 1 | 1, mid + 1, r, ql, qr);
    }
    node[x] = pull(node[x<<1], node[x<<1|1]);
}
void go() {
  int n, q;
  cin >> n >> q;
  build(1, 1, n);
  while (q--) {
    int op;
    cin >> op;
    if (op == 2) {
        int l, r;
        cin >> l >> r;
        assert (1 <= l && l <= r && r <= n);
        s a = query(1, 1, n, l, r);
        cout << a.ans<<'\n';
    }
    else {
        int l, r;
        cin >> l >> r;
        assert (1 <= l && l <= r && r <= n);
        update(1, 1, n, l, r);
    }
  }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int c = 0;
    int t;
    if (!c) {
        t = 1;
    }
    else {
        cin >> t;
    }
    while (t--) {
        go();
    }
    
}