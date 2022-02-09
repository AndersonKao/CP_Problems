#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
//#define DEBUGANS
using PII = pair<int, int>;

using P3i = tuple<int, int, int>;
int T;
enum cardinal
{
    W = 0,
    S = 1,
    E = 2,
    N = 3
};
enum direction
{
    L = 0,
    R = 1,
    F = 2
};
struct grid{
    bool exist;
    vector<direction> directs[4]; // W, S, E, N
    bool visitedfrom[4];
};
PII coord[4] = { // WSEN
    PII(0, -1),
    PII(1, 0),
    PII(0, 1),
    PII(-1, 0)
};
int start_r, start_c, end_r, end_c;
grid maze[10][10];
int anslen = 10000000;
bool solved;
vector<PII> ANS;
stack<PII> walk;
void p_cardinal(cardinal c);
void p_direction(direction c);
void reset();
cardinal ch2car(char ch);
direction ch2dir(char ch);
cardinal car_dir(cardinal c, direction d);
void routine(stack<P3i> &mypath, int r, int c, cardinal car){

#ifdef DEBUG
    cout << "came to " << r << ", " << c << " with cardinal ";
    p_cardinal(car);
#endif
    if(r < 0 || r > 9 || c < 0 || c > 9 || !maze[r][c].exist || maze[r][c].visitedfrom[car] || mypath.size() >= anslen){
#ifdef DEBUG
        if(!maze[r][c].exist)
            cout << "not exist\n";
        else
            cout << "visited\n";
#endif
        return;
    }
    maze[r][c].visitedfrom[car] = true;
    mypath.emplace(r, c, (int)car);
    if(r == end_r && c == end_c){
        solved = true;
#ifdef DEBUGANS
            cout << "shorter Ans: \n";
#endif
            ANS.clear();
            stack<P3i> copied(mypath);// 倒出來
            stack<P3i> revC;
            while(copied.size()){
                revC.emplace(copied.top());
                copied.pop();
            }
            int u, v, un;
            while(revC.size()){
                tie(u, v, un) = revC.top();
#ifdef DEBUGANS
                cout << "(" << u << ", " << v << ") ";
#endif
                revC.pop();
                ANS.emplace_back(u, v);
            }
#ifdef DEBUGANS
            cout << endl;
#endif
            anslen = ANS.size();
        maze[r][c].visitedfrom[car] = false;
        mypath.pop();
        return; 
    }

    for(direction p: maze[r][c].directs[car]){

        cardinal newcar = (car_dir(car, p));
#ifdef DEBUG
        cout << "at " << r << ", " << c << "  ";
        cout << "turn ";
        p_direction(p);
        cout << "trans: ";
        p_cardinal(newcar);
#endif
        routine(mypath, r + coord[newcar].first, c + coord[newcar].second, newcar);
    }
    mypath.pop();
    maze[r][c].visitedfrom[car] = false;
}

void solve(){
    cardinal start_cardinal;
    char ch;
    cin >> start_r >> start_c >> ch >> end_r >> end_c;
    maze[end_r][end_c].exist = true;
    maze[start_r][start_c].exist = true;
    start_cardinal = ch2car(ch);
#ifdef DEBUG
    p_cardinal(start_cardinal);
#endif
    int r, c;
    while(true){
        cin >> r;
        if(r == 0)
            break;
        cin >> c;
        maze[r][c].exist = true;
        string str;
        getline(cin, str);
        cardinal cur;
        for (int i = 0; i < str.length() && str[i] != '*'; i++){
            if(str[i] == ' ')
                continue;
            if(str[i] == 'W' || str[i] == 'E' || str[i] == 'S' || str[i] == 'N'){
                cur = ch2car(str[i]);
                continue;
            }else{
                maze[r][c].directs[cur].emplace_back(ch2dir(str[i]));
            }
        }
    }
#ifdef DEBUG
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            if(!maze[i][j].exist)
                continue;
            cout << "r, c = " << i << ", " << j << endl;
            for (int k = 0; k < 4; k++){
                cout << "  ";
                p_cardinal((cardinal)k);
                for(auto p: maze[i][j].directs[k]){
                    cout << "    ";
                    p_direction((direction)p);
                }
            }
        }
    }
#endif
    stack<P3i> mypath;
    mypath.emplace(start_r, start_c, start_cardinal);
#ifdef DEBUG
    for (cardinal s = cardinal::W; s < 4; s = (cardinal)(s + 1)){
        cout << coord[s].first << ", " << coord[s].second << endl;
    }
        cout << "going to " << start_r + coord[start_cardinal].first << ", " << start_c + coord[start_cardinal].second << endl;
#endif
    routine(mypath, start_r + coord[start_cardinal].first, start_c + coord[start_cardinal].second, start_cardinal);
   // routine(mypath, start_r + coord[start_cardinal].first, start_c + coord[start_cardinal].second, start_cardinal);
}

// 如果曾經從那個方向來到過這個node 就 return;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    string str;

    bool neednewline = false;

    while(cin >> str){
        
        if(str == "END")
            break;
        //if(neednewline)
         //   cout << endl;
        reset();
        cout << str << endl;
        solve();
        if(solved == false){
            neednewline = true;
            cout << "  No Solution Possible\n";
        }else{
            int cnt = 0;
            neednewline = false;
            bool needspace = true;
            for(auto &p: ANS){
                if(needspace){
                    cout << " ";
                    needspace = false;
                }

                cout << " (" << p.first << "," << p.second << ")";
                cnt++;
                if(cnt == 10){
                    cnt = 0;
                    cout << "\n";
                    needspace = true;
                }
            }
            if(cnt != 0)
            {
                cout << endl;
                neednewline = true;
            }
        }
    }

    return 0;
}
void p_cardinal(cardinal c){
    switch (c)
    {
    case cardinal::W:
        cout << " West ";
        break;
    case cardinal::S:
        cout << " South ";
        break;
    case cardinal::E:
        cout << " East ";
        break;
    case cardinal::N:
        cout << " North ";
        break;
    default:
        cout << " WTF? ";
        break;
    }
    cout << endl;
}
void p_direction(direction c){
    switch (c)
    {
    case direction::F:
        cout << " Forward ";
        break;
    case direction::R:
        cout << " Right ";
        break;
    case direction::L:
        cout << " LEFT ";
        break;
    default:
        cout << " WTF?? ";
        break;
    }
    cout << endl;
}
void reset(){
    anslen = 10000000;
    solved = false;
    ANS.clear();
    while(walk.size())
        walk.pop();
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            maze[i][j].exist = false;
            for (int k = 0; k < 4; k++){
                maze[i][j].directs[k].clear();
                maze[i][j].visitedfrom[k] = false;
            }
        }
    }
}
cardinal ch2car(char ch){
    if(ch == 'W')
        return cardinal::W;
    else if(ch == 'S')
        return cardinal::S;
    else if(ch == 'E')
        return cardinal::E;
    else
        return cardinal::N;
}
direction ch2dir(char ch){
    if(ch == 'L')
        return L;
    else if(ch == 'R')
        return R;
    else
        return F;
}
cardinal car_dir(cardinal c, direction d){
    if(d == direction::F)
        return c;
    switch (c)
    {
    case cardinal::N:
        return (d == direction::R ? cardinal::E : cardinal::W);
        break;
    case cardinal::E:
        return (d == direction::R ? cardinal::S : cardinal::N);
        break;
    case cardinal::S:
        return (d == direction::R ? cardinal::W : cardinal::E);
        break;
    case cardinal::W:
        return (d == direction::R ? cardinal::N : cardinal::S);
        break;
    default:
        return c; // WTF??
        break;
    }
    
}