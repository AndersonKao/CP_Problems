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
        if(std::is_integral<T>::value)
            return x == b.x and y == b.y;
        return fcmp(x, b.x) == 0 && fcmp(y, b.y) == 0;
    }
    bool operator<(const Point b) const
    {
        if(std::is_integral<T>::value)
            return x == b.x ? y < b.y : x < b.x;
        return fcmp(x, b.x) == 0 ? (fcmp(y, b.y)) < 0 : (fcmp(x, b.x) < 0);
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
    return os << "(" << pt.x << " " << pt.y << ")";
}
template <class F>
istream &operator>>(istream &is, Point<F> &pt)
{
    return is >> pt.x >> pt.y;
}
template <class F>
bool collinearity(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    if(std::is_integral<F>::value)
        return (p1 - p3) ^ (p2 - p3) == 0;
    return fcmp((p1 - p3) ^ (p2 - p3), 0.0) == 0;
}
// check co-line first. properly
template<class F>
inline bool btw(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3){
    if(std::is_integral<F>::value)
        return ((p1 - p3) & (p2 - p3)) <= 0;
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
	Line(T x1, T y1, T x2, T y2) :st(x1, y1), ed(x2, y2){}
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
#define debug(x) cout << #x << ": " << x << endl;
double getY(const Line<double>& L, double x){
	if(fcmp(x, L.st.x) == 0)
		return L.st.y;
	else if(fcmp(x, L.ed.x) == 0)
		return L.ed.y;
	double offset = x - L.st.x;
/*
	cout << "getY:\n";
	debug(x);
	cout << L << endl;
	debug(offset);
	debug(L.vec().y);
	debug(L.vec().x);
*/
	return L.st.y + L.vec().y * (offset / L.vec().x);
}
#define eb emplace_back
int main(){	
	int N;
	int caseN = 1;
	while(cin >> N){
		if(N == 0)
			break;
		vector<Line<double>> segs;
		vector<double> onlyX;
		for(int i = 0; i < N; i++){
			double X, H, B;
			cin >> X >> H >> B;
			segs.eb(X-B/2.0, 0.0, X, H);
			segs.eb(X, H, X+B/2.0 ,0.0);
			onlyX.eb(X-B/2.0);
			onlyX.eb(X);
			onlyX.eb(X+B/2.0);
		}
		int Lsize = segs.size();
		for(int i = 0; i < Lsize; i++){
			for(int j = i + 1; j < Lsize; j++){
				if(segs[i].isSegProperIntersection(segs[j])){
					onlyX.eb(segs[i].getIntersection(segs[j]).x);
				}
			}
		}
		auto doublePred = [](double a, double b){
			return fcmp(a, b) == 0;
		};
		sort(onlyX.begin(), onlyX.end());
		onlyX.resize(distance(onlyX.begin(), unique(onlyX.begin(), onlyX.end(), doublePred)));
		double ans = 0.0;
		for(int i = 0; i < onlyX.size() - 1; i++){
			double lx = onlyX[i], rx = onlyX[i+1];
			double toply = 0.0, topry = 0.0;
			double midy = 0.0;
			for(int i = 0; i < segs.size();i++){
				if(fcmp(lx, segs[i].ed.x) >= 0 || fcmp(rx, segs[i].st.x) <= 0)
					continue;
				double ly = getY(segs[i], lx), ry = getY(segs[i], rx);
				if(fcmp((ly + ry) / 2.0, midy) >= 0)	{
					toply = ly, topry = ry, midy = (ly+ry)/2.0;
				}
			}
			if(fcmp(midy, 0.0) > 0){
				double xoff = abs(rx - lx), yoff = abs(topry - toply);		
				ans+= (sqrt(xoff *xoff+yoff*yoff));
			}
		}	
		cout << "Case " << caseN++ << ": " << (int)round(ans) << endl << endl;
	}	
	
	return 0;
}
