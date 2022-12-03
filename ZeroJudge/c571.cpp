// AC 2022-11-17 16:49
// failed, when doing # x_j > x_i, rather than doing in forward approach
// we should switch to count # x_j <= x_j 
// otherwise it's hard to say the differenct like
// becarefull if two point with same x
// like (8, 7, 8) (8, 7, 2) (8, 6, 4)
// that (8, 6, 4) may think (8, 7, 8) is larger than it
// so we have to do some trick in cmp function
// if the `x` is the same, sort in decreasing order of y and z
// in this way, the doing mergin will no possible merge some wrong pair

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
#define mp make_pair
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
struct point{
	int x, y, z;
	int idx;
	point(){x = y = z = 0;}	
	point(int a, int b, int c, int id):x(a), y(b), z(c), idx(id){}
	friend ostream& operator<<(ostream& os, point& p);
};
ostream& operator<<(ostream& os, point& p){
	return (os << "(" << p.x << ", " << p.y << ", " << p.z <<")");
}
const int maxn = 100001;
vec<point> origin_pts, pts;
point staticArr[maxn];
int ans[maxn] = {0};
ll mt[maxn] = {0};

void add(int x, int val){
	while(x < maxn){
		mt[x] += val;
		x += (x & (~x+1));
	}
}

int query(int x){
	int res = 0;
	while(x > 0){
		res += mt[x];
		x -= (x & (~x+1));
	}
	return res;
}

void cdq(int l, int r){
	if(l == r){
		return ;
	}
	int mid = (l + r) >> 1;
	cdq(l, mid);
	cdq(mid + 1, r);

	int cpidx = 0;
	vec<int> arr;
	for (int i = l ;i <= r; i++){
		arr.eb(pts[i].z);	
	}
	sort(al(arr));
	arr.resize(unique(al(arr)) - arr.begin());
	fill(mt, mt + arr.size()+1, 0);
	
	int lid = l, rid = mid + 1;
	int zval;
	for(rid = mid+1; rid <= r; rid++){
		while(lid <= mid && pts[lid].y > pts[rid].y){
			zval = upper_bound(al(arr), pts[lid].z) - arr.begin() ;
			add(zval, 1);	
			staticArr[cpidx++] = pts[lid];
			lid++;
		}
		zval = upper_bound(al(arr), pts[rid].z) - arr.begin() ;
		ans[pts[rid].idx] += (query(arr.size()) - query(zval));
		staticArr[cpidx++] = pts[rid];
	}
	while(lid <= mid){
		staticArr[cpidx++] = pts[lid];
		lid++;
	}

	for(int i = 0; i < cpidx; i++){
		pts[i + l] = staticArr[i];
	}
}
int main(){
	yccc;		
	int n;
	cin >> n;
	origin_pts.resize(n);
	int idx = 0;
	for (point& e: origin_pts) {
		cin >> e.x >> e.y >> e.z; e.idx = idx++;
	}
	pts = origin_pts;
	auto cmp_1 = [](point&a , point &b){
		return a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y ): a.x > b.x;
	};
	sort(al(pts), cmp_1);

	cdq(0, n-1);	
	for(int i = 0; i < n; i++){
		cout << ans[i] << endl;
	}

	return 0;
}

