#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i< n; i++)
#define MAXL 10

int N;

struct entry{
    int r, c;
    int strI; // current using string index.
    int maxLen;
};

vector<vector<bool>> isOp(12, vector<bool>(12, false));
vector<vector<char>> opD(12, vector<char>(12, 'F')); // opening Direction
vector<vector<char>> grid(12, vector<char>(12, ' '));
vector<vector<int>> ongrid(12, vector<int>(12, 0));
vector<bool> filled;
int filledCnt = 0;
vector<int> ANS;
vector<int> freeStr;
vector<bool> used;
vector<string> strs;
vector<entry> entries;

int checkCons(int cur){
    int rr = entries[cur].r;
    int rc = entries[cur].c;
    int ans = -1;
    int conChI;
    REP(i, N){
        int r = entries[i].r;
        int c = entries[i].c;
        if(filled[i] || opD[r][c] == opD[rr][rc]){
            continue;
        }
        if(opD[r][c] == 'A'){
            int lastr = r + strs[entries[i].strI].length();
            if(r < rr || r >= lastr) // no intersect
                continue;
            conChI = rr - r;
        }else{
            int lastc = c + strs[entries[i].strI].length();
            if(c < rc || c >= lastc) // no intersect
                continue;
            conChI = rc - c;
        } 
    } 
    return ans;
}
void putin(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;


    if(opD[r][c] == 'D'){
        ongrid[r - 1][c] = -1;
        
        for(int i = 0; i < strs[strI].length(); i++){
            grid[r + i][c] = strs[strI][i];
            ongrid[r+i][c]++;
        }
        ongrid[r + strs[strI].length()][c] = -1;
    }
    else{
        ongrid[r][c-1] = -1;
        for(int i = 0; i < strs[strI].length(); i++){
            grid[r][c + i] = strs[strI][i];
            ongrid[r][c + i]++;
        }
        ongrid[r][c + strs[strI].length()] = -1;
    }
}
void plugout(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;
    if(opD[r][c] == 'D'){
        ongrid[r - 1][c] = 0;
        for(int i = 0; i < strs[strI].length(); i++){
            ongrid[r + i][c]--;
            if(ongrid[r+i][c] == 0)
                grid[r + i][c] = ' ';
        }
        ongrid[r + strs[strI].length()][c] = 0;
    }
    else{
        ongrid[r][c-1] = 0;
        for(int i = 0; i < strs[strI].length(); i++){
            ongrid[r][c + i]--;
            if(ongrid[r][c + i] == 0)
                grid[r][c + i] = ' ';
        }
        ongrid[r][c + strs[strI].length()] = 0;
    }
}
bool valid(int strI, int slotI){
    int r = entries[slotI].r;
    int c = entries[slotI].c;
    if(opD[r][c] == 'D'){
        for(int i = 0; i < strs[strI].length(); i++){
            if(ongrid[r+i][c] == -1) // head and back
                return false;
            if(ongrid[r+i][c] != 0 && grid[r + i][c] != strs[strI][i])
                return false;
        }
    }
    else{
        for(int i = 0; i < strs[strI].length(); i++){
            if(ongrid[r+i][c] == -1)
                return false;
            if(ongrid[r][c+i] != 0 && grid[r][c + i] != strs[strI][i])
                return false;
        }
    }
    return true;
}
int renewFreedom(){

    int freeCnt = 0;

    int ans = -1;
    int ansCnt = N + 1;
    REP(i, N){
        if(filled[i])
            continue;
        freeCnt = 0;

        REP(j, (int)strs.size()){
            if(valid(i, j))
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

    REP(i, strs.size()){
        if(!used[i]){
            cout << "find ans: " << strs[i] << endl;
            ANS.emplace_back(i);
            break;
        }
    }
}

void rec(int cur){
    filled[cur] = true;

    REP(i, strs.size()){
        if(used[i])
            continue;
        if(strs[i].length() > entries[cur].maxLen) //尾部已經被處李
            continue;
        if(!valid(i, cur))
            continue;
        // stack in.
        entries[cur].strI = i; 
        used[i] = true; 
        putin(i, cur);
        filledCnt++;

        int ConsI = checkCons(i);

        if(ConsI != -1){
            rec(ConsI);
        }
        if(filledCnt == N){
            processANS();
        }

        // stack out.
        filledCnt--;
        plugout(i, cur);
        used[i] = false;
    }
    filled[cur] = false;
}
void printGrid(){
    for (int i = 0; i <= N + 1; i++){
        for (int j = 0; j <= N + 1; j++){
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
int main(){
    //cin.tie(0);
    //ios_base::sync_with_stdio(false);

    while(cin >> N){
        if(N == 0)
            break;
        strs.resize(N+1);
        entries.resize(N);
        filled.clear();
        filled.resize(N, false);
        used.clear();
        used.resize(N+1, false);
        freeStr.clear();
        freeStr.resize(N, 0);
        ANS.clear();
        filledCnt = 0;

        int r, c;
        char d;
        REP(i, N){
            cin >> r >> c >> d;
            entries[i].c = c;
            entries[i].r = r;
            isOp[r][c] = true;
            opD[r][c] = d;
        }
        cout << "input\n";
        REP(i, N + 1){
            cin >> strs[i];
        }
        REP(i, N){ // compute maxLen
            r = entries[i].r;
            c = entries[i].c;
            int rAdd, cAdd;
            rAdd = cAdd = 0;
            if(opD[r][c] == 'D')
                rAdd = 1; 
            else
                cAdd = 1; 
            int cnt = 1;
            do{
                cout << "r, c = " << r << ", " << c << endl;
                if(r > 10 || r < 1 || c > 10 || c < 1)
                    break;
                if(isOp[r][c + 1] && opD[r][c] == 'A')
                    break;
                if(isOp[r + 1][c] && opD[r][c] == 'D')
                    break;
                r += rAdd;
                c += cAdd;  
                cnt++;
            }
            while(r <= 10 && c <= 10);
            entries[i].maxLen = cnt;
        }

        rec(0);

    }
    


    return 0;
}
