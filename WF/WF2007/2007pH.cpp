#include<bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ":= " << x << endl;
const double eps = 1e-6;
using ll = long long;
inline int fcmp(const double &a, const double &b)
{
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
        return fcmp(x, b.x) == 0 ? (fcmp(y, b.y) < 0) : (fcmp(x, b.x) < 0);
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
	Line(){};
    Line(const Point<T> x, const Point<T> y) : st(x), ed(y) {}
    Line(const T x1,const T y1,const T x2, const T y2) : st(x1, y1), ed(x2, y2) {}
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
        return fcmp(l.ori(st) * l.ori(ed), 0.0) < 0 and fcmp(ori(l.st) * ori(l.ed), 0.0) < 0;
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
struct Point3D{
	ll x, y, z;
	Point3D():x(0), y(0), z(0){}
	Point3D(int x, int y, int z):x(x), y(y), z(z){}
	Point3D operator-(Point3D& a){
		return Point3D(x - a.x, y - a.y, z - a.z);
	}
	Point3D operator+(Point3D& a){
		return Point3D(x + a.x, y + a.y, z + a.z);
	}
	Point3D operator^(Point3D& v2){
		ll a = y * v2.z - v2.y * z;
		ll b = z * v2.x - v2.z * x;
		ll c = x * v2.y - v2.x * y;
		return Point3D(a, b, c);
	}
	friend ostream& operator<<(ostream&os, Point3D&a);
};
ostream& operator<<(ostream&os, Point3D&a){
	return os << "(" << a.x << ", " << a.y << ", " << a.z << ")";
}
vector<Point3D> pts3d;
vector<vector<int>> triangles;
struct Plane3D
{
	Point3D v1, v2;
	Point3D st;
	Plane3D(){}
	Plane3D(Point3D& a, Point3D &b, Point3D &c){
		st = a;	
		v1 = b - a;
		v2 = c - a;
	}
	double getz(double x, double y){
		x -= st.x;	
		y -= st.y;
		double t1 = (x * v2.y - y * v2.x) / (v1.x * v2.y - v1.y * v2.x);
		double t2 = (x * v1.y - y * v1.x) / (v2.x * v1.y - v2.y * v1.x);
		double t12 = (y * v2.x - x * v2.y) / (v2.x * v1.y - v1.x * v2.y);
		double t22 = (y * v1.x - x * v1.y) / (v1.x * v2.y - v2.x * v1.y);
		/*
				if(fcmp(t1 ,t12) != 0){
					cout << "gentaz\n";
					cout << v1 << ", " << v2 << endl;
					cout << x << ", " << y << endl;
					debug(t1);
					debug(t12);
				}
				if(fcmp(t2 ,t22) != 0){
					cout << "gentaz\n";
					cout << v1 << ", " << v2 << endl;
					cout << x << ", " << y << endl;
					debug(t2);
					debug(t22);
				}
		*/
		if(isnan(t1))
			t1 = t12;
		if(isnan(t2))
			t2 = t22;
		return st.z + v1.z * t1 + v2.z * t2;
	}
	double get2Area(){
		// get 2 * Area
		ll a = (ll)v1.y * v2.z - v1.z * v2.y;
		ll b = (ll)v1.z * v2.x - v1.x * v2.z;
		ll c = (ll)v1.x * v2.y - v1.y * v2.x;
		return sqrt(a * a + b * b + c * c);
	}
};
template <typename T>
using vec = vector<T>;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define eb emplace_back
#define al(x) x.begin(), x.end()
int Vn, Tn;
inline int nti(int i, int n = Vn){ // next i
	return (i + 1 == n ? 0 : i + 1);
}
inline int pvi(int i, int n = Vn){ // prev i
	return (i == 0 ? n-1 : i - 1);
}
auto doublePred = [](double a, double b){
	return fcmp(a, b) == 0;
};

void fillIntersection(vec<double>& onlyX, vec<vec<int>>& triangles, vec<Point3D>& pts3d){
	REP(ti, Tn){
		REP(tj, Tn){
			REP(tipi, 3){
				int tif, tit;
				tif = triangles[ti][tipi];	
				tit = triangles[ti][nti(tipi,3)];
				Line<double> L1(pts3d[tif].x, pts3d[tif].y, pts3d[tit].x, pts3d[tit].y);
				REP(tjpi, 3){
					int tjf, tjt;
					tjf = triangles[tj][tjpi];	
					tjt = triangles[tj][nti(tjpi,3)];
					if((tif == tjf && tit == tjt) || (tif == tjt && tit == tjf))
						continue;		
					Line<double> L2(pts3d[tjf].x, pts3d[tjf].y, pts3d[tjt].x, pts3d[tjt].y);
					if(L1.isSegProperIntersection(L2)){
						Point<double> inter= L1.getIntersection(L2);
						onlyX.eb(inter.x);
					}
				}
			}			
		}
	}					
}
vec<Plane3D> triplanes;
Point<double> heapify_parameter;
int heapstatus;
auto myheapify = [](int a, int b)
{
	if(a == b)
		return false;
	double z1 = triplanes[a].getz(heapify_parameter.x, heapify_parameter.y);
	double z2 = triplanes[b].getz(heapify_parameter.x, heapify_parameter.y);
	if (fcmp(z1, z2) == 0)
	{
		if(heapstatus == 0){ //insert
			z1 = triplanes[a].getz(heapify_parameter.x, heapify_parameter.y - 0.0001);
			z2 = triplanes[b].getz(heapify_parameter.x, heapify_parameter.y - 0.0001);
		}
		else { //erase
			z1 = triplanes[a].getz(heapify_parameter.x, heapify_parameter.y + 0.0001);
			z2 = triplanes[b].getz(heapify_parameter.x, heapify_parameter.y + 0.0001);
		}
		return fcmp(z1, z2) > 0;
	}
	return fcmp(z1, z2) > 0;
};
double TrapeziumArea(const Line<double>& L1, const Line<double>& L2){
	double h = abs(L1.ed.x - L1.st.x);
	if(fcmp(L1.st.y, L2.st.y) == 0 && fcmp(L1.ed.y, L2.ed.y) == 0)
		return 0.0;
	return (abs(L1.st.y - L2.st.y) + abs(L1.ed.y - L2.ed.y)) * h;
}
const int roundT =72;
double doslice(vec<tuple<Line<double>, int, int>>& segments, vec<double>& rate, int round){
	double res = 0.0;
	double tmp;
//	priority_queue<int, vector<int>, decltype(myheapify)> pq(myheapify);
#ifdef USEHEAP
	vec<int> pq;
	make_heap(pq.begin(), pq.end(), myheapify);
#endif
	set<int, decltype(myheapify)> pq(myheapify);
	Line<double> L1;
	vec<int> inpq(Tn, false);
	for(auto&e: segments){
		int id, inout;
		Line<double> L;
		tie(L, id, inout) = e;
		heapify_parameter = (L.st + L.ed) / 2.0;
		#ifdef Dslice	
		if(round == 72){
			cout << L;
			cout << ", " << id << ", " << inout << endl;
			cout << heapify_parameter << endl;
			cout << "now set" << endl;
			for (const int &e : pq)
			{
				cout << e << " " << triplanes[e].getz(heapify_parameter.x, heapify_parameter.y) << endl;
			}
			cout << id << ": " << triplanes[id].getz(heapify_parameter.x, heapify_parameter.y) << endl;
			cout << "heapfiy " << myheapify(id, *pq.begin()) << endl;
		}
		#endif
		heapstatus = inout;
		if (inout == 0)
		{ // in
			inpq[id] = true;
			if (pq.empty())
			{
				pq.insert(id);
				L1 = L;
			}
			else{
				int curtop = *pq.begin();
				pq.insert(id);
				res += abs(TrapeziumArea(L1, L) * rate[curtop]);				
					#ifdef DArea	
					if(round == roundT){
						cout << "counted " << curtop << "\n from " << L1 << "\n to " << L << "\n";
						debug(TrapeziumArea(L1, L) * rate[curtop]/ 2.0);
					}
					#endif	
					L1 = L;
				//}
			}
		}
		else if(inout == 1){
			inpq[id] = false;
			int curtop = *pq.begin();
				res += abs(TrapeziumArea(L1, L) * rate[curtop]);
				#ifdef DArea	
				if(round == roundT){

				cout << "counted " << curtop << "\n from " << L1 << "\n to " << L << "\n";	
				debug(TrapeziumArea(L1, L) * rate[curtop] / 2.0);
				}
				#endif
				L1 = L;
			pq.erase(id);
			//	while (pq.size() && inpq[*pq.begin()] == false)
			//		pq.erase(pq.begin());
		}
		else{
			cout << "WTFFFFFFFFFFFF\n";
		}
		#ifdef Dround
		if(round == roundT){

			cout << "after \n";
			for (const int &e : pq)
			{
				cout << e << " " << triplanes[e].getz(heapify_parameter.x, heapify_parameter.y) << endl;
			}
			cout << "end after----------\n";
			cout << endl;
		}
		#endif
	}	
	return res;
}
double getY(const Line<int>& L, double x){
	if(fcmp(x, L.st.x) == 0)
		return L.st.y;
	else if(fcmp(x, L.ed.x) == 0)
		return L.ed.y;
	double offset = x - L.st.x;
	return L.st.y + L.vec().y * (offset / L.vec().x);
}
void getSegments(vec<tuple<Line<double>, int, int>>&segments, vec<Point<int>>&pts, vec<vec<int>>& triangles, double xL, double xR){
	#ifdef DgetSeg
	debug(xL);	
	debug(xR);	
	#endif
	for(int i = 0; i < Tn; i++){
//		int visited = 0;
		vec<Line<double>> Lines;
		REP(j, 3){
			int pi = triangles[i][j];	
			int pj = triangles[i][nti(j, 3)];	
			if(pts[pi].x == pts[pj].x){
				continue;
			}
			Line<int> L1(pts[pi], pts[pj]);	
			if(pts[pi].x > pts[pj].x){
				swap(L1.st, L1.ed);	
			}	
//			cout << L1  << ":\n";
			if(fcmp(xL, L1.st.x) >= 0 && fcmp(xR, L1.ed.x) <= 0){
				double yL = getY(L1, xL);
				double yR = getY(L1, xR);
				#ifdef DgetSeg
				cout << " on " << xL << " is " << yL << endl;
				cout << L1 << " on " << xR << " is " << yR << endl;			
				#endif
				Lines.eb(xL, yL, xR, yR);		
			}
			#ifdef DgetSeg
			else{
				debug(L1.st.x);
				debug(L1.ed.x);
				debug(fcmp(xR, L1.ed.x));
				debug(fcmp(xL, L1.st.x));
			}
			#endif
		}
		if(Lines.size() == 2){
			if(fcmp(((Lines[0].st + Lines[0].ed) /2.0).y, ((Lines[1].st + Lines[1].ed) /2.0).y) < 0){
				swap(Lines[0], Lines[1]);
			}
			for(int inout = 0; inout < 2; inout++)
				segments.eb(Lines[inout], i, inout);	
		}
		else if(Lines.size() == 1)	
			cout << "Whatriangle?\n";
	}
	auto cmp = [](tuple<Line<double>, int ,int> &a, tuple<Line<double>, int ,int> &b){
		double ya = (get<0>(a).st.y + get<0>(a).ed.y) / 2.0; 
		double yb = (get<0>(b).st.y + get<0>(b).ed.y) / 2.0; 
		if(fcmp(ya, yb) != 0)
			return fcmp(ya, yb) > 0;	
		return get<2>(a) > get<2>(b);
	};
	sort(al(segments), cmp);
	#ifdef DSeg
		for(auto&e: segments){
			Line<double> L;
			int id, inout;
			tie(L, id, inout) = e;
			cout << L << ", " << id << ", " << inout << endl;
		}
	#endif
}

auto onlyXcmp= [](double&a, double &b){
	return fcmp(a, b) <0 ;
};
int main(){
	int caseN = 1;	
	while(cin >> Vn >> Tn){
		if(Vn == 0 && Tn == 0)
			break;
		if(caseN == 12)
			cout << Vn << " " << Tn << endl;
//		vec<Point3D> pts3d(Vn);
		pts3d.resize(Vn);
		triplanes.clear();
		triangles.clear();
		REP(i, Vn)
		{
			cin >> pts3d[i].x >> pts3d[i].y >> pts3d[i].z;
			if(caseN == 12)
				cout<<  pts3d[i].x << " " << pts3d[i].y << " " << pts3d[i].z << endl;
		}
		vec<Point<int>> pts;	
		REP(i, Vn){
			pts.eb(pts3d[i].x, pts3d[i].y)	;
		}	
		vector<double> onlyX;
		vec<double> rate;
		REP(i, Tn){
			vec<int> pi(3);
			REP(j, 3){
				cin >> pi[j];
				if(caseN == 12)
					cout << pi[j] << " ";
				pi[j]--;
			}
			if(caseN == 12)
				cout << endl;
			int Area2D = (pts[pi[1]] - pts[pi[0]]) ^ (pts[pi[2]] - pts[pi[0]]);
			int curi = triangles.size();
			if(Area2D == 0){
//				cout << "discard " << i << endl;
				continue;
			}
			REP(j, 3)
				onlyX.eb((double)pts3d[pi[j]].x);
			#ifdef DonlyX
				cout << i << ": ";
				REP(j, 3){
					cout << "(" << pts3d[pi[j]].x << ", " << pts3d[pi[j]].y << "), ";
				}
				cout << endl;
			#endif
			triangles.eb(pi);
			triplanes.eb(pts3d[pi[0]], pts3d[pi[1]], pts3d[pi[2]]);
			rate.eb((triplanes[curi].get2Area() / Area2D));
		}
		Tn = triplanes.size();
		/*
		REP(i, Tn){
			if(i == 40 || i == 25){
				cout << i << ": ";
				REP(j, 3){
					cout << "(" << pts3d[triangles[i][j]].x << ", " << pts3d[triangles[i][j]].y << ", " << pts3d[triangles[i][j]].z << "), ";
				}
				cout << endl;
			}
		}
		*/
		// get all intersections' x value	
		fillIntersection(onlyX, triangles, pts3d); 
		sort(al(onlyX), onlyXcmp);
		onlyX.resize(distance(onlyX.begin(), unique(al(onlyX), doublePred)));
		#ifdef DonlyX	
		cout << "onlyX:";
		for(double&x: onlyX){
			cout << x << " \n" ;
		}
		cout << endl;
		#endif	
		double ans = 0.0;
		for(int i = 0; i < (int)onlyX.size()-1; i++){
			#ifdef DgetSeg
			cout << "cutting:\n";
			#endif
			vec<tuple<Line<double>, int, int>> segments; // Line, tri id, in(0)/out(1)
			getSegments(segments, pts, triangles, onlyX[i], onlyX[i+1]);
			double ans2 = ans;
			ans += doslice(segments, rate, i);
			#ifdef Dans
			cout << fixed << setprecision(10);
			cout << (ans - ans2) / 2.0 << endl;
			#endif
		}

		cout << "Case " << caseN++ << ": " <<fixed << setprecision(2) << ans /2.0<< endl;
		cout << endl;
		
	}

	return 0;

}
