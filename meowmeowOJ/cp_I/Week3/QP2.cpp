#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops,no-stack-protector,Ofast")
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef long double ld;
#define pb emplace_back
#define mp make_pair
#define fi first
#define se second
#define lwb lower_bound
#define setp setprecision
#define SZ(_a) (ll)(_a).size()
#define SQ(_a) ((_a)*(_a))
#define all(_a) (_a).begin(), (_a).end()
#define chmax(_a, _b) _a = max(_a, _b)
#define chmin(_a, _b) _a = min(_a, _b)
#define tpt template<class T>
tpt inline ostream& operator << (ostream& out, vector<T> v) {
    for (int i = 0;i < SZ(v); ++i) out << v[i] << (i == SZ(v)-1 ? "" : " ");
    return out;
}

const ll N = 6e6 + 5;
const ll MOD = 1e9 + 7;
const ld pi = acos(-1);
const ll INF = (1LL<<60);

ll n, m, head[N], tail[N], ba[N], fr[N];

void solve() {
    cin >> n >> m;
    for (ll i = 1;i <= n; ++i) {
        head[i] = i+n, tail[i] = i+2*n;
        ba[head[i]] = i;
        fr[i] = head[i];
        ba[i] = tail[i];
        fr[tail[i]] = i;
    }
    for (ll i = 1, ty, a, b;i <= m; ++i) {
        cin >> ty >> a >> b;
        if (ty == 0) {
            ll ff = fr[a], bb = ba[a];
            ba[ff] = bb;
            fr[bb] = ff;
            ll p = ba[b];
            ba[b] = a;
            fr[a] = b;
            ba[a] = p;
            fr[p] = a;
        } else {
            ll l = ba[head[a]], r = fr[tail[a]], to = fr[tail[b]];
            if (l == tail[a]) continue;
            fr[l] = to;
            ba[to] = l;
            ba[r] = tail[b];
            fr[tail[b]] = r;
            ba[head[a]] = tail[a];
            fr[tail[a]] = head[a];
        }
    }
    for (ll i = 1;i <= n; ++i) {
        ll now = head[i];
        vector<ll> lis;
        while(ba[now] != tail[i]) {
            lis.pb(ba[now]);
            now = ba[now];
        }
        cout << "#" << i << ": " << lis << "\n";
    }
}

int main () {
    ios_base::sync_with_stdio(0);cin.tie(0);
    solve();
    return 0;
}
