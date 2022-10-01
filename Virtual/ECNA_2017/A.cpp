#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using p = pair<T, T>;
template<typename T> using deq = deque<T>;
#define debug(x) cout << #x << ": " << x << endl;
#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()

const double eps = 1e-7;
int fcmp(double a, double b){
	if(abs(a-b) < eps){
		return 0;
	}
	return (a - b > 0.0) * 2 - 1;
}

struct point{
	double x, y;
	point(){x = y = 0.0;}
	point(double x, double y): x(x), y(y){};
	point operator+(point b){
		return point(x + b.x, y + b.y);
	}
	point operator-(point b){
		return point(x - b.x, y - b.y);
	}
	double operator^(point b) {
		return x * b.y - y * b.x;
	}
	point operator*(double fac) {
		return point(x * fac, y * fac);
	}
	point operator/(double fac) {
		return point(x / fac, y / fac);
	}
	friend ostream& operator<<(ostream& os, point& e);
};
ostream& operator<<(ostream& os, point& e){
	return (os << "(" << e.x <<", " << e.y << ")");
}
struct line{
	point st, ed;
	int pid;
	line(){}
	line(point st, point ed):st(st), ed(ed){}
	line(point st, point ed, int id):st(st), ed(ed), pid(id){}
	line(double x1, double y1, double x2, double y2, int id):st(x1, y1), ed(x2, y2), pid(id){}
	point vec() {
		return ed - st;	
	}
	double ori(point p) {
		return (ed - st) ^ (p - st);
	}
	point operator()(double x) {
		return st + vec() * x;
	}
	bool isSegProperIntersection(line& l){
		return fcmp(l.ori(st) * l.ori(ed), 0.0) < 0 and fcmp(ori(l.st) * ori(l.ed), 0.0) < 0;
	}
	point getIntersection(line l){
		line h = *this;
		double hlst = -h.ori(l.st);
		double hled = h.ori(l.ed);
		return ((l.st * hled) + (l.ed * hlst)) / (hlst + hled);
	}
	friend ostream& operator<<(ostream& os, line& e);
};
ostream& operator<<(ostream& os, line& e){
	return (os << "{" << e.st <<" to " << e.ed << "}");
}

double dis(point&a, point&b){
	double xd = a.x - b.x;
	double yd = a.y - b.y;
	return sqrt(xd * xd + yd * yd);
}
double gety(point& st, point& ed, double x){
	double xd = abs(ed.x - st.x);	
	double xd2 = abs(x - st.x);
	return st.y + (ed.y - st.y) * xd2 / xd;
}
double cal(line&up, line& down){
	double ly = abs(up.st.y - down.st.y);
	double ry = abs(up.ed.y - down.ed.y);
	return abs(up.st.x - up.ed.x) * (ly + ry);
}


using polygon = vec<point>;
int ni(int idx, int n){
	return (idx+1 == n ? 0 : idx+1);
}

double poly_sum = 0;
int main() {

	int n;
	cin >> n;
	vec<polygon> polys(n);
	vec<double> onlyx;
	for(int i = 0; i < n; i++){
		int m;
		cin >> m;
		for(int j = 0; j < m; j++){
			double x, y;
			cin >> x >> y;
			onlyx.eb(x);
			polys[i].eb(x, y);
		}
	}
#ifdef Dpoly
	for(int i = 0; i < n; i++){
		printf("poly[%d]: ", i);
		for(int j = 0; j < polys[i].size(); j++){
			cout << polys[i][j] << " ";
		}
		cout << "\n";
	}
#endif
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){
			for(int li = 0; li < polys[i].size(); li++){
				for(int lj = 0; lj < polys[j].size(); lj++){
					line l1(polys[i][li], polys[i][ni(li, polys[i].size())]);
					line l2(polys[j][lj], polys[j][ni(lj, polys[j].size())]);
					if(l1.isSegProperIntersection(l2)){
						onlyx.eb(l1.getIntersection(l2).x);
					}
				}
			}	
		}
	}

	for (auto i : polys) {
		double tmp = 0;
		for (int k = 0; k < i.size(); k++) {
			
//			tmp += i[k].x * i[ni(k, i.size())].y - i[k].y * i[ni(k, i.size())].x;
				tmp += i[k] ^ i[ni(k, i.size())];
		}

		poly_sum += (abs(tmp) / 2);
	}
	auto cmpx = [](double a, double b){
		return (fcmp(a, b) == 0);
	};
	sort(al(onlyx));
	onlyx.resize(distance(onlyx.begin(), unique(al(onlyx), cmpx)));
#ifdef Dx
	for(double x: onlyx){
		cout << x << ", " ;
	}
	cout << endl;
#endif
	double kans = 0.0;
	for(int xi = 0; xi < onlyx.size() - 1; xi++){
		double lx = onlyx[xi], rx = onlyx[xi+1];
		vec<line> lines;
		for(int k = 0; k < n; k++){
			polygon &po = polys[k];

			for(int i = 0; i < po.size(); i++){
				int j = ni(i, po.size());
				point p1 = po[i], p2 = po[j];
				if(fcmp(p1.x, p2.x)== 0){
					continue;
				}

				if(fcmp(p1.x, p2.x) > 0){
					swap(p1, p2);
				}

				if(fcmp(p2.x, lx) <= 0 || fcmp(rx, p1.x) <= 0){
					continue;
				}

				lines.eb(lx, gety(p1, p2, lx), rx, gety(p1, p2, rx), k);
			}
		}
		auto cmp = [](const line&a, const line&b){
			double mida = (a.st.y + a.ed.y) / 2.0;
			double midb = (b.st.y + b.ed.y) / 2.0;
			return fcmp(mida, midb) >= 0;
		};

		sort(al(lines), cmp);
		vec<bool> inside(n, false);
		line last;
		int cover = 0;
		for(line& e: lines){
			if(inside[e.pid]){
				inside[e.pid] = false;
				cover--;
				if(cover == 0){
					kans += cal(last, e);
				}
			}
			else{
				inside[e.pid] = true;
				cover++;
				if(cover == 1){
					last = e;
				}
			}
		}
	}
	kans /= 2.0;


	
	cout << fixed << setprecision(9) << poly_sum << " " << kans;
	return 0;
}
