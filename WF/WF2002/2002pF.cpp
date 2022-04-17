#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false)
#define TOP second 
#define BOT first 
#define X real() 
#define Y imag() 
#define al(a) (a).begin(), (a).end()
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define eb emplace_back
#define PR(x) cout << #x << " = " << (x) << endl
#define PRP(x) cout << #x << " = " << (x).first << ", " << (x).second << endl
#define PRp(x) cout << #x << " = " << (x).real()<< ", " << (x).imag()<< endl
#define endl "\n"

using ll = long long;
using pii = pair<int, int>;
using point = complex<double>;
template<typename T>
using vec = vector<T>;
using segment = pair<point, point>;
using viIter = vec<int>::iterator;
const double eps = 1e-9;

int nTrapz = 0;
vec<point> pnts;
vec<point> holes;
vec<int> onlyY;
vec<bool> bothole, tophole;
vec<vec<int>> G;

struct UnionFind{
    vec<int> seq;
    UnionFind(){
        seq.clear();
    }
    UnionFind(int n){
        seq.resize(n);
        for(int i = 0 ;i < n; i++){
            seq[i] = i;
        }
    }
    void reset(int n){
        seq.resize(n);
        for(int i = 0 ;i < n; i++){
            seq[i] = i;
        }
    }
    int getSet(int a){
        if(seq[a] == a)
            return a;
        return seq[a] = this->getSet(seq[a]);
    }
    void Union(int a, int b){
        int pa = getSet(a);
        int pb = getSet(b);
        if(pa == pb)
            return;
        seq[pa] = pb;
    }
    bool sameSet(int a, int b){
        return getSet(a) == getSet(b);
    }
};

struct Trapezium{
    segment left, right;
    int id;
    Trapezium(segment& l, segment& r):left(l), right(r){
        id = nTrapz++;
    }
    double minx(){
        return min(left.TOP.X, left.BOT.X);
    }
    double maxx(){
        return max(right.TOP.X, right.BOT.X);
    }
    double miny(){
        return min(left.BOT.Y, right.BOT.Y);
    }
    double maxy(){
        return max(left.TOP.Y, right.TOP.Y);
    }
    void info(){
        cout << "Trapezium id: " << id << endl;
        cout << "left: (" << left.BOT.X << ", " << left.BOT.Y << ") to (" << left.TOP.X << ", " << left.TOP.Y << ") \n";
        cout << "right : (" << right.BOT.X << ", " << right.BOT.Y << ") to (" << right.TOP.X << ", " << right.TOP.Y << ") \n";
        if(bothole[id]){
            cout << "\nfail to store \n";
        }
        cout << endl;
    }
    double area(){
        return  (right.TOP.Y - right.BOT.Y) / 2.0 * (right.TOP.X+ right.BOT.X - left.BOT.X - left.TOP.X ) ;
    }
};

void printseg(segment a){
    cout << "seg : (" << a.BOT.X << ", " << a.BOT.Y << ") to (" << a.TOP.X << ", " << a.TOP.Y << ") \n";
}

auto ycmp = [](const point& a, const point&b){
    return a.Y < b.Y;
};

