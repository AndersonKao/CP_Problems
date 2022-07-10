// AC 2022-07-08 18:48:01
// WA
// taking advice from fong-yi that using vector rather than double in rate to compare colinear
// forget to set N = Ps.size();
// WA
// co be, colinear need to be processed.
// Try __int128 still WA
// WA
// guess: overflow
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
inline int fcmp(const double &a, const double &b){
    if(fabs(a - b) < eps)
        return 0;
    return ((a - b > 0.0) * 2) - 1;
}

template <typename T>
struct Point
{
    T x, y;
    Point() : x(0), y(0) {}
    Point(const T x, const T y) : x(x), y(y) {}
    template <class F>
    explicit operator Point<F>() const
    {
        return Point<F>((F)x, (F)y);
    }

    Point operator+(const Point b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator-(const Point b) const
    {
        return Point(x - b.x, y - b.y);
    }
    template <class F>
    Point<F> operator*(const F fac)
    {
        return Point<F>(x * fac, y * fac);
    }
    template <class F>
    Point<F> operator/(const F fac)
    {
        return Point<F>(x / fac, y / fac);
    }

    T operator&(const Point b) const { return x * b.x + y * b.y; }
    // dot operator
    T operator^(const Point b) const { return x * b.y - y * b.x; }
    // cross operator
    bool operator==(const Point b) const
    {
        return x == b.x and y == b.y;
    }
    bool operator<(const Point b) const
    {
        return x == b.x ? y < b.y : x < b.x;
    } // 字 典 序

    Point operator-() const { return Point(-x, -y); }
    T norm() const { return *this & *this; }    // 歐 式 長 度 平 方
    Point prep() const { return Point(-y, x); } // 左 旋 直 角 法 向 量
    template <class F>
    friend istream &operator>>(istream &is, Point<F> &pt);
    template<class F>
    friend ostream &operator<<(ostream &os, const Point<F> &pt);
};
template <class F>
ostream &operator<<(ostream &os, const Point<F> &pt)
{
    return os << pt.x << " " << pt.y;
}
template <class F>
istream &operator>>(istream &is, Point<F> &pt)
{
    return is >> pt.x >> pt.y;
}
template <class F>
bool collinearity(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
//    return (p1 - p3) ^ (p2 - p3) == 0;
    return fcmp((p1 - p3) ^ (p2 - p3), 0.0) == 0;
}
// check co-line first. properly
template<class F>
inline bool btw(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    return fcmp((p1 - p3) & (p2 - p3), 0.0) <= 0;
}

// is p3 on (p1, p2)?
template<class F>
inline bool pointOnSegment(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    return collinearity(p1, p2, p3) && btw(p1, p2, p3);
}

template <typename T, typename Real = double>
struct Line
{
    Point<T> st, ed;
    Point<T> vec() const { return ed - st; }
    T ori(const Point<T> p) const { return (ed - st) ^ (p - st); }
    int orint(const Point<T> p) const{
        T a = this->ori(p);
        return (fcmp(a, 0.0), 0); // 1 on posi-side // -1 nega-side
        // a little bit useless?
    }
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
    template <class F>
    operator Line<F>() const
    {
        return Line<F>((Point<F>)st, (Point<F>)ed);
    }

    // sort by arg, the left is smaller for parallel lines
    bool operator<(Line B) const
    {
        Point<T> a = vec(), b = B.vec();
        auto sgn = [](const Point<T> t) { return (t.y == 0 ? t.x : t.y) < 0; };
        if (sgn(a) != sgn(b))
            return sgn(a) < sgn(b);
        if (abs(a ^ b) == 0)
            return B.ori(st) > 0;
        return (a ^ b) > 0;
    }

    // Regard a line as a function
    template <typename F>
    Point<F> operator()(const F x) const // A + AB * x = the point position.
    {
        return Point<F>(st) + vec() * x;
    }

    bool isSegProperIntersection(const Line l) const
    {
        return l.ori(st) * l.ori(ed) < 0 and ori(l.st) * ori(l.ed) < 0;
    }
    bool isSegIntersection(const Line l)const{
        Line<Real> h = *this;
        // hst = 1, hed = 2, lst = 3, led = 4
        double hlst = h.ori(l.st);
        double hled = h.ori(l.ed);
        double lhst = l.ori(h.st);
        double lhed = l.ori(h.ed);
        if(fcmp(hlst, 0.0) == 0 && fcmp(hled,0.0) == 0)
            return h.isPointOnSeg(l.st) || h.isPointOnSeg(l.ed) || l.isPointOnSeg(h.st) || l.isPointOnSeg(h.ed);

        return fcmp(hlst * hled, 0.0) <= 0 && fcmp(lhst * lhed, 0.0) <= 0;
    }
    
    bool isPointOnSegProperly(const Point<T> p) const
    {
        return fcmp(ori(p), 0.0) == 0 and fcmp(((st - p) & (ed - p)), 0.0) < 0;
    }
    bool isPointOnSeg(const Point<T>p) const{
        return fcmp(ori(p), 0.0) == 0 and fcmp((st - p) & (ed - p), 0.0) <= 0;
    }
    Real disP2Line(const Point<T> p) const
    {
        return Line<double>(projection(p), Point<double>(p)).vec().norm();
    }

