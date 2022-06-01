// AC using Antpos not PathSet to renew map
#include <bits/stdc++.h>
using namespace std;
#define yccc cin.tie(0), ios_base::sync_with_stdio(false);
#define REP(i, n) for (int i = 0; i < n; i++)
#define X real() 
#define Y imag() 
#define eb emplace_back
#define al(x) x.begin(), x.end()
using pt = complex<int>;
using pii = pair<int, int>;
#define debug(x) //cout << #x << ": " << x << "\n";
#define debug2(x) //cout << #x << ": " << x << "\n";
#define dept(x) cout << #x << "(" << x.X << ", " << x.Y << ")\n";

#define NOTYET 0
#define HOLD 1
#define MF 2
#define IN_Q 3
#define TO_END 4

template <typename T>
using vec = vector<T>;
vec<pt> dir = {
    {0, 1},
    {0, -1},
    {-1, 0},
    {1, 0}
};
struct ant{
    pt cur_pos, last_pos;
    int waitT, oldT; // waited time;
    int plen;  // pathlen
    int dir = -1, ldir = -1;
    ant() : cur_pos(0, 0), last_pos(0, 0), waitT(0), plen(0)
    {
    }
};
template<typename T>
void domap(vec<vec<T>>& map, int x, int y, T val){
    map[x + 100][y + 100] = val;
}
template<typename T>
T getmap(vec<vec<T>>& map, int x, int y){
    /*
    if(x + 100 > 200)
        cout << "error " << x << endl;
    else if(y + 100 > 200)
        cout << "error " << y << endl;
        */

    return map[x + 100][y + 100];
}
template<typename T>
void do3map(vec<vec<vec<T>>>& map, int x, int y, int i, T val){
    map[x + 100][y + 100][i] = val;
}
template<typename T>
T get3map(vec<vec<vec<T>>>& map, int x, int y, int i){
    return map[x + 100][y + 100][i];
}
pii antother(vec<vec<vec<int>>>& Antmap, int x, int y, int id){
    //cout << "Another at " << x << ", " << y << endl;
    for (int i = 0; i < 4; i++)
    {
        int idx = Antmap[x + 100][y + 100][i];
        //cout << ": " << idx << endl;
       
        if (idx != -1 && idx != id)
            return {idx, i};
    }
    return {-1, -1};
}
void PrintMap(vec<vec<int>>& Map){
    for (int y = 10; y >= -10; y--){
        for (int x = -10; x <= 10; x++){
            if(Map[x + 100][y + 100] != -1)
                cout << " ";
            cout << Map[x + 100][y + 100] << " ";
        }
        cout << endl;
    }
}
void PrintIntersect(vec<vec<bool>>& inter){
    for (int y = 10; y >= -10; y--){
        for (int x = -10; x <= 10; x++){
            cout << inter[x + 100][y + 100] << " ";
        }
        cout << endl;
    }
}
const int LEN = 205;
int main()
{
    yccc;
    int T;
    cin >> T;
    int cnt = 1;
    while (T--)
    {
        if(cnt != 1)
            cout << endl;
        int n, m, d;
        cin >> n >> m >> d;
        vec<vec<int>> Map(LEN, vec<int>(LEN, -1));
        vec<vec<vec<int>>> Antmap(LEN, vec<vec<int>>(LEN, vec<int>(4, -1)));
        vec<vec<bool>> intersect(LEN, vec<bool>(LEN, false));
        vec<ant> Ants(m);
        vec<int> Carl;
//        vec<pt> PathSet;
        pt END;
        pt cur(0, 0);
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            pt nxt(x, y);
            END = nxt;
            if (cur.X == nxt.X)
            {
                if(cur.Y < nxt.Y){
                    for (int j = cur.Y; j < nxt.Y; j++){
                        Carl.eb(0);
                        if(getmap(Map, cur.X, j) == 0)
                            domap(intersect, cur.X, j, true);
                        else{
                            domap(Map, cur.X, j, 0);
                            //PathSet.eb(cur.X, j);
                        }
                    }
                }else{
                    for (int j = cur.Y; j > nxt.Y; j--){
                        Carl.eb(1);
                        if(getmap(Map, cur.X, j) == 0)
                            domap(intersect, cur.X, j, true);
                        else{
                            domap(Map, cur.X, j, 0);
                            //PathSet.eb(cur.X, j);
                        }
                    }
                }
            }
            else
            {
                if (cur.X < nxt.X)
                {
                    for (int j = cur.X; j < nxt.X; j++){
                        Carl.eb(3);
                        if(getmap(Map, j, cur.Y) == 0)
                            domap(intersect, j, cur.Y, true);
                        else{
                            domap(Map, j, cur.Y, 0);
                            //PathSet.eb(j, cur.Y);
                        }
                    }
               }else{
                    for (int j = cur.X; j > nxt.X; j--){
                        Carl.eb(2);
                        if(getmap(Map, j, cur.Y) == 0)
                            domap(intersect, j, cur.Y, true);
                        else{
                            domap(Map, j, cur.Y, 0);
                            //PathSet.eb(j, cur.Y);
                        }
                    }
               }
            }
            cur = nxt;
        }
        /*sort(al(PathSet), [](const pt A, pt B){
            if (A.X == B.X)
                return A.Y < B.Y;
            return A.X < B.X;
        });*/
        //PrintMap(Map);
        //PrintIntersect(intersect);
        /*
        for (int &e : Carl)
        {
            cout << e << ", ";
        }
        cout << endl;
        for(auto& e: PathSet){
            cout << "(" << e.X << ", " << e.Y << ") ";
        }
        cout << endl;
        */
        // test

        // simulate
        vec<bool>  inque(m, false), reached(m ,false);
        vec<int> moved(m);
        vec<int> finish;
        deque<int> emer;
        queue<int> error;
        vec<vec<vec<int>>> newAMap(LEN, vec<vec<int>>(LEN, vec<int>(4, -1)));
        int done = 0;
        int t = 0;
        int CarlANS = 0;
        while (done < m)
        {
            
            debug2(t+1);
            fill(al(moved), NOTYET);
            // reseting newAMap
            
            // Carl move;
            pt &curl = Ants[0].cur_pos;
            if (!reached[0])
            {
                if (curl == END)
                {
                    CarlANS = t;
                    reached[0] = true;
                    moved[0] = TO_END;
                    finish.eb(0);
                    done++;
                }
                else
                {
                    //dept(curl);
                    //debug(Carl.size());
                    domap(Map, curl.X, curl.Y, Carl[t]);
                    if (getmap(intersect, curl.X, curl.Y) == true)
                    {
                        int another, dirID;
                        tie(another, dirID) = antother(Antmap, curl.X, curl.Y, 0);
                        if (another != -1)
                        {
                            moved[another] = HOLD;
                            do3map(newAMap, Ants[another].cur_pos.X, Ants[another].cur_pos.Y, dirID, another);
                            Ants[another].waitT++;
                  //          cout << "not move  " << another << endl;
                        }
                    }
                    curl = curl + dir[Carl[t]];
                    moved[0] = MF;
                    Ants[0].plen++;
                    do3map(newAMap, curl.X, curl.Y, Carl[t], 0);
                }
            }
            // Ants move;
            bool onefromqueue = false;
            for (int i = 1; i < m; i++)
            {
                if(moved[i] || t +1< d*i || reached[i])
                    continue;
                //cout << "moveing " << i << endl;
                if (t + 1 == d * i){
                 //   cout << "iput " << i << " into queue\n";
                    emer.emplace_back(i), inque[i] = true, Ants[i].cur_pos = {0, 0};
                    moved[i] = IN_Q;
                }
                else{
                    if(inque[i]){
                        if(emer.front() != i || onefromqueue){
                            moved[i] = IN_Q;
                            continue;
                        }
                        else{
                            emer.pop_front(), inque[i] = false, onefromqueue = true;
                //            cout << "Grep " << i << " out of queue" << endl;
                        }
                    }
                    pt & tcp = Ants[i].cur_pos;
                    int tomove = i;
                    if(tcp == END){
                        reached[i] = true;
                        done++;
                        moved[i] = TO_END;
                        finish.eb(i);
                        //cout << "the END of " << i << endl;
                        continue;
                    }
                    if (getmap(intersect, tcp.X, tcp.Y) == true)
                    {
                        int another, dirID;
                        tie(another, dirID) = antother(Antmap, tcp.X, tcp.Y, i);
                        if(another != -1){
                            /*
                            if(Ants[another].plen > Ants[tomove].plen){
                                tomove = another;
                            }
                            else if(Ants[another].plen == Ants[tomove].plen){
                                if(Ants[another].waitT > Ants[tomove].waitT)
                                    tomove = another;
                            }
                            */
                            if(Ants[another].waitT > Ants[tomove].waitT)
                                tomove = another;
                            int notmove = (tomove == i ? another : i);
                            dirID = (tomove == i ? dirID : Ants[i].dir);
                            moved[notmove] = HOLD;
                            Ants[notmove].waitT++;
                            do3map(newAMap, Ants[notmove].cur_pos.X, Ants[notmove].cur_pos.Y, dirID, notmove);
                        //    cout << "not move  " << notmove << endl;
                        }
                    }
                    ant &mover = Ants[tomove];
                    pt &lp = mover.last_pos, &cp = mover.cur_pos;
                    lp = cp;
                    int dirID = getmap(Map, cp.X, cp.Y);
                    //dept(cp);
                    cp = cp + dir[dirID];
                    //dept(cp);
                    moved[tomove] = 2;
                    mover.plen++;
                    mover.oldT = mover.waitT;
                    mover.waitT = 0;
                    mover.ldir = mover.dir;
                    mover.dir = dirID;
                    do3map(newAMap, cp.X, cp.Y, dirID, i);
                }
            }

            for (int i = 1; i < m; i++){
                if(moved[i] != MF)
                    continue;
                
                pt &cp = Ants[i].cur_pos;
                int ori = get3map(Antmap, cp.X, cp.Y, Ants[i].dir);
                if(ori != -1 && ori != i && moved[ori] == 1){
                    error.emplace(i);
                    do3map(newAMap, cp.X, cp.Y, Ants[i].dir, ori);
                    //cout << " ant " << i << " step on ant " << ori << endl;
                    //dept(Ants[ori].cur_pos);
                }
            }

            while(!error.empty()){
                
                int err = error.front();
                ant &errer = Ants[err];
                error.pop();
                pt &cp = errer.cur_pos;
                /*
                cout << "go " << err << " back from ";
                dept(cp);
                cout << " to ";
                dept(errer.last_pos);
                cout << endl;
                */
                cp = errer.last_pos;
                errer.plen--;
                if(cp == pt(0, 0)){
                    inque[err] = true;
                    emer.emplace_front(err);
                    continue;
                }

                if(getmap(intersect, cp.X, cp.Y) == true)
                    Ants[err].waitT = Ants[err].oldT;
                int ori = get3map(newAMap, cp.X, cp.Y, Ants[err].ldir);
                if(ori != -1)
                    error.emplace(ori);
                do3map(newAMap, cp.X, cp.Y, errer.ldir, err);
                errer.dir = errer.ldir;
            }
            //Antmap = newAMap;
            for (int i = 0; i < m; i++){
                pt &cp = Ants[i].last_pos;
                if(Ants[i].ldir >= 0)
                do3map(Antmap, cp.X, cp.Y, Ants[i].ldir, -1);
            }
            for (int i = 0; i < m; i++){
                pt &cp = Ants[i].cur_pos;
                if (Ants[i].dir >= 0){
                    do3map(Antmap, cp.X, cp.Y, Ants[i].dir, get3map(newAMap, cp.X, cp.Y, Ants[i].dir));
                    do3map(newAMap, cp.X, cp.Y, Ants[i].dir, -1);
                }
            }
            //swap(Antmap, newAMap);
            /*
            for (pt &grid : PathSet)
            {
                cout << "pos ";
                dept(grid);
                cout << " with " ;
                for (int i = 0; i < 4; i++)
                {
                    do3map(Antmap, grid.X, grid.Y, i, get3map(newAMap, grid.X, grid.Y, i));
                    //    cout << i <<": " << get3map(Antmap, grid.X, grid.Y, i) << ", ";
                }
                // cout << endl;
                }
            cout << "time: " << t + 1 << endl;
            for (int i = 0; i < min(20, m);i++){
                cout << "Ant " << i << " at : " << Ants[i].cur_pos.X << ", " << Ants[i].cur_pos.Y  << "\n";
                cout << Ants[i].plen << ", " << Ants[i].waitT << " dir " << Ants[i].dir<< endl;
            }
            */
            t++;
        }
        cout << "Case " << cnt++ << ":\n";
        cout << "Carl finished the path at time " << CarlANS +1 << endl;
        cout << "The ants finished in the following order:\n";
        REP(i, m)
            cout << finish[i] << (i == m - 1 ? "\n" : " ");
        cout << "The last ant finished the path at time " << t << endl;
    }

    return 0;
}