// next_permutation return boolean.
// if want descreasing, remember to put compare function
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
vector<double> rs(4);
vector<Point<double>> center(4);
Point<double> get(double r1, double M, double& theta){
	double a = M - rs[0];	
	double b = M - r1;
	double c = rs[0] + r1;
	theta = acos((a*a + b*b - c*c) / (a*b * 2));
	// c^2 = a ^2 + b^2 - 2abcos(theta).
	return Point<double>(b * sin(theta), -b * cos(theta));
}
bool verify(){
	for(int i = 0; i < 4; i++){
		for(int j = i + 1; j < 4; j++){
			double dis2 = (center[i] - center[j]).norm();
			double R = rs[i] + rs[j];
			if(fcmp(dis2, R*R) < 0)
				return false; 
		}
	}
	return true;
}
bool test(double M){
	if(fcmp(M, rs[0]) <= 0)
		return false;
	center[0] = Point<double>(0.0, -(M-rs[0]));
		
	double t1;
	for(int i = 1; i <= 2; i++)
		center[i] = get(rs[i], M, t1);
	center[2].x = -center[2].x;
	double a = M - rs[2];
	double b = M - rs[3];
	double c = rs[2] + rs[3];
	double theta3 = acos((a*a + b*b - c*c) / (a*b * 2));
	theta3 += t1;
	//theta3 = max(theta0, theta3);
	center[3] = Point<double>(-b*sin(theta3), -b*cos(theta3));
#ifdef Dpt
	for(int i = 0; i < 4; i++){
		cout << i << ": " << center[i] << endl;
	}
#endif
	if(verify())
		return true;
	a = M - rs[0];
	c = rs[0] + rs[3];
	theta3 = acos((a*a + b*b - c*c) / (a*b * 2));
	center[3] = Point<double>(-b*sin(theta3), -b*cos(theta3));
	if(verify())
		return true;
	center[3] = Point<double>(b*sin(theta3), -b*cos(theta3));
	
	return verify();

	
	
}

int main(){
	int caseN = 1;
	while(cin >> rs[0]){
		if(fcmp(rs[0], 0.0) == 0)
			break;	
		for(int i = 1; i < 4; i++)
			cin >> rs[i];
		sort(rs.begin(), rs.end(), greater<double>());
		double L = 0.0, R = 100000.0;					
		while(abs(R-L) > eps){
			double M = (L+ R)/2;
//			debug(M);
			bool sol = false;
			do{
				sol = test(M);
				if(sol)	
					break;
			}while(next_permutation(rs.begin()+1, rs.end(),greater<double>()) && sol == false);
			if(sol){
				R = M;
			}
			else{
				L = M;
			}
		}
		R += eps;
		cout << "Case " << caseN++ << ": ";
		cout << (int)(round(R)) << endl;

	}	
	return 0;
}
