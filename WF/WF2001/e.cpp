#include <bits/stdc++.h>
using namespace std;
//#define debugDuck
#define F first
#define S second
#define X first
#define Y second
#define REP(i,n) for(int i = 0; i < n; i++)
#define REP1(i,n) for(int i = 1; i <= n; i++)
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(), a.end()
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a,b);
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for(auto i:v)cout << i << ' ';cout << endl;
#define debugp(x) cout << " > " << #x << ": (" << x.F << ", " << x.S << ")" << endl;
#define U 0
#define D 1
#define L 2
#define R 3
inline int next(int i, int n){
	return (i + 1 == n ? 0 : i + 1);
}


using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
template<typename T> using vec = vector<T>;
const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = numeric_limits<long long>::max();
int m, n, k; // m -> x, n -> y.
double dm,dn;
vec<pll> duck;
vector<vector<int>> dstep;
vec<vec<int>> vis;
vec<pii> ANSs;
#define DL 0 // 00
#define DR 1 // 01
#define UL 2 // 10
#define UR 3 // 11

pii mD[4]= {pii(0,1), pii(0, -1), pii(-1, 0), pii(1, 0)};
void init(){
    duck.resize(k);
    dstep.clear();
    dstep.resize(k);
	ANSs.clear();
}
int startpt(int did){ 
    int ans = 0;

    ans |= (duck[did].F > 0 ? 0 : 1);
    ans |= (duck[did].S > 0 ? 0 : 2);

    return ans;
}
pii  getstart(int did){
    switch(startpt(did)){
        case DL:
            return pii(0, 0);
            break;
        case DR:
            return pii(m - 1, 0);
            break;
        case UL:
            return pii(0, n-1);
            break;
        case UR:
            return pii(m-1, n-1);
            break;
    }
    return pii(-1, -1);
}
inline pii toint(pdd& a){
    
    return pii(floor(a.F), floor(a.S));
}
#define EQ 0
#define LT -1
#define GT 1
#define eps 1e-9
int feq(double a, double b){
    if(abs(a - b) < eps)
        return EQ;
    return (a > b ? GT : LT);
}
void transposeduck(int did){
    int from = startpt(did);
    if(!from)
        return;
    for(int&x: dstep[did]){
        if(from & 1){
            if(x == R)
                x = L;
        }
        if(from & 2){
            if(x == U)
                x = D;
        }
    }
}
ll gcd(ll a, ll b){
	if(a < b)
		swap(a, b);
	if(a % b == 0){
		return b;
	}
	return gcd(b, a % b); 
}
bool isint(pll b, ll t){
	if(b.S == 1)
		return (((b.F * t) & 1) == 0);
	if(t % b.S == 0){
		return ((b.F * (b.S / t) & 1) == 0);
	}
	return false;
}
void precal(int did){

    pll axe = duck[did];
	axe.F = abs(axe.F);
	axe.S = abs(axe.S);
	ll agcd = gcd(axe.F, axe.S);
	axe.F /= agcd;
	axe.S /= agcd;
	//debugp(axe);
	ll xt = 0; // xtimes;
	ll curx = 1;
	
    int roundT = abs(duck[did].S) * 2;
    REP(tmp, roundT){
#ifdef debugDuck
		cout << "ouodb----------------\n";
#endif
		xt++;
		ll nextx = 1 + (axe.F * xt) / axe.S; 
		int st = (curx & 1) ? curx >> 1 : (curx - 1) >> 1;
	   	int	end = (nextx & 1) ? nextx>> 1 : (nextx- 1) >> 1;
		st = curx >> 1;
		end = nextx >> 1;
		/*
		debug(tmp);
		debug(curx);
		debug(nextx);
		*/
				
        if ((tmp & 1) == 0) {
#ifdef debugDuck
			cout << "eve\n";
#endif
            bool cornor= false;
            if (isint(axe, xt)) {
                cornor = true;
				/*
				cout << "cornor at xt = " << xt << "\n";
				debugp(axe);
				*/
            }

            for(int i = st; i < end - cornor; i++){// avoid more step in the end
                dstep[did].eb(R);
            }
			if(cornor)
				dstep[did].eb(R);

            dstep[did].eb(U);
        }else{
#ifdef debugDuck
			cout << "odd\n";
#endif
            for(int i = st; i < end; i++){// avoid more step in the end
                dstep[did].eb(R);
            }
        }
		curx = nextx;
#ifdef debugDuck
    for(int d: dstep[did]){
        switch(d){
            case U:
                cout << "U";
                break;
            case D:
                cout << "D";
                break;
            case L:
                cout << "L";
                break;
            case R:
                cout << "R";
                break;
            default:
                cout << "wtf";
                break;
        }
    }
    cout << endl;
#endif
    }
    transposeduck(did);
#ifdef debugDuck
    cout << "for duck " << did << ": ";
    for(int d: dstep[did]){
        switch(d){
            case U:
                cout << "U";
                break;
            case D:
                cout << "D";
                break;
            case L:
                cout << "L";
                break;
            case R:
                cout << "R";
                break;
            default:
                cout << "wtf";
                break;
        }
    }
    cout << endl;
#endif
}

