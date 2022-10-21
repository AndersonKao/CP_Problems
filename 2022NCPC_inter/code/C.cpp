// AC
// right a need to be in counter clockwise, otherwise we'll count same one twice
// 
#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
struct point{
	ll x, y;
	point(){}
	point(ll x, ll y):x(x), y(y){}
	point operator+(point b){
		return point(x + b.x, y + b.y);
	}
	friend ostream& operator<<(ostream& os, const point& a);
};
ostream& operator<<(ostream& os, const point& a){
	return (os << "(" << a.x << ", " << a.y << ")");
}

ll cross(point a, point b){
	return a.x * b.y - a.y * b.x;
}
ll dot(point a, point b){
	return a.x*b.x + a.y * b.y;
}
bool up(point a){
	return a.y > 0 or (a.y == 0 && a.x >= 0);
}
bool cmp(point a, point b){
	if(up(a) != up(b))
		return up(a) > up(b);	
	return a.x * b.y > a.y * b.x;
//	return a.x * b.y - a.y * b.x > 0;
}
int nexti(int i, int n){
	return i + 1 < n ? i+1 : 0;
}
int main(){
	ll n;
	cin >> n;
	vec<point> pts(n);
	REP(i, n){
		cin >> pts[i].x >> pts[i].y;	
	}
	ll obtuse = 0, righta = 0;
	REP(Bi, n){
		/*
		cout << "picked: ";
		debug(pts[Bi]);
		*/
		vec<point> ptcp;	
		for(int i = 0; i < n; i++){
			if(i == Bi) continue;
			ptcp.eb(pts[i].x - pts[Bi].x, pts[i].y - pts[Bi].y);
		}
		sort(al(ptcp), cmp);
/*
		for(int i = 0; i < n-1; i++){
			cout << ptcp[i] + pts[Bi] << " , ";
		}
		cout << endl;
*/
		int Ui = 0, Vi = 0;

		for(int Ai = 0; Ai < n-1; Ai++){
//			debug(Ai);
			while(dot(ptcp[Ai], ptcp[Ui]) > 0 && cross(ptcp[Ai], ptcp[Ui]) >= 0){
				Ui = nexti(Ui, n-1);
//				cout << "Ui go: " << Ui << endl;
				if(Ui == Ai)
					break;
			}
			while(Vi == Ai || cross(ptcp[Ai], ptcp[Vi]) > 0){
				Vi = nexti(Vi, n-1);
//				cout << "Vi go: " << Vi << endl;
				if(Vi == Ai)
					break;
			}		
	/*
			debug(Ui);
			debug(Vi);
			debug(ptcp[Ui] + pts[Bi]);
			debug(ptcp[Vi] + pts[Bi]);
			debug(dot(ptcp[Ai], ptcp[Ui]));
			debug(cross(ptcp[Ai], ptcp[Ui]));
			debug(dot(ptcp[Ai], ptcp[Vi]));
			debug(cross(ptcp[Ai], ptcp[Vi]));
			*/
			ll diff = Vi >= Ui ? Vi - Ui : (n-1 - (Ui-Vi));
			obtuse += diff;
			if(dot(ptcp[Ai] ,ptcp[Ui]) == 0 && cross(ptcp[Ai], ptcp[Ui]) > 0){
				obtuse--;
				righta++;
			}
			/*
			debug(obtuse);
			debug(righta);
			*/
			if(Ui == Ai){
				Ui = nexti(Ui, n-1);
			}
			if(Vi == Ai){
				Vi = nexti(Vi, n-1);
			}
		}
	}

	cout << n * (n-1) * (n-2) / 6 - obtuse - righta << " " << righta << " " << obtuse << endl;
	return 0;
}