    // notice if you should check Segment intersect or not;
    // be careful divided by 0
    Point<Real> getIntersection(Line<Real> l)
    {
        Line<Real> h = *this;
//        return l(((l.st - h.st)^ h.vec()) / (h.vec() ^ l.vec())); // use operator()
        Real hlst = -h.ori(l.st);
        Real hled = h.ori(l.ed);
        return ((l.st * hled) + (l.ed * hlst)) / (hlst + hled);

        // 需要確認+-號的合理性
        // Area of triangle(l.st, h.st, h.ed) divided by Area of Quadrilateral(h.st, l.st, h.ed, l.ed)
    }

    Point<Real> projection(const Point<T> p) const
    {
        return operator()(((p - st) & vec()) / (Real)(vec().norm()));
    }
    template <class F>
    friend ostream &operator<<(ostream &os, const Line<F> &l);
};
template <class F>
ostream &operator<<(ostream &os, const Line<F> &l)
{
    return os << "(" << l.st.x << ", " << l.st.y << ") to (" << l.ed.x << ", " << l.ed.y << ")";
}
template <class F>
using Polygon = vector<Point<F>>;
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;
template <typename T>
using vec = vector<T>;
using ll = long long;
ll gcd(ll a, ll b)
{
    if(b == 0)
        return a;
    return gcd(b, a % b);
}
int N, M;
inline int ni(int i){
    return (i + 1) >= N ? 0 : i + 1;
}
int main()
{
    int caseN = 1;
    while (cin >> N >> M)
    {
        if(N == 0 && M == 0)
            break;
        Polygon<ll> Ps;
        for (int i = 0; i < N; i++){
            ll x, y;
            cin >> x >> y;
            int id = Ps.size() - 1;
            if(id >= 1){
                Point<ll> v1 = Ps[id] - Ps[id - 1];
                v1 = v1 / (gcd(abs(v1.x), abs(v1.y)));
                Point<ll> v2(x - Ps[id].x, y - Ps[id].y);
                v2 = v2 / (gcd(abs(v2.x), abs(v2.y)));
                if(v1 == v2)
                {
                    Ps[id].x = x;
                    Ps[id].y = y;
                }
                else
                    Ps.eb(x, y);
            }
            else{
                Ps.eb(x, y);
            }
        }
        int id = Ps.size() - 1;
        Point<ll> v1 = Ps[id] - Ps[id - 1];
        v1 = v1 / (gcd(abs(v1.x), abs(v1.y)));
        Point<ll> v2 = Ps[0] - Ps[id];
        v2 = v2 / (gcd(abs(v2.x), abs(v2.y)));
//        if (fcmp(r1, r2) == 0 || (isinf(r1) && isinf(r2) && ((r1>0) == (r2 > 0)))){
        if (v1 == v2){
            Ps.erase(Ps.end()-1);
        }
//        r1 = (Ps[1].y - Ps[0].y) / (double)(Ps[1].x - Ps[0].x);
//        r2 = (Ps[0].y - Ps[id].y) / (double)(Ps[0].x - Ps[id].x);
        {
            int id = Ps.size() - 1;
            Point<ll> v1 = Ps[1] - Ps[0];
            v1 = v1 / (gcd(abs(v1.x), abs(v1.y)));
            Point<ll> v2 = Ps[0] - Ps[id];
            v2 = v2 / (gcd(abs(v2.x), abs(v2.y)));
//            if (fcmp(r1, r2) == 0 || (isinf(r1) && isinf(r2) && ((r1>0) == (r2 > 0)))){
            if(v1 == v2){
                Ps.erase(Ps.begin());
            }
        }
        N = Ps.size();

        ll mygcd = abs(Ps[0].x -Ps[1].x);
        for (int i = 0; i < N; i++)
        {
            int j = ni(i);
            mygcd = gcd(mygcd, abs(Ps[i].x - Ps[j].x));
            mygcd = gcd(mygcd, abs(Ps[i].y - Ps[j].y));
        }
        Polygon<ll> newP;
        newP.eb(Ps[0]);
        for (int i = 1; i < N; i++){
            Point<ll> direc = (Ps[i] - Ps[i - 1]) / mygcd;
            newP.eb(newP[i - 1] + direc);
        }
#ifdef DnewP
        cout << "Peset\n";
        for (int i = 0; i < N; i++)
        {
            cout << newP[i] << endl;
        }
        cout << "end\n";
#endif
        ll Area = 0;
        Point<ll> o(0, 0);
        for (int i = 0; i < N; i++)
        {
            int j = ni(i);
            Line<ll> L(o, newP[i]);
            Area += L.ori(newP[j]);
        }
    //    Area /= 2;
        if(Area < 0){
            Area = -(Area);
        }
        ll boundp = 0;
        for (int i = 0; i < N; i++){
            int j = ni(i);
            boundp += gcd(abs(newP[i].x - newP[j].x), abs(newP[i].y - newP[j].y));
        }
        ll ans = 0;
        for (int i = 1; i <= M; i++)
        {
            ll A = (Area);
            A *= i;
            A *= i;
            A /= 2;
            ll b = boundp;
            b *= i;
            #ifdef Dans
            debug(A);
            debug(b);
            debug((A - b / 2 + 1));
            #endif
            ll ask = (A - b / 2 + 1);
//            ans = ans + (A - b / 2 + 1);
            ans += ask;
#ifdef Dans
            debug(ans);
            #endif
        }
        ll ref = ans;
        cout << "Case " << caseN++ << ": " << ref << endl;
    }

    return 0;
}