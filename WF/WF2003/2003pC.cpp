#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define F first
#define S second 
#define X real()
#define Y imag()
#define REP(i, n) for(int i = 0; i < (int)n ;i++)
#define REP1(i, n) for(int i = 1; i <= (int)n ;i++)
#define al(a) a.begin(), a.end()
using pii = pair<int, int>;
using ll = long long;
using pll = pair<ll, ll>;
template<typename T>
using vec = vector<T>;
using point = complex<double>;
#define debugP(x) cout << #x << ": (" << x.X <<  ", " << x.Y << ")\n"
#define debug(x) cout << #x << ": " << x << endl
#define depii(x) cout << #x << ": (" << x.F <<  ", " << x.S << ")\n"
struct Linfo{
	int order;
	int unitLen;
	double Len;
};
const double eps = 1e-9;

int fcmp(const double&a, const double& b){
	if(fabs(a - b) < eps)
		return 0;
	return (a > b) * 2 - 1;
}
void getLen(int order, Linfo& L){
	L.order = order;
	L.unitLen = 2;
	for(int i = 1; i < L.order; i++)
		L.unitLen = L.unitLen * 3 + 2;
	L.Len = 1.0 / L.unitLen;
}

pair<pii, double> getCt(const point& pt, const Linfo& L){
	int r = (int)floor(pt.Y / L.Len);	
	int c = (int)floor(pt.X / L.Len);	
	pii ans(r,c);
//	depii(ans);
	double cur = 10.0;
	REP(i, 2){
		REP(j, 2){
			point ct((c + i) * L.Len, (r+j) * L.Len);
			double xdis = pt.X - ct.X, ydis = pt.Y - ct.Y;
			double dis = xdis * xdis + ydis * ydis;	
			if(fcmp(dis, cur) == -1){
				ans = {r + j, c + i};	
				cur = dis;
			}
		}
	}
	//depii(ans);
	return {ans, cur};
}
// type
// 1 ld -> ru
// 2 rd -> lu
// 3 lu -> rd
// 4 ru -> ld
int getBlockNum(const pii Ct, int type){
	int ans = 0;
	if(type == 2 || type == 1)
		for(int i = 0; i < Ct.F; i++)
			ans += 3;
	else
		for(int i = 2; i > Ct.F; i--)
			ans += 3;
	bool lrconvert = (type == 2 || type == 4);	
	if(((!lrconvert)&& (Ct.F == 0 || Ct.F == 2)) || (lrconvert && Ct.F == 1)) {
		for(int i = 0; i < Ct.S; i++)
			ans++;
	}
	else{
		for(int i = 2; i > Ct.S; i--)
			ans++;
	}
	return ans;
}

int typetrans[4][3][3] = {
	{
		{1, 3, 1},
		{2, 4, 2},
		{1, 3, 1}
	},
	{
		{2, 4, 2},
		{1, 3, 1},
		{2, 4, 2}
	},
	{
		{3, 1, 3},
		{4, 2, 4},
		{3, 1, 3}
	},
	{
		{4, 2, 4},
		{3, 1, 3},
		{4, 2, 4}
	}
};

int getUnitDis(const pii Ct, int layer, int type){
	if(layer == 1){
		return getBlockNum(Ct, type);
	}
	
	int Lsize = 1;
	for(int i = 1; i < layer; i++)
		Lsize *= 3;
//	int partr = Ct.F / Lsize, partc = Ct.S / Lsize;	
	pii pCt (Ct.F / Lsize, Ct.S / Lsize);
	pii nCt (Ct.F % Lsize, Ct.S % Lsize);	
	int prevNum = getBlockNum(pCt, type); 	
	int punitLen = 1;
	for(int i = 1; i < layer; i++)
		punitLen *= 9;
	int ans = punitLen * prevNum;

	return getUnitDis(nCt, layer-1, typetrans[type-1][pCt.F][pCt.S]) + ans;
}

int main(){
	yccc;
	int order;
	int cnt = 1;
	while(cin >> order)	{
		if(order == 0)
			break;
		if(cnt != 1)
			cout << endl;
		//cout << fixed << setprecision(10);
		double x1, x2, y1, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		point st(x1, y1), ed(x2, y2);	
		Linfo TopL;
		getLen(order, TopL);
		pair<pii, double> stCt = getCt(st, TopL), edCt = getCt(ed, TopL);	
		int stUnitDis = getUnitDis(stCt.F, order, 1);
		int edUnitDis = getUnitDis(edCt.F, order, 1);
		double ans = abs(edUnitDis - stUnitDis) * TopL.Len + sqrt(stCt.S) + sqrt(edCt.S) ;
		cout << fixed << setprecision(4);
		cout << "Case " << cnt++ << ".  Distance is " << ans << endl;
	}
	return 0;
}


