#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 2*1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int n, m;
double eps = 1e-11;
struct Robot {
	int x, y;
	int nx, ny;
	
	int now, s;
	vec<int> move;

	Robot() {}

	// 0: up, 1: down, 2: left, 3: right.
	Robot(int x, int y) : x(x), y(y) {
		nx = (x > 0 ? 0 : n-1);
		ny = (y > 0 ? 0 : m-1);

		int tx = x, ty = y;
		x = abs(x);
		y = abs(y);
		
		double ny = 0.5;
		
		for (int i = 1; i <= x; i++) {
			double nexty = 1.0 * y / x * i + 0.5 * (x-y) / x;
			
			// cout << i << ' ' << nexty << endl;
			
			double nexty_int, ny_int;
			modf(nexty,&nexty_int);
			modf(ny, &ny_int);
		   
			if (nexty - nexty_int < eps) { // on point.
				for (int k = 0; k < nexty_int - ny_int - 1; k++)
					move.eb(ty > 0 ? 0 : 1);
				
				move.eb(tx > 0 ? 3 : 2);
				move.eb(ty > 0 ? 0 : 1);
				ny = nexty;
			} else {
				for (int k = 0; k < nexty_int - ny_int; k++)
					move.eb(ty > 0 ? 0 : 1);

				move.eb(tx > 0 ? 3 : 2);	
				ny = nexty;
			}
		}

		for (int k = 0; k < int(0.5+y) - int(ny); k++)
			move.eb(ty > 0 ? 0 : 1);
	
		s = move.size();
		now = 0;

		x = tx, y = ty;
		// devec(move);
	}

	void reset() {
		now = 0;
		
		nx = (x > 0 ? 0 : n-1);
		ny = (y > 0 ? 0 : m-1);

	}
};

void next(int& src, int n) {
	src = (src + 1) % n;
}

void prev(int& src, int n) {
	src = (src + n-1) % n;
}

int main()
{
    yccc;
	
	int c = 1;
	while (cin >> n >> m) {
		if (n == 0)
			break;

		int r;
		cin >> r;
		
		vec<Robot> robot(r);
		for (int i = 0; i < r; i++) {
			int x, y;
			cin >> x >> y;

			robot[i] = Robot(x, y);
		}
		
		int acount = 0, at = 0;
		vec<pii> ans;
		for (int i = 0; i < r; i++)
			for (int k = i+1; k < r; k++) {
				robot[i].reset();
				robot[k].reset();

				if (robot[i].nx == robot[k].nx and robot[i].ny == robot[k].ny)
					continue;

				deq<deq<bool>> vis(n, deq<bool>(m));

				int t = 1, count = 0;
                bool stopA = false, stopB = false;
				for (; ; t++) {
					// cout << "at (" << robot[i].nx << ", " << robot[i].ny
					// 	 << ") and (" << robot[k].nx << ", " << robot[k].ny << ")\n";
					if (robot[i].nx == robot[k].nx and robot[i].ny == robot[k].ny) {
						count++;
					    break;
					}

                    if (!stopA) {
    					vis[robot[i].nx][robot[i].ny] = true;
                        count++;
                    }

                    if (!stopB) {
    					vis[robot[k].nx][robot[k].ny] = true;
                        count++;
                    }
                    
					int b = 0, ix = robot[i].nx, iy = robot[i].ny;
                    if (!stopA) {
						switch (robot[i].move[robot[i].now]) {
							case 0:
								next(robot[i].ny, m);
								break;
							case 1:
								prev(robot[i].ny, m);
								break;
							case 2:
								prev(robot[i].nx, n);
								break;
							case 3:
								next(robot[i].nx, n);
						}
                    }

					if (robot[i].nx == robot[k].nx and robot[i].ny == robot[k].ny)
						b++;
						
                    if (!stopB) {
						switch (robot[k].move[robot[k].now]) {
							case 0:
								next(robot[k].ny, m);
								break;
							case 1:
								prev(robot[k].ny, m);
								break;
							case 2:
								prev(robot[k].nx, n);
								break;
							case 3:
								next(robot[k].nx, n);
						}
                    }

					if (robot[k].nx == ix and robot[k].ny == iy and b == 1 and !stopA and !stopB) {
						// cout << "collision\n";
						break;
					}

					next(robot[i].now, robot[i].s);
					next(robot[k].now, robot[k].s);
					
                    if (vis[robot[i].nx][robot[i].ny])
                        stopA = true;
                    if (vis[robot[k].nx][robot[k].ny])
                        stopB = true;

					if (stopA and stopB)
                        break;
				}
				
				if (count == acount and t == at)
					ans.eb(i+1, k+1);
				else if (count > acount or (count == acount and t < at)) {
					acount = count;
					at = t;

					ans.clear();
					ans.eb(i+1, k+1);
				}
			}

		cout << "Case " << c++ << "   Cells Illuminated: " << acount << "   Minimum Time: " << at << endl;
		for (int i = 0; i < ans.size(); i++) {
			cout << "   Geoduck IDs:  " << ans[i].F << "  " << ans[i].S << '\n';
		}
	}

}

