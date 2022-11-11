#define _CRT_SECURE_NO_WARNINGS
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma comment(linker, "/stack:200000000")
#include <bits/stdc++.h>
#define ll long long
using namespace std;
void io() { ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); }
int num;
 
struct Point {
	ll x, y;
	Point() {}
	Point(ll xx, ll yy) :x(xx), y(yy) {}
	Point operator + (const Point& k1) const { return Point(k1.x + x, k1.y + y); }
	Point operator - (const Point& k1) const { return Point(x - k1.x, y - k1.y); }
	Point operator * (ll k1) const { return Point(x * k1, y * k1); }
	Point operator / (ll k1) const { return Point(x / k1, y / k1); }
	bool operator < (const Point& b) const {
		return (x < b.x) || (x == b.x && y < b.y);
	}
	bool operator ==(const Point& b) const {
		return (x == b.x) && (y == b.y);
	}
	ll abs() { return x * x + y * y; }
	ll dis(Point k1) { return ((*this) - k1).abs(); }
};
 
ll cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }	//叉积
ll dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }	//点积
ll area(Point a, Point b, Point c) { return abs(cross(a - b, a - c)); }
 
vector<Point> ConvexHull(vector<Point>A, int flag = 1) { // flag = 0 不严格 flag = 1 严格
	int n = A.size(); vector<Point>ans(n * 2);
	sort(A.begin(), A.end()); int now = -1;
	for (int i = 0; i < A.size(); i++) {
		while (now > 0 && cross(ans[now] - ans[now - 1], A[i] - ans[now - 1]) < flag) now--;
		ans[++now] = A[i];
	}
	int pre = now;
	for (int i = n - 2; i >= 0; i--) {
		while (now > pre&& cross(ans[now] - ans[now - 1], A[i] - ans[now - 1]) < flag) now--;
		ans[++now] = A[i];
	}
	ans.resize(now);
	return ans;
}
 
inline int nxt(int i) { return i == num - 1 ? 0 : i + 1; }

ll Rotating_calipers(int n, vector<Point>& p) {
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int p1 = nxt(i);
		int p2 = nxt(nxt(nxt(i)));
		for (int j = nxt(nxt(i)); nxt(j) != i; j = nxt(j)) {
			while (nxt(p1) != j && area(p[i], p[nxt(p1)], p[j]) > area(p[i], p[p1], p[j]))
				p1 = nxt(p1);
			if (p2 == j) p2 = nxt(p2);
			while (nxt(p2) != i && area(p[j], p[nxt(p2)], p[i]) > area(p[j], p[p2], p[i]))
				p2 = nxt(p2);
			ans = max(ans, area(p[i], p[p1], p[j]) + area(p[j], p[p2], p[i]));
		}
	}
	return ans;
}
 
int main() {
	io(); int t;
	cin >> t;
	while (t--) {
		int n; cin >> n;
		vector<Point> p(n);
		for (auto& i : p) cin >> i.x >> i.y;
		vector<Point> ch = ConvexHull(p, 0);
		num = ch.size();
		ll maxs = 0;
		if (ch.size() < 3) maxs = 0;
		else if (ch.size() == 3) {
			ll s = area(ch[0], ch[1], ch[2]);
			for (auto i : p) {
				if (i == ch[0] || i == ch[1] || i == ch[2]) continue;
				ll mins = min(area(i, ch[1], ch[2]), min(area(ch[0], i, ch[2]),
					area(ch[0], ch[1], i)));
				maxs = max(maxs, s - mins);
			}
		}
		else maxs = Rotating_calipers(ch.size(), ch);
		cout << ((maxs & 1ll) ? to_string(maxs / 2ll) + ".5\n" : to_string(maxs / 2ll) + "\n");
	}
}
