// remember tid * 3 shit
// modify cp geometry
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
    Line() : st(0, 0), ed(0,0) {}
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
    bool isSegIntersection(const Line<Real> l)const{
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
#define eb emplace_back
#define F first
#define S second
using ll = long long;
using uint = unsigned int;
inline int nexti(int i, int n){
	return i + 1 == n ? 0 : i + 1;
}
int N, ans;
bool sol;
vector<Line<ll>> lines;
vector<int> ty;
vector<tuple<int, int, int>> events; // x-val, triangle id, event-id(0,1,2)
vector<int> layer;
ll curx;

int cmpid = -1;
using Lii = tuple<Line<ll>, int, int>;
auto Linecmp = [](int a, int b){
	double y1, y2;	
	Line<ll>&L1 = lines[a], &L2 = lines[b];
	if(curx == L1.st.x)
		y1 = L1.st.y;
	else
		y1 = L1.st.y + (L1.vec().y * (curx - L1.st.x))/((double)L1.vec().x);
	if(curx == L2.st.x)
		y2 = L2.st.y;
	else
		y2 = L2.st.y + (L2.vec().y * (curx - L2.st.x))/((double)L2.vec().x);
	
	if(fcmp(y1, y2) != 0){
		return y1 < y2; 
	}
	return ty[a] < ty[b];
};
set<int, decltype(Linecmp)> myS(Linecmp);
using sIter = set<int, decltype(Linecmp)>::iterator;
vector<sIter> where;
sIter next(sIter it){
	return ++it; 
}
sIter prev(sIter it){
	return it == myS.begin() ? myS.end() : --it; 
}
bool check(const int a, const int b){
	if(a / 3 == b / 3)
		return false;
	return (lines[a]).isSegIntersection(lines[b]);
}
void planesweeeep(){
	int tid, pid;
	Line<ll> cmpL;
	int cmptid, cmpeid;
	for(uint ei =0 ; ei < events.size(); ei++){
		tie(curx, tid, pid) = events[ei];
//	cout << curx << ", " << tid << ", " << pid << endl;
		sIter itd, itu;
		if(pid == 0){
			for(int i = 0; i <= 1; i ++){
				int in = tid * 3 + i;
				itu = myS.lower_bound(in); //up  
				if(itu != myS.end()){
					for(int j = 0; j <= 1; j++){
						int chi = tid * 3 + j;
						if(check(chi, *itu)){
							sol = false;
						}
					}
				}	
				itd = prev(itu); // down 
				if(itd != myS.end()){
					for(int j = 0; j <= 1; j++){
						int chi = tid * 3 + j;
						if(check(chi, *itd)){
							sol = false;
						}
					}
				}	
				if(i == 0){
					if(itu == myS.end() || itd == myS.end()){
						layer[tid] = 2;
					}
					else{
//						cout << "tri " << tid << " is under " << *itu/3 << " above " << *itd /3 << endl;
						int ulayer = layer[*itu / 3];
						int dlayer = layer[*itd / 3];
						if(*itu/3 == *itd/3)
							layer[tid] = ulayer+1;
						else 
							layer[tid] = max(ulayer, dlayer);							
					}
				}
			}
			for(int i = 0; i <= 1; i ++){
				where[tid * 3 + i] = myS.insert(tid * 3 + i).F;
			}
		}
		else if(pid == 1){
			int out = tid*3 + 0;
			int in = tid*3 + 2;
			// plugout
			myS.erase(out);	
			itu = myS.lower_bound(out); //up 
			itd = prev(itu); //  down
			if(itd != myS.end() && itu != myS.end()){
				if(check(*itd, *itu)){
					sol = false;	
				}	
			}
			itu = myS.lower_bound(in);
			itd = prev(itu);
			if(itd != myS.end()){
				if(check(in, *itd)){
					sol = false;
				}
			}	
			if(itu != myS.end()){
				if(check(in, *itu)){
					sol = false;
				}
			}	
			where[in] = myS.insert(in).F;
		}
		else if(pid == 2){
			int out = tid*3 + 1, out2 = tid*3 + 2;
			myS.erase(out);
			myS.erase(out2);
			//myS.erase(where[out2]);
			//myS.erase(where[out2]);
			itu = myS.lower_bound(out);
			itd = prev(itu);
			if(itu != myS.end() && itd != myS.end()){
				if(check(*itd, *itu)){
					sol = false;	
				}	
			}
			itu = myS.lower_bound(out2);
			itd = prev(itu);
			if(itu != myS.end() && itd != myS.end()){
				if(check(*itd, *itu)){
					sol = false;	
				}	
			}

		}
/*
		cout << "insect\n";
		for(auto e: myS){
			cout  << "tri: " << e/ 3 << "lid " << e%3 << ": "<< lines[e]  << endl; 
		}
*/
	}
}
int main(){
    int caseN = 1;
    while(cin >> N){
		if(N == -1)
			break;
		if(N == 0){
			cout << "Case " << caseN++ << ": 1 shades\n";
			continue;
		}
		lines.clear();
		myS.clear();
		events.clear();
		sol = true;
		where.resize(3*N);
		layer.resize(N);
		ty.resize(3*N);	
        for (int i = 0; i < 3* N; i+= 3){
			vector<Point<ll>> pts(3);
            for (int j = 0; j < 3; j++){
                cin >> pts[j];
            }
            sort(pts.begin(), pts.end());
			lines.eb(pts[0], pts[1]);
			lines.eb(pts[0], pts[2]);
			lines.eb(pts[1], pts[2]);
			ty[i + 0]= ty[i + 2] = lines[i + 0].orint(pts[2]) < 0;
			ty[i + 1] = ty[i + 0] ^ 1;
            for (int j = 0; j < 3; j++){
				events.eb(pts[j].x, i/3, j);
			}
        }
		auto eventcmp = [](tuple<int, int, int>&a, tuple<int,int,int>&b){
			int x1 = get<0>(a);
			int x2 = get<0>(b);
			return x1 == x2 ? get<2>(a) < get<2>(b) : x1 < x2; 
		};
		sort(events.begin(), events.end(), eventcmp);
/*
		for(uint ei =0 ; ei < events.size(); ei++){
			int tid, pid;
			tie(curx, tid, pid) = events[ei];
			cout << curx << ", " << tid << ", " << pid << endl;
		}
*/
		planesweeeep();					
		ans = 0;
		for(int i = 0; i< N; i++){
			ans = max(ans, layer[i]);
		}
        cout << "Case " << caseN++ << ": ";
        if(sol){
            cout << ans << " shades\n";
        }
        else{
            cout << "ERROR\n";
        }
    }


    return 0;
}
