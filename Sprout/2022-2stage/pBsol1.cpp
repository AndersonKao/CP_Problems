#include <iostream>

using namespace std;

int dX[4] = {0, 1, 0, -1};
int dY[4] = {1, 0, -1, 0};

int main(){
    char maze[100][100];
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> maze[i][j];
        }    
    }
    int x, y, dx, dy;
    cin >> x >> y;
    for(int i = 0; i < 4; i++){
        if(maze[x + dX[i]][y + dY[i]] == '.'){
            dx = dX[i];
            dy = dY[i];
            break;
        }
    }
    while(maze[x + dx][y + dy] == '.'){
        x += dx;
        y += dy;
    }
    
    if(dx == 0){
        dy = 0;
        if(maze[x + 1][y] == '.'){
            dx = 1;
        }
        else dx = -1;
    }
    else{
        dx = 0;
        if(maze[x][y + 1] == '.'){
            dy = 1;
        }
        else dy = -1;
    }

    while(maze[x + dx][y + dy] == '.'){
        x += dx;
        y += dy;
    }

    cout << x << " " << y << endl;

}