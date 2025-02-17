// WA
// need brute force check inconsistent
// since rotation and scale may be symmetric
// WA
// numeric_limits<double>::min causing error, idk why...
// WA
// init max should be dMIN...
// WA
// scale ans translation parameter has to be integer
#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
const int dINF = 100000;
const int dMIN = -100000;
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
        return fcmp((p1 - p3) ^ (p2 - p3), 0.0) == 0;
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
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << ": " << x << endl;
using pii = pair<int, int>;
#define F first
#define S second

#define mp make_pair
#define eb emplace_back 
vector<pair<pii, pii>> ANSs;
vector<int> mto(3);
vector<Point<int>> from(3), to(3);
template<typename T>
void PrintVec(vector<Point<T>>& Vs){
	for(int i = 0; i < 3; i++){
		cout << Vs[i] << ", ";
	}
	cout << endl;
}
void rotation(int rx, int ry, vector<Point<int>>& pts){
	double theta = -atan2(ry, rx);
	for(int i = 0; i < 3; i++){
		Point<double> pt(from[i].x * cos(theta) - from[i].y * sin(theta), from[i].x * sin(theta) + from[i].y * cos(theta));	
		pts[i] = Point<int>(round(pt.x), round(pt.y));
	}	
}
void transcale(vector<Point<int>>& pt, int rx, int ry){
	double xscale = 1.0, yscale = 1.0;
	int toxmax = dMIN, toxmin = dINF, toymax = dMIN, toymin = dINF;
	int ptxmax = dMIN, ptxmin = dINF, ptymax = dMIN, ptymin = dINF;
	for(int i = 0; i < 3; i++){
		ptxmax = max(ptxmax, pt[i].x);
		ptymax = max(ptymax, pt[i].y);
		ptxmin = min(ptxmin, pt[i].x);
		ptymin = min(ptymin, pt[i].y);
	}
	for(int i = 0; i < 3; i++){
		toxmax = max(toxmax, to[i].x);
		toymax = max(toymax, to[i].y);
		toxmin = min(toxmin, to[i].x);
		toymin = min(toymin, to[i].y);
	}
	int ptxoff = abs(ptxmax - ptxmin), ptyoff = abs(ptymax - ptymin);
	int toxoff = abs(toxmax - toxmin), toyoff = abs(toymax - toymin);
	
	if(ptxoff != 0 && toxoff != 0)
		xscale = toxoff / ptxoff;
	if(ptyoff != 0 && toyoff != 0)
		yscale = toyoff / ptyoff;
#ifdef Dmm
		debug(ptxmax);
		debug(ptxmin);
		debug(ptymax);
		debug(ptymin);
		debug(toxmax);
		debug(toxmin);
		debug(toymax);
		debug(toymin);
		debug(ptxoff);
		debug(ptyoff);
		debug(toxoff);
		debug(toyoff);
		debug(xscale);
		debug(yscale);
#endif
	for(int t = 0; t < 4; t++){
		int xs = ((t & 1) ? xscale : -xscale);
		int ys = ((t & 2) ? yscale : -yscale);
//		double xs = xscale, ys = yscale;
		vector<Point<int>> mpt(3);
		for(int i = 0; i < 3;i++)
			mpt[i] = Point<int>(pt[i].x * xs, pt[i].y * ys);
		Point<int> offset(to[mto[0]].x - mpt[0].x, to[mto[0]].y - mpt[0].y);
		for(int i = 0; i < 3;i++)
			mpt[i] = mpt[i] + offset;
#ifdef Dscale
		debug(xscale);
		debug(yscale);
#endif
#ifdef Dsame
		cout << "mpt: ";
		PrintVec(mpt);
		cout << "mto: ";
		for(int i = 0; i < 3; i++){
			cout << to[mto[i]] << ", ";
		}
		cout << endl;
#endif
		bool same = true;	
		for(int i = 0; i < 3; i++){
			if(fcmp(mpt[i].x, to[mto[i]].x) != 0){
				same = false; break;
			}
			if(fcmp(mpt[i].y, to[mto[i]].y) != 0){
				same = false; break;
			}
		}
		if(same){
#ifdef Dget
			cout << "getsol\n";			
			debug(offset);
			debug(xs);
			debug(ys);
			debug(rx);
			debug(ry);
#endif
			ANSs.eb(mp(xs, ys), mp(rx, ry));
		}
	}
}

void check(){
	for(int yi = 0; yi < 2; yi++){
		int ry = (yi == 0 ? 10 : -10);
		for(int rx = -10; rx <= 10; rx++){
			vector<Point<int>> rotated(3);	
			rotation(rx, ry, rotated);
#ifdef Drotate
			debug(rx);
			debug(ry);
			cout << "rotated: ";
			PrintVec(rotated);
#endif
			transcale(rotated, rx, ry);
		}
	}
	for(int xi = 0; xi < 2; xi++){
		int rx = (xi == 0 ? 10 : -10);
		for(int ry = -9; ry <= 9; ry++){
			vector<Point<int>> rotated(3);	
			rotation(rx, ry, rotated);
#ifdef Drotate
			debug(rx);
			debug(ry);
			cout << "rotated: ";
			PrintVec(rotated);
#endif
			transcale(rotated, rx, ry);
		}
	}
}

int main(){
	int caseN = 1;
	while(cin >> from[0] >> from[1] >> from[2]){
		bool allzero = true;
		for(int i = 0; i < 3; i++){
			if(from[i].x != 0 || from[i].y != 0){
				allzero = false;
				break;
			}
		}
		if(allzero)
			break;
		for(int i = 0; i < 3; i++){
			cin >> to[i];
			mto[i] = i;
		}
#ifdef Dinput
		cout << "from: ";
		PrintVec(from);
		cout << "to : ";
		PrintVec(to);
#endif
		ANSs.clear();
		do{
			#ifdef Dtry
			cout << "trying : ";
			for(int i = 0 ;i < 3; i++)
				cout << i << " to " << mto[i] << ", ";
			cout << endl;
#endif
			check();
		}while(next_permutation(al(mto)));
		vector<bool> valid(ANSs.size(), true);
		for(int i = 0; i < ANSs.size(); i++){
			if(valid[i] == false) continue;
			for(int j = i; j < ANSs.size(); j++){
				if(ANSs[i].F.F + ANSs[j].F.F == 0 &&
					ANSs[i].F.S + ANSs[j].F.S == 0 &&
					ANSs[i].S.F + ANSs[j].S.F == 0 &&
					ANSs[i].S.S + ANSs[j].S.S == 0){
					valid[j] = false;
				}
			}
		}
		int sol = 0;
		for(int i = 0; i < valid.size(); i++){
			if(valid[i]) sol++;
		}

		cout<< "Case " << caseN++ << ": ";
		if(sol == 1){
			cout << "equivalent solutions";
		}
		else if(sol > 1){
			cout << "inconsistent solutions";
		}
		else
			cout << "no solution";
		cout << endl;
	}
	return 0;
}
