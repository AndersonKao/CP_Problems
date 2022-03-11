// 在case 判斷那邊確認過，剛好碰到也是不被允許的
#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;
 
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
 


const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;
const double epos = 1e-9;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
//#define otD
//#define biD
//#define kaD
//#define VD

int feq(double a, double b){
    a -= b;
    return ((abs(a) < 1e-9) ? 0 : (a > 0 ? 1 : -1));
}
 
int T, N;
ll xmin, ymin, xmax, ymax;
struct tree{
    ll x, y, d, h;
};
ll distance2(ll x, ll y, ll x2, ll y2){
    return ((x - x2) * (x - x2) + (y - y2) * (y - y2));
}
vec<tree> Fst; // Forest
int ka(int cut, int obs){
    // 0 for no ka, 1 for external bisector, 2 for otherwise
    double dis2 = distance2(Fst[cut].x, Fst[cut].y, Fst[obs].x, Fst[obs].y);
    double r = Fst[cut].d / 2.0;
    double r2 = Fst[obs].d / 2.0;
    double fdis = sqrt(dis2) - r2;
    double kdis = sqrt(Fst[cut].h * Fst[cut].h + r * r);
    if(feq(Fst[cut].h, fdis) < 0 && feq(kdis, fdis) < 0)
        return 0;
    else if(feq(Fst[cut].h, fdis) < 0 && feq(kdis, fdis) >= 0)
        return 1;
    else
        return 2;
}
int wallka(int cut, ll dis){
    double r = Fst[cut].d / 2.0;
    double kdis = sqrt(Fst[cut].h * Fst[cut].h + r * r);
    if(Fst[cut].h < dis && feq(kdis, dis) < 0)
        return 0;
    else if(Fst[cut].h < dis && feq(kdis, dis) >= 0)
        return 1;
    else
        return 2;
}
double mod2pi(double rad){ // remaining (-PI, PI)
    if(feq(rad, M_PI) == 1)
        return rad - 2 * M_PI;
    else if(feq(rad, -M_PI) == -1)
        return rad + 2 * M_PI;
    return rad;
}