pii simulate(int a, int b){
    
    pii posA= getstart(a);
    pii posB= getstart(b);
	pii nposA, nposB;
    
    int Ai = 0, Bi = 0; 
    int tstp = 1;
    bool stopA, stopB;
    stopA = stopB = false;
	vis.clear();
	vis.resize(m, vec<int>(n, 0));
    vis[posA.X][posA.Y] =vis[posB.X][posB.Y] = true;
	
	int Acnt = 1;
	int Bcnt = 1;
/*
	cout << "processing \n";
	debug(a);
	debug(b);
*/
    while(!stopA || !stopB){
/*
		debugp(posA);
		debugp(posB);
*/
		if(!stopA){
			nposA.X = posA.X + mD[dstep[a][Ai]].X;
			nposA.Y = posA.Y + mD[dstep[a][Ai]].Y;
		}
		if(nposA.X >= m)
			nposA.X = 0;
		if(nposA.Y >= n)
			nposA.Y = 0;
		if(nposA.X < 0)
			nposA.X = m - 1;
		if(nposA.Y < 0)
			nposA.Y = n - 1;

		if(!stopB){
			nposB.X = posB.X + mD[dstep[b][Bi]].X;
			nposB.Y = posB.Y + mD[dstep[b][Bi]].Y;
		}
		if(nposB.X >= m)
			nposB.X = 0;
		if(nposB.Y >= n)
			nposB.Y = 0;
		if(nposB.X < 0)
			nposB.X = m - 1;
		if(nposB.Y < 0)
			nposB.Y = n - 1;
		// mutually
//		debugp(nposA);
//		debugp(nposB);
		if(nposB == posA && nposA == posB){
			stopA = true;
			stopB = true;
//			cout << "collide\n";
			break;
		}
		
		if(nposA == nposB){
			Acnt++;
			break;
		}
		
		if(vis[nposA.X][nposA.Y])
			stopA = true;
		else{
			++Acnt;
		}
		vis[nposA.X][nposA.Y] = true;
		if(vis[nposB.X][nposB.Y])
			stopB = true;
		else{
			vis[nposB.X][nposB.Y] = true;
			if(nposB != nposA)
				Bcnt++;
		}
		Ai = next(Ai, dstep[a].size()); 
		Bi = next(Bi, dstep[b].size()); 
		posB = nposB, posA = nposA;	
		if(!stopA || !stopB)
			tstp++;
    }
/*
	for(vec<int>& a: vis){
		for(int& te: a){
			cout << te << "  ";
		}		
		cout << endl;

	}

		debugp(posA);
		debugp(posB);
*/
    return pii(Acnt + Bcnt, tstp);
}

int main(){

    yccc;
	int Case = 1;
    while(cin >> m >> n){
        if(m == 0 && n == 0)
            break;
        dm = (double)m, dn = (double)n;
        //debug(dm);
        //debug(dn);
        cin >> k;
        init();
        REP(i, k){
            cin >> duck[i].F >> duck[i].S;
        }
        REP(i, k){
            precal(i);
        }
		pii getsimu;
		pii curans ;
        REP(i, k){
            for(int j = i + 1; j < k; j++){
                if(startpt(i) == startpt(j))
                    continue;
                getsimu = simulate(i, j); 
				/*
				cout << "i, j= " << i+1 << ", " << j+1  << endl;
				*/
				/*
				if(i == 4 && j == 9){
					cout << "i, j= " << i+1 << ", " << j+1  << endl;
					debugp(getsimu);
				}
				*/
				if(ANSs.empty()){
					ANSs.eb(i, j);
					curans = getsimu;
	//				debugp(getsimu);
				}else{
					if(getsimu.F > curans.F || (getsimu.F == curans.F && getsimu.S < curans.S)){
						ANSs.clear();
						ANSs.eb(i, j);
						curans = getsimu;
	//					debugp(getsimu);
					}else if(getsimu.F == curans.F && getsimu.S == curans.S){
						ANSs.eb(i, j);
					}

				}
            }
        }

		cout << "Case " << Case++ << "   Cells Illuminated: " << curans.F << "   Minimum Time: " << curans.S << endl;
		for(pii& item: ANSs){
			cout << "   Geoduck IDs:  " << item.F + 1 << "  " <<  item.S + 1 << endl;
		}
    }
    return 0;
}

