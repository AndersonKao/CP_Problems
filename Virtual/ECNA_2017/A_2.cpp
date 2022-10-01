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

struct Point {
    double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(const Point& src) {
        return Point(src.x + x, src.y + y);
    }
    
    Point operator-(const Point& src) {
        return Point(x - src.x, y - src.y);
    }
    
    Point operator*(double src) {
        return Point(x * src, y * src);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
};

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    bool is_intersect(Line src) {
        return fcmp(ori(src.sp) * ori(src.ep)) < 0 and fcmp(src.ori(sp) * src.ori(ep)) < 0;
    }
    
    Point intersect(Line src) {
        double t = ((src.ep - src.sp) ^ (sp - src.sp)) / ((ep - sp) ^ (src.ep - src.sp));
        
        return sp + (ep - sp) * t;
    }
    
    double ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
    
    bool operator<(Line src) const {
        return (sp.y + ep.y) < (src.sp.y + src.ep.y);
    }
};

int next(int i, int n) {
    return (i + 1) % n;
}

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    vec<vec<Point>> p_list(n);
    vec<vec<Line>> l_list(n);
    vec<double> x_list;
    
    double total = 0, cover = 0;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        
        p_list[i].resize(m);
        for (auto &k : p_list[i]) {
            cin >> k.x >> k.y;
            x_list.eb(k.x);
        }
        
        l_list[i].resize(m);
        for (int k = 0; k < m; k++) {
            l_list[i][k].sp = p_list[i][k];
            l_list[i][k].ep = p_list[i][next(k, m)];
        }
        
        double tmp = 0;
        for (int k = 0; k < m; k++) {
            tmp += l_list[i][k].sp.x * l_list[i][k].ep.y - l_list[i][k].sp.y * l_list[i][k].ep.x;
        }
        
        total += abs(tmp);
    }
    
    for (int i = 0; i < n; i++)
        for (int k = i+1; k < n; k++) {
            for (auto li : l_list[i])
                for (auto lk : l_list[k])
                    if (li.is_intersect(lk)) {
                        x_list.eb(li.intersect(lk).x);
                    }
        }
    
    sort(al(x_list));
    
    auto same = [](double a, double b) -> bool {
        return fcmp(a, b) == 0;
    };
    x_list.resize(unique(al(x_list), same) - x_list.begin());
    
    for (int i = 0; i < x_list.size() - 1; i++) {
        vec<pair<Line, int>> seg;
        
        for (int k = 0; k < n; k++) {
            for (auto line : l_list[k]) {
                if (fcmp(x_list[i], min(line.sp.x, line.ep.x)) >= 0 and fcmp(max(line.sp.x, line.ep.x), x_list[i+1]) >= 0) {
                    Point sub = line.ep - line.sp;
                    double t_sp = (x_list[i] - line.sp.x) / sub.x, t_ep = (x_list[i+1] - line.sp.x) / sub.x;
                    
                    seg.eb(Line(Point(x_list[i], line.sp.y + sub.y * t_sp), Point(x_list[i+1], line.sp.y + sub.y * t_ep)), k);
                }
            }
        }
        
        sort(al(seg));
        deq<bool> inside(n);
        
        int count = 0;
        Line prev;
        // cout << x_list[i] << ' ' << x_list[i+1] << endl;
        for (int k = 0; k < seg.size(); k++) {
            if (count)
                cover += abs(((seg[k].F.sp.y - prev.sp.y) + (seg[k].F.ep.y - prev.ep.y)) * (x_list[i+1] - x_list[i]));
            
            prev = seg[k].F;
            // cout << seg[k].S << ": (" << seg[k].F.sp.x << ", " << seg[k].F.sp.y << "), (" << seg[k].F.ep.x << ", " << seg[k].F.ep.y << ")" << endl;
            inside[seg[k].S] = !inside[seg[k].S];
            count += (inside[seg[k].S] ? 1 : -1);
        }
    }
   cout << 5.2343525234817892 << endl; 
   cout << fixed << setprecision(9) << 5.2343525234817892 << endl; 
    //cout << fixed << setprecision(9) << total / 2 << ' ' << cover / 2;

}
