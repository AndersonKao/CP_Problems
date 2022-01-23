#include <bits/stdc++.h>
using namespace std;
#define K 16

using LL = long long;
using pii = pair<int, int>;
const LL INF = 1e12;
struct Dinic {
  struct Node : vector<int> { int d, p; };
  struct Edge { int u, v; LL f, c; };

  vector<Node> N; vector<Edge> E;

  void addNode() {
    N.emplace_back();
  }

  size_t numOfNode() const {
    return N.size();
  }

  void addEdge(int u, int v, LL c) {
    int m = E.size();
    E.push_back({u, v, 0, c}); N[u].push_back(m++);
    E.push_back({v, u, 0, c}); N[v].push_back(m++);
  }

  void popBackEdge() {
    int u = E.back().u;
    int v = E.back().v;
    N[u].pop_back();
    N[v].pop_back();
    E.pop_back();
    E.pop_back();
  }

  size_t numOfEdge() const {
    return E.size() >> 1;
  }

  void clear() {
    for (auto &e : E) e.f = 0;
  }

  bool bfs(int s, int t) {
    for (auto &v : N) v.d = -1, v.p = 0;
    queue<int> q; q.push(s); N[s].d = 0;
    while (q.size()) { int u = q.front(); q.pop();
      for (auto &e : N[u]) { int v = E[e].v;
        if (!~N[v].d && E[e].f < E[e].c)
          q.push(v), N[v].d = N[u].d + 1;
      }
    }
    return ~N[t].d;
  }

  LL dfs(int u, int t, LL a) {
    if (u == t || !a) return a; LL flow = 0;
    for (int &p = N[u].p; p < N[u].size(); p++) {
      auto e = N[u][p], v = E[e].v;
      if (N[u].d + 1 != N[v].d) continue;
      LL f = dfs(v, t, min(a, E[e].c - E[e].f));
      E[e].f += f; E[e ^ 1].f -= f; flow += f; a -= f;
      if (!a) break;
    }
    return flow;
  }

  LL run(int s, int t) {
    LL flow = 0; clear();
    while (bfs(s, t)) flow += dfs(s, t, INF);
    return flow;
  }
};

struct Q {
  int u, i, v, j;
};

int getBit(int u, int i) {
  return (u >> i) & 1;
}
#define encode(u, i) (i * n + u)
tuple<int, int, int, Dinic, vector<Q>> init() {
  int n, m; cin >> n >> m;
  assert(1 <= n and n <= 1000);
  assert(1 <= m and m <= 5000);

  auto solver = Dinic();
  for (int i = 0; i < K * n + 2; i++)
    solver.addNode();
  int s = K * n, t = K * n + 1;
  
  set<pii> st;
  while (m--) {
    int u, v; cin >> u >> v;
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    assert(u != v);
    if (u > v) swap(u, v);
    assert(st.count({u, v}) == 0);
    st.insert({u, v});
    for (int i = 0; i < K; i++)
      solver.addEdge(encode(u, i), encode(v, i), 1);
  }

  for (int i = 0; i < n; i++) {
    int v; cin >> v;
    assert(-1 <= v and v < (1 << K));
    if (v == -1)
      continue;
    for (int j = 0; j < K; j++) {
      if (getBit(v, j) == 0)
        solver.addEdge(s, encode(i, j), INF);
      else
        solver.addEdge(encode(i, j), t, INF);
    }
  }

  vector<Q> qs;
  int q; cin >> q;
  assert(0 <= q and q <= 8);
  while (q--) {
    int t, u, i, v, j;
    cin >> t >> u >> i >> v >> j;
    assert(t == 0 or t == 1);
    assert(0 <= u and u < n);
    assert(0 <= v and v < n);
    assert(0 <= i and i < K);
    assert(0 <= j and j < K);
    assert(u != v or i != j);
    if (t == 0)
      solver.addEdge(encode(u, i), encode(v, j), INF);
    else
      qs.push_back({u, i, v, j});
  }

  return {n, s, t, solver, qs};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  
  auto [n, s, t, base, qs] = init();

  LL ans = INF;
  for (int S = 0; S < (1 << qs.size()); S++) {
    for (int i = 0; i < (int)qs.size(); i++) {
      if (getBit(S, i) == 0) {
        base.addEdge(s, encode(qs[i].u, qs[i].i), INF);
        base.addEdge(encode(qs[i].v, qs[i].j), t, INF);
      } else {
        base.addEdge(s, encode(qs[i].v, qs[i].j), INF);
        base.addEdge(encode(qs[i].u, qs[i].i), t, INF);
      }
    }
    ans = min(ans, base.run(s, t));
    for (int i = 0; i < (int)qs.size(); i++)
      base.popBackEdge(), base.popBackEdge();
    base.clear();
  }
  if (ans == INF)
    cout << -1 << '\n';
  else
    cout << ans << '\n';
}
