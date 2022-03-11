#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> vis;
vector<vector<char>> grid;
int R, C;
int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
void DFS(int x, int y){
    vis[x][y] = true;
    for (int i = 0; i < 4; i++){
        int u = x + dir[i][0], v = y + dir[i][1];
        if(!vis[u][v] && grid[u][v] != '#'){
            DFS(u, v);
        }
    }
}
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> R >> C;
    vis.resize(R + 2, vector<bool>(C + 2, false));
    grid.resize(R + 2, vector<char>(C + 2, '#'));
    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++){
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 1; i <= R; i++){
        for (int j = 1; j <= C; j++){
            if(grid[i][j] != '#' && !vis[i][j])
                DFS(i, j), ans++;
        }
    }
    cout << ans << endl;

    return 0;
}