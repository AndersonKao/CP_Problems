// AC 2022-02-25 01:15:50
// Correct BF version A*sin(alpha)*B*sin(1/2pi+C-alpha)
// refer https://blog.csdn.net/Fuxey/article/details/50410233
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define MAXD 1e20
#define MIND -1 
const double eps = 1e-10;

const int INSIDE = -1;
const int BOUNDARY = 0;
const int OUTSIDE = 1;
int dcmp(double a) { return fabs(a) < eps ? 0 : (a < 0 ? -1 : 1); };
inline int prev(int i, int n) { return i == 0 ? n - 1 : i - 1; }
inline int next(int i, int n) { return i == n - 1 ? 0 : i + 1; }
#define rad2A(a) (a / M_PI * 180.0)
template <class T> inline int sgn(const T& x){
    return (T(0) < x) - (x < T(0));
}

template <typename T, typename Real = double>
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
    // 內 積 運 算 子
    T operator^(const Point b) const { return x * b.y - y * b.x; }
    // 外 積 運 算 子
    bool operator==(const Point b) const
    {
        return x == b.x and y == b.y;
    }
    bool operator!=(const Point b) const
    {
        return x != b.x or y != b.y;
    }
    bool operator<(const Point b) const
    {
        return x == b.x ? y < b.y : x < b.x;
    } // 字 典 序
    Real Angle(){
        return atan2(y, x);
    }
    Real turnAngle(const Point L2){
        return atan2((*this) ^ L2, (*this) & L2);
    }
    Point Rotate(double rad){
        return Point(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
    }

    Point operator-() const { return Point(-x, -y); }
    T norm() const { return *this & *this; }    // 歐 式 長 度 平 方
    Point prep() const { return Point(-y, x); } // 左 旋 直 角 法 向 量
    

    template <class F>
    friend istream &operator>>(istream &is, Point<F> &pt);
    template<class F>
    friend ostream &operator<<(ostream &os, const Point<F> &pt);
};
using Vector = Point<double>;
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

template <typename T, typename Real = double>
struct Line
{
    Point<T> st, ed;
    Point<T> vec() const { return ed - st; }
    T ori(const Point<T> p) const { return (ed - st) ^ (p - st); }
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
    template<class F> 
    Line(const Point<F> x, const Point<F> y) {
        st = Point<T>(x);
        ed = Point<T>(y);
    }
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

    bool isPointOnSegProperly(const Point<T> p) const
    {
        return ori(p) == 0 and ((st - p) & (ed - p)) < 0;
    }
    Real disP2Line(const Point<T> p) const
    {
        return Line<double>(projection(p), Point<double>(p)).vec().norm();
    }

    Point<Real> getIntersection(const Line<Real> l)
    {
        Line<Real> h = *this;
        return l((l.st ^ h.vec()) / (h.vec() ^ l.vec())); // use operator()
    }

    Point<Real> projection(const Point<T> p) const
    {
        return operator()(((p - st) & vec()) / (Real)(vec().norm()));
    }
  

};
template <class F>
using Polygon = vector<Point<F>>;

template <class F>
Polygon<F> getConvexHull(Polygon <F> points) {
    sort(points.begin(), points.end());
    Polygon<F> CH;
    CH.reserve(points.size() + 1); // for what ??
    for (int round = 0; round < 2; round++){
        int start = CH.size();
        for (Point<F> &pt: points) {
            while (CH.size() - start >= 2 && Line<F>(CH[CH.size() - 2], CH[CH.size() - 1]).ori(pt) <= 0) // ? Line is different than senpai's .
            {
                CH.pop_back();
            }
            CH.emplace_back(pt);
        }
        CH.pop_back();
        
        reverse(points.begin(), points.end());
    }
    if (CH.size() == 2 && CH[0] == CH[1])
        CH.pop_back();
    return CH;
}

