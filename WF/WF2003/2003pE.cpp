// AC 
// cut impossible offset, max, min in failed range.
// TLE
// cut tested offset
// TLE
// cut if hys.size==0, or cys.size==0
// WA
// vhli == vhlj and vcli == vclj logic error, may cause wrong offset
// WA
// mergesort的order有些問題，如果有重複的hy cy要特別處裡
#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define eb emplace_back
#define X first
#define Y second
#define endl '\n'
#define al(a) a.begin(), a.end()
#define debug(x) cout << #x << ": " << x << endl;
#define dept(x) cout << "(" << x.X << ", " << x.Y << ")\n";
template <typename T>
using vec = vector<T>;
using point = pair<int, int>;
using pii = pair<int, int>;
const int MININT = numeric_limits<int>::min();
const int MAXINT = numeric_limits<int>::max();

vec<point> hpnts, cpnts;
vec<pair<int, pair<int, int>>> hlines, clines;
pii c_off(0, 0);
inline int next_i(int i, int n){
    return (i + 1 == n ? 0 : i + 1);
}
inline point cp(const point& pt){
    return {pt.X + c_off.X, pt.Y + c_off.Y};
}

void ppt(point a, point b){
    cout << "(" << a.X << ", " << a.Y << ") to (" << b.X << ", " << b.Y << ")\n";
}
vec<int> xset;
vec<int> hys, cys;
bool simulate()
{
    xset.clear();
    REP(i, hpnts.size())
    {
        xset.eb(hpnts[i].X);
    }
    REP(i, cpnts.size()){
        xset.eb(cp(cpnts[i]).X);
    }
    sort(al(xset));
    xset.resize(distance(xset.begin(), unique(al(xset))));
    for (int iter = 0; iter < xset.size() - 1; iter++)
    {
        hys.clear(), cys.clear();
        int l = xset[iter], r = xset[iter + 1];
#ifdef SIM
        cout << "\nrange " << l << ", " << r << "--------------\n";
        #endif
        REP(i, hlines.size()){
            int lx = min(hlines[i].second.first, hlines[i].second.second);
            int rx = max(hlines[i].second.first, hlines[i].second.second);
            if (lx <= l && r <= rx){
                hys.eb(hlines[i].first);
            }
        }
        if(hys.size() == 0)
            continue;
        REP(i, clines.size())
        {
            int lx = min(clines[i].second.first, clines[i].second.second) + c_off.X;
            int rx = max(clines[i].second.first, clines[i].second.second) + c_off.X;
            if (lx <= l && r <= rx){
                cys.eb(clines[i].first + c_off.Y);
            }
        }
        if(hys.size() != 0 && cys.size() == 0)
            return false;
#ifdef SIM
        cout << "hys:\n";
        for (int y : hys)
        {
            cout << y << " ";
        }
        cout << "cys:\n";
        for (int y : cys)
        {
            cout << y << " ";
        }
        cout << endl;
        #endif

        int hid, cid;
        hid = cid = 0;
        bool incover = false;
        bool inhole = false;
        while (hid < hys.size())
        {
            if (cid < cys.size() && cys[cid] < hys[hid])
            {
                cid++;
                incover = !incover;
                if(hid < hys.size() && cys[cid-1] == hys[hid])
                    continue;
            }
            else{
                hid++;
                inhole = !inhole;
                if(cid < cys.size() && cys[cid] == hys[hid-1])
                    continue;
            }
            
            if(inhole && !incover){
                #ifdef SIM
                if(cid < cys.size())
                    cout << cys[cid] << endl;
                if(hid < cys.size()) 
                    cout << cys[hid] << endl;
                cout << "error\n";
                #endif
                return false;
            }
        }
    }
    return true;
}
set<pii> offSet;

