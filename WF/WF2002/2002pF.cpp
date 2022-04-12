#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(false), ios_base::sync_with_stdio(false)
#define TOP first
#define BOT second
#define X first
#define Y second
#define al(a) (a).begin(), (a).end()
#define REP(i, n) for(int i = 0; i < (int)(n); i++)
#define eb emplace_back
#define PR(x) cout << #x << " = " << (x) << endl
#define PRP(x) cout << #x << " = " << (x).first << ", " << (x).second << endl

using ll = long long;
using pii = pair<int, int>;
using point = pair<int, int>;
template<typename T>
using vec = vector<T>;

const double eps = 1e-9;





vec<point> pnts;
vec<point> holes;

auto ycmp = [](const point& a, const point&b){
    return a.Y < b.Y;
};

int dcmp(double a, double b){
    if(fabs(a - b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}


int main(){
//  yccc;
    int n;
    int cnt = 1;
    while(cin >> n){
        if(n == 0)
            break;
        REP(i, n){
            int x, y, ishole;
            cin >> x >> y >> ishole;
            pnts.eb(x, y);
            if(ishole == 1){
                holes.eb(x,y);
            }
        } 
        sort(al(holes), ycmp);
        for(auto& a: holes){
            PRP(a); 
        }
        cout << "Cave " << cnt++ << ": Oil capacity = " << endl;
    }

    return 0;
}
