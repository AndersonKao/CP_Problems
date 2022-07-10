// AC 
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define debug(x) cout << #x << ":= " << x << endl;
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
    return os << "(" << pt.x << " " << pt.y << ") ";
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
        return (fcmp(a, 0.0)); // 1 on posi-side // -1 nega-side
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

    bool isSegProperIntersection(const Line ol) const
    {
        Line<Real> l(ol);
        return l.ori(st) * l.ori(ed) < 0 and ori(l.st) * ori(l.ed) < 0;
    }
    bool isSegIntersection(const Line ol)const{
        Line<Real> h = *this;
        Line<Real> l(ol);
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
#define REP(i, n) for (int i = 0; i < (int)n; i++)
template <typename T>
using vec = vector<T>;
#define eb emplace_back
int N;
const double disINF = numeric_limits<double>::infinity();
inline int nexti(int i, int size = N)
{
    return (i + 1 >= size ? 0 : i + 1);
}
inline int previ(int i, int size = N){
    return (i - 1 >= 0 ? i - 1 : size-1);
}

void addEdge(int pi, int pj, vec<vec<double>>&G, Polygon<int>& pts){
    //for (int pi = 0; pi < N; pi++){
    Line<int> L1(pts[previ(pi)], pts[pi]);
    Line<int> L2(pts[pi], pts[nexti(pi)]);
    bool convex = (L1.orint(pts[nexti(pi)]) >= 0);
    #ifdef Daddedge
    cout << "try add edge (" << pi << ", " << pj << ")\n";
    cout << pts[pi] << pts[pj] << endl;
    cout << "L1: " <<  L1 << "L2: " << L2 << endl;
    #endif
    int ori1 = L1.orint(pts[pj]);
    int ori2 = L2.orint(pts[pj]);
    if(convex){
        if(ori1 > 0 && ori2 > 0)
            return;
    }
    else {
        if(ori1 > 0 || ori2 > 0)
            return;
    }
    /*
    if (L1.orint(pts[pj]) >= 0 && L2.orint(pts[pj]) >= 0) // this is wrong
    {
        return;
    }
    */
        Line<int> L3(pts[pi], pts[pj]);
        bool makeit = true;
        for (int pi2 = 0; pi2 < N; pi2++){
            int pj2 = nexti(pi2);
            if (pi2 == pi || pi2 == pj || pj2 == pi || pj2 == pj){
                continue;
            }
            Line<int> L4(pts[pi2], pts[pj2]);
            if (L3.isSegIntersection(L4)){
                makeit = false;
                break;
            }
        }
        if(makeit){
            #ifdef Daddedge
            cout << "added edge (" << pi << ", " << pj << ")\n";
            cout << pts[pi] << pts[pj] << endl;
            #endif
            double dis = sqrt((pts[pi] - pts[pj]).norm());
            G[pi][pj] = dis;
            G[pj][pi] = dis;
        }
    //}
}
void delEdge(int pi, int pj, vec<vec<double>>&G){
    G[pi][pj] = G[pj][pi] = disINF;
}
Point<double> simulate(int Lv, Polygon<int>& pts, double t, vec<vec<double>>& G, int &lpi, int&rpi){
    double walklen = Lv * t;

    int cur = 0;
    while (fcmp(walklen, 0.0) > 0)
    {
        double dis = sqrt((pts[cur] - pts[nexti(cur)]).norm());
        walklen -= dis;
        cur = nexti(cur);
    }
    int pre = previ(cur);
    Point<double> v1(pts[cur] - pts[pre]);
    double len = sqrt(v1.norm());
    Point<double> ans = Point<double>(pts[cur]) + v1 *(walklen / len);
    lpi = pre;
    rpi = cur;

    G[N + 1][cur] = G[cur][N + 1] = sqrt((ans - Point<double>(pts[cur])).norm());
    G[N + 1][pre] = G[pre][N + 1] = sqrt((ans - Point<double>(pts[pre])).norm());

    return ans;
}
int main()
{
    int caseN = 1;
    const int T = 1000;
    while (cin >> N)
    {
        if(N == 0)
            break;
        Polygon<int> pts(N+1);
        double perimeter = 0.0;
        REP(i, N)
        {
            cin >> pts[i];
        }
        REP(i, N){
            perimeter += sqrt((pts[i] - pts[nexti(i)]).norm());
        }
        #ifdef Ddebug
        debug(perimeter);
        #endif
        cin >> pts[N]; // person
        int Lspeed, Pspeed;
        cin >> Lspeed >> Pspeed;
        vec<vec<double>> G(N + 2, vec<double>(N + 2, disINF)); // N for Person, N+1 for Luggage.

        for (int pi = 0; pi < N; pi++){
            for (int pj = pi+1; pj < N; pj++){
                addEdge(pi, pj, G, pts);
            }
            addEdge(pi, N, G, pts);
            G[nexti(pi)][pi] =G[pi][nexti(pi)] = sqrt((pts[pi] - pts[nexti(pi)]).norm());
        }
        #ifdef Dg
        for (int i = 0; i < N + 2; i++){
            for (int j = 0; j < N + 2; j++){
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
        #endif

            double L = 0.0; // TBD
        double R = 0.0;
        REP(i, N){
            if(G[N][i] != disINF)
                R = max(R, G[N][i] / Pspeed);
        }
        REP(i, N+2)
            G[i][i] = 0.0;
        R += (perimeter / Lspeed);
        R *= 2;
        REP(times, T)
        {
            double M = (L + R) / 2.0;
            int lpi, rpi;
            Point<double> luggage = simulate(Lspeed, pts, M, G, lpi, rpi);
            #ifdef Dluggage
            cout << "luggage: " << luggage << endl;
            #endif
            for (int pi = 0; pi <= N; pi++){
                if (pi == lpi || pi == rpi) // already connected;
                    continue;
                Point<double> pti(pts[pi]);
                if(pi != N){
                    Point<double> prevti(pts[previ(pi)]);
                    Point<double> nextti(pts[nexti(pi)]);
                    Line<double> L1(prevti, pti);
                    Line<double> L2(pti, nextti);
                    bool convex = (L1.orint(nextti) >= 0);
                    int ori1 = L1.orint(luggage);
                    int ori2 = L2.orint(luggage);
                    if(convex){
                        if(ori1 > 0 && ori2 > 0)
                            continue;;
                    }
                    else {
                        if(ori1 > 0 || ori2 > 0)
                            continue;;
                    }
                }
                Line<double> L3(pti, luggage);
                bool makeit = true;
                for (int pi2 = 0; pi2 < N; pi2++){
                    int pj2 = nexti(pi2);
                    if (pi2 == pi || pj2 == pi || (pi2 == lpi && pj2 == rpi)){
                        continue;
                    }
                    Line<double> L4 = Line<double>(Point<double>(pts[pi2]), Point<double>(pts[pj2]));
                    if (L3.isSegIntersection(L4))
                    {
                        makeit = false;
                        break;
                    }
                }
                if(makeit){
                    double dis = sqrt((pti - luggage).norm());
                    G[pi][N+1] = dis;
                    G[N+1][pi] = dis;
                }
            }
            #ifdef Dluggage
            cout << "add G to :\n ";
            for (int i = 0; i < N + 2; i++)
            {
                cout << G[N + 1][i] << " ";
            }
            cout << endl;
            #endif
            vec<double> distoN(N + 2, disINF);
            priority_queue<pair<double, int>, vec<pair<double, int>>, greater<pair<double, int>>> Q;
            Q.emplace(distoN[N] = 0.0, N);
            while(Q.size()){
                double dis, u;
                tie(dis, u) = Q.top();
                Q.pop();
                if (fcmp(dis, distoN[u]) != 0)
                    continue;
                for (int v = 0; v < N + 2; v++){
                    if(G[u][v] == disINF){
                        continue;
                    }
                    if(fcmp(distoN[v], dis + G[u][v]) > 0){
                        Q.emplace(distoN[v] = dis + G[u][v], v);
                    }
                }
            }
            #ifdef Dluggage
            debug(distoN[N + 1]);
            #endif
            double matchT = distoN[N + 1] / Pspeed;
            if(fcmp(matchT, M) <= 0){
                R = M;
            }
            else{
                L = M;
            }
            for (int i = 0; i < N + 1; i++){
                G[i][N + 1] = G[N + 1][i] = disINF;
            }
            #ifdef Dluggage
            debug(L);
            debug(R);
            #endif
        };
        cout << "Case " << caseN++ << ": Time = ";
        cout << setw(1) << (ll)(R + 0.001) << ":" << setw(2) << setfill('0') << ((ll)(round(R * 60))) % 60 << endl;
    }
    return 0;
}