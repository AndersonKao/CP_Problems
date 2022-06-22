#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)n; i++)
#define REP1(i, n) for (int i = 1; i <= (int)n; i++)
#define eb emplace_back
template <typename T>
using vec = vector<T>;
#define al(x) x.begin(), x.end()
#define debug(x) cout << #x << " := " << x << endl;
#define depii(x) cout << #x << " := " << x.first << ", " << x.second << endl;
#define F first
#define S second
#define x first
#define y second

using point = pair<int, int>;
using edge = pair<point, point>;
using pii = pair<int, int>;
vec<vec<int>> direc = {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0}};

void BFS(vec<vec<int>>& dis, vec<vec<char>>&chmap, vec<vec<bool>>& vis, point st, point ed){
    
    queue<pii> mQ;
    queue<pii> nextQ;
    mQ.emplace(st);
    vis[st.y][st.x] = true;
    int round = 1;
    do
    {
        while (!mQ.empty())
        {
            point cur = mQ.front();
            mQ.pop();
            REP(i, 4){
                int xi = cur.x + direc[i][0];
                int yi = cur.y + direc[i][1];
                if(xi <0 || xi >= chmap[0].size() || yi < 0 || yi >= chmap.size())
                    continue;
                if(vis[yi][xi])
                    continue;
                vis[yi][xi] = true;
                if (chmap[yi][xi] == '.') {
                    dis[yi][xi] = dis[cur.y][cur.x];
                    mQ.emplace(xi, yi);
                }
                else if (chmap[yi][xi] == 'R')
                {
                    dis[yi][xi] = min(dis[yi][xi], dis[cur.y][cur.x] + 1);
                    nextQ.emplace(xi, yi);
                }
            }
            if(vis[ed.y][ed.x]){
//                cout << "found\n";
                break;
            }
        }
        if(vis[ed.y][ed.x])
            break;
        mQ = nextQ;
    } while (!mQ.empty());
}

int main()
{

    int n;
    int citN = 1;
    while (cin >> n)
    {
        if(n == 0)
            break;
        vec<edge> E;
        vec<int> xset, yset;
        REP(i, n)
        {
            point st, ed;
            cin >> st.x >> st.y >> ed.x >> ed.y;
            E.emplace_back(min(st, ed), max(st, ed));
            xset.eb(st.x);
            xset.eb(ed.x);
            yset.eb(st.y);
            yset.eb(ed.y);
        }
        point peter, univer;
        cin >> peter.x >> peter.y >> univer.x >> univer.y;
        xset.eb(peter.x), xset.eb(univer.x);
        yset.eb(peter.y), yset.eb(univer.y);
        sort(al(xset));
        sort(al(yset));
        xset.resize(distance(xset.begin(), unique(al(xset))));
        yset.resize(distance(yset.begin(), unique(al(yset))));
        #ifdef UNIQLO
        cout << "xset:\n";
        for(int x: xset)
            cout << x << " ";
        cout << endl;
        cout << "yset:\n";
        for(int y: yset)
            cout << y << " ";
        cout << endl;
        #endif
        REP(i, n){
            E[i].F.x = 1+2*(lower_bound(al(xset), E[i].F.x) - xset.begin());
            E[i].F.y = 1+2*(lower_bound(al(yset), E[i].F.y) - yset.begin());
            E[i].S.x = 1+2*(lower_bound(al(xset), E[i].S.x) - xset.begin());
            E[i].S.y = 1+2*(lower_bound(al(yset), E[i].S.y) - yset.begin());
        }
        peter.x = 1+2*(lower_bound(al(xset), peter.x) - xset.begin());
        peter.y = 1+2*(lower_bound(al(yset), peter.y) - yset.begin());
        univer.x = 1+2*(lower_bound(al(xset), univer.x) - xset.begin());
        univer.y = 1+2*(lower_bound(al(yset), univer.y) - yset.begin());
        int xmaplen = xset.size() * 2 + 4;
        int ymaplen = yset.size() * 2 + 4;
        #ifdef Relabel
        debug(xmaplen);
        debug(ymaplen);
        depii(peter);
        depii(univer);
        #endif
        vec<vec<char>> chmap(ymaplen, vec<char>(xmaplen, '.'));
        vec<vec<int>> dismap(ymaplen, vec<int>(xmaplen, 1000000000));
        vec<vec<bool>> vismap(ymaplen, vec<bool>(xmaplen, false));
        
        REP(i, n){
            if(E[i].F.x == E[i].S.x){
                int xi = E[i].F.x;
                for (int yi = E[i].F.y; yi <= E[i].S.y; yi++)
                {
                    chmap[yi][xi] = 'R';
                }
            }
            else {
                int yi = E[i].F.y;
                for (int xi = E[i].F.x; xi <= E[i].S.x; xi++)
                {
                    chmap[yi][xi] = 'R';
                }
            }
        }
        dismap[peter.y][peter.x] = 0;
        BFS(dismap, chmap, vismap, peter, univer);
        #ifdef DBFS
        for (int yi = chmap.size() - 1; yi >= 0; yi--){
            for (int xi = 0; xi < chmap[yi].size(); xi++)
            {
                cout << setw(2) << chmap[yi][xi] << " ";
            }
            cout << endl;
        }
        cout <<"----------------" << endl;
        for (int yi = dismap.size() - 1; yi >= 0; yi--){
            for (int xi = 0; xi < dismap[yi].size(); xi++)
            {
                cout << setw(4) << dismap[yi][xi] << " ";
            }
            cout << endl;
        }
        cout <<"----------------" << endl;
        #endif
        cout << "City " << citN++ << endl;
        cout << "Peter has to cross " << dismap[univer.y][univer.x] << " streets\n";
    }

    return 0;
}