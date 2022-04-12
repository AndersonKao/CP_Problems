#include <bits/stdc++.h>
#include <ext/hash_map>
#include <ext/numeric>

using namespace std;
using namespace __gnu_cxx;

#define REP(i, n) for( (i) = 0 ; (i)<(n) ; (i)++)
#define rep(i,x,n) for( (i)=(x); (i)<(n); (i)++ )
#define REV(i,n) for( (i)=(n) ; (i) >= 0 ; (i)-- )
#define FORIT(it,x) for( (it)=(x).begin() ; (it) != (x).end() ; (it)++ )
#define foreach(it,c) for(__typeof((c).begin()) it=(c).begin();it!=(c).end();++it)
#define rforeach(it,c) for(__typeof((c).rbegin()) it=(c).rbegin();it!=(c).rend();++it)
#define foreach2d(i, j, v) foreach(i,v) foreach(j, *i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define SZ(x) ((int)(x).size())
#define MMS(x,n) memset(x,n,sizeof(x))
#define mms(x,n,s) memset(x,n,sizeof(x)*s)
#define pb push_back
#define mp make_pair
#define NX next_permutation
#define UN(x) sort(all(x)), x.erase(unique(all(x)),x.end())
#define CV(x,n) count(all(x), (n))
#define FIND(x,n) find(all(x),(n))-(x).begin()
#define ACC(x) accumulate(all(x),0)
#define PPC(x) __builtin_popcountll(x)
#define LZ(x) __builtin_clz(x)
#define TZ(x) __builtin_ctz(x)
#define mxe(x) *max_element(all(x))
#define mne(x) *min_elelment(all(x))
#define low(x,i) lower_bound(all(x), i)
#define upp(x,i) upper_bound(all(x), i)
#define NXPOW2(x) (1ll << ((int)log(x)+1))
#define PR(x) cout << #x << " = " << (x) << endl;

typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

const int OO = (int) 2e9;
const double eps = 1e-9;

typedef complex<double> point;
typedef pair<point, point> segment;

#define Y imag()
#define X real()
#define TOP second
#define BOT first

const int N = 102;

point pnts[N];
int np;

point holes[N];
int nh;

int ys[N];
int ny;
int nTrapz;

struct Trapezium {
	segment left, right;
	int id;
		Trapezium(const segment& L, const segment &R) :
						left(L), right(R) {
				id = nTrapz++;
		}
		int ymin() const {
				return left.BOT.Y;
		}
		int ymax() const {
				return left.TOP.Y;
		}
		double area() {
				return (ymax() - ymin()) / 2.0 * (right.BOT.X + right.TOP.X - left.BOT.X - left.TOP.X);
		}
};

double getX(const segment& seg, const double &y) {
		// (y-y1)/(x-x1)=(y1-y2)/(x1-x2)
		// x = x1 + (y-y1) * (x1 - x2) / (y1 - y2);
		return seg.first.X + (y - seg.first.Y) / (seg.first.Y - seg.second.Y) * (seg.first.X - seg.second.X);
}

map<int, vector<segment>> getSegments() {
	map<int, vector<segment>> ret;
	for (int i = 0; i < np; i++) {
		int j = (i + 1) % np;
		int mny = min(pnts[i].Y, pnts[j].Y);
		int mxy = max(pnts[i].Y, pnts[j].Y);
		auto nxt = lower_bound(ys, ys + ny, mny);
		auto end = lower_bound(ys, ys + ny, mxy);
		for( auto cur = nxt++; cur != end; cur++, nxt++) { // for all points' y in range mny, mxy.
			double curX = getX(segment(pnts[i], pnts[j]), *cur); // get the intersection of line y=cur and segment(pnts[i], pnts[j]).
			double nxtX = getX(segment(pnts[i], pnts[j]), *nxt);
			ret[*cur].emplace_back(point(curX, *cur), point(nxtX, *nxt));
		}
	}
	for (auto &it : ret) {
		// sort every segments which are with same y starting value, by their midpoint.
		// in this way, pair and pair forms a Trapzium.
		sort(it.second.begin(), it.second.end(), [](const segment &a, const segment &b) {
			double xamid = (a.first.X + a.second.X);
			double xbmid = (b.first.X + b.second.X);
			return xamid < xbmid;
		});
	}
	return ret;
}