double getAreabyAlpha(Polygon<LL>&hull, int vu, int vd, int vl, int vr, double Rad, double C){
    return sqrt(Vector(hull[vu] - hull[vd]).norm() * Vector(hull[vl] - hull[vr]).norm()) * sin(Rad) * (sin(M_PI / 2 + C - Rad));
}
void solve(int n){
    Polygon<long long> P;
    long long x, y;
    for (int i = 0; i < n; i++){
        cin >> x >> y;
        P.emplace_back(x, y);
    }
    Polygon<long long> hull = getConvexHull(P);
    int H = hull.size();
    double maxA = MIND, minA = MAXD, tmp;
    double Minx = hull[0].x, Miny = hull[0].y, Maxx = hull[0].x, Maxy = hull[0].y;
    int vu, vd, vr, vl;
    vu = vd = vr = vl = 0;
    Vector v1(1.0, 0.0);
    Vector v2(0.0, 1.0);

    Vector ori(v1);
    
    for(int i = 0; i < hull.size(); i++){
        if(Minx > hull[i].x){
            Minx = hull[i].x;
            vl = i;
        }else if(Miny > hull[i].y){
            Miny = hull[i].y;
            vd = i;
        }else if(Maxx < hull[i].x){
            Maxx = hull[i].x;
            vr = i;
        }else if(Maxy < hull[i].y){
            Maxy = hull[i].y;
            vu = i;
        }
    }
    
    while(dcmp((ori^v1) >= 0)){ // 線還沒有轉回到原本的線
        // 找到本次最小可以旋轉的角度
        double MinRad = MAXD;
        MinRad = min(MinRad,v1.turnAngle(Vector(hull[next(vd, H)] - hull[vd])));
        MinRad = min(MinRad,(-v1).turnAngle(Vector(hull[next(vu, H)] - hull[vu])));
        MinRad = min(MinRad,v2.turnAngle(Vector(hull[next(vr, H)] - hull[vr])));
        MinRad = min(MinRad, (-v2).turnAngle(Vector(hull[next(vl, H)] - hull[vl])));
        // 找到逆時針最小可以旋轉的角度
        double LMinRad = MAXD;
        LMinRad = min(LMinRad, Vector( hull[prev(vd, H)] - hull[vd]).turnAngle(-v1));
        LMinRad = min( LMinRad, (Vector(hull[prev(vu, H)]- hull[vu])).turnAngle(v1));
        LMinRad = min( LMinRad, (Vector(hull[prev(vr, H)]- hull[vr])).turnAngle(-v2));
        LMinRad = min(LMinRad, (Vector(hull[prev(vl, H)]- hull[vl])).turnAngle(v2));
        // Rad C
        double CRad = Vector(hull[vr] - hull[vl]).turnAngle(Vector(hull[vu] - hull[vd]));

        double MaxAreaRad = (M_PI / 2 + CRad)/2;
        double alpha = v1.turnAngle(Vector(hull[vu] - hull[vd]));

        double maxAlpha = (alpha + LMinRad);
        double minAlpha = alpha - MinRad;

        // renew min Answer
        minA = min(minA, getAreabyAlpha(hull, vu, vd, vl, vr, minAlpha, CRad));
        minA = min(minA, getAreabyAlpha(hull, vu, vd, vl, vr, maxAlpha, CRad));
        // renew max Answer
        if(dcmp(MaxAreaRad - maxAlpha) == -1 && dcmp(MaxAreaRad - minAlpha) == 1){
            maxA = max(maxA, getAreabyAlpha(hull, vu, vd, vl, vr, MaxAreaRad, CRad));
        }else{
            maxA = max(maxA, getAreabyAlpha(hull, vu, vd, vl, vr, minAlpha, CRad));
            maxA = max(maxA, getAreabyAlpha(hull, vu, vd, vl, vr, maxAlpha, CRad));
        }
        // renew edge by MinRad
        v1 = v1.Rotate(MinRad);
        v2 = v2.Rotate(MinRad);

        // 更新四點
        if( dcmp(v1.turnAngle(Point<double>(hull[next(vd, H)] - hull[vd]))) == 0)           vd = next(vd, H);
        if( dcmp((-v1).turnAngle(Point<double>(hull[next(vu, H)] - hull[vu]))) == 0) vu = next(vu, H);
        if( dcmp(v2.turnAngle(Point<double>(hull[next(vr, H)] - hull[vr]))) == 0) vr = next(vr, H);
        if( dcmp((-v2).turnAngle(Point<double>(hull[next(vl, H)] - hull[vl]))) == 0) vl = next(vl, H);
    }

    cout << "Minimum area = " << (minA) << endl;
    cout << "Maximum area = " << (maxA) << endl;
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int n;
    cout << fixed << setprecision(3);
    int cnt = 1;
    while(cin >> n){
        if(n == 0)
            break;
        cout << "Gift " << cnt++ << endl;
        solve(n);
        cout << endl;
    }
    return 0;
}