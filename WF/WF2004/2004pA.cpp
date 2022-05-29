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
#define dept(x) //cout << #x << "(" << x.X << ", " << x.Y << ")\n";

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
    int dir = 0;
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
        vec<vec<int>> map(201, vec<int>(201, -1));
        vec<vec<vec<int>>> Antmap(201, vec<vec<int>>(201, vec<int>(4, -1)));
        vec<vec<bool>> intersect(201, vec<bool>(201, false));
        vec<ant> Ants(m);
        vec<int> Carl;
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
                    for (int i = cur.Y; i < nxt.Y; i++){
                        Carl.eb(0);
                        if(getmap(map, cur.X, i) == 0)
                            domap(intersect, cur.X, i, true);
                        domap(map, cur.X, i, 0);
                    }
                }else{
                    for (int i = cur.Y; i > nxt.Y; i--){
                        Carl.eb(1);
                        if(getmap(map, cur.X, i) == 0)
                            domap(intersect, cur.X, i, true);
                        domap(map, cur.X, i, 0);
                    }
                }
            }
            else
            {
                if (cur.X < nxt.X)
                {
                    for (int i = cur.X; i < nxt.X; i++){
                        Carl.eb(3);
                        if(getmap(map, i, cur.Y) == 0)
                            domap(intersect, i, cur.Y, true);
                        domap(map, i, cur.Y, 0);
                    }
               } else{
                    for (int i = cur.X; i > nxt.X; i--){
                        Carl.eb(2);
                        if(getmap(map, i, cur.Y) == 0)
                            domap(intersect, i, cur.Y, true);
                        domap(map, i, cur.Y, 0);
                    }
               }
            }
            cur = nxt;
        }
        /*
        for(int&e : Carl){
            cout << e << ", ";
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
        int done = 0;
        int t = 0;
        int CarlANS = 0;
        while (done < m)
        {
            debug(t+1);
            vec<vec<vec<int>>> newAMap(201, vec<vec<int>>(201, vec<int>(4, -1)));
            fill(al(moved), 0);
            // Carl move;
            pt &curl = Ants[0].cur_pos, &lasl = Ants[0].last_pos;
            if(!reached[0]){
            if(curl == END){
                CarlANS = t;
                reached[0] = true;
                moved[0] = 2;
                finish.eb(0);
                done++;
            }
            else
            {
                dept(curl);
                debug(Carl.size());
                domap(map, curl.X, curl.Y, Carl[t]);
                lasl = curl;
                if(getmap(intersect, curl.X, curl.Y) == true){
                    int another, dirID;
                    tie(another, dirID) = antother(Antmap, curl.X, curl.Y, 0);
                    if(another != -1){
                        moved[another] = 1;
                        do3map(newAMap, Ants[another].cur_pos.X,Ants[another].cur_pos.Y, dirID, another);
                    }
                }

                curl = curl + dir[Carl[t]];
                moved[0] = 2;
                Ants[0].plen++;
                do3map(newAMap, curl.X, curl.Y, Carl[t], 0);
            }
            }

            // Ants move;
            for (int i = 1; i < m; i++)
            {
                if(moved[i] || t < d*i || reached[i])
                    continue;
                //cout << "moveing " << i << endl;
                if (t + 1== d * i){
                    //cout << "put " << i << " into queue\n";
                    emer.emplace_back(i), inque[i] = true, Ants[i].cur_pos = {0, 0};
                }
                else{
                    if(inque[i]){
                        if(emer.front() != i)
                            continue;
                        else
                            emer.pop_front(), inque[i] = false;
                        //cout << "Grep " << i << " out of queue\n";
                    }
                    pt & tcp = Ants[i].cur_pos;
                    int tomove = i;
                    if(tcp == END){
                        reached[i] = true;
                        done++;
                        moved[i] = 2;
                        finish.eb(i);
                        //cout << "the END of " << i << endl;
                        continue;
                    }
                    if (getmap(intersect, tcp.X, tcp.Y) == true)
                    {
                        //cout << i << " stand in intersection\n";
                        int another, dirID;
                        tie(another, dirID) = antother(Antmap, tcp.X, tcp.Y, i);
                        // debug

                        if(another != -1){
                            if(Ants[another].plen > Ants[i].plen){
                                tomove = another;
                            }
                            else if(Ants[another].plen == Ants[i].plen){
                                if(Ants[another].waitT > Ants[i].plen)
                                    tomove = another;
                            }
                            int notmove = (tomove == i ? another : i);
                            moved[notmove] = 1;
                            Ants[notmove].waitT++;
                            do3map(newAMap, Ants[notmove].cur_pos.X, Ants[notmove].cur_pos.Y, dirID, notmove);
                            //cout << "not move  " << notmove << endl;
                        }
                    }
                    pt &lp = Ants[tomove].last_pos, &cp = Ants[tomove].cur_pos;
                    lp = cp;
                    int dirID = getmap(map, cp.X, cp.Y);
                    dept(cp);
                    cp = cp + dir[dirID];
                    dept(cp);
                    moved[tomove] = 2;
                    Ants[tomove].plen++;
                    Ants[tomove].oldT = Ants[tomove].waitT;
                    Ants[tomove].waitT = 0;
                    do3map(newAMap, cp.X, cp.Y, dirID, i);
                }
            }

            for (int i = 1; i < m; i++){
                pt &cp = Ants[i].cur_pos;
                int ori = get3map(Antmap, cp.X, cp.Y, Ants[i].dir);
                
                if(ori != -1 && ori != i && moved[ori] == 1){
                    error.emplace(i);
                    //cout << " ant " << i << " step on ant " << ori << endl;
                    dept(Ants[ori].cur_pos);
                }
            }

            while(!error.empty()){
                int err = error.front();
                error.pop();
                pt &cp = Ants[err].cur_pos;
                cp = Ants[err].last_pos;
                Ants[err].plen--;
                if(getmap(intersect, cp.X, cp.Y) == true)
                    Ants[err].waitT = Ants[err].oldT + 1;
                int ori = get3map(newAMap, cp.X, cp.Y, Ants[err].dir);
                if(ori != -1)
                    error.emplace(ori);
            }
            Antmap = newAMap;

            for (int i = 0; i < m;i++){
                //cout << "Ant " << i << " at : " << Ants[i].cur_pos.X << ", " << Ants[i].cur_pos.Y  << "\n";
                //cout << Ants[i].plen << ", " << Ants[i].waitT << endl;
            }
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