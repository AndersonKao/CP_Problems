#include <bits/stdc++.h>
using namespace std;
//#define DEBUG
//#define DEINOUT
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i< n; i++)
#define MAXL 10

int N;

struct entry{
    int r, c;
    int strI; // current using string index.
    int maxLen;
    char dir;
};

vector<vector<bool>> isOp(12, vector<bool>(12, false));
vector<vector<int>>opD(12, vector<int>(12, 0)); // opening Direction
// A 1, D 2, both 3
vector<vector<char>> grid(12, vector<char>(12, ' '));
vector<vector<int>> ongrid(12, vector<int>(12, 0));
vector<bool> filled;
int filledCnt = 0;
set<int> ANS;
vector<int> freeStr;
vector<bool> used;
vector<string> strs;
vector<entry> entries;

void printGrid();
void putin(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;


    if(entries[slotI].dir == 'D'){
        REP(i, (int)strs[strI].length()){
            grid[r + i][c] = strs[strI][i];
            ongrid[r+i][c]++;
        }
        ongrid[r + strs[strI].length()][c]--;
    }
    else{
        REP(i,(int)strs[strI].length()){
            grid[r][c + i] = strs[strI][i];
            ongrid[r][c + i]++;
        }
        ongrid[r][c + strs[strI].length()]--;
    }
#ifdef DEINOUT
    cout << "putin: " << strs[strI] << endl;
    printGrid();
#endif
}
void plugout(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;
    if(entries[slotI].dir == 'D'){
        for(int i = 0; i < strs[strI].length(); i++){
            ongrid[r + i][c]--;
            if(ongrid[r+i][c] == 0)
                grid[r + i][c] = ' ';
        }
        ongrid[r + strs[strI].length()][c]++;
    }
    else{
        for(int i = 0; i < strs[strI].length(); i++){
            ongrid[r][c + i]--;
            if(ongrid[r][c + i] == 0)
                grid[r][c + i] = ' ';
        }
        ongrid[r][c + strs[strI].length()]++;
    }
#ifdef DEINOUT
    cout << "plugout: " << strs[strI] << endl;
   printGrid();
#endif
}
bool valid(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;
    //cout << "trying " << strs[strI] << endl;
    if(strs[strI].length() > entries[slotI].maxLen)
        return false;
    if(entries[slotI].dir == 'D'){

        int nr = r + strs[strI].length(), nc = c;
        if(ongrid[nr][nc] > 0)
            return false;
        for(int i = 0; i < strs[strI].length(); i++){
            if(ongrid[r+i][c] < 0) // head and back
            {
            #ifdef DEBUG
                cout << "ch " << i << " at " << r + i << ", " << c << "touch headback\n"; 
            #endif
                return false;
            }
            if(ongrid[r+i][c] != 0 && grid[r + i][c] != strs[strI][i]){
            #ifdef DEBUG
                cout << r + i << ", " << c << endl;
                cout << grid[r+i][c] << " != " << strs[strI][i] << endl; 
            #endif
                return false;
            }
        }
    }
    else{
        int nr = r, nc = c + strs[strI].length();
        if(ongrid[nr][nc] > 0)
            return false;
        for(int i = 0; i < strs[strI].length(); i++){
            if(ongrid[r][c + i] < 0)
            {
#ifdef DEBUG
                cout << "char " << i << " at " << r + i << ", " << c << " touch headback\n"; 
#endif
                return false;
            }
            if(ongrid[r][c+i] != 0 && grid[r][c + i] != strs[strI][i]){
#ifdef DEBUG
                cout << r + i << ", " << c << endl;
                cout << grid[r][c + i] << " != " << strs[strI][i] << endl; 
#endif
                return false;
            }
        }
    }
    return true;
}
int renewFreedom(){

    int freeCnt = 0;

    int ans = -1;
    int ansCnt = N + 2;
    REP(i, N){
        if(filled[i])
            continue;
        freeCnt = 0;

        REP(j, (int)strs.size()){
            if(used[j])
                continue;
            if(valid(j, i))
                freeCnt++;
        }
        if(freeCnt < ansCnt){
            ans = i;
            ansCnt = freeCnt;
        }
    }
    return ans;
}
void processANS(){

    REP(i, (int)strs.size()){
        if(!used[i]){
#ifdef DEBUG
            cout << "find ans" << " i = " << i << ": " << strs[i] << endl;
#endif
            ANS.emplace(i);
            break;
        }
    }
}
void printSlot(int i){
#ifdef DEBUG
    cout << "SLot: " << i << endl;
#endif
    int r, c;
    r= entries[i].r;
    c = entries[i].c;
#ifdef DEBUG
    cout << "begin: " << r << ", " << c << endl;
    cout << "maxLen: " << entries[i].maxLen << endl;
    cout << "direction:" << entries[i].dir<< endl;
#endif
}

