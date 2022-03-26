// AC 2022-02-22 08:08:20
#include <bits/stdc++.h>
using namespace std;
int T;
 
#define MAXP 2000000
using PII = pair<int, int>;
char grid[1002][1002];
int mPath[1002][1002];
int Path[1002][1002];
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int cdir[4] = {'D', 'R', 'U', 'L'};
int N, M;
void pPath(){
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            cout << (Path[i][j] == MAXP ? -1 : Path[i][j]) << " ";
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            cout << (mPath[i][j] == MAXP ? -1 : mPath[i][j]) << " ";
        }
        cout << endl;
    }
}
char path[1000000];
int p_i = 0;
bool solve = false;
bool visited[1001][1001] = {false};

bool reach(int a, int b){
    return (a == 1 || b == 1 || a == N || b == M);
}
void DFS(int u, int v){
    if(solve)
        return;
    visited[u][v] = true;
    if(reach(u, v)){
        solve = true;
        cout << "YES" << endl;
        cout << p_i << endl;
        for (int i = 0; i < p_i; i++)
            cout << path[i];
        cout << endl;
        return;
    }
    int a, b;
    for (int d = 0; d < 4; d++)
    {
        a = u + dir[d][0];
        b = v + dir[d][1];
        if (grid[a][b] != '#' && !visited[a][b] && (Path[a][b] < mPath[a][b]))
        {
            path[p_i++] = cdir[d];
            DFS(a, b);
            p_i--;
        }
        if (solve)
            break;
        
    }
}
int main(){
    cin >> N >> M;
    queue<PII> Q;
    int sx, sy;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            cin >> grid[i][j];
            Path [i][j] = mPath[i][j] = MAXP;
            if(grid[i][j] == 'M'){
                Q.emplace(i, j);
                mPath[i][j] = 0;
            }else if(grid[i][j] == 'A'){
                sx = i;
                sy = j;
            }
        }
    }
    int u, v;
    int a, b;
    while(!Q.empty()){
        tie(u, v) = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++){
            a = u + dir[i][0];
            b = v + dir[i][1];
            if(grid[a][b] != '#' && mPath[a][b] == MAXP){
                mPath[a][b] = mPath[u][v] + 1;
                Q.emplace(a, b);
            }
        }
    }
    Q.emplace(sx, sy);
    Path[sx][sy] = 0;
    while(!Q.empty()){
        tie(u, v) = Q.front();
        Q.pop();
        for (int i = 0; i < 4; i++){
            a = u + dir[i][0];
            b = v + dir[i][1];
            if(grid[a][b] != '#' && Path[a][b] == MAXP){
                Path[a][b] = Path[u][v] + 1;
                Q.emplace(a, b);
            }
        }
    }
    DFS(sx, sy);
    if(!solve){
        cout << "NO\n";
    }
    return 0;
}