int dcmp(double a, double b){
    if(fabs(a - b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}


void init(){
    nTrapz = 0;
    pnts.clear();
    holes.clear();
    onlyY.clear();
    bothole.clear();
    tophole.clear();
    G.clear();
}

double getXonSegment(const segment& seg, int liney){
    double y = (double)liney; 
    // linear algebra
    // asking for X-axis of the intersect of `y = liney` and segment seg.
    return (y - seg.BOT.Y) * (seg.TOP.X - seg.BOT.X) / (seg.TOP.Y - seg.BOT.Y) + seg.BOT.X;
}

map<int, vec<segment>> getSegments(){
    map<int, vec<segment>> ret;
    for(int i = 0; i < (int)pnts.size(); i++){
        int j = (i + 1 == (int)pnts.size() ? 0 : i + 1);
        segment seg = make_pair(pnts[i], pnts[j]);
        int miny = min(pnts[i].Y, pnts[j].Y);
        int maxy = max(pnts[i].Y, pnts[j].Y);
        viIter nxt = lower_bound(al(onlyY), miny); 
        viIter end = lower_bound(al(onlyY), maxy); 
//        cout << "nxt " << *nxt << ", end " << *end << endl; 
        for(viIter it = nxt++; it != end; nxt++, it++){
            double botX = getXonSegment(seg, *it);
            double topX = getXonSegment(seg, *nxt);
            ret[*it].eb(point(botX, *it), point(topX, *nxt)); 
        }
    }

    for(pair<const int, vec<segment>> &it : ret){
        sort(al((it.second)), [](const segment&a, const segment& b) {
            double axmid = a.TOP.X + a.BOT.X;
            double bxmid = b.TOP.X + b.BOT.X;
            return axmid < bxmid;
        });
    }
    return ret;
}

vec<vec<Trapezium>> getTraps(map<int, vec<segment>>& segments){
    vec<vec<Trapezium>> ret;
    for(pair<const int, vec<segment>>& segs: segments){
        vec<Trapezium> trapz;

        for(int i = 0; i < (int)segs.second.size(); i+=2) // do this always even ? then we can use iterator
        {
            trapz.eb(segs.second[i], segs.second[i+1]); 
        }
        ret.eb(trapz);
    }
    return ret;
}

bool touched(Trapezium &top, Trapezium& bot){
    return dcmp(max(top.left.BOT.X, bot.left.TOP.X), min(top.right.BOT.X, bot.right.TOP.X)) < 0;
}
void buildGraph(vec<vec<Trapezium>>& traps){
    G.resize(nTrapz);
    for(int i = 0 ;i < (int)traps.size() - 1; i++){
        vec<Trapezium>& bot = traps[i];
        vec<Trapezium>& top = traps[i+1];
        for(int k = 0; k < (int)bot.size(); k++)
            for(int j = 0; j < (int)top.size(); j++){
                if (touched(top[j], bot[k])) {
                    G[top[j].id].eb(bot[k].id);
                    //G[bot[k].id].eb(top[j].id);
                }
            }
    }
}
bool inside(point& hole, double st, double ed){
    return dcmp(hole.X, st) >= 0 && dcmp(hole.X, ed) <= 0;
}
void dealholes(vec<vec<Trapezium>> & traps){
    bothole.resize(nTrapz, false);
    tophole.resize(nTrapz, false);
    for(vec<Trapezium>& trapz: traps){
        for(Trapezium& trap: trapz){
            double maxy = trap.maxy();
            double miny = trap.miny();
            vec<point>::iterator it = lower_bound(al(holes), point(0, miny), ycmp);
            for(; it != holes.end() && dcmp(it->Y, miny) == 0; it++){
                if(inside(*it, trap.left.BOT.X, trap.right.BOT.X)){
                    bothole[trap.id] = true;
                }
            }
            //it = lower_bound(al(holes), point(0, maxy), ycmp);
            for(; it != holes.end() && dcmp(it->Y, maxy) == 0; it++){
                if(inside(*it, trap.left.TOP.X, trap.right.TOP.X)){
                    tophole[trap.id] = true;
                }
            }
        }
    }
}

double solve(vec<vec<Trapezium>> & traps){
    UnionFind UF(nTrapz);
    double ans = 0.0;
    for(vec<Trapezium>& trapz: traps){
        for(Trapezium& trap: trapz){
            for(int &u: G[trap.id]){
                /*
                if(u > trap.id){ // maybe buggy because same layer
                    continue;
                }
                */
                int uSet = UF.getSet(u);
                int trapS = UF.getSet(trap.id);
                if(bothole[uSet] || bothole[trapS]){
                    bothole[uSet] = bothole[trapS] = true;
                }
                UF.Union(u, trap.id);
            } 
        }
        for(Trapezium& trap: trapz){
            if(!bothole[UF.getSet(trap.id)]){
                ans += trap.area();
            }
        }
        for(Trapezium& trap: trapz){
            if(tophole[trap.id]){
                bothole[UF.getSet(trap.id)] = true;
            }
        }
    }
    return ans;
}

int main(){
    //yccc;
    int n;
    int cnt = 1;
    while(cin >> n){
        if(n == 0)
            break;
        init();
        REP(i, n){
            int x, y, ishole;
            cin >> x >> y >> ishole;
            pnts.eb(x, y);
            if(ishole == 1){
                holes.eb(x,y);
            }
            onlyY.eb(y);
        } 
        /*
        for(auto it: pnts){
            cout << it.X << ", " << it.Y << endl;
        }
        */
        sort(al(onlyY));
        onlyY.resize(distance(onlyY.begin(), unique(al(onlyY))));

        /*
        for(auto it: onlyY){
            cout << "ys: " << it << endl;
        }
        */
        sort(al(holes), ycmp);
        /*
        for(auto& a: holes){
            PRp(a); 
        }
        */
        map<int, vec<segment>> segments = getSegments();
        vec<vec<Trapezium>> traps = getTraps(segments);
        buildGraph(traps);
        dealholes(traps);
        /*
        cout << segments.size() << endl;
        cout << traps.size() << endl;
        int lid = 0;
        for(vec<Trapezium>& trapz: traps){
            cout << "layer: " << lid++ << endl;
            for(Trapezium& trap: trapz){
                trap.info();
            }
        }

        for(int i = 0; i < nTrapz; i++){
            cout << "id " << i << " : ";
            for(int & v: G[i]){
                cout << v << ", ";
            }
            cout << endl;
        }
        */
        float ans = solve(traps);
  //      cout << fixed << setprecision(7);
//        cout << "Cave " << cnt++ << ": Oil capacity = " << round(solve(traps) / 2.0 ) << endl << endl;
		printf("Cave %d: Oil capacity = %.0f\n\n", cnt++, ans);
//        cout << "Cave " << cnt++ << ": Oil capacity = " << round(ans) << endl << endl;
    }
    return 0;
}