vector<vector<Trapezium>> getTrapziums(const map<int, vector<segment>> &mp) {
	vector<vector<Trapezium>> ret;
	for (auto &it : mp) {
		vector<Trapezium> trapz;
		auto &p = it.second;
		for(int i = 0; i < SZ(p); i += 2) {
			int j = i + 1;
			trapz.emplace_back(p[i], p[j]);
		}
		ret.push_back(trapz);
	}
	return ret;
}

int dcmp(double a, double b) {
	if (fabs(a - b) < eps)
		return 0;
	return (a > b) * 2 - 1;
}

vector<vector<pii>> buildGraph(const vector<vector<Trapezium>> &trapz) {
	vector<vector<pii>> ret(nTrapz);
	for (int i = 0; i < SZ(trapz) - 1; i++) {
		auto &bot = trapz[i];
		auto &top = trapz[i + 1];
		for (auto &b : bot) {
			for (auto &t : top) {
				double left = max(b.left.TOP.X, t.left.BOT.X);
				double right = min(b.right.TOP.X, t.right.BOT.X);
				if (dcmp(left, right) < 0) {
					int y = b.left.TOP.Y;
					ret[b.id].emplace_back(t.id, y);
					ret[t.id].emplace_back(b.id, y);
					// ? what is this y for ??
				}
			}
		}
	}
	return ret;
}

auto ycmp = [](const point &a, const point &b) {
	return a.Y < b.Y;
};

bool inside(const double &x, const double &st, const double &en) {
	return dcmp(x, st) >= 0 && dcmp(x, en) <= 0;
}

pair<priority_queue<pii>, vector<int> > getSrc(const vector<vector<Trapezium>> &trapz) {
	priority_queue<pii> ret;
	vector<int> dist(nTrapz, INT_MAX);
	for(auto &v : trapz) {
		for(auto &t : v) {
			int ymin = t.ymin();
			int ymax = t.ymax();
			auto cur = lower_bound(holes, holes + nh, point(0, ymin), ycmp);
			for (; cur - holes < nh && cur->Y == ymin; cur++) {
				if (inside(cur->X, t.left.BOT.X, t.right.BOT.X)) {
					ret.push( { -ymin, t.id});
					dist[t.id] = min(dist[t.id], ymin);
				}
			}
			for (; cur - holes < nh && cur->Y == ymax; cur++) {
				if (inside(cur->X, t.left.TOP.X, t.right.TOP.X)) {
					ret.push( {-ymax, t.id});
					dist[t.id] = min(dist[t.id], ymax);
				}
			}
		}
	}
	return {ret, dist};
}

void dijkstra(priority_queue<pii> &Q, vector<int> &dist, const vector<vector<pii>> &adj) {
	while (SZ(Q)) {
		int u = Q.top().second;
		int d = -Q.top().first;
		Q.pop();
		if (d != dist[u])
			continue;
		for (auto e : adj[u]) {
			int v = e.first;
			int c = max(e.second, d);
			if (dist[v] > c) {
				dist[v] = c;
				Q.push( { -c, v });
			}
		}
	}
}

int main() {
// 		std::ios_base::sync_with_stdio(false);
//		cin.tie(NULL);
//		cout.tie(NULL);
#ifndef ONLINE_JUDGE
		freopen("in.txt", "rt", stdin);
//		freopen("out.txt", "wt", stdout);
#endif

	int tt = 1;
	while(scanf("%d", &np), np) {
		nh = nTrapz = 0;
		for(int i = 0 ; i < np; i++) {
			int x, y, ishole;
			scanf("%d %d %d", &x, &y, &ishole);
			pnts[i] = point(x, y);
			if (ishole) {
				holes[nh++] = pnts[i];
			}
			ys[i] = y;
		}
		sort(ys, ys + np);
		ny = unique(ys, ys + np) - ys;
		sort(holes, holes + nh, ycmp);
		auto mp = getSegments();
		auto trapz = getTrapziums(mp);
		auto adj = buildGraph(trapz);
/*
		for (int i = 0; i < nTrapz; i++) {
 			cout << i << ":";
			for (auto j : adj[i]) {
				cout << " (" << j.first << ", " << j.second << ")";
			}
			cout << endl;
		}			
*/
		auto P = getSrc(trapz);
		dijkstra(P.first, P.second, adj);
		double ret = 0;
		for (auto &v : trapz) {
			for (auto &t : v) {
				if (P.second[t.id] >= t.ymax()) {
					ret += t.area();
				}
			}
		}
		printf("Cave %d: Oil capacity = %.0lf\n\n", tt++, ret + eps);
	}
	return 0;
}
