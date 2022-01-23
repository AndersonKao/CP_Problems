#include <iostream>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <queue>
#include <cstdio>
using namespace std;

int L, R, C;
struct Node{
    int l, r, c, dis;
};
char map[40][40][40];
bool visited[40][40][40] = {false};
int shortdis;
int direc[6][3] = {
    {0,0,1},{0,0,-1}, {0,1,0}, {0,-1,0},
    {1,0,0},{-1,0,0}
};
bool valid(int l, int r, int c){
    if(l > 0 && l <= L && r > 0 && r <= R && c > 0 && c <= C){
        if(map[l][r][c] != '#')
            return true;
    }
    return false;
}
bool valid(Node a){
    int l = a.l, r = a.r, c = a.c;
    return valid(a.l,a.r,a.c);
}

int main(){
    int sl,sr,sc;
    while(~scanf("%d %d %d", &L, &R, &C)){
        if(L == 0 && R == 0 && C == 0)
            break;
        queue<Node> q;
        Node Start;
        Start.dis = 0;
        shortdis = -1;
        memset(visited, 0, sizeof(visited));
        
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
        visited[Start.l][Start.r][Start.c] = true;
        while (!q.empty())
        {
            Node Top = q.front();
            q.pop();
            if(map[Top.l][Top.r][Top.c] == 'E'){
                shortdis = Top.dis;
                break;
            }
            // visited[Top.l][Top.r][Top.c] = true;

            for(int i = 0; i <6 ;i++){
                Node next;
                next.l = Top.l + direc[i][0];
                next.r = Top.r + direc[i][1];
                next.c = Top.c + direc[i][2];
                next.dis = Top.dis + 1;
                if(valid(next) && !visited[next.l][next.r][next.c]){
                    q.push(next);
                    visited[next.l][next.r][next.c] = true;
                }
            }
        }
        
        if(shortdis != -1){
            cout << "Escaped in " << shortdis << " minute(s).\n";
            // file << "Escaped in " << shortdis << " minute(s).\n";
        }
        else{
            cout << "Trapped!\n";
            // file << "Trapped!\n";
        }
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