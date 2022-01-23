#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

int L, R, C;
struct Node{
    int l, r, c, dis;
};
char map[40][40][40];
bool visited[40][40][40] = {false};
int direc[6][3] = {
    {0,0,1},{0,0,-1}, {0,1,0}, {0,-1,0},
    {1,0,0},{-1,0,0}
};
bool flag;
int shortdis;
int dis;
bool valid(int l, int r, int c){
    if(l > 0 && l <= L && r > 0 && r <= R && c > 0 && c <= C){
        if(map[l][r][c] != '#')
            return true;
    }
    return false;
}
bool valid(Node a){
    int l = a.l, r = a.r, c = a.c;
    if(l > 0 && l <= L && r > 0 && r <= R && c > 0 && c <= C){
        if(map[l][r][c] != '#')
            return true;
    }
    return false;
}

int main(){
    int sl,sr,sc;
    std::ios_base::sync_with_stdio(false);
    while(cin >> L >> R >> C){
        if(L == 0 && R == 0 && C == 0)
            break;
        queue<Node> q;
        flag = false;
        shortdis = INT32_MAX;
        dis = 0;
        Node Start;
        Start.dis = 0;
        memset(visited, 0, sizeof(visited));
        memset(map, 0, sizeof(map));
        for(int i = 1; i <= L; i++){
            for(int j = 1; j <= R; j++){
                for(int k = 1; k <= C; k++){
                    cin >> map[i][j][k];
                    if(map[i][j][k] == 'S'){
                        Start.l = i;
                        Start.r = j;
                        Start.c = k;
                    }
                }
            }
                    getchar();
        }
        q.push(Start);
        while (!q.empty())
        {
            Node Top = q.front();
            q.pop();
            // cout << "Visiting " << Top.l << Top.r << Top.c << "\n";
            if(map[Top.l][Top.r][Top.c] == 'E'){
                shortdis = Top.dis;
                break;
            }
            visited[Top.l][Top.r][Top.c] = true;

            for(int i = 0; i <6 ;i++){
                Node next;
                next.l = Top.l + direc[i][0];
                next.r = Top.r + direc[i][1];
                next.c = Top.c + direc[i][2];
                next.dis = Top.dis + 1;
                if(valid(next) && !visited[next.l][next.r][next.c]){
                    q.push(next);
                }
            }
        }
        
        if(shortdis != INT32_MAX)
            cout << "Escaped in " << shortdis << " minute(s).\n";
        else
            cout << "Trapped!\n";
        // for(int i = 1; i <= L; i++){
        //     for(int j = 1; j <= R; j++){
        //         for(int k = 1; k <= C; k++){
        //             cout << map[i][j][k];
                    
        //         }
        //         cout << '\n';
        //     }
        //     cout << '\n';
        // }

    }
       
    return 0;
}