int main()
{
    yccc;
    int h, c;
    int caseN = 1;
    while (cin >> h >> c)
    {
        if(h < 4 && c < 4)
            break;
        hpnts.clear();
        cpnts.clear();
        hlines.clear();
        clines.clear();
        offSet.clear();
        point hmaxpt(MININT, MININT);
        point hminpt(MAXINT, MAXINT);
        point cmaxpt(MININT, MININT);
        point cminpt(MAXINT, MAXINT);
        REP(i, h)
        {
            int x, y;
            cin >> x >> y;
            hpnts.eb(x, y);
            hmaxpt.X = max(x, hmaxpt.X);
            hmaxpt.Y = max(y, hmaxpt.Y);
            hminpt.X = min(x, hminpt.X);
            hminpt.Y = min(y, hminpt.Y);
        }
        REP(i, c){
            int x, y;
            cin >> x >> y;
            cpnts.eb(x, y);
            cmaxpt.X = max(x, cmaxpt.X);
            cmaxpt.Y = max(y, cmaxpt.Y);
            cminpt.X = min(x, cminpt.X);
            cminpt.Y = min(y, cminpt.Y);
        }
        for (int i = 0; i < h; i++){
            int j = next_i(i, h);
            if (hpnts[i].Y == hpnts[j].Y)
            {
                hlines.eb(hpnts[i].Y, pii(hpnts[i].X, hpnts[j].X));
            }
        }
        for (int i = 0; i < c; i++){
            int j = next_i(i, c);
            if (cpnts[i].Y == cpnts[j].Y)
            {
                clines.eb(cpnts[i].Y, pii(cpnts[i].X, cpnts[j].X));
            }
        }
        sort(al(hlines));
        sort(al(clines));
        #ifdef linecheck
        for(auto&e: hlines){
            cout << e.first << " with range " << e.second.first << ", " << e.second.second << endl;
        }
        for(auto&e: clines){
            cout << e.first << " with range " << e.second.first << ", " << e.second.second << endl;
        }
        #endif

        bool vhli, vhlj, vcli, vclj;
        vhli = vhlj = vcli = vclj = false;
        int hx, hy, cx, cy;
        bool ans = false;
        for (int hli = 0; hli < h; hli++)
        {
            vhli = hpnts[next_i(hli, h)].X == hpnts[hli].X;
            if (vhli)
            {
                hx = hpnts[hli].X;
            }
            else
            {
                hy = hpnts[hli].Y;
            }
            for (int hlj = hli + 1; hlj < h; hlj+=2)
            {

                vhlj = (hpnts[next_i(hlj, h)].X == hpnts[hlj].X);
                //if (vhli == vhlj)
                 //   continue;
                if(vhlj){
                    hx = hpnts[hlj].X;
                }else{
                    hy = hpnts[hlj].Y;
                }
                for (int cli = 0; cli < c; cli++)
                {
                    vcli = cpnts[next_i(cli, c)].X == cpnts[cli].X;
                    if (vcli)
                    {
                        cx = cpnts[cli].X;
                    }
                    else
                    {
                        cy = cpnts[cli].Y;
                    }
                    for (int clj = cli+1; clj < c; clj+=2){
                        vclj = (cpnts[next_i(clj, c)].X == cpnts[clj].X);
                  //      if (vcli == vclj)
                   //         continue;
                        if(vclj){
                            cx = cpnts[clj].X;
                        }else{
                            cy = cpnts[clj].Y;
                        }
                        c_off.X = (hx - cx);
                        c_off.Y = (hy - cy);
                        point ncmaxpt = cp(cmaxpt);
                        point ncminpt = cp(cminpt);
                        if (hmaxpt.X > ncmaxpt.X || hmaxpt.Y > ncmaxpt.Y || hminpt.X < ncminpt.X || hminpt.Y < ncminpt.Y)
                            continue;                
                        if (offSet.find(c_off) != offSet.end())
                            continue;
                        offSet.emplace(c_off);
                        #ifdef picking
                        cout << "pinking hLine ";
                        ppt(hpnts[hli], hpnts[next_i(hli, h)]);
                        cout << "and ";
                        ppt(hpnts[hlj], hpnts[next_i(hlj, h)]);
                        cout << endl;
                        cout << "pinking cLine ";
                        ppt(cpnts[cli], cpnts[next_i(cli, c)]);
                        cout << "and ";
                        ppt(cpnts[clj], cpnts[next_i(clj, c)]);
                        cout << endl;
                        #endif
                        #ifdef Doffset
                        cout << "using offset ";
                        dept(c_off);
                        #endif
                        if ((ans = simulate()))
                        {
                            break;
                        }
                    }
                    if(ans)
                        break;
                }
                if(ans)
                    break;
            }
            if(ans)
                break;
        }
        cout << "Hole " << caseN++ << ": ";
        if (ans)
            cout << "Yes";
        else
            cout << "No";
        cout << endl;
    }
    return 0;
}