pdd otherSol(int cut, int obs){
    double crad = atan2(Fst[obs].y - Fst[cut].y, Fst[obs].x - Fst[cut].x); // center rad
    double dis2 = distance2(Fst[cut].x, Fst[cut].y, Fst[obs].x, Fst[obs].y);
    double dis = sqrt(dis2);
    double r = Fst[cut].d / 2.0, r2 = Fst[obs].d / 2.0;
    double biseclen2 = (dis2 - (r + r2) * (r+r2));
    double newh2 = min((double)Fst[cut].h * Fst[cut].h, biseclen2);
    double k2 = (newh2+ (r * r));
    double k = sqrt(k2);
    /*
    double AS = (k + dis + r2) / 2;
    double Area = sqrt(AS * (AS - k) * (AS - dis) * (AS - r2));
    double fh = Area * 2 / dis;
    */
    //double rad = abs(atan2(fh, sqrt(k2 - fh * fh))) + abs(atan2(r,  newh));
    double rad = abs(acos((k2 + dis2 - r2*r2) / 2.0 / k / dis)) + abs(atan2(r,  sqrt(newh2)));
 //   double brad =  atan2(r + r2, biseclen2) - atan2(r, biseclen2); // bisector rad;
    //rad = min(rad, brad);
#ifdef otD
    debug(crad);
    debug(rad);
    debug(dis2);
    debug(r);
    debug(r2);
    debug(k2);
    debug(k);
    /*
    debug(AS);
    debug(Area);
    debug(fh);
    */
    cout << mod2pi(crad - rad) << ", " <<   mod2pi(crad + rad) << endl;
#endif 
    return pdd(mod2pi(crad - rad), mod2pi(crad + rad));
}
pdd interSol(int cut, int obs){
    double crad = atan2(Fst[obs].y - Fst[cut].y, Fst[obs].x - Fst[cut].x); // center rad
    double r = Fst[cut].d / 2.0, r2 = Fst[obs].d / 2.0;
    double dis2 = distance2(Fst[cut].x, Fst[cut].y, Fst[obs].x, Fst[obs].y);
    double dis = sqrt(dis2);
    double rx = dis * r2 / (Fst[cut].h + r2); //另一方斜邊
    double rad = abs(atan2(sqrt(rx * rx - r2 * r2), r2));
    //double rad = abs(acos(r2/ rx));
    return pdd(mod2pi(crad - rad), mod2pi(crad + rad));
}
double walrad(double dis2, int cut){
    double r = Fst[cut].d / 2.0;
    double K2 = r * r + Fst[cut].h * Fst[cut].h;
    double dis = sqrt(dis);
    double K = sqrt(K2);
    double rad = abs(atan2(sqrt(K2 - dis2), sqrt(dis2))) + abs(atan2(r,  Fst[cut].h));
    //double rad = abs(acos(dis/K)) + abs(atan2(r,  Fst[cut].h));
    //cout << "rad: " << rad << endl;
    return rad;
}
double wallInrad(double dis2, int cut){
    double r = Fst[cut].d / 2.0;
    double K2 = r * r + Fst[cut].h * Fst[cut].h;
    double rad = abs(atan2(sqrt(K2 - dis2), sqrt(dis2)));
    //cout << "Inrad: " << rad << endl;
    return rad;
}
double toangle(double rad){
    return rad / M_PI * 180;
}
int main(){

    int cnt = 0;
    vector<bool> removed(100);
    while(cin >> xmin >> ymin >> xmax >> ymax >> N){
        if(!xmin && !ymin && !xmax && !ymax && !N)
            break;
        Fst.resize(N);
        fill(removed.begin(), removed.end(), false);
        REP(i, N){
            cin >> Fst[i].x >> Fst[i].y >> Fst[i].d >> Fst[i].h;
        }
        int ANS = 0;
        vec<pdd> V;
        REP(i, N){
            //cout << "doing " << i << endl;
            if(removed[i])
                continue;
            V.clear();
            // trees
            int kacase;
            REP(j, N){
                if(i == j || removed[j])
                    continue;
                #ifdef VD
                cout << i << ", " << j << endl;
                #endif
                if(kacase = ka(i, j)){
                    #ifdef VD
                    cout << ".  ka case: " << kacase << endl;
                    #endif
                    if(kacase == 1){
                        pdd indisable = interSol(i, j);
                        pdd disable = otherSol(i, j);
                        #ifdef VD
                        cout << toangle(indisable.F) << ", " << toangle(indisable.S) << ", " << toangle(disable.F) << ", " << toangle(disable.S) << endl;
                        #endif
                        // Normally, disable.first < indisable.first < indisable.second < disable.second
                        if(feq(disable.F, indisable.F) == 1){ // uprad < down rad
                            V.emplace_back(disable.F, M_PI);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                            V.emplace_back(-M_PI, indisable.F);
                        }else
                            V.emplace_back(disable.F, indisable.F);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                        if(feq(indisable.S, disable.S) == 1){ // uprad < down rad
                            V.emplace_back(indisable.S, M_PI);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                            V.emplace_back(-M_PI, disable.S);
                        }else
                            V.emplace_back(indisable.S, disable.S);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                    }
                    else if(kacase == 2){
                        pdd disable = otherSol(i, j);
                        if(feq(disable.F, disable.S) == 1){ // uprad < down rad
                            V.emplace_back(disable.F, M_PI);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                            V.emplace_back(-M_PI, disable.S);
                        }else
                            V.emplace_back(disable);
                        #ifdef VD
                        cout << "collide with " << j <<  ": [" << toangle(V.back().F) << ", " << toangle(V.back().S)<< "]\n";
                        #endif
                    }
                }
            }
            // wall
            // minx
            double rad, Inrad;
            ll dis = Fst[i].x - xmin;
            #ifdef VD
            cout << "minx: ";
            #endif
            if(kacase = wallka(i, dis)){
                #ifdef VD
                cout << kacase << " ";
                #endif
                if(kacase == 1){
                    rad = walrad(dis * dis, i);
                    Inrad = wallInrad(dis * dis, i);
                    V.emplace_back(M_PI - rad, M_PI - Inrad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    V.emplace_back(Inrad -M_PI, rad - M_PI);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif 
                }else{
                    rad = walrad(dis * dis, i);
                    V.emplace_back(M_PI - rad, M_PI);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                    V.emplace_back(-M_PI, rad - M_PI);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }
            }
            #ifdef VD
            cout << "maxx: ";
            #endif
            dis = xmax - Fst[i].x; //
            if(kacase = wallka(i, dis)){
                #ifdef VD
                cout << kacase << " ";
                #endif
                if(kacase == 1){
                    rad = walrad(dis * dis, i);
                    Inrad = wallInrad(dis * dis, i);
                    V.emplace_back(Inrad, rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                    V.emplace_back(-rad , -Inrad );
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }else{
                    rad = walrad(dis * dis, i);
                    V.emplace_back(-rad, rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }
            }
            #ifdef VD
            cout << "miny: ";
            #endif
            dis = Fst[i].y - ymin; //
            if(kacase = wallka(i, dis)){
                #ifdef VD
                cout << kacase << " ";
                #endif
                double HPI = -M_PI / 2.0;
                if(kacase == 1){
                    rad = walrad(dis * dis, i);
                    Inrad = wallInrad(dis * dis, i);
                    V.emplace_back(HPI - rad, HPI - Inrad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                    V.emplace_back(HPI + Inrad, HPI + rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif 
                }else{
                    rad = walrad(dis * dis, i);
                    V.emplace_back(HPI - rad, HPI + rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }
            }
            #ifdef VD
            cout << "maxy: ";
            #endif
            dis = ymax - Fst[i].y; //
            if(kacase = wallka(i, dis)){
                #ifdef VD
                cout << kacase << " ";
                #endif
                double HPI = M_PI / 2.0;
                if(kacase == 1){
                    rad = walrad(dis * dis, i);
                    Inrad = wallInrad(dis * dis, i);
                    V.emplace_back(HPI - rad, HPI - Inrad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                    V.emplace_back(HPI + Inrad, HPI + rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }else{
                    rad = walrad(dis * dis, i);
                    V.emplace_back(HPI - rad, HPI + rad);
                    #ifdef VD
                    cout << "[" << toangle(V.back().F) << ", "  << toangle(V.back().S)<<"]\n";
                    #endif
                    
                }
            }
            bool could = false;
            if(V.size() == 0){
                could = true;
                #ifdef VD
                cout << "noclide \n";
                #endif
            }else{
                sort(V.begin(), V.end());
                #ifdef VD
                for(auto& e: V)
                    cout << "[" << toangle(e.first) << ", " << toangle(e.S) << "], ";
                cout << endl;
                #endif
                if(feq(V[0].first, -M_PI) == 1){
                    #ifdef VD
                    cout << "\ncouutin----\n";
                    cout << V[0].first << " for the V[0]\n";
                    #endif
                    could = true;
                }
                else{
                    double last = -M_PI;
                    for (unsigned int i = 0; i < V.size(); i++){
                        last = max(last, V[i].second);
                        if(i != V.size() - 1){
                            if(feq(last, V[i+1].first) < 0){
                                #ifdef VD
                                cout << "\ncouutin\n";
                                cout << "V[i, i+1] : " << toangle(V[i].second) << ", " << toangle(V[i + 1].first) << endl;
                                #endif
                                could = true;
                                break;
                            }
                        }else{
                            if(feq(last, M_PI) == -1){
                                #ifdef VD
                                cout << "\ncouutin\n";
                                cout << "last: " << last << endl;
                                #endif
                                could = true;
                            }
                        }
                    }
                }
            }
            if(could){
                #ifdef VD
                cout << "tree : " << i  << " was cut"<< endl;
                #endif
                removed[i] = true;
                i = -1;
                ANS++;
            }
        }
        cout << "Forest " << ++cnt << endl;
        cout << ANS << " tree(s) can be cut" << endl << endl;
    }
        
    return 0;
}

/*

0 0 10 10 3
3 3 2 10
5 5 3 1
2 8 3 9
0 0 0 0 0

*/

