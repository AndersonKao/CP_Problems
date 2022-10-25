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
struct line{
	int a, b;	
	line(){}
	line(int a, int b):a(a), b(b){};	
};
struct event{
	double t;
	int type;
	int id;	
	event(){}
	event(double t, int type, int id):t(t), type(type), id(id){}
};
vec<line> lines;
vec<int> vals;
double intersect(line L1, line L2){
	return (L2.b - L1.b) / (double)(L1.a - L2.a);
}
int main(){
	int n, A;
	cin >> n >> A;	
	for(int i = 0; i < n; i++){
		int w, a, b;
		cin >> w >> b >> a;
		vals.eb(w);
		lines.eb(a, b);
	}
	int ans = 0;
	for(int i = 0; i < n; i++){
//		debug(i);
		vec<event> events; // time, 0 = in, 1 = out

		for(int j = 0; j < n; j++){
			if(i == j || lines[i].a == lines[j].a) continue;
			double t = intersect(lines[i], lines[j]);	
			if(t > 0.0){
				if(lines[j].a > lines[i].a){
					events.eb(t, 0, j);
				}
				else{
					events.eb(t, 1, j);
				}
			}
			t = intersect(line(lines[i].a, lines[i].b + A), lines[j]);	
			if(t > 0.0){
				if(lines[j].a > lines[i].a){
					events.eb(t, 1, j);
				}
				else{
					events.eb(t, 0, j);
				}
			}
		}
		int cur = 0;
		for(int j = 0; j < n; j++){
			if(lines[j].b >= lines[i].b && lines[j].b <= lines[i].b + A){
				cur += vals[j];
				if(lines[j].b == lines[i].b){
					if(lines[j].a < lines[i].a){
						events.eb(0.0, 1, j);
					}
				}
				if(lines[j].b == lines[i].b + A){
					if(lines[j].a > lines[i].a){
						events.eb(0.0, 1, j);
					}
				}
			}
			
		}
		auto cmp = [&](event a, event b){
			return a.t < b.t;
		};
		sort(al(events), cmp);
		ans = max(ans, cur);	
		for(event& e: events){
//			cout << e.id << " " << (e.type ? "out" : "in") << " " << e.t << endl;
			if(e.type == 0){
				cur += vals[e.id];
			}
			else{
				cur -= vals[e.id];
			}
			ans = max(ans, cur);	
//			debug(cur);
		}
	}
	cout << ans << endl;

	
	return 0;
}

