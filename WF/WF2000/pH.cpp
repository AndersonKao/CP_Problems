#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using pdd = pair<double, double>;
#define MAXD 1e20
#define MIND -1 


//#define debuginnerP
//#define debugarrange
//#define debugout
//#define debugud

inline int prev(int i, int n) { return i == 0 ? n - 1 : i - 1; }
inline int next(int i, int n) { return i == n - 1 ? 0 : i + 1; }

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

void solve(double a, double b, double c, double *arr);
void Possi(vector<Point<double>> &Vertexs, vector<Point<double>> &centers, vector<pdd> &dias, Point<double> innerP);
bool valid(vector<Point<double>> &centers, vector<pdd> &dias);
bool solved;

int main(){
    int a, b, c;
    double arr[6];
    int cnt = 1;
    while(cin >> a >> b >> c){
        for (int i = 0; i < 6; i++){
            cin >> arr[i];
            arr[i] /= 2;
        }
        if(a == 0 && b == 0 && c == 0)
            break;
        solved = false;
        solve((double)a, (double)b, (double)c, arr);
        if(cnt != 1)
            cout << endl;
        cout << "Triangle number " << cnt++ << ":\n";
        if(solved)
            cout << "All three stoppers will fit in the triangular space\n";
        else
            cout << "Stoppers will not fit in the triangular space\n";
    }

    return 0;
}
void solve(double a, double b, double c, double *arr){
    // larger than maximum inscribed circle.
    //cout << "len " << a << ", " << b << ", " << c << endl;
    double s = (a + b + c) / 2;
    double Area= sqrt(s * (s - a) * (s - b) * (s - c)) ;
    double maxR = Area / (a + b + c) * 2;

    //cout << "maximum Diameter = " << maxR << endl;

    for (int i = 0; i < 6; i++){
        if(arr[i] > maxR){
            return;
        }
    }
    // formal
    //     pC
    //    /  \
    //  a/    \c  
    //  /      \
    //pA--------pB
    //     b
    vector<Point<double>> Vertexs(3);
    Vertexs[0] = Point<double>(0, 0);
    Vertexs[1] = Point<double>(b, 0);
    double h = 2 * Area / b;
    //cout << "h : " << h << endl;
    Vertexs[2] = Point<double>((a * a + b * b > c * c ? 1 : -1) * sqrt((double)a * a - h * h), h);
    double len[3] = {c, a, b};
    Point<double> innerP(0,0);
    for (int i = 0; i < 3; i++){
        innerP = innerP + Vertexs[i] * (double)len[i];
#ifdef debuginnerP
        cout << "vertex " << i << " at position " << Vertexs[i] << endl;
#endif
    }
    innerP = innerP / (double)(a + b + c);
#ifdef debuginnerP
    cout << "InnerP position: " << innerP << endl;
#endif

    vector<pdd> V; // diameter arrange;
    for (int i = 0; i < 6; i += 2){
        V.emplace_back(arr[i], arr[i + 1]);
    }
    sort(V.begin(), V.end());
    vector<Point<double>> centers;
    centers.resize(3);
    do{
        // get center by current permutation.
        for (int i = 0; i < 3; i++){
            Line<double> tmP(Vertexs[i], innerP);
            centers[i] = Vertexs[i] + tmP.vec() * (max(V[i].first, V[i].second) / maxR);
        }
#ifdef debugarrange
        cout << "new arrange ----------- \n";
        for (int i = 0; i < 3; i++){
            cout << "center " << i << " with dia = " << V[i].first << " or " << V[i].second << endl;
            cout << "at " << centers[i] << endl;
        }
#endif
        Possi(Vertexs, centers, V, innerP);
        if(solved)
            return;
    } while (next_permutation(V.begin(), V.end()));
#ifdef debugout
    cout << "not solved\n";
#endif

}
void Possi(vector<Point<double>> & Vertexs, vector<Point<double>> &centers, vector<pdd>& dias, Point<double> innerP){
    for (int i = 0; i < 8; i++){
        vector<pdd> diasecond(dias);
        for (int j = 0; j < 3; j++){
            if(i & (1 << j)){
                swap(diasecond[j].first, diasecond[j].second);
            }
        }

#ifdef debugud
        
        cout << "current up " << endl;
        for (int j = 0; j < 3; j++)
            cout << diasecond[j].first << ", ";
        cout << endl;
        cout << "current down  " << endl;
        for (int j = 0; j < 3; j++)
            cout << diasecond[j].second<< ", ";
        cout << endl;
#endif
        if(valid(centers, diasecond)){
            //cout << "valid for this set!!!-------\n";
            solved = true;
            return;
        }
    }
}

bool valid(vector<Point<double>>& centers, vector<pdd>&dias){
    // up
    for (int i = 0; i < 3; i++){
        int j = next(i, 3);
        Line<double> dis(centers[i], centers[j]);
        //cout << "st=" << dis.st << ", ed = " << dis.ed << endl;
        double tmp = dias[i].first + dias[j].first;
        if(dis.vec().norm() < tmp * tmp){
#ifdef debugnorm
            cout << "node " << i << " and node " << j << endl;
            cout << "dis.vec().norm() = " << dis.vec().norm() << ", availdis^2= " << tmp * tmp << endl;
#endif
            return false;
        }
        tmp = dias[i].second + dias[j].second;
        if(dis.vec().norm() < tmp * tmp){
#ifdef debugnorm
            cout << "node " << i << " and node " << j << endl;
            cout << "dis.vec().norm() = " << dis.vec().norm() << ", diameter^2= " << tmp * tmp << endl;
#endif
            return false;
        }
    }
   return true;
}