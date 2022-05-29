#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
#define F first
#define S second 
#define al(x) x.begin(), x.end()
#define eb emplace_back
#define LC(x) (2 * x + 1)
#define RC(x) (2 * x + 2)
template <typename T>
using vec = vector<T>;
using p3i = tuple<int, int, int>;
using ll = long long;
// segmentTree
// range +-x, first >= k position, local maximum.
struct segT{
    int N;
    vec<ll> seq;
    vec<ll> tag;
    void Build(int N){
        this->N = N;
        seq.resize(4*N, 0);
        tag.resize(4*N, 0);
    }
    void Modify(int l, int r, ll val){
        modify(l, r, 0, N - 1, 0, val);
    }
    void modify(int l, int r, int L, int R, int idx, ll val){
        if(l > R || r < L)
            return ;
        if(l <= L && r >= R){
            tag[idx] += val;
            return ;
        }
        int M = (L + R) >> 1;
        push(idx);
        modify(l, r, L, M, LC(idx), val);
        modify(l, r, M+1, R, RC(idx), val);
        pull(idx);
    }
    int Query(ll val){
        return query(0, N - 1, 0, val);
    };
    int query(int L, int R, int idx, ll val){
        if(L == R)
            return L;
        push(idx);
        int M = (L + R) >> 1;
        int ans = -1;
        if (seq[LC(idx)] + tag[LC(idx)] >= val)
            ans = query(L, M, LC(idx), val);
        else if(seq[RC(idx)] + tag[RC(idx)] >= val) 
            ans = query(M+1, R, RC(idx), val);
        pull(idx);
        return ans;
    }
    void push(int idx)
    {
        ll &t = tag[idx];
        tag[LC(idx)] += t;
        tag[RC(idx)] += t;
        t = 0;
    }
    void pull(int idx){
        int lc = LC(idx), rc = RC(idx);
        seq[idx] = max(seq[lc] + tag[lc], seq[rc] + tag[rc]);
    }
};

int main()
{
    yccc;
    int N, P, Q;
    cin >> N >> P >> Q;
    vec<vec<pair<int ,int>>> Qs(N);
    vec<vec<pair<int, int>>> add(N + 1);
    vec<int> ans(Q);
    for (int i = 0; i < P; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        l--, r--;
        add[l].eb(i, x);
        add[r + 1].eb(i, -x);
    }
    for (int i = 0; i < Q; i++)
    {
        int x, k;
        cin >> x >> k;
        Qs[x - 1].emplace_back(i, k);
    }
    segT mT;
    mT.Build(P);
    for (int i = 0; i < N; i++)
    {
        for(auto& e: add[i]){
            mT.Modify(e.F, P - 1, e.S);
        }
        for (auto [id, k] : Qs[i])
        {
            ans[id] = mT.Query(k);
        }
    }

    for(int& an: ans){
        cout << (an == -1 ? -1 : an + 1) << endl;
    }
    return 0;
}