void rec(int cur){
#ifdef DEBUG
    cout << "processing " << cur << "--------------" << endl;
#endif
    //printSlot(cur);
    //printGrid();
    
    filled[cur] = true;

    REP(i, (int)strs.size()){
        if(used[i]){
#ifdef DEBUG
            cout << "used by others:\n";
#endif
            continue;
        }
        if(!valid(i, cur)){
            continue;
        }
        // stack in.
        entries[cur].strI = i; 
        used[i] = true; 
        putin(i, cur);
        filledCnt++;

        int ConsI = renewFreedom();

        if(ConsI != -1){
            rec(ConsI);
        }else{
        }
        if(filledCnt == N){
            processANS();
        }
        // stack out.
        entries[cur].strI = -1;
        filledCnt--;
        plugout(i, cur);
        used[i] = false;
    }
    filled[cur] = false;
}
void printGrid(){

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 12; j++){
            if(ongrid[i][j] != -1)
                cout << " ";
            cout << ongrid[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);
    int round = 1;

    while(cin >> N){
        if(N == 0)
            break;
        fill(isOp.begin(), isOp.end(), vector<bool>(12, false));
        fill(opD.begin(), opD.end(), vector<int>(12, 0));
        fill(grid.begin(), grid.end(), vector<char>(12, ' '));
        fill(ongrid.begin(), ongrid.end(), vector<int>(12, 0));
        filled.clear();
        filled.resize(N, false);
        ANS.clear();
        freeStr.clear();
        freeStr.resize(N, 0);
        used.clear();
        used.resize(N+1, false);
        strs.resize(N+1);
        entries.resize(N);
        filledCnt = 0;

        int r, c;
        char d;
        REP(i, N){
            cin >> r >> c >> d;
            entries[i].c = c;
            entries[i].r = r;
            isOp[r][c] = true;
            opD[r][c] |= (d == 'D' ? 2 : 1);
            entries[i].dir = d;
        }


        REP(i, N + 1){
            cin >> strs[i];
        }
        REP(i, N){ // compute maxLen
            r = entries[i].r;
            c = entries[i].c;
            int rAdd, cAdd;
            rAdd = cAdd = 0;
            if(entries[i].dir == 'D'){
                rAdd = 1; 
                ongrid[r-1][c] = -1;
            }
            else{
                cAdd = 1; 
                ongrid[r][c-1] = -1;
            }
            int cnt = 0;
            do{
                if(isOp[r][c + 1] && opD[r][c + 1]  & 1)
                    break;
                if(isOp[r + 1][c] && opD[r + 1][c] & 2)
                    break;
                r += rAdd;
                c += cAdd;  
                cnt++;
            }
            while(r <= 10 && c <= 10 && r >= 1 && c>=1);

            entries[i].maxLen = cnt;
        }
        //printGrid();
        rec(0);
        cout << "Trial " << round++ << ":";
        if(ANS.size() == 0){
            cout << " Impossible\n"; 
        }
        else{
            for(auto& ans: ANS){
                cout << " " << strs[ans] ;
            } 
            cout << "\n";
        }
        cout << endl;

    }
    return 0;
}
