#include <bits/stdc++.h>
#define debug(a) cout << #a << " = " << a << "\n";
using namespace std;
 
typedef long long ll;
ll MOD = 998244353LL;

int n;
int c[200009];
int p[200009];
ll t[200009];
vector<int> v[200009];

ll Dfs(int u) {
    if (v[u].empty()) return 1;

    ll now = 1;
    for (auto i : v[u])
        now = now * Dfs(i) % MOD;

    int cnt = (c[u] == 0);
    for (auto i : v[u]) cnt += (c[i] == 0);

    multiset<int> s;
    for (auto i : v[u]) if (c[i] != 0) s.insert(c[i]);
    if (c[u] != 0) s.insert(c[u]);

    for (auto i : v[u]) if (s.find(i) != s.end()) {
        if (i == c[u]) c[u] = 0;
        s.erase(i);
    }
    if ((int)s.size() >= 2) return 0;
    else if ((int)s.size() == 1) c[u] = *s.begin();

    if (u == 1 && c[u] > 1) return 0;
    
    return now * t[cnt] % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);

    t[0] = 1;
    for (int i = 1; i <= 200000; ++ i) t[i] = t[i - 1] * i % MOD;

    int _ ; cin >> _ ;
    while ( _ -- ) {
        cin >> n;
        for (int i = 1; i <= n; ++ i) v[i].clear();
        for (int i = 2; i <= n; ++ i) {
            cin >> p[i];
            v[p[i]].push_back(i);
        }
        for (int i = 1; i <= n; ++ i) cin >> c[i];
        cout << Dfs(1) << "\n";
    }
}
