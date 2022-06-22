#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) {cout << ' '; if (k == INF) cout << '-'; else cout << k;} cout << endl; }

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Point {
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

struct Line {
    Point sp, ep;

    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
};

istream& operator>>(istream& in, Point& src) {
    in >> src.x >> src.y;

    return in;
}

inline bool isin(int val, int low, int high) {
    return val >= low and val < high;
}

int main() {
    yccc;

    int n, c = 1;
    while (cin >> n) {
        if (!n)
            break;

        vec<int> x, y;

        vec<Line> _list(n);
        for (int i = 0; i < n; i++) {
            cin >> _list[i].sp >> _list[i].ep;

            x.eb(_list[i].sp.x);
            x.eb(_list[i].ep.x);
            y.eb(_list[i].sp.y);
            y.eb(_list[i].ep.y);
        }

        Point s, t;
        cin >> s >> t;

        x.eb(s.x);
        x.eb(t.x);
        y.eb(s.y);
        y.eb(t.y);

        sort(al(x));
        x.resize(distance(x.begin(), unique(al(x))));
        sort(al(y));
        y.resize(distance(y.begin(), unique(al(y))));
        for (int i = 0; i < n; i++) {
            _list[i].sp.x = (lower_bound(al(x), _list[i].sp.x) - x.begin()) * 2 + 2;
            _list[i].ep.x = (lower_bound(al(x), _list[i].ep.x) - x.begin()) * 2 + 2;

            _list[i].sp.y = (lower_bound(al(y), _list[i].sp.y) - y.begin()) * 2 + 2;
            _list[i].ep.y = (lower_bound(al(y), _list[i].ep.y) - y.begin()) * 2 + 2;
        }

        s.x = (lower_bound(al(x), s.x) - x.begin()) * 2 + 2;
        t.x = (lower_bound(al(x), t.x) - x.begin()) * 2 + 2;
        s.y = (lower_bound(al(y), s.y) - y.begin()) * 2 + 2;
        t.y = (lower_bound(al(y), t.y) - y.begin()) * 2 + 2;
        
        vec<vec<int>> _map(x.size() * 2 + 4, vec<int>(y.size() * 2 + 4, INF));
        vec<vec<int>> road(x.size() * 2 + 4, vec<int>(y.size() * 2 + 4));
        deq<deq<bool>> vis(_map.size(), deq<bool>(_map[0].size()));

        for (int i = 0; i < n; i++) {
            if (_list[i].sp.x == _list[i].ep.x) { // vertical.
                if (_list[i].sp.y > _list[i].ep.y)
                    swap(_list[i].sp.y, _list[i].ep.y);
                
                for (int k = _list[i].sp.y; k <= _list[i].ep.y; k++)
                    road[_list[i].sp.x][k] += 1;

            } else {
                if (_list[i].sp.x > _list[i].ep.x)
                    swap(_list[i].sp.x, _list[i].ep.x);
                
                for (int k = _list[i].sp.x; k <= _list[i].ep.x; k++)
                    road[k][_list[i].sp.y] += 1;
            }

            // road[_list[i].sp.x][_list[i].sp.y] = 2;
            // road[_list[i].ep.x][_list[i].ep.y] = 2;
        }
        
        int level = 0;
        queue<Point> que, wall;
        que.emplace(s.x, s.y);
        vis[s.x][s.y] = true;
        
        // cout << _map.size() << ' ' << _map[0].size() << endl;

        // devec2(_map);
        devec2(road);
        
       do {
            while (!que.empty()) {
                auto now = que.front();
                que.pop();
                
                _map[now.x][now.y] = level;
                
                // cout << now.x << ' ' << now.y << endl;
                devec2(_map);

                int gx[4] = {0, -1, 0, 1};
                int gy[4] = {1, 0, -1, 0};

                for (int i = 0; i < 4; i++) {
                    if (!isin(now.x + gx[i], 0, _map.size()))
                        continue;
                    if (!isin(now.y + gy[i], 0, _map[0].size()))
                        continue;
                    if (vis[now.x+gx[i]][now.y+gy[i]])
                        continue;
                    if (road[now.x+gx[i]][now.y+gy[i]] == 2)
                        continue;

                    if (road[now.x+gx[i]][now.y+gy[i]])
                        wall.emplace(now.x + gx[i], now.y + gy[i]);
                    else
                        que.emplace(now.x + gx[i], now.y + gy[i]);
                    
                    vis[now.x + gx[i]][now.y + gy[i]] = true;
                }
            }

            level++;
            que = wall;
            wall = queue<Point>();
        } while (!que.empty());
        

        cout << "City " << c++ << endl;
        cout << "Peter has to cross " << _map[t.x][t.y] << " streets" << endl;
    }
}