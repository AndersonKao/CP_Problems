#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

vec<int> ans;
vec<int> vis;
vec<vec<p<ll>>> G;

bool dfs(int now) {
		vis[now] = true;
    if (now == 1) {
        ans.eb(now);
        return true;
    }
    
    for (auto i : G[now]) {
        if (vis[i.F]) continue; 
				if (dfs(i.F)) {
						ans.eb(now);
						return true;
				}
    }
    return false;
}

int main()
{
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    G.resize(n);
    for (int i = 0; i < m; i++) {
        int a, b, v;
        cin >> a >> b >> v;
        
        G[a].eb(b, v);
        G[b].eb(a, v);
    }
    
    auto cmp = [](p<ll>& a, p<ll>& b) {
        return a.F > b.F;
    };
    
    vec<p<ll>> dis(n, make_pair(llINF, -1));
    priority_queue<p<ll>, vec<p<ll>>, decltype(cmp)> pq(cmp);
    
    dis[1] = make_pair(0, -1);
    pq.emplace(0, 1);
    
    while (!pq.empty()) {
        auto now = pq.top();
        pq.pop();
        
        if (now.F != dis[now.S].F)
            continue;
            
        for (auto i : G[now.S]) {
            if (i.S + now.F < dis[i.F].F) {
                dis[i.F] = make_pair(i.S + now.F, now.S);
                pq.emplace(dis[i.F].F, i.F);
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        auto pointer = dis[i].S;
        G[i].erase(remove_if(al(G[i]), [pointer](p<ll>& src) { return src.F == pointer; }));
    }
		vis.resize(n, 0);    
    dfs(0);
    
    if (ans.size() == 0) cout << "impossible\n";
    else {
        reverse(al(ans));
        
        cout << ans.size() << ' ';
        for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " \n"[i == ans.size()-1];
    }
}
