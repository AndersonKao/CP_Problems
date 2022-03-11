
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<typename T> using vec = vector<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": \n "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const int MOD = 1e9+7;

const double PI = 3.1415926535;

//* get degree from radian.
double deg(double Rad) {
    return Rad * 360 / 2 / PI;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << deg(a.F) << ' ' << deg(a.S) << endl; return out; }

inline int next(int i, int n) { return (i+1) % n; }
inline int prev(int i, int n) { return (i-1+n) % n; }

//* cosine theorem, get length of c.
double cosT(double a, double b, double dC) {
    return sqrt(a*a + b*b - 2*a*b*cos(dC));
}

//* consine theorem, get radian of dC.
double DcosT(double c, double a, double b) {
    return acos((a*a + b*b - c*c) / (2*a*b));
}

//* get radian from degree.
double rad(double Deg) {
    return Deg * 2 * PI / 360;
}

class Point {
    public:
    
    double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(Point p) { return Point(x+p.x, y+p.y); }
    Point operator-(Point p) { return Point(x-p.x, y-p.y); }
    double operator^(Point p) { return x * p.y - y * p.x; }
    double operator*(Point p) { return x * p.x + y * p.y; }
    
    //* distance between two points.
    double dis(Point src) {
        Point sub = *this - src;
        return sqrt(sub.x * sub.x + sub.y * sub.y);
    }
};

Point operator*(double a, Point src) {
    return Point(src.x * a, src.y * a);
}

class Line {
    public:
    
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    Point intersection(Point src) {
        double t = (src-sp) * (ep-sp) / ((ep-sp) * (ep-sp));
        
        return sp + t * (ep-sp);
    }
    
    //* the shortest distance from point to the line.
    double dis(Point src) {
        Point inter = intersection(src);
        
        return inter.dis(src);
    }
};

class Tree {
    public:
    
    Point pos;
    int d, h;
    double bias;
    double Hbias;
    
    Tree() {}
    Tree(int x, int y, int d, int h) : pos(Point(x, y)), d(d), h(h) {}
};

vec<Tree> tree;
deque<bool> done;
int H, W;

using range = pair<double, double>;
bool cut(int idx) {
    double Dis = Point(0, 0).dis(Point(tree[idx].d / 2.0, tree[idx].h));
    
    int gx[4] = {W, W, 0, 0};
    int gy[4] = {0, H, H, 0};
    vec<Line> edge(4);
    vec<range> invalid_rad;
    
    for (int i = 0; i < 4; i++) {
        edge[i].sp = Point(gx[i], gy[i]);
        edge[i].ep = Point(gx[next(i, 4)], gy[next(i, 4)]);
        
        if (Dis <= edge[i].dis(tree[idx].pos)) {
            continue;
        }
        
        double rad = acos(edge[i].dis(tree[idx].pos) / Dis);
        invalid_rad.eb(PI * i / 2 - rad - tree[idx].bias, PI * i / 2 + rad + tree[idx].bias);
    }
    
    for (int i = 0; i < tree.size(); i++) {
        if (done[i] or i == idx)
            continue;
        
        double ppDis = tree[idx].pos.dis(tree[i].pos), ttRadius = tree[i].d/2.0 + tree[idx].d/2.0;
        double _maxH = sqrt((ppDis * ppDis) - (ttRadius * ttRadius));
        tree[idx].Hbias = atan(tree[idx].d/2.0/_maxH);
        
        if (Dis + tree[i].d/2.0 < ppDis) { //* no effect
            continue;
        } else if (tree[idx].h < _maxH) { 
            Point sub = Point(tree[i].pos - tree[idx].pos);
            double baseRad = atan(sub.y / sub.x);
            if (sub.x < 0)
                baseRad += PI;
                
            double offset = DcosT(tree[i].d/2.0, Dis, ppDis);
            
            invalid_rad.eb(baseRad - offset - tree[idx].bias, baseRad + offset + tree[idx].bias);
        } else {
            Point sub = Point(tree[i].pos - tree[idx].pos);
            double baseRad = atan(sub.y / sub.x);
            if (sub.x < 0)
                baseRad += PI;
                
            double slopeDis = Point(0, 0).dis(Point(tree[idx].d/2.0, _maxH));
            double offset = DcosT(tree[i].d/2.0, slopeDis, ppDis);
            
            invalid_rad.eb(baseRad - offset - tree[idx].Hbias, baseRad + offset + tree[idx].Hbias);
        }
    }
    
    double now = 0, finish = 2 * PI;
    for (int i = 0; i < invalid_rad.size(); i++) {
        while (invalid_rad[i].F >= 2 * PI) invalid_rad[i].F -= 2 * PI;
        while (invalid_rad[i].F < 0) invalid_rad[i].F += 2 * PI;
        while (invalid_rad[i].S >= 2 * PI) invalid_rad[i].S -= 2 * PI;
        while (invalid_rad[i].S < 0) invalid_rad[i].S += 2 * PI;
        
        if (invalid_rad[i].S < invalid_rad[i].F) {
            now = max(now, invalid_rad[i].S);
            finish = min(finish, invalid_rad[i].F);
        }
    }
    
    sort(al(invalid_rad));
    
    for (int i = 0; i < invalid_rad.size(); i++) {
        if (now >= finish)
            return false;
        
        if (invalid_rad[i].S < invalid_rad[i].F)
            continue;
            
        if (invalid_rad[i].F >= now)
            return true;
        
        now = max(now, invalid_rad[i].S);
    }
    
    return !(now >= finish);
}

int main()
{
    yccc;
    
    int c = 1;
    while (true) {       
        vec<int> area(4);
        for (auto &i : area)
            cin >> i;
        
        H = area[3] - area[1], W = area[2] - area[0];
        
        int n;
        cin >> n;
        
        if (n == 0)
            break;
        
        tree.resize(n);
        done.clear();
        done.resize(n);
        
        for (auto &i : tree) {
            cin >> i.pos.x >> i.pos.y >> i.d >> i.h;
            i.pos.x -= area[0];
            i.pos.y -= area[1];
            i.bias = atan(i.d/2.0/i.h);
        }
        
        int sum = 0;
        for (int i = 0; i < n; i++) {   //* at most cut n trees.
            for (int k = 0; k < n; k++) {   //* if k-th tree can be removed?
                if (!done[k] and cut(k)) {
                    done[k] = true;
                    sum++;
                }
            }
        }
        
        cout << "Forest " << c++ << endl;
        cout << sum << " tree(s) can be cut" << endl << endl;
    }
}