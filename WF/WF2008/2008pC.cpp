// WA
// less than d
#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ": " << x <<endl;
#define eb emplace_back
const double PI = M_PI;
int N;
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
inline double adjTheta(double a){
	// op = 0 for add , op = 1 for sub;
	if(fcmp(a, PI) > 0)
		a = -PI + (a - PI);
	else if(fcmp(a, -PI) < 0)
		a = PI + (a + PI);
	return a;
}

struct shaft{
	Point<double> pt;
	double r;
	double inTheta, outTheta;
	int turning; // 0 for clockwise, 1 for counterclockwise
	shaft():pt(0,0), r(0), inTheta(0.0), outTheta(0.0), turning(0){}	
	friend ostream& operator<<(ostream& os, shaft& st);
	bool validTheta(){ // unused
		return true;
	}
	double getParameter(){
		double radius;
		if(turning == 0){
			radius = abs(inTheta -outTheta);
			if(fcmp(outTheta, inTheta) > 0){
				radius = 2 * PI - radius;
			}
		}
		else{
			radius = abs(outTheta - inTheta);
			if(fcmp(inTheta, outTheta) > 0){
				radius = 2 * PI - radius;
			}
		}
		return r * radius;
	}
	Line<double> connectLine(shaft& s2){
		double dis = ((s2.pt - pt).norm());
		double roff;
		double theta1, theta2, len;
		theta1 = atan2(s2.pt.y - pt.y,s2.pt.x - pt.x);
		if(turning == s2.turning)
			roff = abs(r - s2.r);
		else
			roff = abs(r + s2.r);
		len = sqrt(dis- roff*roff); 
		theta2 = atan(roff / len);
		int rcmp = fcmp(r, s2.r);		
		int tcase = (turning << 1) + s2.turning;
/*
		if(rcmp == 0){
			debug(theta2);
		}
*/
		if(tcase == 0){
			if(rcmp >= 0){ // 0????
				this->outTheta = s2.inTheta = adjTheta(theta1+(PI/2 - theta2));	
			}else{
				this->outTheta = s2.inTheta = adjTheta(theta1+(PI/2 + theta2));	
			}
		}
		else if(tcase == 3){
			if(rcmp >= 0){ // 0????
				this->outTheta = s2.inTheta = adjTheta(theta1-(PI/2 - theta2));	
			}else{
				this->outTheta = s2.inTheta = adjTheta(theta1-(PI/2 + theta2));	
			}
		}
		else if(tcase == 1){
			this->outTheta = adjTheta(theta1 + (PI/2 - theta2));
			s2.inTheta = adjTheta(theta1 - (PI/2 + theta2));
		}
		else { // tcase == 3
			this->outTheta = adjTheta(theta1 - (PI/2 - theta2));
			s2.inTheta = adjTheta(theta1 + (PI/2 + theta2));
		}
		Point<double> st(pt.x + r * cos(this->outTheta), pt.y + r * sin(this->outTheta));
		Point<double> ed(s2.pt.x + s2.r * cos(s2.inTheta), s2.pt.y + s2.r * sin(s2.inTheta));
		return Line<double>(st, ed);
	}	
	bool LineIntersection(Line<double> &L){
		return (fcmp((L.disP2Line(pt)), r*r) <= 0) && L.isPointOnSeg(L.projection(pt));
	}
};
ostream& operator<<(ostream& os, shaft& st){
	return (os << st.pt << " r " << st.r << ", turn: " << st.turning  << " in " << st.inTheta / PI * 180 << " out " << st.outTheta / PI * 180);
}
bool sol = false;
vector<bool> used;
vector<shaft> shafts(N);
vector<Line<double>> lines;
int stShaft ,edShaft;	
double maxd;
double ANS;
void DFS(int cur, double curlen){
//	cout << "visiteding " << cur << endl;
	if(cur == edShaft){
		sol = true;	
		ANS = min(ANS, curlen);
		return ;
	}
	for(int i = 0; i < N; i++){
		if(used[i])
			continue;
//		cout << "try " << i << endl;
		bool makeit = true;
		Line<double> newL = shafts[cur].connectLine(shafts[i]);		
		double newLen = (newL.vec().norm());
		if(fcmp(newLen, maxd*maxd) >=0){
//			cout << "fail Length\n";
			continue;
		}
		for(Line<double> &L : lines){
			if(newL.isSegProperIntersection(L)){
				makeit = false;
//				cout << "fail Line Intersection to " << L << endl;	
				break;
			}
		}
		if(makeit == false)
			continue;
		for(int j = 0; j < N; j++){
			if(j == cur || j == i)
				continue;
			if(shafts[j].LineIntersection(newL)){
				makeit = false;
//				cout << "fail Shaft Intersection to " << j << endl;	
				break;
			}
		}
		if(makeit){
			used[i] = true;
			lines.eb(newL);
			if(cur == stShaft)
				DFS(i, curlen + sqrt(newLen));
			else
				DFS(i, curlen + shafts[cur].getParameter() + sqrt(newLen));
			used[i] = false;
			lines.pop_back();
		}
	}	
}
int main(){
	int caseN = 1;
	while(cin >> N){
		if(N == 0)
			break;
		sol = false;
		ANS = numeric_limits<double>::max();
		used.clear();
		used.resize(N, false);
		shafts.clear();	
		shafts.resize(N);
		lines.clear();
		for(int i = 0; i < N; i++){
			cin >> shafts[i].pt >> shafts[i].r;
			string str;
			cin >> str;
			if(str == "C")
				shafts[i].turning = 0;
			else
				shafts[i].turning = 1;
		}
		cin >> stShaft >> edShaft >> maxd;
		used[stShaft] = true;
		DFS(stShaft, 0.0);
		cout << "Case " << caseN++ << ": ";
		if(sol){
			cout << "length = " << round(ANS*100)/100 << endl;
		}
		else{
			cout << "Cannot reach destination shaft\n";
		}
		/* testing sample input 1
		double testans = 0.0;	
		lines.eb(shafts[0].connectLine(shafts[1]));
		lines.eb(shafts[1].connectLine(shafts[2]));
		lines.eb(shafts[2].connectLine(shafts[3]));
		for(int i = 0; i < lines.size(); i++){
			cout << lines[i] << endl;
			testans += sqrt(lines[i].vec().norm());
			debug(sqrt(lines[i].vec().norm()));
			debug(testans);
		}
		for(int i =0 ; i < N; i++){
			cout << shafts[i] << endl;
		}
		for(int i = 1; i <= 2; i++){
			}
			debug(testans);
		}
		*/
//		debug(round(testans * 100) / 100);
	
	}
	return 0;
}
